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
uint32_t scan_keypad_matrix(void) {
    static const struct { GPIO_TypeDef *port; uint16_t pin; } rows[5] = {
        { KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN },
        { KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN },
        { KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN },
        { KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN },
        { KEYPAD_ROW4_PORT, KEYPAD_ROW4_PIN },
    };
    static const struct { GPIO_TypeDef *port; uint16_t pin; } cols[4] = {
        { KEYPAD_COL0_PORT, KEYPAD_COL0_PIN },
        { KEYPAD_COL1_PORT, KEYPAD_COL1_PIN },
        { KEYPAD_COL2_PORT, KEYPAD_COL2_PIN },
        { KEYPAD_COL3_PORT, KEYPAD_COL3_PIN },
    };

    uint32_t pressed_mask = 0;

    for (int y = 0; y < 5; y++) {
        // Drive current row LOW
        HAL_GPIO_WritePin(rows[y].port, rows[y].pin, GPIO_PIN_RESET);

        // Brief settling delay (~10us)
        for (volatile int i = 0; i < 150; i++);

        // Read columns (COL0..COL3)
        for (int x = 0; x < 4; x++) {
            if (HAL_GPIO_ReadPin(cols[x].port, cols[x].pin) == GPIO_PIN_RESET) {
                pressed_mask |= (1U << (x * 5 + y));
            }
        }

        // Release current row back to HIGH
        HAL_GPIO_WritePin(rows[y].port, rows[y].pin, GPIO_PIN_SET);
    }

    return pressed_mask;
}

static uint32_t g_pressed_keys_mask = 0;
#else
extern uint32_t sim_pressed_keys_mask;
#define g_pressed_keys_mask sim_pressed_keys_mask
#endif

#define IS_KEY_PRESSED(bit) (g_pressed_keys_mask & (1U << (bit)))

static void update_keyboard_test_button_states(void) {
    if (objects.keyboard_test) {
#ifndef PC_SIMULATOR
        g_pressed_keys_mask = scan_keypad_matrix();
#endif
        struct { lv_obj_t **obj; int bit; } btn_map[] = {
            // COL0: Nav Cluster
            { &objects.btn_up,        0 },
            { &objects.btn_down,      1 },
            { &objects.btn_left,      2 },
            { &objects.btn_right,     3 },
            { &objects.btn_enter,     4 },
            // COL1: Vertical Strip
            { &objects.btn_backspace, 5 }, // v01 / V1
            { &objects.btn_v_2,       6 },
            { &objects.btn_v_3,       7 },
            { &objects.btn_v_4,       8 },
            { &objects.btn_v_5,       9 },
            // COL2: Horizontal Board 1 (Left)
            { &objects.btn_g_1,      10 },
            { &objects.btn_g_2,      11 },
            { &objects.btn_g_3,      12 },
            { &objects.btn_g_4,      13 },
            { &objects.btn_g_5,      14 },
            // COL3: Horizontal Board 2 (Right)
            { &objects.btn_g_6,      15 },
            { &objects.btn_g_7,      16 },
            { &objects.btn_g_8,      17 },
            { &objects.btn_g_9,      18 },
            { &objects.btn_g_10,     19 },
        };

        for (size_t i = 0; i < sizeof(btn_map)/sizeof(btn_map[0]); i++) {
            if (*btn_map[i].obj) {
                if (IS_KEY_PRESSED(btn_map[i].bit)) {
                    lv_obj_add_state(*btn_map[i].obj, LV_STATE_PRESSED);
                } else {
                    lv_obj_clear_state(*btn_map[i].obj, LV_STATE_PRESSED);
                }
            }
        }
    }
}
#endif

bool is_keyboard_test_active(void) {
#if defined(KEYBOARD_TEST_ENABLE) && KEYBOARD_TEST_ENABLE
    if (objects.keyboard_test && !lv_obj_has_flag(objects.keyboard_test, LV_OBJ_FLAG_HIDDEN)) {
        return true;
    }
#endif
    return false;
}

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
