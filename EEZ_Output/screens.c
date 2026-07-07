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
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -4252, 0);
                            lv_obj_set_size(obj, 32, 24);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            add_style_button_ico_container_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_ico_custom(obj);
                                    lv_label_set_text_static(obj, "W");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -28, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
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
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -4252, 0);
                            lv_obj_set_size(obj, 32, 24);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            add_style_button_ico_container_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_ico_custom(obj);
                                    lv_label_set_text_static(obj, "N");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
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
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -4290, 64);
                            lv_obj_set_size(obj, 32, 24);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            add_style_button_ico_container_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_ico_custom(obj);
                                    lv_label_set_text_static(obj, ";");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
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
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -4290, 64);
                            lv_obj_set_size(obj, 32, 24);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            add_style_button_ico_container_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_ico_custom(obj);
                                    lv_label_set_text_static(obj, "V");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
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
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -4290, 64);
                            lv_obj_set_size(obj, 32, 24);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            add_style_button_ico_container_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_ico_custom(obj);
                                    lv_label_set_text_static(obj, "A");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
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
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -4290, 64);
                            lv_obj_set_size(obj, 32, 24);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            add_style_button_ico_container_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_ico_custom(obj);
                                    lv_label_set_text_static(obj, "M");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
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
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -4290, 64);
                            lv_obj_set_size(obj, 32, 24);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            add_style_button_ico_container_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    add_style_ico_custom(obj);
                                    lv_label_set_text_static(obj, "P");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, -5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_btn_label(obj);
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
                                    // label_seventh_view
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_seventh_view = obj;
                                    lv_obj_set_pos(obj, 36, 54);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text_static(obj, "Sys Settings View");
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // login_modal
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.login_modal = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 600);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // login_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.login_card = obj;
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
                            // login_title_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.login_title_label = obj;
                            lv_obj_set_pos(obj, -22, -13);
                            lv_obj_set_size(obj, 420, 22);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text_static(obj, "USER SIGN IN");
                        }
                        {
                            // login_user_dropdown
                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                            objects.login_user_dropdown = obj;
                            lv_obj_set_pos(obj, 38, 45);
                            lv_obj_set_size(obj, 300, LV_SIZE_CONTENT);
                            lv_dropdown_set_options_static(obj, "admin\noperator\nviewer");
                            lv_dropdown_set_selected(obj, 0);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0x0f172a), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0x475569), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // login_password_ta
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.login_password_ta = obj;
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
                            // login_cancel_btn
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.login_cancel_btn = obj;
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
                                    // login_cancel_btn_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.login_cancel_btn_label = obj;
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
                            // login_signin_btn
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.login_signin_btn = obj;
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
                                    // login_signin_btn_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.login_signin_btn_label = obj;
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
                {
                    // pinpad_panel
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.pinpad_panel = obj;
                    lv_obj_set_pos(obj, 732, 157);
                    lv_obj_set_size(obj, 184, 258);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0x3b82f6), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0x121212), LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            // pinpad_btn_1
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_1 = obj;
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
                            // pinpad_btn_2
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_2 = obj;
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
                            // pinpad_btn_3
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_3 = obj;
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
                            // pinpad_btn_4
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_4 = obj;
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
                            // pinpad_btn_5
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_5 = obj;
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
                            // pinpad_btn_6
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_6 = obj;
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
                            // pinpad_btn_7
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_7 = obj;
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
                            // pinpad_btn_8
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_8 = obj;
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
                            // pinpad_btn_9
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_9 = obj;
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
                            // pinpad_btn_clear
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_clear = obj;
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
                            // pinpad_btn_0
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_0 = obj;
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
                            // pinpad_btn_back
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_back = obj;
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
                            // pinpad_btn_cancel
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_cancel = obj;
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
                            // pinpad_btn_ok
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_ok = obj;
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
                                    objects.obj0 = obj;
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
                            // pinpad_btn_dummy
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.pinpad_btn_dummy = obj;
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
        {
            // keyboard-test
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.keyboard_test = obj;
            lv_obj_set_pos(obj, 0, 0);
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
                    lv_obj_set_pos(obj, 48, 427);
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
                    lv_obj_set_pos(obj, 110, 427);
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
                    lv_obj_set_pos(obj, 173, 427);
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
                    lv_obj_set_pos(obj, 238, 427);
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
                    lv_obj_set_pos(obj, 303, 427);
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
                    lv_obj_set_pos(obj, 365, 427);
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