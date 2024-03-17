#define DT_DRV_COMPAT maxim_max30101

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>


#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

const struct device *hr_sensor;


void timer_handler(struct k_timer *timer_id)
{
    printk("Timer expired!\n");
}



void init_max30101(){
    hr_sensor = DEVICE_DT_GET_ANY(maxim_max30101);

	if (hr_sensor == NULL) {
		printk("Could not get max30101 device\n");
		return 0;
	}
	if (!device_is_ready(hr_sensor)) {
		printk("max30101 device %s is not ready\n", hr_sensor->name);
		return 0;
	}

    int ret;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	gpio_pin_set(led.port, led.pin, 1);
}

void fetch_pulse(){


    // Led data value
    struct sensor_value ir;

	int rate_size = 20;

	static uint8_t rates[20]; 
	static uint8_t rateSpot = 0;
	k_ticks_t lastBeat = 0;   

	static float beatsPerMinute;
	static int beatAvg;

	int beats = 0;


	struct k_timer my_timer;
    int64_t start_time;

	k_timer_init(&my_timer, timer_handler, NULL);
    k_timer_start(&my_timer, K_MSEC(10000), K_MSEC(10000)); 


	int beatIntervals[10] = {0, 0, 0, 0, 0, 0 ,0, 0, 0, 0};
	int length = 10;

    while (1) {

		//gpio_pin_set(led.port, led.pin, 1);

        sensor_sample_fetch(hr_sensor);
	    sensor_channel_get(hr_sensor, SENSOR_CHAN_GREEN, &ir);

		
		if (checkForBeat(ir.val1)) {

			beats++;
			printk("BEAT number: %d\n", beats);

			k_timer_stop(&my_timer);
			// Calculate and print the time taken
            int64_t end_time = k_uptime_get();
            int64_t elapsed_time = end_time - start_time;
            printk("Time taken: %lld milliseconds\n", elapsed_time);

			for (int i = length - 1; i > 0; i--) {
				beatIntervals[i] = beatIntervals[i - 1];
			}
			beatIntervals[0] = elapsed_time;


			int sum = 0;
			for (int i = 0; i < length; i++) {
				sum += beatIntervals[i];
			}
			double average = (double)sum / length;
			printk("AVERAGE INTERVAL: %lf\n", average);


			double bpm = 60.0 / (average / 1000.0);
			printk("Beats per minute: %.2f\n", bpm);

			start_time = k_uptime_get();
			k_timer_start(&my_timer, K_MSEC(10000), K_MSEC(10000)); 

    	}

		//gpio_pin_set(led.port, led.pin, 0);
		//gpio_pin_toggle(led.port, led.pin);
        k_msleep(20);  
    }


}

static const struct sensor_driver_api max30101_driver_api = {
    .sample_fetch = fetch_pulse
};


SYS_INIT(init_max30101, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY);