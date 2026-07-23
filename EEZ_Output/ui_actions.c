#include "actions.h"
#include "ui.h"
#include "screens.h"

#include "app_hardware.h"
#include "styles.h"
#include "sha256.h"
#include "shared_memory.h"
#include "ui_translate.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    NAV_MODE_MENU,
    NAV_MODE_TAB
} NavMode_t;

static NavMode_t g_nav_mode = NAV_MODE_MENU;
static void set_navigation_mode(NavMode_t mode);

static void my_ui_log(const char *fmt, ...)
{
    FILE *f = fopen("ui_debug.log", "a");
    if (f) {
        va_list args;
        va_start(args, fmt);
        vfprintf(f, fmt, args);
        va_end(args);
        fclose(f);
    }
}

/* -----------------------------------------------------------------------
 * Focus sync: recursively mirrors the button's FOCUSED / DEFOCUSED state
 * onto ALL descendants (children, grandchildren, etc.).
 * Button tree:
 *   Button
 *     |- Container (child)
 *     |    +- Icon Label (grandchild) <- needs FOCUSED too
 *     +- Text Label (child)           <- needs FOCUSED too
 * --------------------------------------------------------------------- */
static void set_state_recursive(lv_obj_t *obj, lv_state_t state, bool add)
{
    if (add) {
        lv_obj_add_state(obj, state);
    } else {
        lv_obj_clear_state(obj, state);
    }
    uint32_t count = lv_obj_get_child_cnt(obj);
    for (uint32_t i = 0; i < count; i++) {
        set_state_recursive(lv_obj_get_child(obj, i), state, add);
    }
}

static void btn_focus_sync_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    bool focused = (code == LV_EVENT_FOCUSED);

    uint32_t child_count = lv_obj_get_child_cnt(btn);
    for (uint32_t i = 0; i < child_count; i++) {
        set_state_recursive(lv_obj_get_child(btn, i), LV_STATE_FOCUSED, focused);
    }
}

static void get_btn_children_recursive(lv_obj_t *parent, lv_obj_t **btns, uint32_t *count, uint32_t max_count)
{
    if (!parent || !btns || !count) return;
    uint32_t cnt = lv_obj_get_child_cnt(parent);
    for (uint32_t i = 0; i < cnt; i++) {
        lv_obj_t *child = lv_obj_get_child(parent, i);
        if (lv_obj_check_type(child, &lv_btn_class)) {
            if (*count < max_count) {
                btns[*count] = child;
                (*count)++;
            }
        } else {
            get_btn_children_recursive(child, btns, count, max_count);
        }
    }
}

/* Helper: register focus sync on a single button */
static void register_focus_sync(lv_obj_t *btn)
{
    lv_obj_add_event_cb(btn, btn_focus_sync_cb, LV_EVENT_FOCUSED,   NULL);
    lv_obj_add_event_cb(btn, btn_focus_sync_cb, LV_EVENT_DEFOCUSED, NULL);
}

void action_dashboard_button_clicked(lv_event_t * e)
{
    (void)e;
    if (objects.tabview) {
        lv_tabview_set_act(objects.tabview, 0, LV_ANIM_OFF);
    }
    app_log_event("Dashboard navigation selected");
}

void action_view_1_button_clicked(lv_event_t * e)
{
    (void)e;
    if (objects.tabview) {
        lv_tabview_set_act(objects.tabview, 1, LV_ANIM_OFF);
    }
    app_log_event("View 1 navigation selected");
}

void action_view_2_button_clicked(lv_event_t * e)
{
    (void)e;
    if (objects.tabview) {
        lv_tabview_set_act(objects.tabview, 2, LV_ANIM_OFF);
    }
    app_log_event("View 2 navigation selected");
}

void action_gen_clusters_button_clicked(lv_event_t * e)
{
    (void)e;
    if (objects.tabview) {
        lv_tabview_set_act(objects.tabview, 3, LV_ANIM_OFF);
    }
    app_log_event("Gen clusters navigation selected");
}

void action_load_management_button_clicked(lv_event_t * e)
{
    (void)e;
    if (objects.tabview) {
        lv_tabview_set_act(objects.tabview, 4, LV_ANIM_OFF);
    }
    app_log_event("Load Management navigation selected");
}

void action_diagnostics_button_clicked(lv_event_t * e)
{
    (void)e;
    if (objects.tabview) {
        lv_tabview_set_act(objects.tabview, 5, LV_ANIM_OFF);
    }
    app_log_event("Diagnostics navigation selected");
}

#include <stdlib.h>

#ifndef PC_SIMULATOR
#include "main.h"
#else
extern SharedBuffer_t sim_shared_buffer;
#endif

static void show_pinpad(lv_obj_t * ta);
static lv_obj_t *login_btn = NULL;


static lv_obj_t *get_login_user_label(void) {
    if (objects.login_btn) {
        return lv_obj_get_child(objects.login_btn, 1);
    }
    if (login_btn) {
        return lv_obj_get_child(login_btn, 0);
    }
    return NULL;
}

extern void action_settings_reset_clicked(lv_event_t * e);

void action_sys_settings_button_clicked(lv_event_t * e)
{
    (void)e;
    if (objects.tabview) {
        lv_tabview_set_act(objects.tabview, 6, LV_ANIM_OFF);
    }
    app_log_event("Sys settings navigation selected");
}

static float get_ta_float(lv_obj_t *ta) {
    if (!ta) return 0.0f;
    const char *txt = lv_textarea_get_text(ta);
    if (!txt || strlen(txt) == 0) {
        txt = lv_textarea_get_placeholder_text(ta);
    }
    if (!txt) return 0.0f;
    return atof(txt);
}

static int get_ta_int(lv_obj_t *ta) {
    if (!ta) return 0;
    const char *txt = lv_textarea_get_text(ta);
    if (!txt || strlen(txt) == 0) {
        txt = lv_textarea_get_placeholder_text(ta);
    }
    if (!txt) return 0;
    return atoi(txt);
}

static void set_ta_float(lv_obj_t *ta, float val, const char *fmt) {
    if (!ta) return;
    char buf[32];
    snprintf(buf, sizeof(buf), fmt, val);
    lv_textarea_set_text(ta, buf);
}

static void set_ta_int(lv_obj_t *ta, int val) {
    if (!ta) return;
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", val);
    lv_textarea_set_text(ta, buf);
}

