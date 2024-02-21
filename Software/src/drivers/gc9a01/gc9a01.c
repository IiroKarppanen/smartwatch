#define DT_DRV_COMPAT buydisplay_gc9a01

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
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
#include "gc9a01.h"
#include "fonts/fonts.h"
#include "img.h"

#define GC9A01_SPI_PROFILING

#define DISPLAY_WIDTH         DT_INST_PROP(0, width)
#define DISPLAY_HEIGHT        DT_INST_PROP(0, height)


/* Data Structs */

struct gc9a01_frame frame = {{0, 0}, {DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1}};
struct GC9A01_draw_prop fonts; 

/**/

const uint8_t initcmd[] = {
    GC9A01A_INREGEN2, 0,
    0xEB, 1, 0x14,
    GC9A01A_INREGEN1, 0,
    GC9A01A_INREGEN2, 0,
    0xEB, 1, 0x14,
    0x84, 1, 0x40,
    0x85, 1, 0xFF,
    0x86, 1, 0xFF,
    0x87, 1, 0xFF,
    0x88, 1, 0x0A,
    0x89, 1, 0x21,
    0x8A, 1, 0x00,
    0x8B, 1, 0x80,
    0x8C, 1, 0x01,
    0x8D, 1, 0x01,
    0x8E, 1, 0xFF,
    0x8F, 1, 0xFF,
    0xB6, 2, 0x00, 0x00,
#if DT_PROP(DT_INST(0, buydisplay_gc9a01), rotation) == 0
    GC9A01A_MADCTL, 1,  MADCTL_MV | MADCTL_MY | MADCTL_MX | MADCTL_BGR,
#elif DT_PROP(DT_INST(0, buydisplay_gc9a01), rotation) == 90
    GC9A01A_MADCTL, 1,  MADCTL_MH | MADCTL_MY | 0 | MADCTL_BGR,
#elif DT_PROP(DT_INST(0, buydisplay_gc9a01), rotation) == 180
    GC9A01A_MADCTL, 1,  MADCTL_MV | 0 | 0 | MADCTL_BGR,
#elif DT_PROP(DT_INST(0, buydisplay_gc9a01), rotation) == 270
    GC9A01A_MADCTL, 1,  MADCTL_MH | MADCTL_MX | 0 | 0 | MADCTL_BGR,
#else
#error "Unsupported rotation. Use 0, 90, 180 or 270."
#endif
    GC9A01A_PIXFMT, 1, COLOR_MODE_16_BIT,
    0x90, 4, 0x08, 0x08, 0x08, 0x08,
    0xBD, 1, 0x06,
    0xBC, 1, 0x00,
    0xFF, 3, 0x60, 0x01, 0x04,
    GC9A01A1_VREG1A, 1, 0x13,
    GC9A01A1_VREG1B, 1, 0x13,
    GC9A01A1_VREG2A, 1, 0x22,
    0xBE, 1, 0x11,
    GC9A01A1_GMCTRN1, 2, 0x10, 0x0E,
    0xDF, 3, 0x21, 0x0c, 0x02,
    GC9A01A_GAMMA1, 6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,
    GC9A01A_GAMMA2, 6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,
    GC9A01A_GAMMA3, 6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,
    GC9A01A_GAMMA4, 6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,
    0xED, 2, 0x1B, 0x0B,
    0xAE, 1, 0x77,
    0xCD, 1, 0x63,
    0x70, 9, 0x07, 0x07, 0x04, 0x0E, 0x0F, 0x09, 0x07, 0x08, 0x03,
    GC9A01A_FRAMERATE, 1, 0x34,
    0x62, 12, 0x18, 0x0D, 0x71, 0xED, 0x70, 0x70,
    0x18, 0x0F, 0x71, 0xEF, 0x70, 0x70,
    0x63, 12, 0x18, 0x11, 0x71, 0xF1, 0x70, 0x70,
    0x18, 0x13, 0x71, 0xF3, 0x70, 0x70,
    0x64, 7, 0x28, 0x29, 0xF1, 0x01, 0xF1, 0x00, 0x07,
    0x66, 10, 0x3C, 0x00, 0xCD, 0x67, 0x45, 0x45, 0x10, 0x00, 0x00, 0x00,
    0x67, 10, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0x54, 0x10, 0x32, 0x98,
    0x74, 7, 0x10, 0x85, 0x80, 0x00, 0x00, 0x4E, 0x00,
    0x98, 2, 0x3e, 0x07,
    GC9A01A_TEON, 1, GC9A01A_INVOFF,
    GC9A01A_INVON, 0,
    GC9A01A_DISPON, 0x80, // Display on
    GC9A01A_SLPOUT, 0x80, // Exit sleep
    0x00                  // End of list
};


