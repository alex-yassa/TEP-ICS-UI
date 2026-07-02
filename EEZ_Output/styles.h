#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: btn_menu_style
lv_style_t *get_style_btn_menu_style_MAIN_DEFAULT();
lv_style_t *get_style_btn_menu_style_MAIN_PRESSED();
lv_style_t *get_style_btn_menu_style_MAIN_FOCUSED();
void add_style_btn_menu_style(lv_obj_t *obj);
void remove_style_btn_menu_style(lv_obj_t *obj);

// Style: pannel_style
lv_style_t *get_style_pannel_style_MAIN_DEFAULT();
void add_style_pannel_style(lv_obj_t *obj);
void remove_style_pannel_style(lv_obj_t *obj);

// Style: tab_view_stayle
lv_style_t *get_style_tab_view_stayle_MAIN_DEFAULT();
void add_style_tab_view_stayle(lv_obj_t *obj);
void remove_style_tab_view_stayle(lv_obj_t *obj);

// Style: button_ico_container_style
lv_style_t *get_style_button_ico_container_style_MAIN_DEFAULT();
void add_style_button_ico_container_style(lv_obj_t *obj);
void remove_style_button_ico_container_style(lv_obj_t *obj);

// Style: ico-custom
lv_style_t *get_style_ico_custom_MAIN_DEFAULT();
lv_style_t *get_style_ico_custom_MAIN_FOCUSED();
void add_style_ico_custom(lv_obj_t *obj);
void remove_style_ico_custom(lv_obj_t *obj);

// Style: ico-big
lv_style_t *get_style_ico_big_MAIN_DEFAULT();
void add_style_ico_big(lv_obj_t *obj);
void remove_style_ico_big(lv_obj_t *obj);

// Style: btn-label
lv_style_t *get_style_btn_label_MAIN_DEFAULT();
lv_style_t *get_style_btn_label_MAIN_FOCUSED();
void add_style_btn_label(lv_obj_t *obj);
void remove_style_btn_label(lv_obj_t *obj);

// Style: pinpad_label
lv_style_t *get_style_pinpad_label_MAIN_DEFAULT();
void add_style_pinpad_label(lv_obj_t *obj);
void remove_style_pinpad_label(lv_obj_t *obj);

// Style: pinpad_btn
lv_style_t *get_style_pinpad_btn_MAIN_DEFAULT();
void add_style_pinpad_btn(lv_obj_t *obj);
void remove_style_pinpad_btn(lv_obj_t *obj);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/