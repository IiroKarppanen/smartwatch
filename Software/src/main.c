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


#define LVGL_THREAD_STACK_SIZE 8192
#define LVGL_THREAD_PRIORITY 1

// LVGL thread
K_THREAD_STACK_DEFINE(lvgl_thread_stack, LVGL_THREAD_STACK_SIZE);
struct k_thread lvgl_thread_data;


static bool lvgl_task_enabled = true;

// LVGL task
void lvgl_task(void *p1, void *p2, void *p3)
{
    while (1) {
        if (lvgl_task_enabled) {
            lv_task_handler();
        }
        k_msleep(50);  
    }
}


#define I2C_SLAVE_ADDR_MIN 0x15  // Minimum 7-bit I2C address
#define I2C_SLAVE_ADDR_MAX 0x99  // Maximum 7-bit I2C address

void i2c_scan(void) {
    struct device *i2c_dev;
    int error;
	int count = 0;

    // Get the I2C device
	// device_get_binding("UART_0");
    i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c2));
    if (!i2c_dev) {
        printk("Could not find I2C device\n");
        return;
    }

    printk("Scanning I2C bus for devices...\n");

    // Iterate over possible 7-bit I2C addresses (0x08 to 0x77)
    for (int addr = I2C_SLAVE_ADDR_MIN; addr <= I2C_SLAVE_ADDR_MAX; addr++) {
        uint8_t reg_addr = 0x00;  // Register address to read (dummy for probing)
        uint8_t rx_data;          // Data read (dummy for probing)

        // Perform a burst read from a register address (0x00) at the device address
        error = i2c_burst_read(i2c_dev, addr, reg_addr, &rx_data, 1);
        if (error == 0) {
            printk("Found device at address 0x%02X\n", addr);
			count++;
        }
		else if (error != -ENODEV) {
            // Print error only if it's not "device not present" (-ENODEV)
        }
    }

    printk("I2C scanning complete\n");
	printk("Amount of devices: %d\n", count);
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



	//i2c_scan();


	while (1) {
	

		printk("-\n");
		k_sleep(K_MSEC(1000));
	
	}
    
}

