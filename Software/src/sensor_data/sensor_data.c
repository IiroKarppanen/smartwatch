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
#include "sensor_data.h"



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

		/*
		printk("AX: %d.%06d; AY: %d.%06d; AZ: %d.%06d; "
		       "GX: %d.%06d; GY: %d.%06d; GZ: %d.%06d;\n",
		       acc[0].val1, acc[0].val2,
		       acc[1].val1, acc[1].val2,
		       acc[2].val1, acc[2].val2,
		       gyr[0].val1, gyr[0].val2,
		       gyr[1].val1, gyr[1].val2,
		       gyr[2].val1, gyr[2].val2);


        k_msleep(75);  
		*/
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

    k_thread_create(&accelometer_thread_data, accelometer_thread_stack,
        K_THREAD_STACK_SIZEOF(accelometer_thread_stack),
        accelometer_task, NULL, NULL, NULL,
        ACCELOMETER_THREAD_PRIORITY, 0, K_NO_WAIT);

}


SYS_INIT(init_sensors, APPLICATION, CONFIG_SENSOR_INIT_PRIORITY);