int gc9a01_write_cmd(const struct device *dev, uint8_t cmd,
                                   const uint8_t *data, size_t len)
{
    const struct gc9a01_config *config = dev->config;
    struct spi_buf buf = {.buf = &cmd, .len = sizeof(cmd)};
    struct spi_buf_set buf_set = {.buffers = &buf, .count = 1};
    gpio_pin_set_dt(&config->dc_gpio, 0);
    if (spi_write_dt(&config->bus, &buf_set) != 0) {
        printk("Failed sending data");
        return -EIO;
    }

    if (data != NULL && len != 0) {
        buf.buf = (void *)data;
        buf.len = len;
        gpio_pin_set_dt(&config->dc_gpio, 1);
        if (spi_write_dt(&config->bus, &buf_set) != 0) {
            printk("Failed sending data");
            return -EIO;
        }
    }

    return 0;
}

void gc9a01_set_frame(const struct device *dev, struct gc9a01_frame frame)
{
    uint8_t data[4];

    data[0] = (frame.start.X >> 8) & 0xFF;
    data[1] = frame.start.X & 0xFF;
    data[2] = (frame.end.X >> 8) & 0xFF;
    data[3] = frame.end.X & 0xFF;
    gc9a01_write_cmd(dev, COL_ADDR_SET, data, sizeof(data));

    data[0] = (frame.start.Y >> 8) & 0xFF;
    data[1] = frame.start.Y & 0xFF;
    data[2] = (frame.end.Y >> 8) & 0xFF;
    data[3] = frame.end.Y & 0xFF;
    gc9a01_write_cmd(dev, ROW_ADDR_SET, data, sizeof(data));
}

int gc9a01_blanking_off(const struct device *dev)
{
    return gc9a01_write_cmd(dev, GC9A01A_DISPON, NULL, 0);
}

int gc9a01_blanking_on(const struct device *dev)
{
    return gc9a01_write_cmd(dev, GC9A01A_DISPOFF, NULL, 0);
}

int gc9a01_write(const struct device *dev, const uint16_t x, const uint16_t y,
                        const struct display_buffer_descriptor *desc,
                        const void *buf)
{
    const struct gc9a01_config *config = dev->config;
    __ASSERT(pm_device_action_run(config->bus.bus, PM_DEVICE_ACTION_RESUME) == 0, "Failed resume SPI Bus");
#ifdef GC9A01_SPI_PROFILING
    uint32_t start_time;
    uint32_t stop_time;
    uint32_t cycles_spent;
    uint32_t nanoseconds_spent;
#endif
    uint16_t x_end_idx = x + desc->width - 1;
    uint16_t y_end_idx = y + desc->height - 1;

    frame.start.X = x;
    frame.end.X = x_end_idx;
    frame.start.Y = y;
    frame.end.Y = y_end_idx;
    gc9a01_set_frame(dev, frame);

    size_t len = (x_end_idx + 1 - x) * (y_end_idx + 1 - y) * 16 / 8;
    //printk("x_start: %d, y_start: %d, x_end: %d, y_end: %d, buf_size: %d, pitch: %d len: %d\n", x, y, x_end_idx, y_end_idx, desc->buf_size, desc->pitch, len);

#ifdef GC9A01_SPI_PROFILING
    start_time = k_cycle_get_32();
#endif
    gc9a01_write_cmd(dev, GC9A01A_RAMWR, buf, len);
#ifdef GC9A01_SPI_PROFILING
    stop_time = k_cycle_get_32();
    cycles_spent = stop_time - start_time;
    nanoseconds_spent = k_cyc_to_ns_ceil32(cycles_spent);
    //printk("%d =>: %dns", len, nanoseconds_spent);
#endif
    __ASSERT(pm_device_action_run(config->bus.bus, PM_DEVICE_ACTION_SUSPEND) == 0, "Failed suspend SPI Bus");
    return 0;
}

int gc9a01_read(const struct device *dev, const uint16_t x, const uint16_t y,
                       const struct display_buffer_descriptor *desc, void *buf)
{
    printk("not supported");
    return -ENOTSUP;
}

void *gc9a01_get_framebuffer(const struct device *dev)
{
    printk("not supported");
    return NULL;
}

