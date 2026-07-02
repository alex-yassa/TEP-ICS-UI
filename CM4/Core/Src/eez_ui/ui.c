#include "ui.h"
#include "screens.h"
#include "images.h"
#include "actions.h"
#include "vars.h"
#include "lvgl/lvgl.h"
#include "app_hardware.h"

#include <string.h>

static int16_t currentScreen = -1;
static uint32_t splash_start_time = 0;
static bool splash_done = false;

static lv_obj_t *getLvglObjectFromIndex(int32_t index) {
    if (index == -1) {
        return 0;
    }
    return ((lv_obj_t **)&objects)[index];
}

void loadScreen(enum ScreensEnum screenId) {
    currentScreen = screenId - 1;
    lv_obj_t *screen = getLvglObjectFromIndex(currentScreen);
    lv_scr_load(screen);

    // If dashboard is loaded, check if we should show/hide keyboard test panel
    if (screenId == SCREEN_ID_DASHBOARD) {
#if defined(KEYBOARD_TEST_ENABLE) && KEYBOARD_TEST_ENABLE
        if (objects.keyboard_test) {
            lv_obj_clear_flag(objects.keyboard_test, LV_OBJ_FLAG_HIDDEN);
        }
#else
        if (objects.keyboard_test) {
            lv_obj_add_flag(objects.keyboard_test, LV_OBJ_FLAG_HIDDEN);
        }
#endif
    }
}

void ui_init() {
    create_screens();
    loadScreen(SCREEN_ID_MAIN);
    splash_start_time = lv_tick_get();
}

#if defined(KEYBOARD_TEST_ENABLE) && KEYBOARD_TEST_ENABLE
#ifndef PC_SIMULATOR
#include "main.h"
#define IS_UP_PRESSED()    (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_UP_PIN) == GPIO_PIN_RESET)
#define IS_DOWN_PRESSED()  (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_DOWN_PIN) == GPIO_PIN_RESET)
#define IS_LEFT_PRESSED()  (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_LEFT_PIN) == GPIO_PIN_RESET)
#define IS_RIGHT_PRESSED() (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_RIGHT_PIN) == GPIO_PIN_RESET)
#define IS_ENTER_PRESSED() (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_ENTER_PIN) == GPIO_PIN_RESET)
#define IS_BACK_PRESSED()  (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_BACK_PIN) == GPIO_PIN_RESET)
#else
extern bool sim_key_up, sim_key_down, sim_key_left, sim_key_right, sim_key_enter, sim_key_back;
#define IS_UP_PRESSED()    sim_key_up
#define IS_DOWN_PRESSED()  sim_key_down
#define IS_LEFT_PRESSED()  sim_key_left
#define IS_RIGHT_PRESSED() sim_key_right
#define IS_ENTER_PRESSED() sim_key_enter
#define IS_BACK_PRESSED()  sim_key_back
#endif

static void update_keyboard_test_button_states(void) {
    if (objects.keyboard_test) {
        if (IS_UP_PRESSED()) {
            lv_obj_add_state(objects.btn_up, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_up, LV_STATE_PRESSED);
        }
        if (IS_DOWN_PRESSED()) {
            lv_obj_add_state(objects.btn_down, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_down, LV_STATE_PRESSED);
        }
        if (IS_LEFT_PRESSED()) {
            lv_obj_add_state(objects.btn_left, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_left, LV_STATE_PRESSED);
        }
        if (IS_RIGHT_PRESSED()) {
            lv_obj_add_state(objects.btn_right, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_right, LV_STATE_PRESSED);
        }
        if (IS_ENTER_PRESSED()) {
            lv_obj_add_state(objects.btn_enter, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_enter, LV_STATE_PRESSED);
        }
        if (IS_BACK_PRESSED()) {
            lv_obj_add_state(objects.btn_backspace, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_backspace, LV_STATE_PRESSED);
        }
    }
}
#endif

void ui_tick() {
    tick_screen(currentScreen);

#if defined(KEYBOARD_TEST_ENABLE) && KEYBOARD_TEST_ENABLE
    update_keyboard_test_button_states();
#endif

    if (!splash_done && currentScreen == (SCREEN_ID_MAIN - 1)) {
        if (lv_tick_elaps(splash_start_time) >= 2000) {
            splash_done = true;
            loadScreen(SCREEN_ID_DASHBOARD);
        }
    }
}
