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


#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);



#define LVGL_THREAD_STACK_SIZE 15360
#define LVGL_THREAD_PRIORITY 1

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


    k_thread_create(&pwm_thread_data, pwm_thread_stack,
        K_THREAD_STACK_SIZEOF(pwm_thread_stack),
        pwm_task, NULL, NULL, NULL,
        PWM_THREAD_PRIORITY, 0, K_NO_WAIT);
    

    k_thread_create(&lvgl_thread_data, lvgl_thread_stack,
        K_THREAD_STACK_SIZEOF(lvgl_thread_stack),
        lvgl_task, NULL, NULL, NULL,
        LVGL_THREAD_PRIORITY, 0, K_NO_WAIT);


	while (1) {

		
		k_sleep(K_MSEC(1000));
		printk("-\n");
	
    }
}

