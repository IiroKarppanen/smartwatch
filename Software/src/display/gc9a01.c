#include "gc9a01.h"
#include <zephyr.h>
#include <device.h>
#include <drivers/spi.h>
#include <logging/log.h>
#include <sys/util.h>   
#include <math.h>
#include <stdio.h>
#include <drivers/gpio.h>
#include <devicetree.h>


#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
LOG_MODULE_REGISTER(main);


#define GPIO DT_LABEL(DT_NODELABEL(gpio0))
#define GPI1 DT_LABEL(DT_NODELABEL(gpio1))


#define ORIENTATION 2 
#define RESET_ON            gpio_pin_set(device_get_binding(GPI1), LCD_RES_Pin, 1)
#define RESET_OFF           gpio_pin_set(device_get_binding(GPI1), LCD_RES_Pin, 0)
#define DC_ON               gpio_pin_set(device_get_binding(GPIO), LCD_DC_Pin, 1)
#define DC_OFF              gpio_pin_set(device_get_binding(GPIO), LCD_DC_Pin, 0)
#define CS_ON               gpio_pin_set(device_get_binding(GPIO), LCD_CS_Pin, 1)
#define CS_OFF              gpio_pin_set(device_get_binding(GPIO), LCD_CS_Pin, 0)


#define SPI_BUF_SIZE 8
static uint8_t m_tx_buf[3]; 
static const struct device *spi_dev;

struct spi_config spi_cfg = {
    .operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8), // Set word size to 8 bits
    .frequency = 1000000,  // 1 MHz
};

/***** Structures *******************************************************************/
struct GC9A01_frame frame;     // coordinates(X(start,end), Y(start,end)) frame, from 0 to 239
/************************************************************************************/


/***** Display write func ***********************************************************/

void GC9A01_spi_tx(uint8_t *data, size_t len) {
    struct spi_buf tx_buf = {
        .buf = data,
        .len = len,
    };
    const struct spi_buf_set tx = {
        .buffers = &tx_buf,
        .count = 1,
    };

    int result = spi_write(spi_dev, &spi_cfg, &tx_buf);
    if (result != 0) {
        LOG_ERR("SPI write failed with error code %d", result);
    } 
}


void GC9A01_write_command(uint8_t cmd) {
    DC_OFF;
    CS_OFF;
    GC9A01_spi_tx(&cmd, sizeof(cmd));
    CS_ON;
}

void GC9A01_write_data(uint8_t *data, size_t len) {
    DC_ON;
    CS_OFF;
    GC9A01_spi_tx(data, len);
    CS_ON;  
}

static inline void GC9A01_write_byte(uint8_t val) {
    GC9A01_write_data(&val, sizeof(val));
}

void GC9A01_write(uint8_t *data, size_t len) {
    GC9A01_write_command(MEM_WR);
    GC9A01_write_data(data, len);
}

void GC9A01_write_continue(uint8_t *data, size_t len) {
    GC9A01_write_command(MEM_WR_CONT);
    GC9A01_write_data(data, len);
}



