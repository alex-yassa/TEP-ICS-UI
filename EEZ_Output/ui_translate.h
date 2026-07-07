#ifndef EEZ_LVGL_UI_TRANSLATE_H
#define EEZ_LVGL_UI_TRANSLATE_H

#include "lvgl/lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LANG_PL = 0,
    LANG_EN,
    LANG_UA,
    LANG_COUNT
} lang_t;

extern int g_current_language;

const char *translate(const char *key, lang_t lang);
void ui_translate_update(void);
void update_login_status_translations(lang_t lang);

#ifdef __cplusplus
}
#endif

#endif // EEZ_LVGL_UI_TRANSLATE_H
