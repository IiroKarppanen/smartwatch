#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <zephyr/sys/printk.h>
#include <SEGGER_RTT.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/sensor.h>
#include "drivers/gc9a01/gc9a01.h"

const struct device *display = DEVICE_DT_GET_ANY(gc9a01);

void main(void){

    SEGGER_RTT_Init();
	printk("RTT LOG\n\n");
    k_sleep(K_SECONDS(3));


	while (1) {

		k_sleep(K_SECONDS(5));
        printk("---\n");

    }

}