void action_settings_apply_clicked(lv_event_t * e) {
    (void)e;
    
    // Parse values from textareas
    int batt_count = get_ta_int(objects.settings_battery_count_ta);
    int pv_count = get_ta_int(objects.settings_pv_count_ta);
    float max_import = get_ta_float(objects.settings_max_import_ta);
    float backup_soc = get_ta_float(objects.settings_backup_soc_ta);
    float max_volt = get_ta_float(objects.settings_max_volt_ta);
    float min_volt = get_ta_float(objects.settings_min_volt_ta);
    float target_pf = get_ta_float(objects.settings_cos_phi_ta);
    int nom_volt = get_ta_int(objects.settings_nom_volt_ta);
    int nom_freq = get_ta_int(objects.settings_nom_freq_ta);
    
    // Save to shared memory
    bool saved = false;
#ifndef PC_SIMULATOR
    if (HAL_HSEM_Take(HSEM_ID_SHARED_MEM, 0) == HAL_OK) {
        volatile SharedBuffer_t *shared = SHARED_BUFFER;
        shared->cfg_grid_max_p_import = max_import;
        shared->cfg_bat_backup_soc = backup_soc;
        shared->cfg_bat_max_volt = max_volt;
        shared->cfg_bat_min_volt = min_volt;
        shared->cfg_target_cos_phi = target_pf;
        shared->cfg_grid_nom_volt = nom_volt;
        shared->cfg_grid_nom_freq = nom_freq;
        HAL_HSEM_Release(HSEM_ID_SHARED_MEM, 0);
        saved = true;
    }
#else
    // PC Simulator direct update
    sim_shared_buffer.cfg_grid_max_p_import = max_import;
    sim_shared_buffer.cfg_bat_backup_soc = backup_soc;
    sim_shared_buffer.cfg_bat_max_volt = max_volt;
    sim_shared_buffer.cfg_bat_min_volt = min_volt;
    sim_shared_buffer.cfg_target_cos_phi = target_pf;
    sim_shared_buffer.cfg_grid_nom_volt = nom_volt;
    sim_shared_buffer.cfg_grid_nom_freq = nom_freq;
    saved = true;
#endif

    if (saved) {
        app_log_event("System settings applied successfully");
        char msg[128];
        snprintf(msg, sizeof(msg), "[Settings] Applied: Bat=%d, PV=%d, PMax=%.1f kW, BackupSoC=%.1f%%, VMax=%.1fV, VMin=%.1fV, PF=%.2f, VNom=%dV, FNom=%dHz",
                 batt_count, pv_count, max_import, backup_soc, max_volt, min_volt, target_pf, nom_volt, nom_freq);
        app_log_event(msg);
    } else {
        app_log_event("Failed to apply system settings: Semaphore busy");
    }
}

void action_settings_reset_clicked(lv_event_t * e) {
    (void)e;
    
    float max_import = 0.0f;
    float backup_soc = 0.0f;
    float max_volt = 0.0f;
    float min_volt = 0.0f;
    float target_pf = 0.0f;
    int nom_volt = 0;
    int nom_freq = 0;
    
    // Read from shared memory
    bool loaded = false;
#ifndef PC_SIMULATOR
    if (HAL_HSEM_Take(HSEM_ID_SHARED_MEM, 0) == HAL_OK) {
        volatile SharedBuffer_t *shared = SHARED_BUFFER;
        max_import = shared->cfg_grid_max_p_import;
        backup_soc = shared->cfg_bat_backup_soc;
        max_volt = shared->cfg_bat_max_volt;
        min_volt = shared->cfg_bat_min_volt;
        target_pf = shared->cfg_target_cos_phi;
        nom_volt = shared->cfg_grid_nom_volt;
        nom_freq = shared->cfg_grid_nom_freq;
        HAL_HSEM_Release(HSEM_ID_SHARED_MEM, 0);
        loaded = true;
    }
#else
    max_import = sim_shared_buffer.cfg_grid_max_p_import;
    backup_soc = sim_shared_buffer.cfg_bat_backup_soc;
    max_volt = sim_shared_buffer.cfg_bat_max_volt;
    min_volt = sim_shared_buffer.cfg_bat_min_volt;
    target_pf = sim_shared_buffer.cfg_target_cos_phi;
    nom_volt = sim_shared_buffer.cfg_grid_nom_volt;
    nom_freq = sim_shared_buffer.cfg_grid_nom_freq;
    loaded = true;
#endif

    if (loaded) {
        // Update textareas with current shared memory values
        set_ta_int(objects.settings_battery_count_ta, 2); // Default to 2
        set_ta_int(objects.settings_pv_count_ta, 2);      // Default to 2
        set_ta_float(objects.settings_max_import_ta, max_import, "%.1f");
        set_ta_float(objects.settings_backup_soc_ta, backup_soc, "%.1f");
        set_ta_float(objects.settings_max_volt_ta, max_volt, "%.1f");
        set_ta_float(objects.settings_min_volt_ta, min_volt, "%.1f");
        set_ta_float(objects.settings_cos_phi_ta, target_pf, "%.2f");
        set_ta_int(objects.settings_nom_volt_ta, nom_volt);
        set_ta_int(objects.settings_nom_freq_ta, nom_freq);
        
        app_log_event("System settings reset to current device state");
    } else {
        app_log_event("Failed to reset system settings: Semaphore busy");
    }
}

static void settings_ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (code == LV_EVENT_KEY) {
        uint32_t key = lv_event_get_key(e);
        if (key == LV_KEY_ENTER) {
            lv_event_stop_processing(e);
            show_pinpad(ta);
        }
    } else if (code == LV_EVENT_CLICKED) {
        lv_indev_t *indev = lv_indev_get_act();
        if (indev) {
            lv_indev_type_t type = lv_indev_get_type(indev);
            if (type == LV_INDEV_TYPE_KEYPAD || type == LV_INDEV_TYPE_ENCODER) {
                return;
            }
        }
        show_pinpad(ta);
    }
}

static void rebuild_settings_group(lv_group_t *g, int page)
{
    if (!g) return;
    lv_group_remove_all_objs(g);
    
    if (page == 0) { // Page 1 (tab7)
        if (objects.settings_battery_count_ta) lv_group_add_obj(g, objects.settings_battery_count_ta);
        if (objects.settings_pv_count_ta)      lv_group_add_obj(g, objects.settings_pv_count_ta);
        if (objects.settings_max_import_ta)    lv_group_add_obj(g, objects.settings_max_import_ta);
        if (objects.settings_backup_soc_ta)    lv_group_add_obj(g, objects.settings_backup_soc_ta);
        if (objects.settings_max_volt_ta)      lv_group_add_obj(g, objects.settings_max_volt_ta);
        if (objects.settings_next_btn)          lv_group_add_obj(g, objects.settings_next_btn);
        if (objects.settings_apply_btn)         lv_group_add_obj(g, objects.settings_apply_btn);
        if (objects.settings_reset_btn)         lv_group_add_obj(g, objects.settings_reset_btn);
    }
    else if (page == 1) { // Page 2 (tab8)
        if (objects.settings_min_volt_ta)      lv_group_add_obj(g, objects.settings_min_volt_ta);
        if (objects.settings_cos_phi_ta)       lv_group_add_obj(g, objects.settings_cos_phi_ta);
        if (objects.settings_nom_volt_ta)      lv_group_add_obj(g, objects.settings_nom_volt_ta);
        if (objects.settings_nom_freq_ta)      lv_group_add_obj(g, objects.settings_nom_freq_ta);
        if (objects.settings_prev_btn_2)        lv_group_add_obj(g, objects.settings_prev_btn_2);
        if (objects.settings_next_btn_2)        lv_group_add_obj(g, objects.settings_next_btn_2);
        if (objects.settings_apply_btn_2)       lv_group_add_obj(g, objects.settings_apply_btn_2);
        if (objects.settings_reset_btn_2)       lv_group_add_obj(g, objects.settings_reset_btn_2);
    }
    else if (page == 2) { // Page 3 (tab9)
        if (objects.fake_settings_ta_0)         lv_group_add_obj(g, objects.fake_settings_ta_0);
        if (objects.fake_settings_ta_1)         lv_group_add_obj(g, objects.fake_settings_ta_1);
        if (objects.fake_settings_ta_2)         lv_group_add_obj(g, objects.fake_settings_ta_2);
        if (objects.fake_settings_ta_3)         lv_group_add_obj(g, objects.fake_settings_ta_3);
        if (objects.fake_settings_ta_4)         lv_group_add_obj(g, objects.fake_settings_ta_4);
        if (objects.fake_settings_ta_5)         lv_group_add_obj(g, objects.fake_settings_ta_5);
        if (objects.settings_prev_btn_3)        lv_group_add_obj(g, objects.settings_prev_btn_3);
        if (objects.settings_apply_btn_3)       lv_group_add_obj(g, objects.settings_apply_btn_3);
        if (objects.settings_reset_btn_3)       lv_group_add_obj(g, objects.settings_reset_btn_3);
    }
}

