// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.2.3
// LVGL version: 8.3.4
// Project name: M5_clock

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void blink_Animation( lv_obj_t *TargetObject, int delay);
void pulse_Animation( lv_obj_t *TargetObject, int delay);
void ui_event_timeScreen( lv_event_t * e);
lv_obj_t *ui_timeScreen;
lv_obj_t *ui_timeLabel;
lv_obj_t *ui_dateText;
lv_obj_t *ui_batteryArc;
lv_obj_t *ui_chargeIcon;
lv_obj_t *ui_minuteText;
lv_obj_t *ui_hourText;
lv_obj_t *ui_cityText;
lv_obj_t *ui_tempText;
lv_obj_t *ui_weatherIcon;
void ui_event_messageScreen( lv_event_t * e);
lv_obj_t *ui_messageScreen;
lv_obj_t *ui_messageIcon;
lv_obj_t *ui_messageTitle;
lv_obj_t *ui_messageText;
lv_obj_t *ui_messageTime;
lv_obj_t *ui____initial_actions0;
const lv_img_dsc_t *ui_imgset_dy[8] = {&ui_img_dy0_png, &ui_img_dy1_png, &ui_img_dy2_png, &ui_img_dy3_png, &ui_img_dy4_png, &ui_img_dy5_png, &ui_img_dy6_png, &ui_img_dy7_png};
const lv_img_dsc_t *ui_imgset_nt[8] = {&ui_img_nt0_png, &ui_img_nt1_png, &ui_img_nt2_png, &ui_img_nt3_png, &ui_img_nt4_png, &ui_img_nt5_png, &ui_img_nt6_png, &ui_img_nt7_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void blink_Animation( lv_obj_t *TargetObject, int delay)
{
ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
PropertyAnimation_0_user_data->target = TargetObject;
PropertyAnimation_0_user_data->val = -1;
lv_anim_t PropertyAnimation_0;
lv_anim_init(&PropertyAnimation_0);
lv_anim_set_time(&PropertyAnimation_0, 100);
lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity );
lv_anim_set_values(&PropertyAnimation_0, 50, 255 );
lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_linear);
lv_anim_set_delay( &PropertyAnimation_0, delay + 900 );
lv_anim_set_deleted_cb( &PropertyAnimation_0, _ui_anim_callback_free_user_data );
lv_anim_set_playback_time(&PropertyAnimation_0, 1000);
lv_anim_set_playback_delay(&PropertyAnimation_0, 100);
lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE );
lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
lv_anim_set_early_apply( &PropertyAnimation_0, false );
lv_anim_start(&PropertyAnimation_0);

}
void pulse_Animation( lv_obj_t *TargetObject, int delay)
{
ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
PropertyAnimation_0_user_data->target = TargetObject;
PropertyAnimation_0_user_data->val = -1;
lv_anim_t PropertyAnimation_0;
lv_anim_init(&PropertyAnimation_0);
lv_anim_set_time(&PropertyAnimation_0, 500);
lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_zoom );
lv_anim_set_values(&PropertyAnimation_0, 256, 200 );
lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_linear);
lv_anim_set_delay( &PropertyAnimation_0, delay + 0 );
lv_anim_set_deleted_cb( &PropertyAnimation_0, _ui_anim_callback_free_user_data );
lv_anim_set_playback_time(&PropertyAnimation_0, 500);
lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE );
lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
lv_anim_set_early_apply( &PropertyAnimation_0, false );
lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_timeScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT  ) {
      _ui_screen_change( ui_messageScreen, LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0);
}
}
void ui_event_messageScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT  ) {
      _ui_screen_change( ui_timeScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
}
}

