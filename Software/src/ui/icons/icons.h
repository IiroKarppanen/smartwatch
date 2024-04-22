#include "lvgl.h"
//#include "icons/icons.h" add to (ui.h)


//extern lv_font_t roboto_48; 
//extern lv_font_t orbitron_24;





extern lv_font_t home_icons_14;

#define STEPS_ICON_14 "\xEF\x95\x8B"
#define LIGHTNING_ICON_14 "\xEF\x83\xA7"


LV_IMG_DECLARE(ui_img_battery_half_png);



/*
char time_str[20]; 
snprintf(time_str, sizeof(time_str), "%02u:%02u", CurrentTime.tm_hour, CurrentTime.tm_min);
lv_label_set_text(ui_TimeLabel, time_str);

char date_str[20]; 
snprintf(date_str, sizeof(date_str), "%u,March", CurrentTime.tm_mday);
lv_label_set_text(ui_DateLabel, date_str);
*/