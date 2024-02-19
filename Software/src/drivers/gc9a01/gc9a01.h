#include <string.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <math.h>
#include <inttypes.h>
#include <zephyr/pm/pm.h>
#include <zephyr/pm/device.h>
#include <zephyr/pm/policy.h>
#include <zephyr/sys/printk.h>


struct gc9a01_config {
    struct spi_dt_spec bus;
    struct gpio_dt_spec dc_gpio;
    struct gpio_dt_spec bl_gpio;
    struct gpio_dt_spec reset_gpio;
};

struct gc9a01_point {
    uint16_t X, Y;
};

struct gc9a01_frame {
    struct gc9a01_point start, end;
};


int gc9a01_blanking_on(const struct device *dev);
int gc9a01_blanking_off(const struct device *dev);
int gc9a01_write(const struct device *dev, const uint16_t x, const uint16_t y,
                 const struct display_buffer_descriptor *desc, const void *buf);
int gc9a01_read(const struct device *dev, const uint16_t x, const uint16_t y,
                const struct display_buffer_descriptor *desc, void *buf);
void *gc9a01_get_framebuffer(const struct device *dev);
int gc9a01_set_brightness(const struct device *dev, const uint8_t brightness);
int gc9a01_set_contrast(const struct device *dev, uint8_t contrast);
void gc9a01_get_capabilities(const struct device *dev, struct display_capabilities *caps);
int gc9a01_set_orientation(const struct device *dev, const enum display_orientation orientation);
int gc9a01_set_pixel_format(const struct device *dev, const enum display_pixel_format pf);
int gc9a01_controller_init(const struct device *dev);
int gc9a01_init(const struct device *dev);
int gc9a01_pm_action(const struct device *dev, enum pm_device_action action);
void display_test(const struct device *dev);

