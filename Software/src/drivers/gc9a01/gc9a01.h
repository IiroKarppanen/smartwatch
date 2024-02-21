#include <string.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
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
#include "fonts/fonts.h"

// Colors
#define	BLACK               0x0000
#define	BLUE                0x001F
#define	RED                 0xF800
#define	GREEN               0x07E0
#define CYAN                0x07FF
#define MAGENTA             0xF81F
#define YELLOW              0xFFE0
#define WHITE               0xFFFF

// Func
#define swap(a,b) {int16_t t=a;a=b;b=t;}
#define RGB565(r, g, b)         (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))


struct GC9A01_draw_prop {
    uint16_t TextColor;
    uint16_t BackColor;
    sFONT *pFont;
};

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


void GC9A01_draw_pixel(const struct device *dev, int x, int y, uint16_t color);
void GC9A01_fill_circle(const struct device *dev, int16_t x, int16_t y, int16_t radius, uint16_t color);
void draw_yellow_rectangle(const struct device *dev, uint16_t x, uint16_t y, uint16_t width, uint16_t height);  


#define GC9A01A_SLPIN 0x10  ///< Enter Sleep Mode
#define GC9A01A_SLPOUT 0x11 ///< Sleep Out
#define GC9A01A_PTLON 0x12  ///< Partial Mode ON
#define GC9A01A_NORON 0x13  ///< Normal Display Mode ON

#define GC9A01A_INVOFF 0x20   ///< Display Inversion OFF
#define GC9A01A_INVON 0x21    ///< Display Inversion ON
#define GC9A01A_DISPOFF 0x28  ///< Display OFF
#define GC9A01A_DISPON 0x29   ///< Display ON

#define GC9A01A_CASET 0x2A ///< Column Address Set
#define GC9A01A_PASET 0x2B ///< Page Address Set
#define GC9A01A_RAMWR 0x2C ///< Memory Write

#define GC9A01A_PTLAR 0x30    ///< Partial Area
#define GC9A01A_VSCRDEF 0x33  ///< Vertical Scrolling Definition
#define GC9A01A_TEOFF 0x34    ///< Tearing effect line off
#define GC9A01A_TEON 0x35     ///< Tearing effect line on
#define GC9A01A_MADCTL 0x36   ///< Memory Access Control
#define GC9A01A_VSCRSADD 0x37 ///< Vertical Scrolling Start Address
#define GC9A01A_PIXFMT 0x3A   ///< COLMOD: Pixel Format Set

#define GC9A01A1_DFUNCTR 0xB6 ///< Display Function Control

#define GC9A01A1_VREG1A 0xC3 ///< Vreg1a voltage control
#define GC9A01A1_VREG1B 0xC4 ///< Vreg1b voltage control
#define GC9A01A1_VREG2A 0xC9 ///< Vreg2a voltage control

#define GC9A01A_RDID1 0xDA ///< Read ID 1
#define GC9A01A_RDID2 0xDB ///< Read ID 2
#define GC9A01A_RDID3 0xDC ///< Read ID 3

#define GC9A01A1_GMCTRP1 0xE0 ///< Positive Gamma Correction
#define GC9A01A1_GMCTRN1 0xE1 ///< Negative Gamma Correction
#define GC9A01A_FRAMERATE 0xE8 ///< Frame rate control

#define GC9A01A_INREGEN2 0xEF ///< Inter register enable 2
#define GC9A01A_GAMMA1 0xF0 ///< Set gamma 1
#define GC9A01A_GAMMA2 0xF1 ///< Set gamma 2
#define GC9A01A_GAMMA3 0xF2 ///< Set gamma 3
#define GC9A01A_GAMMA4 0xF3 ///< Set gamma 4

#define GC9A01A_INREGEN1 0xFE ///< Inter register enable 1

#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left

// Command codes:
#define COL_ADDR_SET        0x2A
#define ROW_ADDR_SET        0x2B
#define MEM_WR              0x2C
#define MEM_WR_CONT         0x3C
#define COLOR_MODE          0x3A
#define COLOR_MODE_12_BIT  0x03
#define COLOR_MODE_16_BIT  0x05
#define COLOR_MODE_18_BIT  0x06
#define SLPIN               0x10
#define SLPOUT              0x11

