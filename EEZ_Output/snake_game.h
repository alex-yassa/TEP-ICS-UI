#ifndef EEZ_LVGL_UI_SNAKE_GAME_H
#define EEZ_LVGL_UI_SNAKE_GAME_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes the classic Snake game inside the given parent object (e.g., tab3).
 * @param parent Pointer to the parent LVGL object.
 */
void snake_game_init(lv_obj_t *parent);
void snake_game_handle_key(uint32_t key);
void snake_game_toggle_visibility(void);
bool snake_game_is_visible(void);

#ifdef __cplusplus
}
#endif

#endif /* EEZ_LVGL_UI_SNAKE_GAME_H */
