#include "ui.h"
#include "screens.h"
#include "images.h"
#include "actions.h"
#include "vars.h"
#include "lvgl/lvgl.h"

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
}

void ui_init() {
    create_screens();
    loadScreen(SCREEN_ID_MAIN);
    splash_start_time = lv_tick_get();
}

void ui_tick() {
    tick_screen(currentScreen);
    if (!splash_done && currentScreen == (SCREEN_ID_MAIN - 1)) {
        if (lv_tick_elaps(splash_start_time) >= 2000) {
            splash_done = true;
            loadScreen(SCREEN_ID_DASHBOARD);
        }
    }
}