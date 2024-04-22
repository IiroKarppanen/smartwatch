#include "ui.h"
#include "../clock/clock.h"

LV_FONT_DECLARE(roboto_14);
LV_FONT_DECLARE(roboto_18);
LV_FONT_DECLARE(roboto_22);
LV_FONT_DECLARE(roboto_68);

#define MASK_WIDTH 240
#define MASK_HEIGHT 240

char timeStr[6]; 
char dateStr[20]; 
static uint16_t hue = 0; 

lv_obj_t * canvas;
lv_obj_t * grad;

lv_draw_label_dsc_t label_minutes;
lv_draw_label_dsc_t label_date;
lv_draw_label_dsc_t label_charge_symbol;
lv_draw_label_dsc_t label_step_symbol;
lv_obj_t * hour_label;


static lv_color_t mask_map[MASK_WIDTH * MASK_HEIGHT];


static void add_mask_event_cb(lv_event_t * e)
{
    static lv_draw_mask_map_param_t m;
    static int16_t mask_id;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    lv_opa_t * mask_map = lv_event_get_user_data(e);
    if(code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED);
    }
    else if(code == LV_EVENT_DRAW_MAIN_BEGIN) {
        lv_draw_mask_map_init(&m, &obj->coords, mask_map);
        mask_id = lv_draw_mask_add(&m, NULL);

    }
    else if(code == LV_EVENT_DRAW_MAIN_END) {
        lv_draw_mask_free_param(&m);
        lv_draw_mask_remove_id(mask_id);
    }
}

static void update_gradient() {
  
    lv_color_t new_color = lv_color_hsv_to_rgb(hue, 80, 80);
    lv_obj_set_style_bg_grad_color(grad, new_color, 0);

    hue += 1; 
    if (hue == 359) {
        hue = 0; 
    }
}

static void update_canvas() {

    // Clear mask map
    memset(mask_map, 0, sizeof(mask_map));  

    // Update labels
    strftime(timeStr, sizeof(timeStr), "%M", &CurrentTime);
    lv_canvas_draw_text(canvas, 45, 90, MASK_WIDTH, &label_minutes, timeStr);

    strftime(timeStr, sizeof(timeStr), "%H", &CurrentTime);
    lv_label_set_text(hour_label, timeStr);

    strftime(dateStr, sizeof(dateStr), "%d %B", &CurrentTime);
    lv_canvas_draw_text(canvas, 0, 40, MASK_WIDTH, &label_date, dateStr);

    lv_canvas_draw_text(canvas, -40, 170, MASK_WIDTH, &label_charge_symbol, LV_SYMBOL_CHARGE);
    lv_canvas_draw_text(canvas, 40, 170, MASK_WIDTH, &label_step_symbol, STEPS_ICON_14);

    


    // Update mask map
    uint32_t i;
    uint8_t * mask8 = (uint8_t *) mask_map;
    lv_color_t * mask_c = mask_map;
    for(i = 0; i < MASK_WIDTH * MASK_HEIGHT; i++) {
        mask8[i] = lv_color_brightness(mask_c[i]);
    }

}



