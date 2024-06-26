/*******************************************************************************
 * Size: 24 px
 * Bpp: 1
 * Opts: --bpp 1 --size 24 --no-compress --font Orbitron-Regular.ttf --symbols ABCDEFGHJIKLMN --format lvgl -o orbitron_24.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ORBITRON_24
#define ORBITRON_24 1
#endif

#if ORBITRON_24

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0041 "A" */
    0x7f, 0xff, 0x7f, 0xff, 0xf0, 0x0, 0x78, 0x0,
    0x3c, 0x0, 0x1e, 0x0, 0xf, 0x0, 0x7, 0x80,
    0x3, 0xc0, 0x1, 0xff, 0xff, 0xff, 0xff, 0xf8,
    0x0, 0x3c, 0x0, 0x1e, 0x0, 0xf, 0x0, 0x7,
    0x80, 0x3, 0xc0, 0x1, 0x80,

    /* U+0042 "B" */
    0xff, 0xff, 0x7f, 0xff, 0xf0, 0x0, 0x78, 0x0,
    0x3c, 0x0, 0x1e, 0x0, 0xf, 0x0, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xe0, 0x0, 0xf0, 0x0, 0x78,
    0x0, 0x3c, 0x0, 0x1e, 0x0, 0xf, 0x0, 0x7,
    0xff, 0xff, 0xff, 0xff, 0x0,

    /* U+0043 "C" */
    0x7f, 0xff, 0xff, 0xff, 0xf0, 0x0, 0x18, 0x0,
    0xc, 0x0, 0x6, 0x0, 0x3, 0x0, 0x1, 0x80,
    0x0, 0xc0, 0x0, 0x60, 0x0, 0x30, 0x0, 0x18,
    0x0, 0xc, 0x0, 0x6, 0x0, 0x3, 0x0, 0x1,
    0xff, 0xff, 0x7f, 0xff, 0x80,

    /* U+0044 "D" */
    0xff, 0xff, 0x7f, 0xff, 0xf0, 0x0, 0x78, 0x0,
    0x3c, 0x0, 0x1e, 0x0, 0xf, 0x0, 0x7, 0x80,
    0x3, 0xc0, 0x1, 0xe0, 0x0, 0xf0, 0x0, 0x78,
    0x0, 0x3c, 0x0, 0x1e, 0x0, 0xf, 0x0, 0x7,
    0xff, 0xff, 0xff, 0xff, 0x0,

    /* U+0045 "E" */
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x0, 0xc0, 0x0,
    0xc0, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0xff, 0xf8,
    0xff, 0xf8, 0xc0, 0x0, 0xc0, 0x0, 0xc0, 0x0,
    0xc0, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0xff, 0xff,
    0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x0, 0xc0, 0x0,
    0xc0, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0xff, 0xf8,
    0xff, 0xf8, 0xc0, 0x0, 0xc0, 0x0, 0xc0, 0x0,
    0xc0, 0x0, 0xc0, 0x0, 0xc0, 0x0, 0xc0, 0x0,
    0xc0, 0x0,

    /* U+0047 "G" */
    0x7f, 0xff, 0x7f, 0xff, 0xf0, 0x0, 0x78, 0x0,
    0x3c, 0x0, 0x6, 0x0, 0x3, 0x0, 0x1, 0x80,
    0x0, 0xc0, 0x1f, 0xe0, 0xf, 0xf0, 0x0, 0x78,
    0x0, 0x3c, 0x0, 0x1e, 0x0, 0xf, 0x0, 0x7,
    0xff, 0xff, 0x7f, 0xff, 0x0,

    /* U+0048 "H" */
    0xc0, 0x0, 0xf0, 0x0, 0x3c, 0x0, 0xf, 0x0,
    0x3, 0xc0, 0x0, 0xf0, 0x0, 0x3c, 0x0, 0xf,
    0xff, 0xff, 0xff, 0xff, 0xf0, 0x0, 0x3c, 0x0,
    0xf, 0x0, 0x3, 0xc0, 0x0, 0xf0, 0x0, 0x3c,
    0x0, 0xf, 0x0, 0x3, 0xc0, 0x0, 0xc0,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+004A "J" */
    0x0, 0x1, 0x80, 0x0, 0xc0, 0x0, 0x60, 0x0,
    0x30, 0x0, 0x18, 0x0, 0xc, 0x0, 0x6, 0x0,
    0x3, 0x0, 0x1, 0x80, 0x0, 0xc0, 0x0, 0x60,
    0x0, 0x30, 0x0, 0x1e, 0x0, 0xf, 0x0, 0x7,
    0xff, 0xff, 0x7f, 0xff, 0x0,

    /* U+004B "K" */
    0xc0, 0x3, 0x60, 0x3, 0x30, 0x3, 0x18, 0x3,
    0xc, 0x3, 0x6, 0x3, 0x83, 0x3, 0x81, 0xff,
    0x80, 0xff, 0xc0, 0x60, 0x60, 0x30, 0x18, 0x18,
    0x6, 0xc, 0x3, 0x86, 0x0, 0xe3, 0x0, 0x39,
    0x80, 0xc, 0xc0, 0x3, 0x0,

    /* U+004C "L" */
    0xc0, 0x0, 0x30, 0x0, 0xc, 0x0, 0x3, 0x0,
    0x0, 0xc0, 0x0, 0x30, 0x0, 0xc, 0x0, 0x3,
    0x0, 0x0, 0xc0, 0x0, 0x30, 0x0, 0xc, 0x0,
    0x3, 0x0, 0x0, 0xc0, 0x0, 0x30, 0x0, 0xc,
    0x0, 0x3, 0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+004D "M" */
    0xe0, 0x0, 0x7f, 0x0, 0xf, 0xf8, 0x1, 0xfd,
    0xc0, 0x3b, 0xce, 0x7, 0x3c, 0x60, 0xe3, 0xc3,
    0xc, 0x3c, 0x19, 0x83, 0xc1, 0xf8, 0x3c, 0xf,
    0x3, 0xc0, 0x60, 0x3c, 0x0, 0x3, 0xc0, 0x0,
    0x3c, 0x0, 0x3, 0xc0, 0x0, 0x3c, 0x0, 0x3,
    0xc0, 0x0, 0x30,

    /* U+004E "N" */
    0xe0, 0x1, 0xf8, 0x0, 0xfe, 0x0, 0x7b, 0x80,
    0x3c, 0xc0, 0x1e, 0x30, 0xf, 0xc, 0x7, 0x87,
    0x3, 0xc1, 0xc1, 0xe0, 0x70, 0xf0, 0x18, 0x78,
    0x6, 0x3c, 0x1, 0x9e, 0x0, 0xef, 0x0, 0x3f,
    0x80, 0xf, 0xc0, 0x3, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 321, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 319, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 316, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 320, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 294, .box_w = 16, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 278, .box_w = 16, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 319, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 327, .box_w = 18, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 82, .box_w = 2, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 300, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 306, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 299, .box_w = 18, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 356, .box_w = 20, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 319, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 65, .range_length = 14, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    5, 13,
    6, 10,
    11, 1,
    11, 8
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -11, -92, -12, -11
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 4,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t orbitron_24 = {
#else
lv_font_t orbitron_24 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if ORBITRON_24*/

