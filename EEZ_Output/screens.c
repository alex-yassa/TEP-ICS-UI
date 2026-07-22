#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_dashboard() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.dashboard = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            // header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_pannel_style(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x121212), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // twerd-energo-plus-label
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.twerd_energo_plus_label = obj;
                    lv_obj_set_pos(obj, -13, -13);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_twerd_energo_plus_logo_h34);
                    lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_img_recolor(obj, lv_color_hex(0xd3d3d3), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // control-system-label
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.control_system_label = obj;
                    lv_obj_set_pos(obj, 208, -19);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_control_system_label_alpha);
                }
                {
                    // date_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.date_label = obj;
                    lv_obj_set_pos(obj, 474, -5);
                    lv_obj_set_size(obj, 117, 21);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xf1f5f9), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // time_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label = obj;
                    lv_obj_set_pos(obj, 597, -5);
                    lv_obj_set_size(obj, 82, 20);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xf1f5f9), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // login_btn
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.login_btn = obj;
                    lv_obj_set_pos(obj, 687, -11);
                    lv_obj_set_size(obj, 100, 30);
                    lv_obj_add_event_cb(obj, action_login_button_clicked, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    add_style_btn_menu_style(obj);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, "1");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 876, -6);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Login...");
                        }
                    }
                }
                {
                    // lang_selector_button
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.lang_selector_button = obj;
                    lv_obj_set_pos(obj, 928, -13);
                    lv_obj_set_size(obj, 56, 34);
                    add_style_btn_menu_style(obj);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, "L");
                        }
                        {
                            // selected_language_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.selected_language_label = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "EN");
                        }
                    }
                }
            }
        }
        {
            // dropdown_lang
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.dropdown_lang = obj;
            lv_obj_set_pos(obj, 950, 46);
            lv_obj_set_size(obj, 0, 0);
            lv_dropdown_set_options_static(obj, "PL\nEN\nUA");
            lv_dropdown_set_selected(obj, 0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x212121), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // menu-panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.menu_panel = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 176, 554);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_pannel_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dashboard-button
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.dashboard_button = obj;
                    lv_obj_set_pos(obj, -13, 10);
                    lv_obj_set_size(obj, 162, 28);
                    lv_obj_add_event_cb(obj, action_dashboard_button_clicked, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    lv_obj_add_state(obj, LV_STATE_FOCUSED);
                    add_style_btn_menu_style(obj);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_FOCUSED);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_FOCUSED);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_FOCUSED);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, "W");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -28, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Dashboard");
                        }
                    }
                }
                {
                    // view-1-button
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.view_1_button = obj;
                    lv_obj_set_pos(obj, -13, 44);
                    lv_obj_set_size(obj, 162, 26);
                    lv_obj_add_event_cb(obj, action_view_1_button_clicked, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    add_style_btn_menu_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, "N");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Grid");
                        }
                    }
                }
                {
                    // view-2-button
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.view_2_button = obj;
                    lv_obj_set_pos(obj, -13, 75);
                    lv_obj_set_size(obj, 162, 26);
                    lv_obj_add_event_cb(obj, action_view_2_button_clicked, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    add_style_btn_menu_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, ";");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Storage clusters");
                        }
                    }
                }
                {
                    // gen-clusters-button
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.gen_clusters_button = obj;
                    lv_obj_set_pos(obj, -13, 106);
                    lv_obj_set_size(obj, 162, 26);
                    lv_obj_add_event_cb(obj, action_gen_clusters_button_clicked, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    add_style_btn_menu_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, "V");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Gen clusters");
                        }
                    }
                }
                {
                    // load-management-button
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.load_management_button = obj;
                    lv_obj_set_pos(obj, -13, 137);
                    lv_obj_set_size(obj, 162, 26);
                    lv_obj_add_event_cb(obj, action_load_management_button_clicked, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    add_style_btn_menu_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, "A");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Load Management");
                        }
                    }
                }
                {
                    // diagnostics-button
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.diagnostics_button = obj;
                    lv_obj_set_pos(obj, -13, 168);
                    lv_obj_set_size(obj, 162, 26);
                    lv_obj_add_event_cb(obj, action_diagnostics_button_clicked, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    add_style_btn_menu_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, "M");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Diagnostics");
                        }
                    }
                }
                {
                    // sys-settings-button
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.sys_settings_button = obj;
                    lv_obj_set_pos(obj, -13, 199);
                    lv_obj_set_size(obj, 162, 26);
                    lv_obj_add_event_cb(obj, action_sys_settings_button_clicked, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    add_style_btn_menu_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_label_set_text_static(obj, "P");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Sys settings");
                        }
                    }
                }
            }
        }
        {
            // tabview
            lv_obj_t *obj = lv_tabview_create(parent_obj, LV_DIR_LEFT, 0);
            objects.tabview = obj;
            lv_obj_set_pos(obj, 176, 46);
            lv_obj_set_size(obj, 848, 554);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_tab_view_stayle(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x121212), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0x565656), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // obj7
                    lv_obj_t *obj = lv_tabview_get_tab_btns(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // obj6
                    lv_obj_t *obj = lv_tabview_get_content(parent_obj);
                    objects.obj6 = obj;
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // tab1
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab1");
                            objects.tab1 = obj;
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_dashboard_title
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_dashboard_title = obj;
                                    lv_obj_set_pos(obj, 49, 47);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Dashboard view");
                                }
                            }
                        }
                        {
                            // tab2
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab2");
                            objects.tab2 = obj;
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_second_view
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_second_view = obj;
                                    lv_obj_set_pos(obj, 36, 54);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text_static(obj, "Grid view");
                                }
                            }
                        }
                        {
                            // tab3
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab3");
                            objects.tab3 = obj;
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_third_view
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_third_view = obj;
                                    lv_obj_set_pos(obj, 36, 54);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text_static(obj, "Storage clusters view");
                                }
                            }
                        }
                        {
                            // tab4
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab4");
                            objects.tab4 = obj;
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_fourth_view
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_fourth_view = obj;
                                    lv_obj_set_pos(obj, 36, 54);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text_static(obj, "Gen Clusters View");
                                }
                            }
                        }
                        {
                            // tab5
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab5");
                            objects.tab5 = obj;
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_fifth_view
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_fifth_view = obj;
                                    lv_obj_set_pos(obj, 36, 54);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text_static(obj, "Load Management View");
                                }
                            }
                        }
                        {
                            // tab6
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab6");
                            objects.tab6 = obj;
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_sixth_view
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_sixth_view = obj;
                                    lv_obj_set_pos(obj, 36, 54);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text_static(obj, "Diagnostics View");
                                }
                            }
                        }
                        {
                            // tab7
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab7");
                            objects.tab7 = obj;
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_settings_title
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_settings_title = obj;
                                    lv_obj_set_pos(obj, 40, 20);
                                    lv_obj_set_size(obj, 300, 40);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xf8fafc), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "SYSTEM CONFIGURATION (1/3)");
                                }
                                {
                                    // label_row_0
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_0 = obj;
                                    lv_obj_set_pos(obj, 40, 84);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Battery Clusters Count (Max 2)");
                                }
                                {
                                    // settings_battery_count_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_battery_count_ta = obj;
                                    lv_obj_set_pos(obj, 390, 80);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "2");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_row_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_1 = obj;
                                    lv_obj_set_pos(obj, 40, 134);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "PV Clusters Count (Max 2)");
                                }
                                {
                                    // settings_pv_count_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_pv_count_ta = obj;
                                    lv_obj_set_pos(obj, 390, 130);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "2");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_row_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_2 = obj;
                                    lv_obj_set_pos(obj, 40, 184);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Peak Shaving Import Limit (kW)");
                                }
                                {
                                    // settings_max_import_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_max_import_ta = obj;
                                    lv_obj_set_pos(obj, 390, 180);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "25.0");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_row_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_3 = obj;
                                    lv_obj_set_pos(obj, 40, 234);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Backup Battery SoC Threshold (%)");
                                }
                                {
                                    // settings_backup_soc_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_backup_soc_ta = obj;
                                    lv_obj_set_pos(obj, 390, 230);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "30.0");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_row_4
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_4 = obj;
                                    lv_obj_set_pos(obj, 40, 284);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Battery Max Charge Voltage (V)");
                                }
                                {
                                    // settings_max_volt_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_max_volt_ta = obj;
                                    lv_obj_set_pos(obj, 390, 280);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "58.4");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // settings_next_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_next_btn = obj;
                                    lv_obj_set_pos(obj, 40, 465);
                                    lv_obj_set_size(obj, 150, 40);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_next_btn_label
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_next_btn_label = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 150, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "Next >");
                                        }
                                    }
                                }
                                {
                                    // settings_apply_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_apply_btn = obj;
                                    lv_obj_set_pos(obj, 390, 465);
                                    lv_obj_set_size(obj, 180, 40);
                                    lv_obj_add_event_cb(obj, action_settings_apply_clicked, LV_EVENT_CLICKED, (void *)0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_apply_btn_label
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_apply_btn_label = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 180, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "Apply");
                                        }
                                    }
                                }
                                {
                                    // settings_reset_btn
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_reset_btn = obj;
                                    lv_obj_set_pos(obj, 590, 465);
                                    lv_obj_set_size(obj, 180, 40);
                                    lv_obj_add_event_cb(obj, action_settings_reset_clicked, LV_EVENT_CLICKED, (void *)0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_reset_btn_label
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_reset_btn_label = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 180, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "Reset Changes");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // tab8
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab8");
                            objects.tab8 = obj;
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_settings_title_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_settings_title_2 = obj;
                                    lv_obj_set_pos(obj, 40, 20);
                                    lv_obj_set_size(obj, 300, 40);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xf8fafc), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "SYSTEM CONFIGURATION (2/3)");
                                }
                                {
                                    // label_row_5
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_5 = obj;
                                    lv_obj_set_pos(obj, 40, 84);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Battery Min Discharge Voltage (V)");
                                }
                                {
                                    // settings_min_volt_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_min_volt_ta = obj;
                                    lv_obj_set_pos(obj, 390, 80);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "44.0");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_row_6
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_6 = obj;
                                    lv_obj_set_pos(obj, 40, 134);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "STATCOM Target Power Factor (cos phi)");
                                }
                                {
                                    // settings_cos_phi_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_cos_phi_ta = obj;
                                    lv_obj_set_pos(obj, 390, 130);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "0.98");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_row_7
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_7 = obj;
                                    lv_obj_set_pos(obj, 40, 184);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Nominal Grid Voltage (V)");
                                }
                                {
                                    // settings_nom_volt_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_nom_volt_ta = obj;
                                    lv_obj_set_pos(obj, 390, 180);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "230");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_row_8
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_row_8 = obj;
                                    lv_obj_set_pos(obj, 40, 234);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xcbd5e1), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Nominal Grid Frequency (Hz)");
                                }
                                {
                                    // settings_nom_freq_ta
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.settings_nom_freq_ta = obj;
                                    lv_obj_set_pos(obj, 390, 230);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "50");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // settings_prev_btn_2
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_prev_btn_2 = obj;
                                    lv_obj_set_pos(obj, 40, 465);
                                    lv_obj_set_size(obj, 150, 40);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_prev_btn_2_label
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_prev_btn_2_label = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 150, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "< Prev");
                                        }
                                    }
                                }
                                {
                                    // settings_next_btn_2
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_next_btn_2 = obj;
                                    lv_obj_set_pos(obj, 210, 465);
                                    lv_obj_set_size(obj, 150, 40);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_next_btn_2_label
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_next_btn_2_label = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 150, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "Next >");
                                        }
                                    }
                                }
                                {
                                    // settings_apply_btn_2
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_apply_btn_2 = obj;
                                    lv_obj_set_pos(obj, 390, 465);
                                    lv_obj_set_size(obj, 180, 40);
                                    lv_obj_add_event_cb(obj, action_settings_apply_clicked, LV_EVENT_CLICKED, (void *)0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_apply_btn_label_2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_apply_btn_label_2 = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 180, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "Apply");
                                        }
                                    }
                                }
                                {
                                    // settings_reset_btn_2
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_reset_btn_2 = obj;
                                    lv_obj_set_pos(obj, 590, 465);
                                    lv_obj_set_size(obj, 180, 40);
                                    lv_obj_add_event_cb(obj, action_settings_reset_clicked, LV_EVENT_CLICKED, (void *)0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_reset_btn_label_2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_reset_btn_label_2 = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 180, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "Reset Changes");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // tab9
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "tab9");
                            objects.tab9 = obj;
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_settings_title_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_settings_title_3 = obj;
                                    lv_obj_set_pos(obj, 40, 20);
                                    lv_obj_set_size(obj, 300, 40);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xf8fafc), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "SYSTEM CONFIGURATION (3/3)");
                                }
                                {
                                    // label_fake_row_0
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_fake_row_0 = obj;
                                    lv_obj_set_pos(obj, 40, 84);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Fake Test Parameter 1");
                                }
                                {
                                    // fake_settings_ta_0
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.fake_settings_ta_0 = obj;
                                    lv_obj_set_pos(obj, 390, 80);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "2");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x334155), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_fake_row_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_fake_row_1 = obj;
                                    lv_obj_set_pos(obj, 40, 134);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Fake Test Parameter 2");
                                }
                                {
                                    // fake_settings_ta_1
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.fake_settings_ta_1 = obj;
                                    lv_obj_set_pos(obj, 390, 130);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "2");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x334155), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_fake_row_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_fake_row_2 = obj;
                                    lv_obj_set_pos(obj, 40, 184);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Fake Test Parameter 3");
                                }
                                {
                                    // fake_settings_ta_2
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.fake_settings_ta_2 = obj;
                                    lv_obj_set_pos(obj, 390, 180);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "2");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x334155), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_fake_row_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_fake_row_3 = obj;
                                    lv_obj_set_pos(obj, 40, 234);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Fake Test Parameter 4");
                                }
                                {
                                    // fake_settings_ta_3
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.fake_settings_ta_3 = obj;
                                    lv_obj_set_pos(obj, 390, 230);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "2");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x334155), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_fake_row_4
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_fake_row_4 = obj;
                                    lv_obj_set_pos(obj, 40, 284);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Fake Test Parameter 5");
                                }
                                {
                                    // fake_settings_ta_4
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.fake_settings_ta_4 = obj;
                                    lv_obj_set_pos(obj, 390, 280);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "2");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x334155), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // label_fake_row_5
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_fake_row_5 = obj;
                                    lv_obj_set_pos(obj, 40, 334);
                                    lv_obj_set_size(obj, 340, 30);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Fake Test Parameter 6");
                                }
                                {
                                    // fake_settings_ta_5
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.fake_settings_ta_5 = obj;
                                    lv_obj_set_pos(obj, 390, 330);
                                    lv_obj_set_size(obj, 180, 34);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_placeholder_text(obj, "2");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0x334155), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // settings_prev_btn_3
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_prev_btn_3 = obj;
                                    lv_obj_set_pos(obj, 40, 465);
                                    lv_obj_set_size(obj, 150, 40);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_prev_btn_3_label
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_prev_btn_3_label = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 150, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "< Prev");
                                        }
                                    }
                                }
                                {
                                    // settings_apply_btn_3
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_apply_btn_3 = obj;
                                    lv_obj_set_pos(obj, 390, 465);
                                    lv_obj_set_size(obj, 180, 40);
                                    lv_obj_add_event_cb(obj, action_settings_apply_clicked, LV_EVENT_CLICKED, (void *)0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_apply_btn_label_3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_apply_btn_label_3 = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 180, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "Apply");
                                        }
                                    }
                                }
                                {
                                    // settings_reset_btn_3
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_reset_btn_3 = obj;
                                    lv_obj_set_pos(obj, 590, 465);
                                    lv_obj_set_size(obj, 180, 40);
                                    lv_obj_add_event_cb(obj, action_settings_reset_clicked, LV_EVENT_CLICKED, (void *)0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    add_style_btn_menu_style(obj);
                                    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_reset_btn_label_3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_reset_btn_label_3 = obj;
                                            lv_obj_set_pos(obj, 0, 10);
                                            lv_obj_set_size(obj, 180, 18);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text_static(obj, "Reset Changes");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 600);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_login_window(obj, 90);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 740, 180);
            lv_obj_set_size(obj, 1499, 260);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_pinpad(obj, 100);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        {
            // keyboard-test
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.keyboard_test = obj;
            lv_obj_set_pos(obj, 64, 1);
            lv_obj_set_size(obj, 1024, 600);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // btn-left
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_left = obj;
                    lv_obj_set_pos(obj, 752, 425);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "5");
                        }
                    }
                }
                {
                    // btn-right
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_right = obj;
                    lv_obj_set_pos(obj, 886, 423);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "6");
                        }
                    }
                }
                {
                    // btn-up
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_up = obj;
                    lv_obj_set_pos(obj, 821, 360);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "7");
                        }
                    }
                }
                {
                    // btn-down
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_down = obj;
                    lv_obj_set_pos(obj, 821, 488);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "4");
                        }
                    }
                }
                {
                    // btn-backspace
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_backspace = obj;
                    lv_obj_set_pos(obj, 817, 43);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "X");
                        }
                    }
                }
                {
                    // btn-enter
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_enter = obj;
                    lv_obj_set_pos(obj, 821, 425);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Z");
                        }
                    }
                }
                {
                    // btn-v_2
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_v_2 = obj;
                    lv_obj_set_pos(obj, 818, 111);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "V2");
                        }
                    }
                }
                {
                    // btn-v_3
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_v_3 = obj;
                    lv_obj_set_pos(obj, 819, 168);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "V3");
                        }
                    }
                }
                {
                    // btn-v_4
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_v_4 = obj;
                    lv_obj_set_pos(obj, 820, 226);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "V4");
                        }
                    }
                }
                {
                    // btn-v_5
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_v_5 = obj;
                    lv_obj_set_pos(obj, 819, 287);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "V5");
                        }
                    }
                }
                {
                    // btn-g_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_1 = obj;
                    lv_obj_set_pos(obj, 8, 426);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G1");
                        }
                    }
                }
                {
                    // btn-g_2
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_2 = obj;
                    lv_obj_set_pos(obj, 72, 427);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G2");
                        }
                    }
                }
                {
                    // btn-g_3
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_3 = obj;
                    lv_obj_set_pos(obj, 133, 428);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G3");
                        }
                    }
                }
                {
                    // btn-g_4
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_4 = obj;
                    lv_obj_set_pos(obj, 195, 429);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G4");
                        }
                    }
                }
                {
                    // btn-g_5
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_5 = obj;
                    lv_obj_set_pos(obj, 258, 428);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G5");
                        }
                    }
                }
                {
                    // btn-g_6
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_6 = obj;
                    lv_obj_set_pos(obj, 343, 430);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G6");
                        }
                    }
                }
                {
                    // btn-g_7
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_7 = obj;
                    lv_obj_set_pos(obj, 403, 430);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G7");
                        }
                    }
                }
                {
                    // btn-g_8
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_8 = obj;
                    lv_obj_set_pos(obj, 465, 431);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G8");
                        }
                    }
                }
                {
                    // btn-g_9
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_9 = obj;
                    lv_obj_set_pos(obj, 525, 433);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G9");
                        }
                    }
                }
                {
                    // btn-g_10
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_g_10 = obj;
                    lv_obj_set_pos(obj, 586, 434);
                    lv_obj_set_size(obj, 50, 50);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x016800), LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "G10");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_dashboard();
}

