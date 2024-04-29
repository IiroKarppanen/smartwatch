#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <SEGGER_RTT.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/sys/util.h>
#include "sensor_data.h"


#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)

const struct gpio_dt_spec backlight_en = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, bl_gpios);

K_TIMER_DEFINE(my_timer, NULL, NULL);
uint32_t last_expiration_time = 0;

void timer_handler2(struct k_timer *timer)
{
	last_expiration_time = k_uptime_get_32();
    printk("Timer expired! Trigger event here...\n");
    gpio_pin_set_dt(&backlight_en, 0);
}

void reset_timer(void)
{
    // Stop the timer if it's currently running
    k_timer_stop(&my_timer);

    // Reset last_expiration_time to zero
    last_expiration_time = 0;
}

void restart_timer(void)
{
    // Calculate the remaining time to the next expiration
    uint32_t current_time = k_uptime_get_32();
    uint32_t remaining_time = last_expiration_time > 0 ? (15000 - (current_time - last_expiration_time)) : 15000;

    // Start the timer with the remaining time
    k_timer_start(&my_timer, K_MSEC(remaining_time), K_MSEC(15000));
    printk("Timer restarted with %u ms remaining\n", remaining_time);
}

#define ACCELOMETER_THREAD_STACK_SIZE 4096
#define ACCELOMETER_THREAD_PRIORITY 5

// LVGL thread
K_THREAD_STACK_DEFINE(accelometer_thread_stack, ACCELOMETER_THREAD_STACK_SIZE);
struct k_thread accelometer_thread_data;

const struct device *bmi270;
struct sensor_value acc[3], gyr[3];
struct sensor_value full_scale, sampling_freq, oversampling;

// accelometer task
void accelometer_task()
{
    while (1) {
        sensor_sample_fetch(bmi270);

		sensor_channel_get(bmi270, SENSOR_CHAN_ACCEL_XYZ, acc);
		sensor_channel_get(bmi270, SENSOR_CHAN_GYRO_XYZ, gyr);

		
		printk("AX: %d.%06d; AY: %d.%06d; AZ: %d.%06d; "
		       "GX: %d.%06d; GY: %d.%06d; GZ: %d.%06d;\n",
		       acc[0].val1, acc[0].val2,
		       acc[1].val1, acc[1].val2,
		       acc[2].val1, acc[2].val2,
		       gyr[0].val1, gyr[0].val2,
		       gyr[1].val1, gyr[1].val2,
		       gyr[2].val1, gyr[2].val2);
		


		if(acc[0].val1 > 8 || acc[0].val1 < -8 || acc[0].val1 > 8 || acc[0].val1 < -8 ){
			printk("Turn on display\n");
	 		gpio_pin_set_dt(&backlight_en, 1);

			reset_timer();
    		restart_timer();
		}

        k_msleep(75);  
		
    }
}


int init_bmi270(){

	bmi270 = DEVICE_DT_GET_ONE(bosch_bmi270);
	
	if (!device_is_ready(bmi270)) {
		printk("Device %s is not ready\n", bmi270->name);
		return 0;
	}

	full_scale.val1 = 2;            /* G */
	full_scale.val2 = 0;
	sampling_freq.val1 = 100;       /* Hz. Performance mode */
	sampling_freq.val2 = 0;
	oversampling.val1 = 1;          /* Normal mode */
	oversampling.val2 = 0;

	sensor_attr_set(bmi270, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_FULL_SCALE,
			&full_scale);
	sensor_attr_set(bmi270, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_OVERSAMPLING,
			&oversampling);
	/* Set sampling frequency last as this also sets the appropriate
	 * power mode. If already sampling, change to 0.0Hz before changing
	 * other attributes
	 */
	sensor_attr_set(bmi270, SENSOR_CHAN_ACCEL_XYZ,
			SENSOR_ATTR_SAMPLING_FREQUENCY,
			&sampling_freq);


	/* Setting scale in degrees/s to match the sensor scale */
	full_scale.val1 = 500;          /* dps */
	full_scale.val2 = 0;
	sampling_freq.val1 = 100;       /* Hz. Performance mode */
	sampling_freq.val2 = 0;
	oversampling.val1 = 1;          /* Normal mode */
	oversampling.val2 = 0;

	sensor_attr_set(bmi270, SENSOR_CHAN_GYRO_XYZ, SENSOR_ATTR_FULL_SCALE,
			&full_scale);
	sensor_attr_set(bmi270, SENSOR_CHAN_GYRO_XYZ, SENSOR_ATTR_OVERSAMPLING,
			&oversampling);
	/* Set sampling frequency last as this also sets the appropriate
	 * power mode. If already sampling, change sampling frequency to
	 * 0.0Hz before changing other attributes
	 */
	sensor_attr_set(bmi270, SENSOR_CHAN_GYRO_XYZ,
			SENSOR_ATTR_SAMPLING_FREQUENCY,
			&sampling_freq);
        
    return 0;
}



void init_sensors(){


    init_bmi270();

	gpio_pin_configure_dt(&backlight_en, GPIO_OUTPUT_HIGH);
	gpio_pin_set_dt(&backlight_en, 1);

	
	// Initialize the timer callback
    k_timer_init(&my_timer, timer_handler2, NULL);

    // Start the timer to trigger every 20 seconds (20,000 milliseconds)
    k_timer_start(&my_timer, K_MSEC(20000), K_MSEC(20000));

    k_thread_create(&accelometer_thread_data, accelometer_thread_stack,
        K_THREAD_STACK_SIZEOF(accelometer_thread_stack),
        accelometer_task, NULL, NULL, NULL,
        ACCELOMETER_THREAD_PRIORITY, 0, K_NO_WAIT);

	

}


SYS_INIT(init_sensors, APPLICATION, CONFIG_SENSOR_INIT_PRIORITY);