void set_navigation_mode(NavMode_t mode)
{
    lv_group_t *g = lv_group_get_default();
    if (!g) return;
    
    g_nav_mode = mode;
    lv_group_remove_all_objs(g);
    
    if (mode == NAV_MODE_MENU) {
        // Add only sidebar menu buttons to the default group
        lv_group_add_obj(g, objects.dashboard_button);
        lv_group_add_obj(g, objects.view_1_button);
        lv_group_add_obj(g, objects.view_2_button);
        lv_group_add_obj(g, objects.gen_clusters_button);
        lv_group_add_obj(g, objects.load_management_button);
        lv_group_add_obj(g, objects.diagnostics_button);
        lv_group_add_obj(g, objects.sys_settings_button);
        if (login_btn) lv_group_add_obj(g, login_btn);
        if (objects.lang_selector_button) lv_group_add_obj(g, objects.lang_selector_button);
        
        // Focus the active menu button based on current tab
        uint16_t act_tab = 0;
        if (objects.tabview) {
            act_tab = lv_tabview_get_tab_act(objects.tabview);
        }
        
        lv_obj_t *focus_target = objects.dashboard_button;
        switch (act_tab) {
            case 0: focus_target = objects.dashboard_button; break;
            case 1: focus_target = objects.view_1_button; break;
            case 2: focus_target = objects.view_2_button; break;
            case 3: focus_target = objects.gen_clusters_button; break;
            case 4: focus_target = objects.load_management_button; break;
            case 5: focus_target = objects.diagnostics_button; break;
            case 6:
            case 7:
            case 8: focus_target = objects.sys_settings_button; break;
        }
        lv_group_focus_obj(focus_target);
        app_log_event("Navigation mode: MAIN MENU");
    } else {
        // Tab Navigation Mode
        uint16_t act_tab = 0;
        if (objects.tabview) {
            act_tab = lv_tabview_get_tab_act(objects.tabview);
        }
        
        if (act_tab == 6 || act_tab == 7 || act_tab == 8) {
            rebuild_settings_group(g, act_tab - 6);
            
            // Focus first element of active tab page
            if (act_tab == 6 && objects.settings_battery_count_ta) {
                lv_group_focus_obj(objects.settings_battery_count_ta);
            } else if (act_tab == 7 && objects.settings_min_volt_ta) {
                lv_group_focus_obj(objects.settings_min_volt_ta);
            } else if (act_tab == 8 && objects.fake_settings_ta_0) {
                lv_group_focus_obj(objects.fake_settings_ta_0);
            }
            app_log_event("Navigation mode: SETTINGS TAB ELEMENTS");
        } else {
            // Other tabs are read-only telemetry tabs, so return to menu mode
            set_navigation_mode(NAV_MODE_MENU);
        }
    }
}



static void action_next_page_clicked(lv_event_t *e)
{
    (void)e;
    if (objects.tabview) {
        uint16_t act_tab = lv_tabview_get_tab_act(objects.tabview);
        if (act_tab == 6) {
            lv_tabview_set_act(objects.tabview, 7, LV_ANIM_OFF);
            rebuild_settings_group(lv_group_get_default(), 1);
            if (objects.settings_min_volt_ta) {
                lv_group_focus_obj(objects.settings_min_volt_ta);
            }
        } else if (act_tab == 7) {
            lv_tabview_set_act(objects.tabview, 8, LV_ANIM_OFF);
            rebuild_settings_group(lv_group_get_default(), 2);
            if (objects.fake_settings_ta_0) {
                lv_group_focus_obj(objects.fake_settings_ta_0);
            }
        }
    }
}

static void action_prev_page_clicked(lv_event_t *e)
{
    (void)e;
    if (objects.tabview) {
        uint16_t act_tab = lv_tabview_get_tab_act(objects.tabview);
        if (act_tab == 7) {
            lv_tabview_set_act(objects.tabview, 6, LV_ANIM_OFF);
            rebuild_settings_group(lv_group_get_default(), 0);
            if (objects.settings_battery_count_ta) {
                lv_group_focus_obj(objects.settings_battery_count_ta);
            }
        } else if (act_tab == 8) {
            lv_tabview_set_act(objects.tabview, 7, LV_ANIM_OFF);
            rebuild_settings_group(lv_group_get_default(), 1);
            if (objects.settings_min_volt_ta) {
                lv_group_focus_obj(objects.settings_min_volt_ta);
            }
        }
    }
}

static void global_navigation_key_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_KEY) {
        uint32_t key = lv_event_get_key(e);
        
        if (g_nav_mode == NAV_MODE_MENU) {
            if (key == LV_KEY_RIGHT) {
                // If any System Settings page is active, go into the tab elements
                if (objects.tabview) {
                    uint16_t act_tab = lv_tabview_get_tab_act(objects.tabview);
                    if (act_tab == 6 || act_tab == 7 || act_tab == 8) {
                        lv_event_stop_processing(e);
                        set_navigation_mode(NAV_MODE_TAB);
                    }
                }
            }
        } else if (g_nav_mode == NAV_MODE_TAB) {
            if (key == LV_KEY_LEFT) {
                // Return to main menu
                lv_event_stop_processing(e);
                set_navigation_mode(NAV_MODE_MENU);
                return;
            }
        }
    }
}

/* Login State Variables */
static char current_username[32] = "Guest";
static uint8_t current_access_level = ACCESS_LEVEL_GUEST;

static lv_obj_t *login_modal_overlay = NULL;
static lv_obj_t *login_modal = NULL;
static lv_obj_t *login_username_dropdown = NULL;
static lv_obj_t *login_password_ta = NULL;
static lv_group_t *modal_group = NULL;
static lv_group_t *prev_group = NULL;

/* Pinpad state — now uses static EEZ-generated objects; no dynamic widget creation */
static lv_group_t *pinpad_group = NULL;
static lv_group_t *pinpad_prev_group = NULL;
static lv_obj_t  *pinpad_target_ta = NULL;
static bool       pinpad_visible = false;
static uint32_t   last_pinpad_hide_time = 0;
static uint32_t   last_pinpad_show_time = 0;