int gc9a01_set_brightness(const struct device *dev,
                                 const uint8_t brightness)
{
    printk("not supported");
    return -ENOTSUP;
}

int gc9a01_set_contrast(const struct device *dev, uint8_t contrast)
{
    printk("not supported");
    return -ENOTSUP;
}

void gc9a01_get_capabilities(const struct device *dev,
                                    struct display_capabilities *caps)
{
    memset(caps, 0, sizeof(struct display_capabilities));
    caps->x_resolution = DISPLAY_WIDTH;
    caps->y_resolution = DISPLAY_HEIGHT;
    caps->supported_pixel_formats = PIXEL_FORMAT_BGR_565;
    caps->current_pixel_format = PIXEL_FORMAT_BGR_565;
    caps->screen_info = SCREEN_INFO_MONO_MSB_FIRST;
}

int gc9a01_set_orientation(const struct device *dev,
                                  const enum display_orientation
                                  orientation) {
    printk("Unsupported");
    return -ENOTSUP;
}

int gc9a01_set_pixel_format(const struct device *dev,
                                   const enum display_pixel_format pf)
{
    printk("not supported");
    return -ENOTSUP;
}

int gc9a01_controller_init(const struct device *dev)
{
    int rc;
    int i = 0;
    uint8_t cmd, x, numArgs;
    const uint8_t *addr;
    const struct gc9a01_config *config = dev->config;

    gpio_pin_set_dt(&config->reset_gpio, 0);
    k_msleep(5);
    gpio_pin_set_dt(&config->reset_gpio, 1);
    k_msleep(150);
    rc = pm_device_action_run(config->bus.bus, PM_DEVICE_ACTION_RESUME);
    __ASSERT(rc == -EALREADY || rc == 0, "Failed resume SPI Bus");

    addr = initcmd;
    while ((cmd = *addr++) > 0) {
        x = *addr++;
        numArgs = x & 0x7F;
        gc9a01_write_cmd(dev, cmd, addr, numArgs);
        addr += numArgs;
        if (x & 0x80) {
            k_msleep(150);
        }
        i++;
    }

    __ASSERT(pm_device_action_run(config->bus.bus, PM_DEVICE_ACTION_SUSPEND) == 0, "Failed suspend SPI Bus");


    printk("Initialization complete!\n");

    
    // Hollow Circle
    int center_x = DISPLAY_WIDTH / 2;
    int center_y = DISPLAY_HEIGHT / 2;
    int radius = DISPLAY_WIDTH / 4;  
    GC9A01_draw_circle(dev, center_x, center_y, radius, RED);

    // Text
    GC9A01_printf(dev, 25, 25, "TEST");

    return 0;
}

int gc9a01_init(const struct device *dev)
{
    const struct gc9a01_config *config = dev->config;

    if (!device_is_ready(config->reset_gpio.port)) {
        printk("Reset GPIO device not ready");
        return -ENODEV;
    }

    if (!device_is_ready(config->dc_gpio.port)) {
        printk("DC GPIO device not ready");
        return -ENODEV;
    }
    gpio_pin_configure_dt(&config->reset_gpio, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&config->dc_gpio, GPIO_OUTPUT_INACTIVE);

    if (!device_is_ready(config->bl_gpio.port)) {
        printk("Busy GPIO device not ready");
        return -ENODEV;
    }

    // Default to 0 brightness
    gpio_pin_configure_dt(&config->bl_gpio, GPIO_OUTPUT_INACTIVE);
    gc9a01_controller_init(dev);
    return 0;
}

int gc9a01_pm_action(const struct device *dev,
                            enum pm_device_action action)
{
    int err = 0;
    const struct gc9a01_config *config = dev->config;
    __ASSERT(pm_device_action_run(config->bus.bus, PM_DEVICE_ACTION_RESUME) == 0, "Failed resume SPI Bus");

    switch (action) {
        case PM_DEVICE_ACTION_RESUME:
            err = gc9a01_write_cmd(dev, GC9A01A_SLPOUT, NULL, 0);
            k_msleep(5); // According to datasheet wait 5ms after SLPOUT before next command.
            err = gc9a01_write_cmd(dev, GC9A01A_DISPON, NULL, 0);
            break;
        case PM_DEVICE_ACTION_SUSPEND:
            err = gc9a01_write_cmd(dev, GC9A01A_DISPOFF, NULL, 0);
            err = gc9a01_write_cmd(dev, GC9A01A_SLPIN, NULL, 0);
            break;
        case PM_DEVICE_ACTION_TURN_ON:
            err = gc9a01_init(dev);
            break;
        case PM_DEVICE_ACTION_TURN_OFF:
            break;
        default:
            err = -ENOTSUP;
    }

