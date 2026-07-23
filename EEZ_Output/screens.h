#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>
#include "ui_translate.h"
#ifndef _
#define _(str) translate(str, (lang_t)g_current_language)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_DASHBOARD = 2,
    _SCREEN_ID_LAST = 2
};

typedef struct _objects_t {
    lv_obj_t *dashboard;
    lv_obj_t *obj0;
    lv_obj_t *obj0__header_1;
    lv_obj_t *obj0__twerd_energo_plus_label_1;
    lv_obj_t *obj0__control_system_label_1;
    lv_obj_t *obj0__date_label_1;
    lv_obj_t *obj0__time_label_1;
    lv_obj_t *obj0__selected_language_label_1;
    lv_obj_t *obj0__obj1;
    lv_obj_t *menu_panel;
    lv_obj_t *dashboard_button;
    lv_obj_t *view_1_button;
    lv_obj_t *view_2_button;
    lv_obj_t *gen_clusters_button;
    lv_obj_t *load_management_button;
    lv_obj_t *diagnostics_button;
    lv_obj_t *sys_settings_button;
    lv_obj_t *login_btn;
    lv_obj_t *lang_selector_button;
    lv_obj_t *selected_language_label;
    lv_obj_t *tabview;
    lv_obj_t *obj7;
    lv_obj_t *obj6;
    lv_obj_t *tab1;
    lv_obj_t *label_dashboard_title;
    lv_obj_t *tab2;
    lv_obj_t *label_second_view;
    lv_obj_t *tab3;
    lv_obj_t *label_third_view;
    lv_obj_t *tab4;
    lv_obj_t *label_fourth_view;
    lv_obj_t *tab5;
    lv_obj_t *label_fifth_view;
    lv_obj_t *tab6;
    lv_obj_t *label_sixth_view;
    lv_obj_t *tab7;
    lv_obj_t *label_settings_title;
    lv_obj_t *label_row_0;
    lv_obj_t *settings_battery_count_ta;
    lv_obj_t *label_row_1;
    lv_obj_t *settings_pv_count_ta;
    lv_obj_t *label_row_2;
    lv_obj_t *settings_max_import_ta;
    lv_obj_t *label_row_3;
    lv_obj_t *settings_backup_soc_ta;
    lv_obj_t *label_row_4;
    lv_obj_t *settings_max_volt_ta;
    lv_obj_t *settings_next_btn;
    lv_obj_t *settings_next_btn_label;
    lv_obj_t *settings_apply_btn;
    lv_obj_t *settings_apply_btn_label;
    lv_obj_t *settings_reset_btn;
    lv_obj_t *settings_reset_btn_label;
    lv_obj_t *tab8;
    lv_obj_t *label_settings_title_2;
    lv_obj_t *label_row_5;
    lv_obj_t *settings_min_volt_ta;
    lv_obj_t *label_row_6;
    lv_obj_t *settings_cos_phi_ta;
    lv_obj_t *label_row_7;
    lv_obj_t *settings_nom_volt_ta;
    lv_obj_t *label_row_8;
    lv_obj_t *settings_nom_freq_ta;
    lv_obj_t *settings_prev_btn_2;
    lv_obj_t *settings_prev_btn_2_label;
    lv_obj_t *settings_next_btn_2;
    lv_obj_t *settings_next_btn_2_label;
    lv_obj_t *settings_apply_btn_2;
    lv_obj_t *settings_apply_btn_label_2;
    lv_obj_t *settings_reset_btn_2;
    lv_obj_t *settings_reset_btn_label_2;
    lv_obj_t *tab9;
    lv_obj_t *label_settings_title_3;
    lv_obj_t *label_fake_row_0;
    lv_obj_t *fake_settings_ta_0;
    lv_obj_t *label_fake_row_1;
    lv_obj_t *fake_settings_ta_1;
    lv_obj_t *label_fake_row_2;
    lv_obj_t *fake_settings_ta_2;
    lv_obj_t *label_fake_row_3;
    lv_obj_t *fake_settings_ta_3;
    lv_obj_t *label_fake_row_4;
    lv_obj_t *fake_settings_ta_4;
    lv_obj_t *label_fake_row_5;
    lv_obj_t *fake_settings_ta_5;
    lv_obj_t *settings_prev_btn_3;
    lv_obj_t *settings_prev_btn_3_label;
    lv_obj_t *settings_apply_btn_3;
    lv_obj_t *settings_apply_btn_label_3;
    lv_obj_t *settings_reset_btn_3;
    lv_obj_t *settings_reset_btn_label_3;
    lv_obj_t *obj1;
    lv_obj_t *obj1__login_modal_1;
    lv_obj_t *obj1__login_card_1;
    lv_obj_t *obj1__login_title_label_1;
    lv_obj_t *obj1__login_user_dropdown_1;
    lv_obj_t *obj1__login_password_ta_1;
    lv_obj_t *obj1__login_cancel_btn_1;
    lv_obj_t *obj1__login_cancel_btn_label_1;
    lv_obj_t *obj1__login_signin_btn_1;
    lv_obj_t *obj1__login_signin_btn_label_1;
    lv_obj_t *obj2;
    lv_obj_t *obj2__pinpad_panel_1;
    lv_obj_t *obj2__pinpad_btn_10;
    lv_obj_t *obj2__pinpad_btn_11;
    lv_obj_t *obj2__pinpad_btn_12;
    lv_obj_t *obj2__pinpad_btn_13;
    lv_obj_t *obj2__pinpad_btn_14;
    lv_obj_t *obj2__pinpad_btn_15;
    lv_obj_t *obj2__pinpad_btn_16;
    lv_obj_t *obj2__pinpad_btn_17;
    lv_obj_t *obj2__pinpad_btn_18;
    lv_obj_t *obj2__pinpad_btn_clear_1;
    lv_obj_t *obj2__pinpad_btn_19;
    lv_obj_t *obj2__pinpad_btn_back_1;
    lv_obj_t *obj2__pinpad_btn_cancel_1;
    lv_obj_t *obj2__pinpad_btn_ok_1;
    lv_obj_t *obj2__obj0;
    lv_obj_t *obj2__pinpad_btn_dummy_1;
    lv_obj_t *obj3;
    lv_obj_t *obj3__obj2;
    lv_obj_t *obj3__view_2_button_1;
    lv_obj_t *obj3__view_2_button_2;
    lv_obj_t *obj3__view_2_button_3;
    lv_obj_t *keyboard_test;
    lv_obj_t *btn_left;
    lv_obj_t *btn_right;
    lv_obj_t *btn_up;
    lv_obj_t *btn_down;
    lv_obj_t *btn_backspace;
    lv_obj_t *btn_enter;
    lv_obj_t *btn_v_2;
    lv_obj_t *btn_v_3;
    lv_obj_t *btn_v_4;
    lv_obj_t *btn_v_5;
    lv_obj_t *btn_g_1;
    lv_obj_t *btn_g_2;
    lv_obj_t *btn_g_3;
    lv_obj_t *btn_g_4;
    lv_obj_t *btn_g_5;
    lv_obj_t *btn_g_6;
    lv_obj_t *btn_g_7;
    lv_obj_t *btn_g_8;
    lv_obj_t *btn_g_9;
    lv_obj_t *btn_g_10;
    lv_obj_t *dropdown_lang;
    lv_obj_t *main;
    lv_obj_t *splash_obj0;
    lv_obj_t *splash_obj1;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_dashboard();
void tick_screen_dashboard();

void create_user_widget_login_window(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_login_window(int startWidgetIndex);

void create_user_widget_pinpad(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_pinpad(int startWidgetIndex);

void create_user_widget_header(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_header(int startWidgetIndex);

void create_user_widget_language_selector(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_language_selector(int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif


#define header                      obj0__header_1
#define twerd_energo_plus_label     obj0__twerd_energo_plus_label_1
#define control_system_label        obj0__control_system_label_1
#define date_label                  obj0__date_label_1
#define time_label                  obj0__time_label_1
#define login_modal                 obj1__login_modal_1
#define login_card                  obj1__login_card_1
#define login_title_label           obj1__login_title_label_1
#define login_user_dropdown         obj1__login_user_dropdown_1
#define login_password_ta           obj1__login_password_ta_1
#define login_cancel_btn            obj1__login_cancel_btn_1
#define login_cancel_btn_label      obj1__login_cancel_btn_label_1
#define login_signin_btn            obj1__login_signin_btn_1
#define login_signin_btn_label      obj1__login_signin_btn_label_1
#define pinpad_panel                obj2__pinpad_panel_1
#define pinpad_btn_1                obj2__pinpad_btn_10
#define pinpad_btn_2                obj2__pinpad_btn_11
#define pinpad_btn_3                obj2__pinpad_btn_12
#define pinpad_btn_4                obj2__pinpad_btn_13
#define pinpad_btn_5                obj2__pinpad_btn_14
#define pinpad_btn_6                obj2__pinpad_btn_15
#define pinpad_btn_7                obj2__pinpad_btn_16
#define pinpad_btn_8                obj2__pinpad_btn_17
#define pinpad_btn_9                obj2__pinpad_btn_18
#define pinpad_btn_clear            obj2__pinpad_btn_clear_1
#define pinpad_btn_0                obj2__pinpad_btn_19
#define pinpad_btn_back             obj2__pinpad_btn_back_1
#define pinpad_btn_cancel           obj2__pinpad_btn_cancel_1
#define pinpad_btn_ok               obj2__pinpad_btn_ok_1
#define pinpad_btn_dummy            obj2__pinpad_btn_dummy_1

#endif /*EEZ_LVGL_UI_SCREENS_H*/