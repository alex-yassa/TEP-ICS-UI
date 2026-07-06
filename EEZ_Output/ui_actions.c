#include "actions.h"
#include "ui.h"
#include "screens.h"
#include "app_hardware.h"
#include "styles.h"
#include "sha256.h"
#include "shared_memory.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

static void my_ui_log(const char *fmt, ...)
{
    FILE *f = fopen("/home/alex/Documents/PROJECTS/INVERTERS/InterpriseEnergySupply/CentralEMS/EMS_app/ui_debug.log", "a");
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

void action_sys_settings_button_clicked(lv_event_t * e)
{
    (void)e;
    if (objects.tabview) {
        lv_tabview_set_act(objects.tabview, 6, LV_ANIM_OFF);
    }
    app_log_event("Sys settings navigation selected");
}

/* Login State Variables */
static char current_username[32] = "Guest";
static uint8_t current_access_level = ACCESS_LEVEL_GUEST;

static lv_obj_t *login_btn = NULL;
static lv_obj_t *login_modal_overlay = NULL;
static lv_obj_t *login_modal = NULL;
static lv_obj_t *login_username_dropdown = NULL;
static lv_obj_t *login_password_ta = NULL;
static lv_group_t *modal_group = NULL;
static lv_group_t *prev_group = NULL;

/* Pinpad state — now uses static EEZ-generated objects; no dynamic widget creation */
static lv_group_t *pinpad_group = NULL;
static lv_obj_t  *pinpad_target_ta = NULL;
static bool       pinpad_visible = false;
static uint32_t   last_pinpad_hide_time = 0;
static uint32_t   last_pinpad_show_time = 0;

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
        lv_obj_add_flag(objects.login_modal, LV_OBJ_FLAG_HIDDEN);
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

        // Update UI status label
        char label_buf[64];
        if (current_access_level == ACCESS_LEVEL_ADMIN) {
            snprintf(label_buf, sizeof(label_buf), "%s (Admin)", current_username);
            lv_obj_set_style_text_color(objects.obj2, lv_color_hex(0xf43f5e), 0); // rose-500
        } else if (current_access_level == ACCESS_LEVEL_OPERATOR) {
            snprintf(label_buf, sizeof(label_buf), "%s (Oper)", current_username);
            lv_obj_set_style_text_color(objects.obj2, lv_color_hex(0x3b82f6), 0); // blue-500
        } else {
            snprintf(label_buf, sizeof(label_buf), "%s (View)", current_username);
            lv_obj_set_style_text_color(objects.obj2, lv_color_hex(0x10b981), 0); // emerald-500
        }
        lv_label_set_text(objects.obj2, label_buf);

        // Change button label
        lv_obj_t *btn_lbl = lv_obj_get_child(login_btn, 0);
        if (btn_lbl) {
            lv_label_set_text(btn_lbl, "Logout");
        }

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

    /* Find the label child to read the button text */
    lv_obj_t *lbl = lv_obj_get_child(btn, 0);
    if (!lbl) return;
    const char *txt = lv_label_get_text(lbl);
    if (!txt) return;

    if (strcmp(txt, "CLR") == 0) {
        lv_textarea_set_text(ta, "");
    } else if (strcmp(txt, "BCK") == 0) {
        lv_textarea_del_char(ta);
    } else {
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

    lv_obj_clear_flag(objects.pinpad_panel, LV_OBJ_FLAG_HIDDEN);

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
    pinpad_target_ta = NULL;

    if (objects.pinpad_panel) {
        lv_obj_add_flag(objects.pinpad_panel, LV_OBJ_FLAG_HIDDEN);
    }

    /* Restore input device focus to the modal group */
    if (pinpad_group) {
        lv_indev_t *indev = lv_indev_get_next(NULL);
        while (indev) {
            if (lv_indev_get_type(indev) == LV_INDEV_TYPE_KEYPAD ||
                lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER) {
                lv_indev_set_group(indev, modal_group);
            }
            indev = lv_indev_get_next(indev);
        }
        lv_group_set_default(modal_group);

        /* Re-focus the password textarea */
        lv_obj_t *ta_focus = objects.login_password_ta ? objects.login_password_ta : login_password_ta;
        if (ta_focus) lv_group_focus_obj(ta_focus);

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
        lv_label_set_text(objects.obj2, "Guest");
        lv_obj_set_style_text_color(objects.obj2, lv_color_hex(0x94a3b8), 0);

        lv_obj_t *btn_lbl = lv_obj_get_child(login_btn, 0);
        if (btn_lbl) {
            lv_label_set_text(btn_lbl, "Login");
        }

        app_log_event("User logged out");
    } else {
        // Guard: If login modal is already visible, ignore click to prevent corrupting prev_group
        if (objects.login_modal && !lv_obj_has_flag(objects.login_modal, LV_OBJ_FLAG_HIDDEN)) {
            return;
        }

        // Show EEZ-designed modal
        prev_group = lv_group_get_default();
        my_ui_log("[UI DEBUG] action_login_button_clicked: prev_group = %p\n", (void*)prev_group);
        modal_group = lv_group_create();
        lv_group_set_default(modal_group);

        lv_obj_clear_flag(objects.login_modal, LV_OBJ_FLAG_HIDDEN);
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
            if (objects.pinpad_panel) {
                lv_obj_add_flag(objects.pinpad_panel, LV_OBJ_FLAG_HIDDEN);
            }
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

    /* Initialize language selector label with current dropdown value */
    if (objects.dropdown_lang) {
        if (objects.selected_language_label) {
            char buf[16];
            lv_dropdown_get_selected_str(objects.dropdown_lang, buf, sizeof(buf));
            lv_label_set_text(objects.selected_language_label, buf);
        }
        
        // Register events on the language dropdown
        extern void dropdown_lang_event_cb(lv_event_t *e);
        lv_obj_add_event_cb(objects.dropdown_lang, dropdown_lang_event_cb, LV_EVENT_ALL, NULL);
    }

    /* Initialize User text label to Guest */
    lv_label_set_text(objects.obj2, "Guest");

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
    }

    if (objects.login_password_ta) {
        lv_obj_add_event_cb(objects.login_password_ta, password_ta_event_cb, LV_EVENT_ALL | LV_EVENT_PREPROCESS, NULL);
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

    /* Add nav buttons to the default LVGL group so keyboard can navigate them */
    if (g) {
        lv_group_add_obj(g, objects.dashboard_button);
        lv_group_add_obj(g, objects.view_1_button);
        lv_group_add_obj(g, objects.view_2_button);
        lv_group_add_obj(g, objects.gen_clusters_button);
        lv_group_add_obj(g, objects.load_management_button);
        lv_group_add_obj(g, objects.diagnostics_button);
        lv_group_add_obj(g, objects.sys_settings_button);
        lv_group_add_obj(g, login_btn);
        if (objects.lang_selector_button) {
            lv_group_add_obj(g, objects.lang_selector_button);
        }

        /* Set initial focus to Dashboard — fires LV_EVENT_FOCUSED,
         * which propagates the focused state to child labels via btn_focus_sync_cb */
        lv_group_focus_obj(objects.dashboard_button);
    }
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
        char buf[16];
        lv_dropdown_get_selected_str(dropdown, buf, sizeof(buf));
        if (objects.selected_language_label) {
            lv_label_set_text(objects.selected_language_label, buf);
        }

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

void action_lang_selector_button_clicked(lv_event_t *e)
{
    (void)e;
    if (objects.dropdown_lang) {
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
