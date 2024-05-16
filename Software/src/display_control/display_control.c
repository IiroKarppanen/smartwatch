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
#include "display_control.h"

#include "../sensor_data/inertial_measurement.h"

#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)

#define DISPLAY_ON_TIME 8000 // Time display stays on after last trigger event

const struct device *display_dev;
const struct device *tp_dev;
const struct gpio_dt_spec backlight_en = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, bl_gpios);

bool backlight_is_on = true;

K_TIMER_DEFINE(display_timer, NULL, NULL);

void display_timer_handler(struct k_timer *timer)
{
    backlight_is_on = false;
    gpio_pin_set_dt(&backlight_en, 0);
    //display_blanking_on(display_dev);
}



#define DISPLAY_CONTROL_THREAD_STACK_SIZE 4096
#define DISPLAY_CONTROL_THREAD_PRIORITY 3

// LVGL thread
K_THREAD_STACK_DEFINE(display_control_thread_stack, DISPLAY_CONTROL_THREAD_STACK_SIZE);
struct k_thread display_control_thread_data;



void display_control_task(){

    while (1) {
		if(acc[1].val1 == -7 || acc[1].val1 == -8 || acc[1].val1 == -9 || acc[1].val1 == -10){
			reset_display_timer();
        }  

        k_msleep(50);
    }

}

void reset_display_timer(){

    printk("display timer reset\n");

    if(!backlight_is_on){
        gpio_pin_set_dt(&backlight_en, 1);
        //display_blanking_off(display_dev);
        backlight_is_on = true;
	}
	
    k_timer_stop(&display_timer);
    k_timer_start(&display_timer, K_MSEC(DISPLAY_ON_TIME), K_MSEC(DISPLAY_ON_TIME));
}



void init_display_control(){

    gpio_pin_configure_dt(&backlight_en, GPIO_OUTPUT_HIGH);
	gpio_pin_set_dt(&backlight_en, 1);

    display_dev = DEVICE_DT_GET_ANY(buydisplay_gc9a01);

	if (!device_is_ready(display_dev))
	{
		printk("Display not ready\n");
		return;
	}

    /*
    tp_dev = DEVICE_DT_GET_ANY(hynitron_cst816d);

	if (!device_is_ready(tp_dev))
	{
		printk("tp_dev not ready\n");
		return;
	}
    */


    /*
    k_msleep(5000);

    
    k_timer_init(&display_timer, display_timer_handler, NULL);
    k_timer_start(&display_timer, K_MSEC(15000), K_MSEC(15000));


    k_thread_create(&display_control_thread_data, display_control_thread_stack,
    K_THREAD_STACK_SIZEOF(display_control_thread_stack),
    display_control_task, NULL, NULL, NULL,
        DISPLAY_CONTROL_THREAD_PRIORITY, 0, K_NO_WAIT);
    
    */
}


SYS_INIT(init_display_control, APPLICATION, 99);