/***** Hardware and soft func *******************************************************/
void lcd_spi_init(void) {
    spi_dev = device_get_binding(DT_LABEL(DT_NODELABEL(spi3)));
    if (!spi_dev) {
        LOG_ERR("SPI device not found");
        return;
    }

    /* GPIO for display */
    gpio_pin_configure(device_get_binding(GPI1), LCD_RES_Pin, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure(device_get_binding(GPIO), LCD_CS_Pin, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure(device_get_binding(GPIO), LCD_DC_Pin, GPIO_OUTPUT_ACTIVE);
    LOG_INF(" - SPI init successfull! - ");
}


void GC9A01_init(void) {
    
    CS_ON;
    k_sleep(K_MSEC(5));
    RESET_OFF;
    k_sleep(K_MSEC(10));
    RESET_ON;
    k_sleep(K_MSEC(120));

    LOG_INF(" - Display Reset - ");
    
    /* Initial Sequence */ 
    
    GC9A01_write_command(0xEF);
    
    GC9A01_write_command(0xEB);
    GC9A01_write_byte(0x14);
    
    GC9A01_write_command(0xFE);
    GC9A01_write_command(0xEF);
    
    GC9A01_write_command(0xEB);
    GC9A01_write_byte(0x14);
    
    GC9A01_write_command(0x84);
    GC9A01_write_byte(0x40);
    
    GC9A01_write_command(0x85);
    GC9A01_write_byte(0xFF);
    
    GC9A01_write_command(0x86);
    GC9A01_write_byte(0xFF);
    
    GC9A01_write_command(0x87);
    GC9A01_write_byte(0xFF);
    
    GC9A01_write_command(0x88);
    GC9A01_write_byte(0x0A);
    
    GC9A01_write_command(0x89);
    GC9A01_write_byte(0x21);
    
    GC9A01_write_command(0x8A);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0x8B);
    GC9A01_write_byte(0x80);
    
    GC9A01_write_command(0x8C);
    GC9A01_write_byte(0x01);
    
    GC9A01_write_command(0x8D);
    GC9A01_write_byte(0x01);
    
    GC9A01_write_command(0x8E);
    GC9A01_write_byte(0xFF);
    
    GC9A01_write_command(0x8F);
    GC9A01_write_byte(0xFF);
    
    
    GC9A01_write_command(0xB6);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00); 
    
    GC9A01_write_command(0x36);
    
#if ORIENTATION == 0
    GC9A01_write_byte(0x18);
#elif ORIENTATION == 1
    GC9A01_write_byte(0x28);
#elif ORIENTATION == 2
    GC9A01_write_byte(0x48); 
#else
    GC9A01_write_byte(0x88);
#endif
    
    GC9A01_write_command(COLOR_MODE);
    GC9A01_write_byte(COLOR_MODE__18_BIT);
    
    GC9A01_write_command(0x90);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    
    GC9A01_write_command(0xBD);
    GC9A01_write_byte(0x06);
    
    GC9A01_write_command(0xBC);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0xFF);
    GC9A01_write_byte(0x60);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0x04);
    
    GC9A01_write_command(0xC3);
    GC9A01_write_byte(0x13);
    GC9A01_write_command(0xC4);
    GC9A01_write_byte(0x13);
    
    GC9A01_write_command(0xC9);
    GC9A01_write_byte(0x22);
    
    GC9A01_write_command(0xBE);
    GC9A01_write_byte(0x11);
    
    GC9A01_write_command(0xE1);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x0E);
    
    GC9A01_write_command(0xDF);
    GC9A01_write_byte(0x21);
    GC9A01_write_byte(0x0c);
    GC9A01_write_byte(0x02);
    
    GC9A01_write_command(0xF0);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x26);
    GC9A01_write_byte(0x2A);
    
    GC9A01_write_command(0xF1);
    GC9A01_write_byte(0x43);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x72);
    GC9A01_write_byte(0x36);
    GC9A01_write_byte(0x37);
    GC9A01_write_byte(0x6F);
    
    GC9A01_write_command(0xF2);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x26);
    GC9A01_write_byte(0x2A);
    
    GC9A01_write_command(0xF3);
    GC9A01_write_byte(0x43);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x72);
    GC9A01_write_byte(0x36);
    GC9A01_write_byte(0x37);
    GC9A01_write_byte(0x6F);
    
    GC9A01_write_command(0xED);
    GC9A01_write_byte(0x1B);
    GC9A01_write_byte(0x0B);
    
    GC9A01_write_command(0xAE);
    GC9A01_write_byte(0x77);
    
    GC9A01_write_command(0xCD);
    GC9A01_write_byte(0x63);
    
    GC9A01_write_command(0x70);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x04);
    GC9A01_write_byte(0x0E);
    GC9A01_write_byte(0x0F);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x03);
    
    GC9A01_write_command(0xE8);
    GC9A01_write_byte(0x34);
    
    GC9A01_write_command(0x62);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x0D);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xED);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x0F);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xEF);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    
    GC9A01_write_command(0x63);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x11);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x13);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xF3);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    
    GC9A01_write_command(0x64);
    GC9A01_write_byte(0x28);
    GC9A01_write_byte(0x29);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x07);
    
    GC9A01_write_command(0x66);
    GC9A01_write_byte(0x3C);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0xCD);
    GC9A01_write_byte(0x67);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0x67);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x3C);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0x54);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x32);
    GC9A01_write_byte(0x98);
    
    GC9A01_write_command(0x74);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x85);
    GC9A01_write_byte(0x80);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x4E);
    GC9A01_write_byte(0x00);
    
    GC9A01_write_command(0x98);
    GC9A01_write_byte(0x3e);
    GC9A01_write_byte(0x07);
    
    GC9A01_write_command(0x35);
    GC9A01_write_command(0x21);
    
    GC9A01_write_command(0x11);
    k_sleep(K_MSEC(120));
    GC9A01_write_command(0x29);
    k_sleep(K_MSEC(20));

    LOG_INF(" - GC9A01 INIT COMPLETE! - ");
    
}

void GC9A01A_sleep_mode(uint8_t Mode) {
	if (Mode)
		GC9A01_write_command(SLPIN);
	else
		GC9A01_write_command(SLPOUT);

	k_sleep(K_MSEC(500));
}


/* Visual Functions */