void tick_screen_dashboard() {
    {
        const char *new_val = get_var_header_date();
        const char *cur_val = lv_label_get_text(objects.date_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.date_label;
            lv_label_set_text(objects.date_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_header_time();
        const char *cur_val = lv_label_get_text(objects.time_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.time_label;
            lv_label_set_text(objects.time_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_login_window(90);
    tick_user_widget_pinpad(100);
}

void create_user_widget_login_window(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // login_modal_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 600);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // login_card_1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 282, 160);
                    lv_obj_set_size(obj, 420, 240);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x1e293b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0x3b82f6), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // login_title_label_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                            lv_obj_set_pos(obj, -22, -13);
                            lv_obj_set_size(obj, 420, 22);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "USER SIGN IN");
                        }
                        {
                            // login_user_dropdown_1
                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 38, 45);
                            lv_obj_set_size(obj, 300, LV_SIZE_CONTENT);
                            lv_dropdown_set_options_static(obj, "admin\noperator\nviewer");
                            lv_dropdown_set_selected(obj, 0);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // login_password_ta_1
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                            lv_obj_set_pos(obj, 38, 95);
                            lv_obj_set_size(obj, 300, 40);
                            lv_textarea_set_max_length(obj, 128);
                            lv_textarea_set_placeholder_text(obj, "Enter Password");
                            lv_textarea_set_one_line(obj, false);
                            lv_textarea_set_password_mode(obj, true);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // login_cancel_btn_1
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 40, 155);
                            lv_obj_set_size(obj, 130, 35);
                            lv_obj_add_event_cb(obj, action_cancel_login_clicked, LV_EVENT_CLICKED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x64748b), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // login_cancel_btn_label_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                                    lv_obj_set_pos(obj, -20, -2);
                                    lv_obj_set_size(obj, 130, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Cancel");
                                }
                            }
                        }
                        {
                            // login_signin_btn_1
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                            lv_obj_set_pos(obj, 208, 156);
                            lv_obj_set_size(obj, 130, 35);
                            lv_obj_add_event_cb(obj, action_signin_clicked, LV_EVENT_CLICKED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x22c55e), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // login_signin_btn_label_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                                    lv_obj_set_pos(obj, -20, -2);
                                    lv_obj_set_size(obj, 130, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text_static(obj, "Sign In");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_login_window(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void create_user_widget_pinpad(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // pinpad_panel_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 184, 258);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x121212), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_GRID, LV_PART_MAIN | LV_STATE_FOCUSED);
            {
                static lv_coord_t dsc[] = {50, 50, 50, 50, 50, LV_GRID_TEMPLATE_LAST};
                lv_obj_set_style_grid_row_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
            {
                static lv_coord_t dsc[] = {60, 60, 60, LV_GRID_TEMPLATE_LAST};
                lv_obj_set_style_grid_column_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
            {
                lv_obj_t *parent_obj = obj;
                {
                    // pinpad_btn_10
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 3, 2);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "1");
                        }
                    }
                }
                {
                    // pinpad_btn_11
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 63, 2);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "2");
                        }
                    }
                }
                {
                    // pinpad_btn_12
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 123, 2);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "3");
                        }
                    }
                }
                {
                    // pinpad_btn_13
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                    lv_obj_set_pos(obj, 3, 52);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "4");
                        }
                    }
                }
                {
                    // pinpad_btn_14
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                    lv_obj_set_pos(obj, 63, 52);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "5");
                        }
                    }
                }
                {
                    // pinpad_btn_15
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                    lv_obj_set_pos(obj, 123, 52);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "6");
                        }
                    }
                }
                {
                    // pinpad_btn_16
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                    lv_obj_set_pos(obj, 3, 102);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "7");
                        }
                    }
                }
                {
                    // pinpad_btn_17
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                    lv_obj_set_pos(obj, 63, 102);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "8");
                        }
                    }
                }
                {
                    // pinpad_btn_18
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                    lv_obj_set_pos(obj, 123, 102);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "9");
                        }
                    }
                }
                {
                    // pinpad_btn_clear_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                    lv_obj_set_pos(obj, 3, 152);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "[");
                        }
                    }
                }
                {
                    // pinpad_btn_19
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                    lv_obj_set_pos(obj, 63, 152);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "0");
                        }
                    }
                }
                {
                    // pinpad_btn_back_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                    lv_obj_set_pos(obj, 123, 152);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_btn_pressed, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "X");
                        }
                    }
                }
                {
                    // pinpad_btn_cancel_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 13] = obj;
                    lv_obj_set_pos(obj, 3, 202);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_cancel_clicked, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Y");
                        }
                    }
                }
                {
                    // pinpad_btn_ok_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 14] = obj;
                    lv_obj_set_pos(obj, 63, 202);
                    lv_obj_set_size(obj, 54, 46);
                    lv_obj_add_event_cb(obj, action_pinpad_ok_clicked, LV_EVENT_CLICKED, (void *)0);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 15] = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_ico_custom(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x22b100), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "Z");
                        }
                    }
                }
                {
                    // pinpad_btn_dummy_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 16] = obj;
                    lv_obj_set_pos(obj, 123, 202);
                    lv_obj_set_size(obj, 54, 46);
                    add_style_pinpad_btn(obj);
                    lv_obj_set_style_grid_cell_column_pos(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_row_pos(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_x_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_grid_cell_y_align(obj, LV_GRID_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_pinpad_label(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, " ");
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_pinpad(int startWidgetIndex) {
    (void)startWidgetIndex;
}

extern const lv_img_dsc_t img_splash_logo;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.splash_obj0 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 600);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x030088), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.splash_obj1 = obj;
            lv_obj_set_pos(obj, 306, 265);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_splash_logo);
            lv_obj_set_style_img_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_dashboard,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 2) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "ico-big", &ui_font_ico_big },
    { "ico-custom", &ui_font_ico_custom },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
    create_screen_dashboard();
}