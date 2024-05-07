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
#include <zephyr/drivers/display.h>

#include "../sensor_data/inertial_measurement.h"

#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)

#define DISPLAY_ON_TIME 8000 // Time display stays on after last trigger event

static bool lvgl_task_enabled = true;
static bool backlight_is_on = true;

const struct device *display_dev;
const struct gpio_dt_spec backlight_en = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, bl_gpios);




K_TIMER_DEFINE(display_timer, NULL, NULL);
uint32_t last_expiration_time = 0;

void display_timer_handler(struct k_timer *timer)
{
	last_expiration_time = k_uptime_get_32();

    backlight_is_on = false;
    gpio_pin_set_dt(&backlight_en, 0);
	display_blanking_on(display_dev);
}

void reset_timer(void)
{
    k_timer_stop(&display_timer);
    last_expiration_time = 0;
}

void restart_timer(void)
{
    // Calculate the remaining time to the next expiration
    uint32_t current_time = k_uptime_get_32();
    uint32_t remaining_time = last_expiration_time > 0 ? (15000 - (current_time - last_expiration_time)) : 15000;

    // Start the timer with the remaining time
    k_timer_start(&display_timer, K_MSEC(remaining_time), K_MSEC(15000));
    printk("Timer restarted with %u ms remaining\n", remaining_time);
}





#define DISPLAY_CONTROL_THREAD_STACK_SIZE 4096
#define DISPLAY_CONTROL_THREAD_PRIORITY 5

// LVGL thread
K_THREAD_STACK_DEFINE(display_control_thread_stack, DISPLAY_CONTROL_THREAD_STACK_SIZE);
struct k_thread display_control_thread_data;



void display_control_task()
{
    while (1) {
        
		if(acc[1].val1 == -7 || acc[1].val1 == -8 || acc[1].val1 == -9 || acc[1].val1 == -10){

			reset_timer();
    		restart_timer();

			if(!backlight_is_on){
				display_blanking_off(display_dev);
				gpio_pin_set_dt(&backlight_en, 1);
				backlight_is_on = true;
			}
		
		}
        
        k_msleep(100);  
		
    }
}







void reset_display_timer(){
	gpio_pin_set_dt(&backlight_en, 1);
	reset_timer();
	restart_timer();
}



void init_display_control(){

    // Turn on display backlight
    gpio_pin_configure_dt(&backlight_en, GPIO_OUTPUT_HIGH);
	gpio_pin_set_dt(&backlight_en, 1);

    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

	if (!device_is_ready(display_dev))
	{
		printk("Display not ready\n");
		return;
	}


    k_timer_init(&display_timer, display_timer_handler, NULL);
    k_timer_start(&display_timer, K_MSEC(DISPLAY_ON_TIME), K_MSEC(DISPLAY_ON_TIME));

    k_thread_create(&display_control_thread_data, display_control_thread_stack,
    K_THREAD_STACK_SIZEOF(display_control_thread_stack),
    display_control_task, NULL, NULL, NULL,
    DISPLAY_CONTROL_THREAD_PRIORITY, 0, K_NO_WAIT);

}


SYS_INIT(init_display_control, APPLICATION, CONFIG_SENSOR_INIT_PRIORITY);




// Turn display on
//if(backlight_status == 1){
//	reset_display_timer();
//}