void ui_Home_screen_init(void)
{
    ui_Home = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Home, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Home, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Home, ui_event_Home, LV_EVENT_ALL, NULL);

    // ##################################################################################

    

    canvas = lv_canvas_create(ui_Home);
    lv_canvas_set_buffer(canvas, mask_map, MASK_WIDTH, MASK_HEIGHT, LV_IMG_CF_RESERVED_16);
 
    lv_draw_label_dsc_init(&label_minutes);
    label_minutes.color = lv_color_white();
    label_minutes.align = LV_TEXT_ALIGN_CENTER;
    label_minutes.font = &roboto_68;

    lv_draw_label_dsc_init(&label_charge_symbol);
    label_charge_symbol.color = lv_color_white();
    label_charge_symbol.align = LV_TEXT_ALIGN_CENTER;
    label_charge_symbol.font = &lv_font_montserrat_14;

    lv_draw_label_dsc_init(&label_step_symbol);
    label_step_symbol.color = lv_color_white();
    label_step_symbol.align = LV_TEXT_ALIGN_CENTER;
    label_step_symbol.font = &home_icons_14;
    label_step_symbol.letter_space = 1;
  
    
    lv_draw_label_dsc_init(&label_date);
    label_date.color = lv_color_white();
    label_date.align = LV_TEXT_ALIGN_CENTER;
    label_date.font = &roboto_22;
    label_date.letter_space = 2;
    
    // Populate mask map
    uint32_t i;
    uint8_t * mask8 = (uint8_t *) mask_map;
    lv_color_t * mask_c = mask_map;
    for(i = 0; i < MASK_WIDTH * MASK_HEIGHT; i++) {
        mask8[i] = lv_color_brightness(mask_c[i]);
    }

    // Add gradient
    grad = lv_obj_create(ui_Home);
    lv_obj_set_size(grad, MASK_WIDTH, MASK_HEIGHT);
    lv_obj_center(grad);
    lv_obj_set_style_bg_color(grad, lv_color_make(255, 255, 255), 0);
    lv_obj_set_style_bg_grad_color(grad, lv_color_make(91, 150, 245), 0);
    lv_obj_set_style_bg_grad_dir(grad, LV_GRAD_DIR_HOR, 0);
    lv_obj_add_event_cb(grad, add_mask_event_cb, LV_EVENT_ALL, mask_map);
    lv_obj_set_style_border_opa(grad, 0, NULL);

    

    // Start tasks
    lv_timer_create(update_canvas, 1000, NULL); 
    lv_timer_create(update_gradient, 100, NULL); 

    
    lv_obj_t * stepButton = lv_obj_create(ui_Home);
    lv_obj_set_width(stepButton, 68);
    lv_obj_set_height(stepButton, 68);
    lv_obj_set_x(stepButton, 40);
    lv_obj_set_y(stepButton, 70);
    lv_obj_set_align(stepButton, LV_ALIGN_CENTER);

    lv_obj_set_style_border_color(stepButton, lv_color_make(66,66,66), NULL);
    lv_obj_set_style_border_width(stepButton, 2, NULL);
    //lv_obj_set_style_border_opa(stepButton, 50, NULL);
    lv_obj_set_style_radius(stepButton, 100, NULL);
    lv_obj_set_style_bg_opa(stepButton, 0, NULL);

    //lv_obj_add_event_cb(stepButton, button_event_handler, LV_EVENT_ALL, NULL);


    lv_obj_t * dividor_Label = lv_label_create(ui_Home);
    lv_obj_set_width(dividor_Label, LV_SIZE_CONTENT);  
    lv_obj_set_height(dividor_Label, LV_SIZE_CONTENT);   
    lv_obj_set_x(dividor_Label, 0);
    lv_obj_set_y(dividor_Label, 0);
    lv_obj_set_align(dividor_Label, LV_ALIGN_CENTER);
    lv_label_set_text(dividor_Label, ":");
    lv_obj_set_style_text_color(dividor_Label, lv_color_make(125, 125, 125), NULL);
    lv_obj_set_style_text_font(dividor_Label, &roboto_68, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_Label3 = lv_label_create(ui_Home);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, 40);
    lv_obj_set_y(ui_Label3, 80);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "10127");
    lv_obj_set_style_text_font(ui_Label3, &roboto_14, LV_PART_MAIN | LV_STATE_DEFAULT);
  

    lv_obj_t * batteryButton = lv_obj_create(ui_Home);
    lv_obj_set_width(batteryButton, 68);
    lv_obj_set_height(batteryButton, 68);
    lv_obj_set_x(batteryButton, -40);
    lv_obj_set_y(batteryButton, 70);
    lv_obj_set_align(batteryButton, LV_ALIGN_CENTER);

    lv_obj_set_style_border_color(batteryButton, lv_color_make(66,66,66), NULL);
    lv_obj_set_style_border_width(batteryButton, 2, NULL);
    //lv_obj_set_style_border_opa(batteryButton, 50, NULL);
    lv_obj_set_style_radius(batteryButton, 100, NULL);
    lv_obj_set_style_bg_opa(batteryButton, 0, NULL);

    //lv_obj_add_event_cb(stepButton, button_event_handler, LV_EVENT_ALL, NULL);

    ui_Label3 = lv_label_create(ui_Home);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -40);
    lv_obj_set_y(ui_Label3, 80);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_obj_set_style_text_letter_space(ui_Label3, 1, NULL);
    lv_label_set_text(ui_Label3, "54%");

    lv_obj_set_style_text_font(ui_Label3, &roboto_14, LV_PART_MAIN | LV_STATE_DEFAULT);



    hour_label = lv_label_create(ui_Home);
    lv_obj_set_width(hour_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(hour_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(hour_label, -45);
    lv_obj_set_y(hour_label, 0);
    lv_obj_set_align(hour_label, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(hour_label, &roboto_68, LV_PART_MAIN | LV_STATE_DEFAULT);
    
}




