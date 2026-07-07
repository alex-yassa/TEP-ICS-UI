#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

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
    lv_obj_t *main;
    lv_obj_t *dashboard;
    
    // Splash screen components
    lv_obj_t *splash_obj0;
    lv_obj_t *splash_obj1;
    lv_obj_t *header;
    lv_obj_t *twerd_energo_plus_label;
    lv_obj_t *control_system_label;
    lv_obj_t *date_label;
    lv_obj_t *time_label;
    lv_obj_t *login_btn;
    lv_obj_t *lang_selector_button;
    lv_obj_t *selected_language_label;
    lv_obj_t *dropdown_lang;
    lv_obj_t *menu_panel;
    lv_obj_t *dashboard_button;
    lv_obj_t *view_1_button;
    lv_obj_t *view_2_button;
    lv_obj_t *gen_clusters_button;
    lv_obj_t *load_management_button;
    lv_obj_t *diagnostics_button;
    lv_obj_t *sys_settings_button;
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
    lv_obj_t *label_seventh_view;
    lv_obj_t *login_modal;
    lv_obj_t *login_card;
    lv_obj_t *login_title_label;
    lv_obj_t *login_user_dropdown;
    lv_obj_t *login_password_ta;
    lv_obj_t *login_cancel_btn;
    lv_obj_t *login_cancel_btn_label;
    lv_obj_t *login_signin_btn;
    lv_obj_t *login_signin_btn_label;
    lv_obj_t *pinpad_panel;
    lv_obj_t *pinpad_btn_1;
    lv_obj_t *pinpad_btn_2;
    lv_obj_t *pinpad_btn_3;
    lv_obj_t *pinpad_btn_4;
    lv_obj_t *pinpad_btn_5;
    lv_obj_t *pinpad_btn_6;
    lv_obj_t *pinpad_btn_7;
    lv_obj_t *pinpad_btn_8;
    lv_obj_t *pinpad_btn_9;
    lv_obj_t *pinpad_btn_clear;
    lv_obj_t *pinpad_btn_0;
    lv_obj_t *pinpad_btn_back;
    lv_obj_t *pinpad_btn_cancel;
    lv_obj_t *pinpad_btn_ok;
    lv_obj_t *obj0;
    lv_obj_t *pinpad_btn_dummy;
    lv_obj_t *keyboard_test;
    lv_obj_t *btn_left;
    lv_obj_t *btn_right;
    lv_obj_t *btn_up;
    lv_obj_t *btn_down;
    lv_obj_t *btn_backspace;
    lv_obj_t *btn_enter;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_dashboard();
void tick_screen_dashboard();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/