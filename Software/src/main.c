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
#include <zephyr/drivers/uart.h>
#include <lvgl.h>
#include <ui.h>
#include <nrfx_clock.h>

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

	// Initialize LVGL
    lv_init();
	ui_init();

    k_thread_create(&lvgl_thread_data, lvgl_thread_stack,
        K_THREAD_STACK_SIZEOF(lvgl_thread_stack),
        lvgl_task, NULL, NULL, NULL,
        LVGL_THREAD_PRIORITY, 0, K_NO_WAIT);


	while (1) {
	
		
		printk("-\n");
		k_sleep(K_MSEC(1000));
	}
    
}

