#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <zephyr/sys/printk.h>
#include <SEGGER_RTT.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/sensor.h>
#include "gc9a01.h"

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


/*
&spi1  {
	status = "okay";
	compatible = "nordic,nrf-spi";
	pinctrl-0 = <&spi1_default>;
	pinctrl-1 = <&spi1_sleep>;
	pinctrl-names = "default", "sleep";
	cs-gpios = <&gpio0 16 GPIO_ACTIVE_LOW>;

	gc9a01: gc9a01@0 {
		compatible = "jak,gc9a01";
		status = "okay";
		spi-max-frequency = <8000000>;
		reg = <0>;
		width = <240>;
		label = "jak_gc9a01";
		height = <240>;
		bl-gpios = <&gpio0 26 GPIO_ACTIVE_HIGH>;
		reset-gpios = <&gpio0 3 GPIO_ACTIVE_HIGH>;
		dc-gpios = <&gpio1 0 GPIO_ACTIVE_HIGH>;
	};
};

&i2c2 {
	compatible = "nordic,nrf-twim";
	status = "okay";
	pinctrl-0 = <&i2c2_default>;
	pinctrl-1 = <&i2c2_sleep>;
	pinctrl-names = "default", "sleep";
	clock-frequency = <100000>;
	max17048:max17048@36 {
		compatible = "maxim,max17048";
		reg = <0x36>;
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
};
*/