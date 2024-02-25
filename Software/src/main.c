#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <zephyr/sys/printk.h>
#include <SEGGER_RTT.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include "drivers/gc9a01/gc9a01.h"


void main(void){

	SEGGER_RTT_Init();
	printk("RTT LOG\n\n");
    k_sleep(K_SECONDS(3));

	const struct device *display = DEVICE_DT_GET_ANY(buydisplay_gc9a01);

	if (display == NULL) {
		printk("Could not get display device\n");
		return 0;
	}
	if (!device_is_ready(display)) {
		printk("display device %s is not ready\n", display->name);
		return 0;
	}

	GC9A01_fill_rect(display, 0, 0, 239, 239, BLACK);
	GC9A01_draw_line(display, WHITE, 0, 80, 239, 80);
	GC9A01_draw_line(display, WHITE, 0, 160, 239, 160);
	GC9A01_draw_string(display, 82, 110, "18:39");

	while (1) {

		k_sleep(K_SECONDS(5));
        printk("---\n");
    }

}


/*
&i2c2 {
	compatible = "nordic,nrf-twim";
	status = "okay";
	pinctrl-0 = <&i2c2_default>;
	pinctrl-1 = <&i2c2_sleep>;
	pinctrl-names = "default", "sleep";
	clock-frequency = <100000>;
	max17048:max17048@37 {
		compatible = "maxim,max17048";
		reg = <0x37>;
	};
	lis2dh@19 {
        compatible = "st,lis2dh";
        reg = <0x19>;
        label = "LIS2DH";
    };
	rtc@36 {
        compatible = "st,lis2dh";
        reg = <0x36>;
        label = "RV-3028-C7";
    };
	max30101@57 {
		compatible = "max,max30101";
		reg = <0x57>;
		label = "MAX30101";
		irq-gpios = <&gpio0 12 0>;
	};
};











*/