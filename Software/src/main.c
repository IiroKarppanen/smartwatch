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
#include <lvgl.h>
#include <ui.h>
#include <nrfx_clock.h>

#include "sensor_data/sensor_data.h"
#include "clock/clock.h"






#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

#define LVGL_THREAD_STACK_SIZE 15360
#define LVGL_THREAD_PRIORITY 1

#define RTC_THREAD_STACK_SIZE 15360
#define RTC_THREAD_PRIORITY 1

// LVGL thread
K_THREAD_STACK_DEFINE(lvgl_thread_stack, LVGL_THREAD_STACK_SIZE);
struct k_thread lvgl_thread_data;

// LVGL task
void lvgl_task(void *p1, void *p2, void *p3)
{
    while (1) {
        lv_task_handler();
        k_msleep(50);  
    }
}


static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

#define MIN_PERIOD PWM_SEC(1U) / 128U
float brightness;

#define PWM_THREAD_STACK_SIZE 8192
#define PWM_THREAD_PRIORITY 4

// PWM Thread
K_THREAD_STACK_DEFINE(pwm_thread_stack, PWM_THREAD_STACK_SIZE);
struct k_thread pwm_thread_data;

// PWM Task
void pwm_task(void *p1, void *p2, void *p3)
{
    while (1) {
        
        int ret;
		int sliderValue = lv_slider_get_value(ui_Slider1);

        
		brightness = (float)sliderValue / 1000.0;

		ret = pwm_set_dt(&pwm_led0, MIN_PERIOD * brightness, MIN_PERIOD);
		if (ret) {
			printk("Error %d: failed to set pulse width\n", ret);
			return 0;
		}

		k_sleep(K_SECONDS(4U));
    }
}



void main(void){
	

	SEGGER_RTT_Init();
	printk("RTT LOG\n\n");
    k_sleep(K_SECONDS(3));


	// NRF_CLOCK_HFCLK_DIV_1 - 128Mhz
	// NRF_CLOCK_HFCLK_DIV_2 - 64Mhz
	// NRF_CLOCK_HFCLK_DIV_4 - 32Mhz
	nrfx_clock_divider_set(NRF_CLOCK_DOMAIN_HFCLK, NRF_CLOCK_HFCLK_DIV_1);




	const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

	if (!device_is_ready(display_dev))
	{
		printk("Display not ready\n");
		return;
	}

	if (!pwm_is_ready_dt(&pwm_led0)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return 0;
	}


	// Initialize LVGL
    lv_init();
	ui_init();



	/*
    k_thread_create(&pwm_thread_data, pwm_thread_stack,
        K_THREAD_STACK_SIZEOF(pwm_thread_stack),
        pwm_task, NULL, NULL, NULL,
        PWM_THREAD_PRIORITY, 0, K_NO_WAIT);
    
	*/
    k_thread_create(&lvgl_thread_data, lvgl_thread_stack,
        K_THREAD_STACK_SIZEOF(lvgl_thread_stack),
        lvgl_task, NULL, NULL, NULL,
        LVGL_THREAD_PRIORITY, 0, K_NO_WAIT);
	


	while (1) {
	
		char time_str[20]; 
		snprintf(time_str, sizeof(time_str), "%02u:%02u", CurrentTime.tm_hour, CurrentTime.tm_min);
		lv_label_set_text(ui_TimeLabel, time_str);
		char date_str[20]; 
		snprintf(date_str, sizeof(date_str), "%u,March", CurrentTime.tm_mday);
		lv_label_set_text(ui_DateLabel, date_str);

		char AX_str[20];
		snprintf(AX_str, sizeof(AX_str), "X: %d.%06d", acc[0].val1, acc[0].val2);
		lv_label_set_text(ui_AXLabel, AX_str);

		char AY_str[20];
		snprintf(AY_str, sizeof(AY_str), "Y: %d.%06d", acc[1].val1, acc[1].val2);
		lv_label_set_text(ui_AYLabel, AY_str);

		char AZ_str[20];
		snprintf(AZ_str, sizeof(AZ_str), "Z: %d.%06d", acc[2].val1, acc[2].val2);
		lv_label_set_text(ui_AZLabel, AZ_str);

		char GX_str[20];
		snprintf(GX_str, sizeof(GX_str), "X: %d.%06d", gyr[0].val1, gyr[0].val2);
		lv_label_set_text(ui_GXLabel, GX_str);

		char GY_str[20];
		snprintf(GY_str, sizeof(GY_str), "Y: %d.%06d", gyr[1].val1, gyr[1].val2);
		lv_label_set_text(ui_GYLabel, GY_str);

		char GZ_str[20];
		snprintf(GZ_str, sizeof(GZ_str), "Z: %d.%06d", gyr[2].val1, gyr[2].val2);
		lv_label_set_text(ui_GZLabel, GZ_str);

		k_sleep(K_MSEC(100));
	
    }
}