///////////////////// SCREENS ////////////////////
void ui_timeScreen_screen_init(void)
{
ui_timeScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_timeScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_timeScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_timeScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_timeLabel = lv_label_create(ui_timeScreen);
lv_obj_set_width( ui_timeLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_timeLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_timeLabel, -4 );
lv_obj_set_y( ui_timeLabel, -10 );
lv_obj_set_align( ui_timeLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_timeLabel,":");
lv_obj_set_style_text_color(ui_timeLabel, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_timeLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_timeLabel, &ui_font_semi100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_dateText = lv_label_create(ui_timeScreen);
lv_obj_set_width( ui_dateText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_dateText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_dateText, -41 );
lv_obj_set_y( ui_dateText, 85 );
lv_obj_set_align( ui_dateText, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_dateText,"16 MON");
lv_obj_set_style_text_color(ui_dateText, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_dateText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_dateText, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_batteryArc = lv_arc_create(ui_timeScreen);
lv_obj_set_width( ui_batteryArc, 50);
lv_obj_set_height( ui_batteryArc, 50);
lv_obj_set_x( ui_batteryArc, 100 );
lv_obj_set_y( ui_batteryArc, -84 );
lv_obj_set_align( ui_batteryArc, LV_ALIGN_CENTER );
lv_arc_set_value(ui_batteryArc, 59);
lv_arc_set_bg_angles(ui_batteryArc,180,179);
lv_obj_set_style_arc_color(ui_batteryArc, lv_color_hex(0x005131), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(ui_batteryArc, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(ui_batteryArc, 7, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_arc_color(ui_batteryArc, lv_color_hex(0x00BA71), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(ui_batteryArc, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(ui_batteryArc, 7, LV_PART_INDICATOR| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(ui_batteryArc, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_batteryArc, 0, LV_PART_KNOB| LV_STATE_DEFAULT);

ui_chargeIcon = lv_img_create(ui_timeScreen);
lv_img_set_src(ui_chargeIcon, &ui_img_bolt_png);
lv_obj_set_width( ui_chargeIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_chargeIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_chargeIcon, 100 );
lv_obj_set_y( ui_chargeIcon, -83 );
lv_obj_set_align( ui_chargeIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_chargeIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_chargeIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_chargeIcon, lv_color_hex(0x00BA71), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_chargeIcon, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_minuteText = lv_label_create(ui_timeScreen);
lv_obj_set_width( ui_minuteText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_minuteText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_minuteText, 172 );
lv_obj_set_y( ui_minuteText, 0 );
lv_obj_set_align( ui_minuteText, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_minuteText,"45");
lv_obj_set_style_text_color(ui_minuteText, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_minuteText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_minuteText, &ui_font_semi100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_hourText = lv_label_create(ui_timeScreen);
lv_obj_set_width( ui_hourText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_hourText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_hourText, -184 );
lv_obj_set_y( ui_hourText, 0 );
lv_obj_set_align( ui_hourText, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_hourText,"23");
lv_obj_set_style_text_color(ui_hourText, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_hourText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_hourText, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_hourText, &ui_font_semi100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_cityText = lv_label_create(ui_timeScreen);
lv_obj_set_width( ui_cityText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_cityText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_cityText, 31 );
lv_obj_set_y( ui_cityText, 26 );
lv_label_set_text(ui_cityText,"Nairobi");
lv_obj_set_style_text_color(ui_cityText, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_cityText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_cityText, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_tempText = lv_label_create(ui_timeScreen);
lv_obj_set_width( ui_tempText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_tempText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_tempText, 90 );
lv_obj_set_y( ui_tempText, 85 );
lv_obj_set_align( ui_tempText, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_tempText,"16C");
lv_obj_set_style_text_color(ui_tempText, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_tempText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_tempText, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_weatherIcon = lv_img_create(ui_timeScreen);
lv_img_set_src(ui_weatherIcon, &ui_img_dy2_png);
lv_obj_set_width( ui_weatherIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_weatherIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_weatherIcon, -110 );
lv_obj_set_y( ui_weatherIcon, -9 );
lv_obj_set_align( ui_weatherIcon, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_weatherIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_weatherIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_weatherIcon, lv_color_hex(0x00BA71), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_weatherIcon, 200, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_timeScreen, ui_event_timeScreen, LV_EVENT_ALL, NULL);

}
void ui_messageScreen_screen_init(void)
{
ui_messageScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_messageScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_messageScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_messageScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_messageIcon = lv_img_create(ui_messageScreen);
lv_img_set_src(ui_messageIcon, &ui_img_whatsapp_png);
lv_obj_set_width( ui_messageIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_messageIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_messageIcon, 11 );
lv_obj_set_y( ui_messageIcon, 10 );
lv_obj_add_flag( ui_messageIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_messageIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_messageTitle = lv_label_create(ui_messageScreen);
lv_obj_set_width( ui_messageTitle, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_messageTitle, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_messageTitle, 58 );
lv_obj_set_y( ui_messageTitle, 12 );
lv_label_set_text(ui_messageTitle,"Whatsapp");
lv_obj_set_style_text_color(ui_messageTitle, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_messageTitle, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_messageTitle, &lv_font_montserrat_26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_messageText = lv_label_create(ui_messageScreen);
lv_obj_set_width( ui_messageText, 300);
lv_obj_set_height( ui_messageText, 180);
lv_obj_set_align( ui_messageText, LV_ALIGN_BOTTOM_MID );
lv_label_set_text(ui_messageText,"This is an example of a notification received on the m5stack");
lv_obj_set_style_text_color(ui_messageText, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_messageText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_messageText, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_messageTime = lv_label_create(ui_messageScreen);
lv_obj_set_width( ui_messageTime, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_messageTime, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_messageTime, 0 );
lv_obj_set_y( ui_messageTime, -6 );
lv_obj_set_align( ui_messageTime, LV_ALIGN_BOTTOM_MID );
lv_label_set_text(ui_messageTime,"10:25");
lv_obj_set_style_text_color(ui_messageTime, lv_color_hex(0x00BA71), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_messageTime, 150, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_messageTime, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_messageScreen, ui_event_messageScreen, LV_EVENT_ALL, NULL);

}

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_timeScreen_screen_init();
ui_messageScreen_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_timeScreen);
}
