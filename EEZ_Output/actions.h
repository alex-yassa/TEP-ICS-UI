#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_dashboard_button_clicked(lv_event_t * e);
extern void action_view_1_button_clicked(lv_event_t * e);
extern void action_view_2_button_clicked(lv_event_t * e);
extern void action_gen_clusters_button_clicked(lv_event_t * e);
extern void action_load_management_button_clicked(lv_event_t * e);
extern void action_diagnostics_button_clicked(lv_event_t * e);
extern void action_sys_settings_button_clicked(lv_event_t * e);
extern void action_login_button_clicked(lv_event_t * e);
extern void action_signin_clicked(lv_event_t * e);
extern void action_cancel_login_clicked(lv_event_t * e);
extern void action_pinpad_ok_clicked(lv_event_t * e);
extern void action_pinpad_cancel_clicked(lv_event_t * e);
extern void action_pinpad_btn_pressed(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/