    err = pm_device_action_run(config->bus.bus, PM_DEVICE_ACTION_SUSPEND);
    __ASSERT(err == 0 || err == -EALREADY, "Failed suspend SPI Bus");

    if (err == -EALREADY) {
        err = 0;
    }

    if (err < 0) {
        printk("%s: failed to set power mode", dev->name);
    }

    return err;
}

const struct gc9a01_config gc9a01_config = {
    .bus = SPI_DT_SPEC_INST_GET(0, SPI_OP_MODE_MASTER | SPI_WORD_SET(8), 0),
    .reset_gpio = GPIO_DT_SPEC_INST_GET(0, reset_gpios),
    .dc_gpio = GPIO_DT_SPEC_INST_GET(0, dc_gpios),
    .bl_gpio = GPIO_DT_SPEC_INST_GET(0, bl_gpios),
};

struct display_driver_api gc9a01_driver_api = {
    .blanking_on = gc9a01_blanking_on,
    .blanking_off = gc9a01_blanking_off,
    .write = gc9a01_write,
    .read = gc9a01_read,
    .get_framebuffer = gc9a01_get_framebuffer,
    .set_brightness = gc9a01_set_brightness,
    .set_contrast = gc9a01_set_contrast,
    .get_capabilities = gc9a01_get_capabilities,
    .set_pixel_format = gc9a01_set_pixel_format,
    .set_orientation = gc9a01_set_orientation,
};

void GC9A01_draw_pixel(const struct device *dev, int x, int y, uint16_t color) {

    // Handle invalid pixel location
    if ((x < 0) || (y < 0) || (x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT))
        return;
    
    // Set frame to one pixel
    frame.start.X = x;
    frame.start.Y = y;
    frame.end.X = x;
    frame.end.Y = y;
    gc9a01_set_frame(dev, frame);

    /* Test if this can be removed
    struct display_buffer_descriptor desc = {
        .buf_size = sizeof(color),
        .height = DISPLAY_HEIGHT,
        .width = DISPLAY_WIDTH,
        .pitch = 2,  
    };
    */

    // Write pixel data
    gc9a01_write(dev, x, y, NULL, color);

    // Set frame back to full screen
    frame.start.X = 0;
    frame.start.Y = 0;
    frame.end.X = 239;
    frame.end.Y = 239;
    gc9a01_set_frame(dev, frame);
}


/* Display geometry */

void GC9A01_fill_rect(const struct device *dev, int16_t x, int16_t y, int16_t w, int16_t h,
		uint16_t color) {

	if ((x + w) > DISPLAY_WIDTH)
		w = DISPLAY_WIDTH - x;
	if ((y + h) > DISPLAY_HEIGHT)
		h = DISPLAY_HEIGHT - y;

    uint8_t color_new[3];
    color_new[2] = (uint8_t)((color & 0x1F) << 3);   // blue
    color_new[1] = (uint8_t)((color & 0x7E0) >> 3);  // green
    color_new[0] = (uint8_t)((color & 0xF800) >> 8); // red

    frame.start.X = x;
    frame.start.Y = y;
    frame.end.X = w;
    frame.end.Y = h;
    gc9a01_set_frame(dev, frame);

    for (uint16_t row = 0; row < h+1; row++) {
		for (uint16_t col = 0; col < w+1; col++) {		
            if (row == 0 && col == 0) {
                gc9a01_write_cmd(dev, MEM_WR, NULL, 0);
                gc9a01_write(dev, x, y, NULL, color_new);
            } else {  
                gc9a01_write_cmd(dev, MEM_WR_CONT, NULL, 0);
                gc9a01_write(dev, x, y, NULL, color_new);
            }
        }
    }
 
    frame.start.X = 0;
    frame.start.Y = 0;
    frame.end.X = 239;
    frame.end.Y = 239;
    GC9A01_set_frame(frame);
}