void GC9A01_set_frame(struct GC9A01_frame frame) {

    uint8_t data[4];
    
    GC9A01_write_command(COL_ADDR_SET);
    data[0] = (frame.start.X >> 8) & 0xFF;
    data[1] = frame.start.X & 0xFF;
    data[2] = (frame.end.X >> 8) & 0xFF;
    data[3] = frame.end.X & 0xFF;
    GC9A01_write_data(data, sizeof(data));

    GC9A01_write_command(ROW_ADDR_SET);
    data[0] = (frame.start.Y >> 8) & 0xFF;
    data[1] = frame.start.Y & 0xFF;
    data[2] = (frame.end.Y >> 8) & 0xFF;
    data[3] = frame.end.Y & 0xFF;
    GC9A01_write_data(data, sizeof(data));
    
}

void GC9A01_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h,
		uint16_t color) {

	if ((x + w) > GC9A01A_Width)
		w = GC9A01A_Width - x;
	if ((y + h) > GC9A01A_Height)
		h = GC9A01A_Height - y;

    uint8_t color_new[3];
    color_new[2] = (uint8_t)((color & 0x1F) << 3);   // blue
    color_new[1] = (uint8_t)((color & 0x7E0) >> 3);  // green
    color_new[0] = (uint8_t)((color & 0xF800) >> 8); // red

    frame.start.X = x;
    frame.start.Y = y;
    frame.end.X = w;
    frame.end.Y = h;
    GC9A01_set_frame(frame);

    for (uint16_t row = 0; row < h+1; row++) {
		for (uint16_t col = 0; col < w+1; col++) {		
            if (row == 0 && col == 0) {
                GC9A01_write(color_new, sizeof(color_new));
            } else {  
                GC9A01_write_continue(color_new, sizeof(color_new));
            }
        }
    }
 
    frame.start.X = 0;
    frame.start.Y = 0;
    frame.end.X = 239;
    frame.end.Y = 239;
    GC9A01_set_frame(frame);
}


void GC9A01_draw_pixel(int x, int y, uint16_t color) {
    if ((x < 0) || (y < 0) || (x >= GC9A01A_Width) || (y >= GC9A01A_Height))
        return;
    frame.start.X = x;
    frame.end.X = x;
    frame.start.Y = y;
    frame.end.Y = y;
    GC9A01_set_frame(frame);
    m_tx_buf[2] = (uint8_t)((color & 0x1F) << 3);    // blue
    m_tx_buf[1] = (uint8_t)((color & 0x7E0) >> 3);   // green
    m_tx_buf[0] = (uint8_t)((color & 0xF800) >> 8);  // red
    GC9A01_write(m_tx_buf, sizeof(m_tx_buf));
    frame.start.X = 0;
    frame.end.X = 239;
    frame.start.Y = 0;
    frame.end.Y = 239;
    GC9A01_set_frame(frame);
}

void GC9A01_draw_line(uint16_t color, uint16_t x1, uint16_t y1,
                      uint16_t x2, uint16_t y2) {
    int steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep)
    {
        swap(x1, y1);
        swap(x2, y2);
    }
    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    int dx, dy;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    int err = dx / 2;
    int ystep;
    if (y1 < y2)
        ystep = 1;
    else
        ystep = -1;
    for (; x1 <= x2; x1++)
    {
        if (steep)
            GC9A01_draw_pixel(y1, x1, color);
        else
            GC9A01_draw_pixel(x1, y1, color);
        err -= dy;
        if (err < 0)
        {
            y1 += ystep;
            err += dx;
        }
    }
}

void GC9A01_draw_circle(uint16_t x0, uint16_t y0, int r, uint16_t color) {
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;
    GC9A01_draw_pixel(x0, y0 + r, color);
    GC9A01_draw_pixel(x0, y0 - r, color);
    GC9A01_draw_pixel(x0 + r, y0, color);
    GC9A01_draw_pixel(x0 - r, y0, color);
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
        GC9A01_draw_pixel(x0 + x, y0 + y, color);
        GC9A01_draw_pixel(x0 - x, y0 + y, color);
        GC9A01_draw_pixel(x0 + x, y0 - y, color);
        GC9A01_draw_pixel(x0 - x, y0 - y, color);
        GC9A01_draw_pixel(x0 + y, y0 + x, color);
        GC9A01_draw_pixel(x0 - y, y0 + x, color);
        GC9A01_draw_pixel(x0 + y, y0 - x, color);
        GC9A01_draw_pixel(x0 - y, y0 - x, color);
    }
}

void GC9A01_fill_circle(int16_t x, int16_t y, int16_t radius,
		uint16_t color) {

    for (uint8_t curX = (x - radius); curX <= (x + radius); curX++)
    {
        for (uint8_t curY = (y - radius); curY <= (y + radius); curY++)
        {
            if ((pow(x-curX, 2) + pow(y-curY, 2)) <= pow(radius, 2))
            {
                GC9A01_draw_pixel(curX, curY, color);
            }
        }
    }

}