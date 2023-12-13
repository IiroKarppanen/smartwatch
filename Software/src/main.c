#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>
#include <drivers/i2c.h>
#include <drivers/sensor.h>
#include <devicetree.h>
#include <SEGGER_RTT.h>
#include <device.h>
#include <zephyr/types.h>
#include <drivers/gpio.h>
#include "display/gc9a01.h"

#define GPIO DT_LABEL(DT_NODELABEL(gpio0))
#define BACKLIGHT_PIN 7


void toggle_backlight(void){

	const struct device *dev;

    dev = device_get_binding(GPIO);
    if (dev == NULL) {
        printk("Error: Could not get GPIO device\n");
        return;
    }

	k_sleep(K_SECONDS(3));

    gpio_pin_configure(dev, BACKLIGHT_PIN, GPIO_OUTPUT);

	printk("BACKLIGHT ON\n");
    gpio_pin_set(dev, BACKLIGHT_PIN, 1);
}


static void draw_arrow(int16_t angle, uint8_t lineLen,
		uint16_t color) {
    /* old */
    int16_t old_angel = (angle - 1) * 6 - 90;
    float old_angleRad = (float)old_angel * 3.14159265 / 180;
    int start_old_x = cos(old_angleRad) * 50 + 120;
    int start_old_y = sin(old_angleRad) * 50 + 120;
    int end_old_x = cos(old_angleRad) * lineLen + 120;
    int end_old_y = sin(old_angleRad) * lineLen + 120;
    GC9A01_draw_line(WHITE, start_old_x, start_old_y, end_old_x, end_old_y);
    
    /* new */
    angle = angle * 6 - 90;
    float angleRad = (float)angle * 3.14159265 / 180;
    int start_x = cos(angleRad) * 50 + 120;
    int start_y = sin(angleRad) * 50 + 120;
    int end_x = cos(angleRad) * lineLen + 120;
    int end_y = sin(angleRad) * lineLen + 120;
    GC9A01_draw_line(color, start_x, start_y, end_x, end_y);
}



void main(void){

    SEGGER_RTT_Init();
	printk("RTT LOG\n\n");

    k_sleep(K_SECONDS(3));
    toggle_backlight();

    lcd_spi_init();
    GC9A01_init();
    struct GC9A01_frame frame = {{45, 45}, {239, 239}};
    GC9A01_set_frame(frame);

    GC9A01_fill_rect(10, 20, 30, 40, 0xF800); // Draw a red filled rectangle at (10, 20) with dimensions 30x40 pixels

	while (1) {

		k_sleep(K_SECONDS(4));

        printk("---\n");
        printk("Display init");

        GC9A01_draw_line(MAGENTA, 220, 50, 150, 240);
    }

}