static void set_login_modal_hidden(bool hidden)
{
    if (objects.login_modal) {
        if (hidden) {
            lv_obj_add_flag(objects.login_modal, LV_OBJ_FLAG_HIDDEN);
            lv_obj_t *parent = lv_obj_get_parent(objects.login_modal);
            if (parent && parent != objects.dashboard) {
                lv_obj_add_flag(parent, LV_OBJ_FLAG_HIDDEN);
            }
        } else {
            lv_obj_clear_flag(objects.login_modal, LV_OBJ_FLAG_HIDDEN);
            lv_obj_t *parent = lv_obj_get_parent(objects.login_modal);
            if (parent && parent != objects.dashboard) {
                lv_obj_clear_flag(parent, LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
}

static void set_pinpad_hidden(bool hidden)
{
    if (objects.pinpad_panel) {
        lv_obj_t *parent = lv_obj_get_parent(objects.pinpad_panel);
        if (hidden) {
            lv_obj_add_flag(objects.pinpad_panel, LV_OBJ_FLAG_HIDDEN);
            if (parent && parent != objects.dashboard && parent != objects.login_modal) {
                lv_obj_add_flag(parent, LV_OBJ_FLAG_HIDDEN);
            }
        } else {
            lv_obj_clear_flag(objects.pinpad_panel, LV_OBJ_FLAG_HIDDEN);
            if (parent && parent != objects.dashboard && parent != objects.login_modal) {
                lv_obj_clear_flag(parent, LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
}

static void hide_pinpad(void);
static void show_pinpad(lv_obj_t * ta);

static void close_login_modal(void)
{
    hide_pinpad();
    my_ui_log("[UI DEBUG] close_login_modal: prev_group=%p, modal_group=%p\n", (void*)prev_group, (void*)modal_group);
    if (objects.login_modal == NULL) {
        if (login_modal_overlay) {
            lv_obj_del(login_modal_overlay);
            login_modal_overlay = NULL;
            login_modal = NULL;
            login_username_dropdown = NULL;
            login_password_ta = NULL;
        }
    } else {
        set_login_modal_hidden(true);
    }
    if (modal_group) {
        // Restore all input devices to the previous group
        lv_indev_t *indev = lv_indev_get_next(NULL);
        while (indev) {
            if (lv_indev_get_type(indev) == LV_INDEV_TYPE_KEYPAD || lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER) {
                my_ui_log("[UI DEBUG] Restoring indev %p to group %p\n", (void*)indev, (void*)prev_group);
                lv_indev_set_group(indev, prev_group);
            }
            indev = lv_indev_get_next(indev);
        }

        lv_group_set_default(prev_group);
        if (prev_group) {
            lv_group_focus_next(prev_group);
            lv_group_focus_obj(objects.dashboard_button);
        }
        lv_group_del(modal_group);
        modal_group = NULL;
        prev_group = NULL;
    }
}

void action_cancel_login_clicked(lv_event_t *e)
{
    (void)e;
    close_login_modal();
}

void action_signin_clicked(lv_event_t *e)
{
    (void)e;
    char username[32] = "";
    const char *password = "";

    if (objects.login_modal == NULL) {
        if (login_username_dropdown && login_password_ta) {
            lv_dropdown_get_selected_str(login_username_dropdown, username, sizeof(username));
            password = lv_textarea_get_text(login_password_ta);
        }
    } else {
        if (objects.login_user_dropdown && objects.login_password_ta) {
            lv_dropdown_get_selected_str(objects.login_user_dropdown, username, sizeof(username));
            password = lv_textarea_get_text(objects.login_password_ta);
        }
    }

    if (strlen(username) == 0) return;

    // Compute SHA-256 password hash
    SHA256_CTX ctx;
    uint8_t hash[32];
    sha256_init(&ctx);
    sha256_update(&ctx, (const uint8_t*)password, strlen(password));
    sha256_final(&ctx, hash);

    char password_hash_hex[65];
    for (int i = 0; i < 32; i++) {
        sprintf(password_hash_hex + (i * 2), "%02x", hash[i]);
    }
    password_hash_hex[64] = '\0';

    // Verify credentials against database
    bool auth_success = false;
    uint8_t access_lvl = ACCESS_LEVEL_GUEST;

    if (strcmp(username, "admin") == 0) {
        if (strcmp(password_hash_hex, "8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918") == 0) {
            auth_success = true;
            access_lvl = ACCESS_LEVEL_ADMIN;
        }
    } else if (strcmp(username, "operator") == 0) {
        if (strcmp(password_hash_hex, "e1064e18c5a891215b2259b13cf14a39f50e56f4d1e21b7b75b9f939e6a724b1") == 0) {
            auth_success = true;
            access_lvl = ACCESS_LEVEL_OPERATOR;
        }
    } else if (strcmp(username, "viewer") == 0) {
        if (strcmp(password_hash_hex, "6a5b67279313a48e77c5c0f5e1f0e4b85c13b2c8a2b5305141e6e0d29d44e45c") == 0) {
            auth_success = true;
            access_lvl = ACCESS_LEVEL_GUEST; // Viewer maps to guest permissions
        }
    }

    if (auth_success) {
        strncpy(current_username, username, sizeof(current_username) - 1);
        current_username[sizeof(current_username) - 1] = '\0';
        current_access_level = access_lvl;

        // Write to Shared Memory
        app_set_login_state(current_username, current_access_level);

        // Update UI status label color
        lv_obj_t *user_lbl = get_login_user_label();
        if (user_lbl) {
            if (current_access_level == ACCESS_LEVEL_ADMIN) {
                lv_obj_set_style_text_color(user_lbl, lv_color_hex(0xf43f5e), 0); // rose-500
            } else if (current_access_level == ACCESS_LEVEL_OPERATOR) {
                lv_obj_set_style_text_color(user_lbl, lv_color_hex(0x3b82f6), 0); // blue-500
            } else {
                lv_obj_set_style_text_color(user_lbl, lv_color_hex(0x10b981), 0); // emerald-500
            }
        }
        update_login_status_translations((lang_t)g_current_language);

        char log_msg[64];
        snprintf(log_msg, sizeof(log_msg), "User logged in: %s", current_username);
        app_log_event(log_msg);

        close_login_modal();
    } else {
        lv_obj_t *ta = (objects.login_modal == NULL) ? login_password_ta : objects.login_password_ta;
        if (ta) {
            lv_obj_set_style_border_color(ta, lv_color_hex(0xef4444), 0); // red-500
            lv_textarea_set_text(ta, "");
            lv_textarea_set_placeholder_text(ta, "Invalid Password!");
        }
        app_log_event("Failed login attempt");
    }
}

/* --------------------------------------------------------------------------
 * Pinpad action implementations
 * These are called by the EEZ-generated screens.c event bindings.
 * -------------------------------------------------------------------------- */

/* Called by every digit / CLR / BCK button */
void action_pinpad_btn_pressed(lv_event_t *e)
{
    // Ignore click/key releases that happen within 300ms of show_pinpad to prevent Enter key bounce/propagation
    if (lv_tick_elaps(last_pinpad_show_time) < 300) return;

    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *ta  = pinpad_target_ta;
    if (!ta) return;

    if (btn == objects.pinpad_btn_clear) {
        lv_textarea_set_text(ta, "");
    } else if (btn == objects.pinpad_btn_back) {
        lv_textarea_del_char(ta);
    } else {
        /* Find the label child to read the button text */
        lv_obj_t *lbl = lv_obj_get_child(btn, 0);
        if (!lbl) return;
        const char *txt = lv_label_get_text(lbl);
        if (!txt) return;
        lv_textarea_add_text(ta, txt);
    }
}

void action_pinpad_ok_clicked(lv_event_t *e)
{
    (void)e;
    hide_pinpad();
}

void action_pinpad_cancel_clicked(lv_event_t *e)
{
    (void)e;
    hide_pinpad();
}

/* --------------------------------------------------------------------------
 * show_pinpad / hide_pinpad — now operates on static EEZ panel
 * -------------------------------------------------------------------------- */

static void show_pinpad(lv_obj_t *ta)
{
    if (pinpad_visible) return;
    if (lv_tick_elaps(last_pinpad_hide_time) < 150) return;
    if (!objects.pinpad_panel) return;

    pinpad_target_ta = ta;
    pinpad_visible   = true;
    last_pinpad_show_time = lv_tick_get();
    pinpad_prev_group = lv_group_get_default();

    // Show login_modal as it is the parent of pinpad_panel
    if (objects.login_modal) {
        set_login_modal_hidden(false);
        
        // Hide the sign-in card if we're inputting settings values
        if (ta != objects.login_password_ta && ta != login_password_ta) {
            if (objects.login_card) {
                lv_obj_add_flag(objects.login_card, LV_OBJ_FLAG_HIDDEN);
            }
            // Keep background overlay light so operator can see the settings screen behind it
            lv_obj_set_style_bg_opa(objects.login_modal, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
        } else {
            if (objects.login_card) {
                lv_obj_clear_flag(objects.login_card, LV_OBJ_FLAG_HIDDEN);
            }
            lv_obj_set_style_bg_opa(objects.login_modal, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    set_pinpad_hidden(false);

    /* Create a focus group containing all pinpad buttons */
    pinpad_group = lv_group_create();
    lv_group_set_default(pinpad_group);

    lv_obj_t *btns[] = {
        objects.pinpad_btn_1,   objects.pinpad_btn_2,   objects.pinpad_btn_3,
        objects.pinpad_btn_4,   objects.pinpad_btn_5,   objects.pinpad_btn_6,
        objects.pinpad_btn_7,   objects.pinpad_btn_8,   objects.pinpad_btn_9,
        objects.pinpad_btn_clear, objects.pinpad_btn_0, objects.pinpad_btn_back,
        objects.pinpad_btn_cancel, objects.pinpad_btn_ok
    };
    for (int i = 0; i < (int)(sizeof(btns)/sizeof(btns[0])); i++) {
        if (btns[i]) lv_group_add_obj(pinpad_group, btns[i]);
    }

    /* Redirect all keypad/encoder input devices to the pinpad group */
    lv_indev_t *indev = lv_indev_get_next(NULL);
    while (indev) {
        if (lv_indev_get_type(indev) == LV_INDEV_TYPE_KEYPAD ||
            lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER) {
            lv_indev_set_group(indev, pinpad_group);
        }
        indev = lv_indev_get_next(indev);
    }

    /* Focus first button */
    if (objects.pinpad_btn_1) lv_group_focus_obj(objects.pinpad_btn_1);
}

static void hide_pinpad(void)
{
    if (!pinpad_visible) return;

    last_pinpad_hide_time = lv_tick_get();
    pinpad_visible = false;
    lv_obj_t *target = pinpad_target_ta;
    pinpad_target_ta = NULL;

    set_pinpad_hidden(true);

    // Hide or restore login_modal depending on context
    if (objects.login_modal) {
        if (!modal_group) {
            // Re-hide login_modal overlay if we were editing settings
            set_login_modal_hidden(true);
        } else {
            // Restore login card visibility
            if (objects.login_card) {
                lv_obj_clear_flag(objects.login_card, LV_OBJ_FLAG_HIDDEN);
            }
        }
    }

    /* Restore input device focus to the previous active group */
    if (pinpad_group) {
        lv_group_t *restore_group = modal_group ? modal_group : pinpad_prev_group;
        lv_indev_t *indev = lv_indev_get_next(NULL);
        while (indev) {
            if (lv_indev_get_type(indev) == LV_INDEV_TYPE_KEYPAD ||
                lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER) {
                lv_indev_set_group(indev, restore_group);
            }
            indev = lv_indev_get_next(indev);
        }
        lv_group_set_default(restore_group);

        if (modal_group) {
            /* Re-focus the password textarea */
            lv_obj_t *ta_focus = objects.login_password_ta ? objects.login_password_ta : login_password_ta;
            if (ta_focus) lv_group_focus_obj(ta_focus);
        } else {
            /* Re-focus the settings textarea that was being edited */
            if (target && restore_group) {
                lv_group_focus_obj(target);
            }
        }

        lv_group_del(pinpad_group);
        pinpad_group = NULL;
    }
}

static void password_ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (code == LV_EVENT_KEY) {
        uint32_t key = lv_event_get_key(e);
        if (key == LV_KEY_ENTER) {
            lv_event_stop_processing(e); // Consume key event to prevent default handler from inserting a newline
            show_pinpad(ta);
        }
    } else if (code == LV_EVENT_CLICKED) {
        lv_indev_t *indev = lv_indev_get_act();
        if (indev) {
            lv_indev_type_t type = lv_indev_get_type(indev);
            if (type == LV_INDEV_TYPE_KEYPAD || type == LV_INDEV_TYPE_ENCODER) {
                return; // Ignore keypad/encoder simulated clicked events on the text area
            }
        }
        show_pinpad(ta);
    }
}

void action_login_button_clicked(lv_event_t *e)
{
    (void)e;
    if (strcmp(current_username, "Guest") != 0) {
        // Logout
        strncpy(current_username, "Guest", sizeof(current_username) - 1);
        current_username[sizeof(current_username) - 1] = '\0';
        current_access_level = ACCESS_LEVEL_GUEST;

        // Update Shared Memory
        app_set_login_state(current_username, current_access_level);

        // Update UI
        lv_obj_t *user_lbl = get_login_user_label();
        if (user_lbl) {
            lv_obj_set_style_text_color(user_lbl, lv_color_hex(0x94a3b8), 0);
        }
        update_login_status_translations((lang_t)g_current_language);

        app_log_event("User logged out");
    } else {
        // Guard: If login modal is already visible, ignore click to prevent corrupting prev_group
        if (objects.login_modal && !lv_obj_has_flag(objects.login_modal, LV_OBJ_FLAG_HIDDEN) &&
            (!lv_obj_get_parent(objects.login_modal) || !lv_obj_has_flag(lv_obj_get_parent(objects.login_modal), LV_OBJ_FLAG_HIDDEN))) {
            return;
        }

        // Show EEZ-designed modal
        prev_group = lv_group_get_default();
        my_ui_log("[UI DEBUG] action_login_button_clicked: prev_group = %p\n", (void*)prev_group);
        modal_group = lv_group_create();
        lv_group_set_default(modal_group);

        set_login_modal_hidden(false);
        lv_obj_add_flag(objects.login_modal, LV_OBJ_FLAG_CLICKABLE);

            // Add EEZ objects to modal group for trapping navigation
            if (objects.login_user_dropdown) {
                lv_group_add_obj(modal_group, objects.login_user_dropdown);
            }
            if (objects.login_password_ta) {
                lv_group_add_obj(modal_group, objects.login_password_ta);
                lv_textarea_set_text(objects.login_password_ta, "");
                lv_textarea_set_placeholder_text(objects.login_password_ta, "Enter Password");
                lv_obj_set_style_border_color(objects.login_password_ta, lv_color_hex(0x475569), 0);
            }
            if (objects.login_cancel_btn) {
                lv_group_add_obj(modal_group, objects.login_cancel_btn);
            }
            if (objects.login_signin_btn) {
                lv_group_add_obj(modal_group, objects.login_signin_btn);
            }
            // Ensure pinpad starts hidden when modal opens
            set_pinpad_hidden(true);
            pinpad_visible = false;

            // Switch all input devices to the new modal group to trap keyboard/encoder navigation
            lv_indev_t *indev = lv_indev_get_next(NULL);
            while (indev) {
                if (lv_indev_get_type(indev) == LV_INDEV_TYPE_KEYPAD || lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER) {
                    lv_indev_set_group(indev, modal_group);
                }
                indev = lv_indev_get_next(indev);
            }

            if (objects.login_user_dropdown) {
                lv_group_focus_obj(objects.login_user_dropdown);
            }
    }
}

static void pinpad_key_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_KEY) return;

    uint32_t key = lv_event_get_key(e);
    lv_obj_t *cur = lv_event_get_target(e);

    lv_obj_t *grid[5][3] = {
        {objects.pinpad_btn_1,   objects.pinpad_btn_2,   objects.pinpad_btn_3},
        {objects.pinpad_btn_4,   objects.pinpad_btn_5,   objects.pinpad_btn_6},
        {objects.pinpad_btn_7,   objects.pinpad_btn_8,   objects.pinpad_btn_9},
        {objects.pinpad_btn_clear, objects.pinpad_btn_0, objects.pinpad_btn_back},
        {objects.pinpad_btn_cancel, objects.pinpad_btn_ok, objects.pinpad_btn_dummy}
    };

    int r = -1, c = -1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == cur) {
                r = i;
                c = j;
                break;
            }
        }
        if (r != -1) break;
    }
    if (r == -1 || c == -1) return;

    int next_r = r;
    int next_c = c;

    if (key == LV_KEY_UP) {
        next_r = r - 1;
    } else if (key == LV_KEY_DOWN) {
        next_r = r + 1;
    } else if (key == LV_KEY_LEFT) {
        next_c = c - 1;
    } else if (key == LV_KEY_RIGHT) {
        next_c = c + 1;
    } else {
        return;
    }

    if (next_r >= 0 && next_r < 5 && next_c >= 0 && next_c < 3) {
        lv_obj_t *target = grid[next_r][next_c];
        if (target == objects.pinpad_btn_dummy || target == NULL) {
            if (next_r == 4 && next_c == 2) {
                target = objects.pinpad_btn_ok;
            }
        }
        if (target && target != cur) {
            lv_group_focus_obj(target);
        }
    }
}

/* -----------------------------------------------------------------------
 * app_ui_init: call once after ui_init() completes.
 * Registers the focus-sync callback on every navigation button so that
 * child labels automatically receive LV_STATE_FOCUSED when the button
 * receives keyboard / encoder focus.
 * --------------------------------------------------------------------- */
void app_ui_init(void)
{
    /* Clear default group of all auto-added objects to prevent focusing invisible widgets */
    lv_group_t *g = lv_group_get_default();
    if (g) {
        lv_group_remove_all_objs(g);
    }

    /* Register focus-sync callbacks on all nav buttons */
    register_focus_sync(objects.dashboard_button);
    register_focus_sync(objects.view_1_button);
    register_focus_sync(objects.view_2_button);
    register_focus_sync(objects.gen_clusters_button);
    register_focus_sync(objects.load_management_button);
    register_focus_sync(objects.diagnostics_button);
    register_focus_sync(objects.sys_settings_button);

    /* Bind EEZ Studio's Focused style state to the keyboard-focus state (LV_STATE_FOCUS_KEY)
     * so that any styling changes made in EEZ Studio's style manager apply here as well. */
    lv_obj_add_style(objects.dashboard_button, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
    lv_obj_add_style(objects.view_1_button, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
    lv_obj_add_style(objects.view_2_button, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
    lv_obj_add_style(objects.gen_clusters_button, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
    lv_obj_add_style(objects.load_management_button, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
    lv_obj_add_style(objects.diagnostics_button, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
    lv_obj_add_style(objects.sys_settings_button, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);

    /* Register focus-sync and styling on the language selector button */
    if (objects.lang_selector_button) {
        register_focus_sync(objects.lang_selector_button);
        lv_obj_add_style(objects.lang_selector_button, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
        lv_obj_add_event_cb(objects.lang_selector_button, action_lang_selector_button_clicked, LV_EVENT_CLICKED, NULL);
    }

    /* Initialize language selector widget (objects.obj3) */
    if (objects.obj3) {
        lv_obj_add_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_t *btns[16];
        uint32_t btn_cnt = 0;
        get_btn_children_recursive(objects.obj3, btns, &btn_cnt, 16);

        extern void lang_widget_btn_event_cb(lv_event_t *e);
        extern void action_view_2_button_clicked(lv_event_t * e);

        for (uint32_t i = 0; i < btn_cnt; i++) {
            lv_obj_remove_event_cb(btns[i], action_view_2_button_clicked);
            register_focus_sync(btns[i]);
            lv_obj_add_style(btns[i], get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
            lv_obj_add_event_cb(btns[i], lang_widget_btn_event_cb, LV_EVENT_ALL, (void *)(uintptr_t)i);
        }
    }

    /* Initialize language selector label with current dropdown value */
    if (objects.dropdown_lang) {
        g_current_language = lv_dropdown_get_selected(objects.dropdown_lang);

        if (objects.selected_language_label) {
            char buf[16];
            lv_dropdown_get_selected_str(objects.dropdown_lang, buf, sizeof(buf));
            lv_label_set_text(objects.selected_language_label, buf);
        }
        
        // Register events on the language dropdown
        extern void dropdown_lang_event_cb(lv_event_t *e);
        lv_obj_add_event_cb(objects.dropdown_lang, dropdown_lang_event_cb, LV_EVENT_ALL, NULL);
    }

    /* Translate UI to default language */
    ui_translate_update();

    /* Create login button dynamically in the header if not designed in EEZ Studio */
    if (objects.login_btn == NULL) {
        login_btn = lv_btn_create(objects.header);
        lv_obj_set_pos(login_btn, 805, 6);
        lv_obj_set_size(login_btn, 100, 30);
        lv_obj_add_event_cb(login_btn, action_login_button_clicked, LV_EVENT_CLICKED, NULL);

        lv_obj_set_style_bg_color(login_btn, lv_color_hex(0x212121), 0);
        lv_obj_set_style_border_color(login_btn, lv_color_hex(0x475569), 0);
        lv_obj_set_style_border_width(login_btn, 1, 0);
        lv_obj_set_style_radius(login_btn, 4, 0);

        lv_obj_t *lbl = lv_label_create(login_btn);
        lv_label_set_text(lbl, "Login");
        lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_text_color(lbl, lv_color_hex(0xffffff), 0);
        lv_obj_set_style_text_font(lbl, &lv_font_montserrat_14, 0);

        register_focus_sync(login_btn);
        lv_obj_add_style(login_btn, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
    } else {
        login_btn = objects.login_btn;
        register_focus_sync(login_btn);
        lv_obj_add_style(login_btn, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
    }

    set_login_modal_hidden(true);

    if (objects.login_password_ta) {
        lv_obj_add_event_cb(objects.login_password_ta, password_ta_event_cb, LV_EVENT_ALL | LV_EVENT_PREPROCESS, NULL);
    }

    /* Configure all settings textareas (real and fake) */
    lv_obj_t *settings_tas[] = {
        objects.settings_battery_count_ta, objects.settings_pv_count_ta, objects.settings_max_import_ta,
        objects.settings_backup_soc_ta, objects.settings_max_volt_ta, objects.settings_min_volt_ta,
        objects.settings_cos_phi_ta, objects.settings_nom_volt_ta, objects.settings_nom_freq_ta,
        objects.fake_settings_ta_0, objects.fake_settings_ta_1, objects.fake_settings_ta_2,
        objects.fake_settings_ta_3, objects.fake_settings_ta_4, objects.fake_settings_ta_5
    };

    for (int i = 0; i < (int)(sizeof(settings_tas)/sizeof(settings_tas[0])); i++) {
        if (settings_tas[i]) {
            lv_textarea_set_one_line(settings_tas[i], true);
            lv_textarea_set_placeholder_text(settings_tas[i], "");
            lv_obj_add_flag(settings_tas[i], LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_add_event_cb(settings_tas[i], settings_ta_event_cb, LV_EVENT_ALL | LV_EVENT_PREPROCESS, NULL);
            lv_obj_add_event_cb(settings_tas[i], global_navigation_key_cb, LV_EVENT_KEY, NULL);
            register_focus_sync(settings_tas[i]);
            if (i >= 9) {
                lv_textarea_set_text(settings_tas[i], "999");
            }
        }
    }

    /* Clear scroll-on-focus flags on tabview and tabs to prevent page offsets during focus shifts */
    if (objects.tabview) {
        lv_obj_clear_flag(objects.tabview, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
        lv_obj_t *tabview_content = lv_tabview_get_content(objects.tabview);
        if (tabview_content) {
            lv_obj_clear_flag(tabview_content, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
        }
    }
    lv_obj_t *tabs[] = {
        objects.tab1, objects.tab2, objects.tab3,
        objects.tab4, objects.tab5, objects.tab6,
        objects.tab7, objects.tab8, objects.tab9
    };
    for (int i = 0; i < 9; i++) {
        if (tabs[i]) {
            lv_obj_clear_flag(tabs[i], LV_OBJ_FLAG_SCROLL_ON_FOCUS);
        }
    }

    /* Register focus sync and callbacks on settings buttons (duplicated on pages 1, 2, and 3) */
    lv_obj_t *apply_btns[] = {objects.settings_apply_btn, objects.settings_apply_btn_2, objects.settings_apply_btn_3};
    lv_obj_t *reset_btns[] = {objects.settings_reset_btn, objects.settings_reset_btn_2, objects.settings_reset_btn_3};
    for (int i = 0; i < 3; i++) {
        if (apply_btns[i]) {
            register_focus_sync(apply_btns[i]);
            lv_obj_add_style(apply_btns[i], get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
            lv_obj_add_event_cb(apply_btns[i], global_navigation_key_cb, LV_EVENT_KEY, NULL);
        }
        if (reset_btns[i]) {
            register_focus_sync(reset_btns[i]);
            lv_obj_add_style(reset_btns[i], get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
            lv_obj_add_event_cb(reset_btns[i], global_navigation_key_cb, LV_EVENT_KEY, NULL);
        }
    }

    /* Register focus sync and callbacks on settings navigation buttons generated from EEZ Studio */
    if (objects.settings_next_btn) {
        register_focus_sync(objects.settings_next_btn);
        lv_obj_add_style(objects.settings_next_btn, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
        lv_obj_add_event_cb(objects.settings_next_btn, action_next_page_clicked, LV_EVENT_CLICKED, NULL);
    }
    if (objects.settings_prev_btn_2) {
        register_focus_sync(objects.settings_prev_btn_2);
        lv_obj_add_style(objects.settings_prev_btn_2, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
        lv_obj_add_event_cb(objects.settings_prev_btn_2, action_prev_page_clicked, LV_EVENT_CLICKED, NULL);
    }
    if (objects.settings_next_btn_2) {
        register_focus_sync(objects.settings_next_btn_2);
        lv_obj_add_style(objects.settings_next_btn_2, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
        lv_obj_add_event_cb(objects.settings_next_btn_2, action_next_page_clicked, LV_EVENT_CLICKED, NULL);
    }
    if (objects.settings_prev_btn_3) {
        register_focus_sync(objects.settings_prev_btn_3);
        lv_obj_add_style(objects.settings_prev_btn_3, get_style_btn_menu_style_MAIN_FOCUSED(), LV_STATE_FOCUS_KEY);
        lv_obj_add_event_cb(objects.settings_prev_btn_3, action_prev_page_clicked, LV_EVENT_CLICKED, NULL);
    }

    /* Register 2D navigation callback on all pinpad buttons */
    lv_obj_t *pinpad_btns[] = {
        objects.pinpad_btn_1,   objects.pinpad_btn_2,   objects.pinpad_btn_3,
        objects.pinpad_btn_4,   objects.pinpad_btn_5,   objects.pinpad_btn_6,
        objects.pinpad_btn_7,   objects.pinpad_btn_8,   objects.pinpad_btn_9,
        objects.pinpad_btn_clear, objects.pinpad_btn_0, objects.pinpad_btn_back,
        objects.pinpad_btn_cancel, objects.pinpad_btn_ok
    };
    for (int i = 0; i < (int)(sizeof(pinpad_btns)/sizeof(pinpad_btns[0])); i++) {
        if (pinpad_btns[i]) {
            lv_obj_add_event_cb(pinpad_btns[i], pinpad_key_cb, LV_EVENT_KEY, NULL);
        }
    }

    /* Register navigation key callback on main menu and header controls */
    if (objects.dashboard_button)       lv_obj_add_event_cb(objects.dashboard_button,       global_navigation_key_cb, LV_EVENT_KEY, NULL);
    if (objects.view_1_button)          lv_obj_add_event_cb(objects.view_1_button,          global_navigation_key_cb, LV_EVENT_KEY, NULL);
    if (objects.view_2_button)          lv_obj_add_event_cb(objects.view_2_button,          global_navigation_key_cb, LV_EVENT_KEY, NULL);
    if (objects.gen_clusters_button)    lv_obj_add_event_cb(objects.gen_clusters_button,    global_navigation_key_cb, LV_EVENT_KEY, NULL);
    if (objects.load_management_button) lv_obj_add_event_cb(objects.load_management_button, global_navigation_key_cb, LV_EVENT_KEY, NULL);
    if (objects.diagnostics_button)     lv_obj_add_event_cb(objects.diagnostics_button,     global_navigation_key_cb, LV_EVENT_KEY, NULL);
    if (objects.sys_settings_button)    lv_obj_add_event_cb(objects.sys_settings_button,    global_navigation_key_cb, LV_EVENT_KEY, NULL);
    if (login_btn)                      lv_obj_add_event_cb(login_btn,                      global_navigation_key_cb, LV_EVENT_KEY, NULL);
    if (objects.lang_selector_button)   lv_obj_add_event_cb(objects.lang_selector_button,   global_navigation_key_cb, LV_EVENT_KEY, NULL);

    /* Initialize navigation mode to Main Menu Mode */
    if (g) {
        set_navigation_mode(NAV_MODE_MENU);
    }

    /* Load initial configuration values from shared memory on startup */
    action_settings_reset_clicked(NULL);
}

bool is_pinpad_focused(void)
{
    if (!pinpad_visible) return false;
    if (!objects.pinpad_panel) return false;

    lv_obj_t *focused = lv_group_get_focused(lv_group_get_default());
    if (!focused) return false;

    lv_obj_t *pinpad_btns[] = {
        objects.pinpad_btn_1,   objects.pinpad_btn_2,   objects.pinpad_btn_3,
        objects.pinpad_btn_4,   objects.pinpad_btn_5,   objects.pinpad_btn_6,
        objects.pinpad_btn_7,   objects.pinpad_btn_8,   objects.pinpad_btn_9,
        objects.pinpad_btn_clear, objects.pinpad_btn_0, objects.pinpad_btn_back,
        objects.pinpad_btn_cancel, objects.pinpad_btn_ok
    };
    for (int i = 0; i < (int)(sizeof(pinpad_btns)/sizeof(pinpad_btns[0])); i++) {
        if (pinpad_btns[i] && focused == pinpad_btns[i]) return true;
    }
    return false;
}

void update_login_status_translations(lang_t lang) {
    lv_obj_t *lbl = get_login_user_label();
    if (lbl) {
        if (strcmp(current_username, "Guest") == 0) {
            lv_label_set_text(lbl, translate("Login", lang));
        } else {
            lv_label_set_text(lbl, translate("Logout", lang));
        }
    }
}

/* --------------------------------------------------------------------------
 * Language Selector dropdown and button logic
 * -------------------------------------------------------------------------- */
static uint32_t last_dropdown_open_time = 0;

void dropdown_lang_event_cb(lv_event_t *e)
{
    static bool in_event = false;
    if (in_event) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *dropdown = lv_event_get_target(e);

    /* Consume Enter/Release event immediately after opening to prevent key bounce propagation */
    if (lv_tick_elaps(last_dropdown_open_time) < 300) {
        if (code == LV_EVENT_RELEASED || code == LV_EVENT_KEY) {
            if (code == LV_EVENT_KEY) {
                uint32_t key = lv_event_get_key(e);
                if (key == LV_KEY_ENTER) {
                    lv_event_stop_processing(e);
                    return;
                }
            } else {
                lv_event_stop_processing(e);
                return;
            }
        }
    }

    if (code == LV_EVENT_VALUE_CHANGED) {
        in_event = true;
        g_current_language = lv_dropdown_get_selected(dropdown);

        char buf[16];
        lv_dropdown_get_selected_str(dropdown, buf, sizeof(buf));
        if (objects.selected_language_label) {
            lv_label_set_text(objects.selected_language_label, buf);
        }

        ui_translate_update();

        /* Done selection: remove from keypad group and restore focus to selector button */
        lv_group_remove_obj(dropdown);
        if (objects.lang_selector_button) {
            lv_group_focus_obj(objects.lang_selector_button);
        }
        in_event = false;
    }
    else if (code == LV_EVENT_CANCEL) {
        in_event = true;
        /* Cancelled/Escaped: remove from keypad group and restore focus */
        lv_group_remove_obj(dropdown);
        if (objects.lang_selector_button) {
            lv_group_focus_obj(objects.lang_selector_button);
        }
        in_event = false;
    }
}

bool is_lang_selector_visible(void)
{
    return (objects.obj3 != NULL && !lv_obj_has_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN));
}

void lang_widget_btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_KEY) {
        uint32_t key = lv_event_get_key(e);
        if (key == LV_KEY_DOWN || key == LV_KEY_RIGHT || key == LV_KEY_NEXT) {
            lv_group_t *g = lv_group_get_default();
            if (g) lv_group_focus_next(g);
            return;
        }
        if (key == LV_KEY_UP || key == LV_KEY_LEFT || key == LV_KEY_PREV) {
            lv_group_t *g = lv_group_get_default();
            if (g) lv_group_focus_prev(g);
            return;
        }
        if (key == LV_KEY_ESC) {
            if (objects.obj3) {
                lv_obj_add_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            }
            set_navigation_mode(NAV_MODE_MENU);
            if (objects.lang_selector_button) {
                lv_group_focus_obj(objects.lang_selector_button);
            }
            return;
        }
    }

    if (code == LV_EVENT_CLICKED) {
        uint32_t lang_idx = (uint32_t)(uintptr_t)lv_event_get_user_data(e);
        g_current_language = lang_idx;

        if (objects.dropdown_lang) {
            lv_dropdown_set_selected(objects.dropdown_lang, lang_idx);
        }

        ui_translate_update();

        if (objects.obj3) {
            lv_obj_add_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
        }
        set_navigation_mode(NAV_MODE_MENU);
        if (objects.lang_selector_button) {
            lv_group_focus_obj(objects.lang_selector_button);
        }
    }
}

void action_lang_selector_button_clicked(lv_event_t *e)
{
    (void)e;
    if (objects.obj3) {
        bool is_hidden = lv_obj_has_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
        if (is_hidden) {
            lv_obj_clear_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            lv_obj_move_foreground(objects.obj3);

            /* Set group to contain language selector button children for Up/Down navigation */
            lv_group_t *g = lv_group_get_default();
            if (g) {
                lv_group_remove_all_objs(g);
                lv_obj_t *btns[16];
                uint32_t btn_cnt = 0;
                get_btn_children_recursive(objects.obj3, btns, &btn_cnt, 16);

                lv_obj_t *focus_target = NULL;
                for (uint32_t i = 0; i < btn_cnt; i++) {
                    lv_group_add_obj(g, btns[i]);
                    if (i == (uint32_t)g_current_language) {
                        focus_target = btns[i];
                    }
                    if (!focus_target) {
                        focus_target = btns[i];
                    }
                }
                if (focus_target) {
                    lv_group_focus_obj(focus_target);
                }
            }
        } else {
            lv_obj_add_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            set_navigation_mode(NAV_MODE_MENU);
            if (objects.lang_selector_button) {
                lv_group_focus_obj(objects.lang_selector_button);
            }
        }
    } else if (objects.dropdown_lang) {
        last_dropdown_open_time = lv_tick_get();

        /* Open the dropdown list */
        lv_dropdown_open(objects.dropdown_lang);

        /* Add dropdown to the default group and focus it so user can navigate options */
        lv_group_t *g = lv_group_get_default();
        if (g) {
            lv_group_add_obj(g, objects.dropdown_lang);
            lv_group_focus_obj(objects.dropdown_lang);
        }
    }
}