void GC9A01_draw_circle(const struct device *dev, uint16_t x0, uint16_t y0, int r, uint16_t color) {
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;
    GC9A01_draw_pixel(dev, x0, y0 + r, color);
    GC9A01_draw_pixel(dev, x0, y0 - r, color);
    GC9A01_draw_pixel(dev, x0 + r, y0, color);
    GC9A01_draw_pixel(dev, x0 - r, y0, color);
    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        GC9A01_draw_pixel(dev, x0 + x, y0 + y, color);
        GC9A01_draw_pixel(dev, x0 - x, y0 + y, color);
        GC9A01_draw_pixel(dev, x0 + x, y0 - y, color);
        GC9A01_draw_pixel(dev, x0 - x, y0 - y, color);
        GC9A01_draw_pixel(dev, x0 + y, y0 + x, color);
        GC9A01_draw_pixel(dev, x0 - y, y0 + x, color);
        GC9A01_draw_pixel(dev, x0 + y, y0 - x, color);
        GC9A01_draw_pixel(dev, x0 - y, y0 - x, color);
    }
}

void GC9A01_fill_circle(const struct device *dev, int16_t x, int16_t y, int16_t radius,
		uint16_t color) {

    for (uint8_t curX = (x - radius); curX <= (x + radius); curX++)
    {
        for (uint8_t curY = (y - radius); curY <= (y + radius); curY++)
        {
            if ((pow(x-curX, 2) + pow(y-curY, 2)) <= pow(radius, 2))
            {
                GC9A01_draw_pixel(dev, curX, curY, color);
            }
        }
    }
}

/*------------------------------------------------------------*/


/* Display Text */

void GC9A01_fonts_init(void) {
    Font8.Height = 8;
    Font8.Width = 5;
    Font12.Height = 12;
    Font12.Width = 7;
    Font16.Height = 16;
    Font16.Width = 11;
    Font20.Height = 20;
    Font20.Width = 14;
    Font24.Height = 24;
    Font24.Width = 17;
    fonts.BackColor = BLACK;
    fonts.TextColor = GREEN;
    fonts.pFont = &Font16;
}

void GC9A01_set_text_color(uint16_t color) {
    fonts.TextColor = color;
}

void GC9A01_set_back_color(uint16_t color) {
    fonts.BackColor = color;
}

void GC9A01_set_font(sFONT *pFonts) {
    fonts.pFont = pFonts;
}


void GC9A01_draw_char(const struct device *dev, uint16_t x, uint16_t y, uint8_t c) {
    uint32_t i = 0, j = 0;
    uint16_t height, width;
    uint8_t offset;
    uint8_t *c_t;
    uint8_t *pchar;
    uint32_t line = 0;
    height = fonts.pFont->Height;
    width = fonts.pFont->Width;
    offset = 8 * ((width + 7) / 8) - width;
    c_t = (uint8_t *)&(fonts.pFont->table[(c - ' ') * fonts.pFont->Height * ((fonts.pFont->Width + 7) / 8)]);
    for (i = 0; i < height; i++)
    {
        pchar = ((uint8_t *)c_t + (width + 7) / 8 * i);
        switch (((width + 7) / 8))
        {
        case 1:
            line = pchar[0];
            break;
        case 2:
            line = (pchar[0] << 8) | pchar[1];
            break;
        case 3:
        default:
            line = (pchar[0] << 16) | (pchar[1] << 8) | pchar[2];
            break;
        }
        for (j = 0; j < width; j++)
        {
            if (line & (1 << (width - j + offset - 1)))
            {
                GC9A01_draw_pixel(dev, (x + j), y, fonts.TextColor);
            }
            else
            {
                GC9A01_draw_pixel(dev, (x + j), y, fonts.BackColor);
                // continue;
            }
        }
        y++;
    }
}

void GC9A01_draw_string(const struct device *dev, uint16_t x,uint16_t y, char *str) {
    while (*str)
    {
        GC9A01_draw_char(dev, x, y, str[0]);
        x += fonts.pFont->Width;
        (void)*str++;
    }
}

void GC9A01_printf(const struct device *dev, int16_t X, int16_t Y, const char *args, ...) {
	char StrBuff[100];

	va_list ap;
	va_start(ap, args);
	vsnprintf(StrBuff, sizeof(StrBuff), args, ap);
	va_end(ap);
	GC9A01_draw_string(dev, X, Y, StrBuff);
}


/*-----------------------------------------------------------------------------*/


PM_DEVICE_DT_INST_DEFINE(0, gc9a01_pm_action);
DEVICE_DT_INST_DEFINE(0, gc9a01_init, PM_DEVICE_DT_INST_GET(0), NULL, &gc9a01_config, POST_KERNEL,
                      CONFIG_DISPLAY_INIT_PRIORITY, &gc9a01_driver_api);

