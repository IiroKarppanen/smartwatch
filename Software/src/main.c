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
#include <zephyr/drivers/fuel_gauge.h>

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

	const struct device *const dev = DEVICE_DT_GET_ANY(maxim_max17048);
	int ret = 0;

	if (dev == NULL) {
		printk("\nError: no device found.\n");
		return 0;
	}

	/*

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return 0;
	}

	*/



	printk("Found device \"%s\", getting fuel gauge data\n", dev->name);

	if (dev == NULL) {
		return 0;
	}

	// Initialize LVGL
    lv_init();
	ui_init();

    k_thread_create(&lvgl_thread_data, lvgl_thread_stack,
        K_THREAD_STACK_SIZEOF(lvgl_thread_stack),
        lvgl_task, NULL, NULL, NULL,
        LVGL_THREAD_PRIORITY, 0, K_NO_WAIT);


	while (1) {
	

		struct fuel_gauge_get_property props[] = {
			{
				.property_type = FUEL_GAUGE_RUNTIME_TO_EMPTY,
			},
			{
				.property_type = FUEL_GAUGE_RUNTIME_TO_FULL,
			},
			{
				.property_type = FUEL_GAUGE_RELATIVE_STATE_OF_CHARGE,
			},
			{
				.property_type = FUEL_GAUGE_VOLTAGE,
			}
		};

		ret = fuel_gauge_get_prop(dev, props, ARRAY_SIZE(props));
		if (ret < 0) {
			printk("Error: cannot get properties\n");
		} else {
			if (ret != 0) {
				printk("Warning: Some properties failed\n");
			}

			if (props[0].status == 0) {
				printk("Time to empty %d\n", props[0].value.runtime_to_empty);
			} else {
				printk(
				"Property FUEL_GAUGE_RUNTIME_TO_EMPTY failed with error %d\n",
				props[0].status
				);
			}

			if (props[1].status == 0) {
				printk("Time to full %d\n", props[1].value.runtime_to_full);
			} else {
				printk(
				"Property FUEL_GAUGE_RUNTIME_TO_FULL failed with error %d\n",
				props[1].status
				);
			}

			if (props[2].status == 0) {
				printk("Charge %d%%\n", props[2].value.relative_state_of_charge);
				char charge_str[5];  // Assuming a reasonable size for the string representation
				snprintf(charge_str, sizeof(charge_str), "%d%%", props[2].value.relative_state_of_charge);

				lv_label_set_text(ui_Label_charge, charge_str);

			} else {
				printk(
				"Property FUEL_GAUGE_STATE_OF_CHARGE failed with error %d\n",
				props[2].status
				);
			}

			if (props[3].status == 0) {
				printk("Voltage %d\n", props[3].value.voltage);
			} else {
				printk(
				"Property FUEL_GAUGE_VOLTAGE failed with error %d\n",
				props[3].status
				);
			}
		}

		
		
		printk("-\n");
		k_sleep(K_MSEC(1000));
	}
    
}

