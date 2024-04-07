#include "lvgl.h"
//#include "icons/icons.h" add to (ui.h)


extern lv_font_t roboto_48; 
extern lv_font_t orbitron_24;



extern lv_font_t icons_36; // 0xf004, 
extern lv_font_t icons_16; // 0xf54b
extern lv_font_t icons_26; // 0xf70c, 0xf294, 0xf293, 0xf241, 0xf017, 0xf06e

#define HEART_ICON_36 "\xEF\x80\x84"

#define STEPS_ICON_16 "\xEF\x95\x8B"

#define RUNNING_ICON_26 "\xEF\x9C\x8C"
#define BLUETOOTH_ICON_26 "\xEF\x8A\x94"
#define BLUETOOTH_FILLED_ICON_26 "\xEF\x8A\x93"
#define BATTERY_ICON_26 "\xEF\x89\x81"
#define CLOCK_ICON_26 "\xEF\x80\x97"
#define EYE_ICON_26 "\xEF\x81\xAE"


LV_IMG_DECLARE(ui_img_battery_half_png);



/*
char time_str[20]; 
snprintf(time_str, sizeof(time_str), "%02u:%02u", CurrentTime.tm_hour, CurrentTime.tm_min);
lv_label_set_text(ui_TimeLabel, time_str);

char date_str[20]; 
snprintf(date_str, sizeof(date_str), "%u,March", CurrentTime.tm_mday);
lv_label_set_text(ui_DateLabel, date_str);
*/