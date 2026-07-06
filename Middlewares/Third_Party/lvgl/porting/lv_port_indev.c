#include "lv_port_indev.h"
#include "main.h"

static lv_indev_drv_t indev_drv;
static lv_indev_t * keypad_indev;

/* Private helper functions */
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);

void lv_port_indev_init(void)
{
  /* Initialize the keypad driver */
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv.read_cb = keypad_read;

  /* Register keypad driver in LVGL */
  keypad_indev = lv_indev_drv_register(&indev_drv);

  /* Set up a default navigation group to receive button events automatically */
  lv_group_t * g = lv_group_create();
  lv_group_set_default(g);
  lv_indev_set_group(keypad_indev, g);
}

/**
  * @brief LVGL keypad input read callback
  */
extern bool is_pinpad_focused(void);
extern bool is_keyboard_test_active(void);

static bool should_use_up_down_keys(void)
{
  lv_group_t * g = lv_group_get_default();
  if (g == NULL) return false;
  lv_obj_t * focused = lv_group_get_focused(g);
  if (focused == NULL) return false;
  if (lv_obj_check_type(focused, &lv_dropdown_class))
  {
    return lv_dropdown_is_open(focused);
  }
  if (is_pinpad_focused())
  {
    return true;
  }
  if (is_keyboard_test_active())
  {
    return true;
  }
  return false;
}

static bool g_both_left_right_pressed_prev = false;

static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
  (void)indev_drv;
  static uint32_t last_key = 0;
  static uint32_t last_act_key = 0;
  uint32_t act_key = keypad_get_key();

  bool key_just_pressed = (act_key != 0 && act_key != last_act_key);
  last_act_key = act_key;

  // 1. Detect simultaneous Left + Right press to toggle Snake Game
  if (act_key == 7) {
    if (!g_both_left_right_pressed_prev) {
      extern void snake_game_toggle_visibility(void);
      snake_game_toggle_visibility();
    }
    g_both_left_right_pressed_prev = true;
    data->state = LV_INDEV_STATE_REL;
    data->key = 0;
    return;
  } else {
    g_both_left_right_pressed_prev = false;
  }

  // 2. Intercept key inputs if the Snake Game is active
  extern bool snake_game_is_visible(void);
  if (snake_game_is_visible()) {
    if (key_just_pressed) {
      uint32_t translated_key = 0;
      switch (act_key) {
        case 1: translated_key = LV_KEY_UP; break;
        case 2: translated_key = LV_KEY_DOWN; break;
        case 3: translated_key = LV_KEY_ENTER; break;
        case 4: translated_key = LV_KEY_ESC; break;
        case 5: translated_key = LV_KEY_LEFT; break;
        case 6: translated_key = LV_KEY_RIGHT; break;
      }
      if (translated_key != 0) {
        if (translated_key == LV_KEY_ESC) {
          extern void snake_game_toggle_visibility(void);
          snake_game_toggle_visibility();
        } else {
          extern void snake_game_handle_key(uint32_t key);
          snake_game_handle_key(translated_key);
        }
      }
    }
    data->state = LV_INDEV_STATE_REL;
    data->key = 0;
    return;
  }

  // 3. Standard LVGL input device mapping
  if(act_key != 0) {
    data->state = LV_INDEV_STATE_PR;
    /* Map key values to standard LVGL Keypad actions */
    switch(act_key) {
      case 1:
        data->key = should_use_up_down_keys() ? LV_KEY_UP : LV_KEY_PREV; /* Up Button */
        break;
      case 2:
        data->key = should_use_up_down_keys() ? LV_KEY_DOWN : LV_KEY_NEXT; /* Down Button */
        break;
      case 3:
        data->key = LV_KEY_ENTER; /* Enter Button */
        break;
      case 4:
        data->key = LV_KEY_ESC; /* Back Button */
        break;
      case 5:
        data->key = LV_KEY_LEFT; /* Left Button */
        break;
      case 6:
        data->key = LV_KEY_RIGHT; /* Right Button */
        break;
    }
    last_key = data->key;
  } else {
    data->state = LV_INDEV_STATE_REL;
    data->key = last_key;
  }
}

/**
  * @brief Scan the 3x2 matrix keypad and return the pressed key code
  */
static uint32_t keypad_get_key(void)
{
  uint32_t pressed_key = 0;

  /* Scan Strobe 1 (PC6) */
  HAL_GPIO_WritePin(KEYPAD_ST_PORT_1, KEYPAD_ST_PIN_1, GPIO_PIN_SET);
  HAL_GPIO_WritePin(KEYPAD_ST_PORT_2, KEYPAD_ST_PIN_2, GPIO_PIN_RESET);
  for (volatile int i = 0; i < 50; i++); 

  // Check Col 4 (PA4) for UP
  if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL4_PIN) == GPIO_PIN_SET) {
    pressed_key = 1; /* UP */
  } 
  // Check Col 3 (PA3) for DOWN
  else if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL3_PIN) == GPIO_PIN_SET) {
    pressed_key = 2; /* DOWN */
  }
  HAL_GPIO_WritePin(KEYPAD_ST_PORT_1, KEYPAD_ST_PIN_1, GPIO_PIN_RESET);
  if (pressed_key != 0) return pressed_key;

  /* Scan Strobe 2 (PB0) */
  HAL_GPIO_WritePin(KEYPAD_ST_PORT_1, KEYPAD_ST_PIN_1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(KEYPAD_ST_PORT_2, KEYPAD_ST_PIN_2, GPIO_PIN_SET);
  for (volatile int i = 0; i < 50; i++); 

  // Check Col 3 (PA3) for ENTER
  if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL3_PIN) == GPIO_PIN_SET) {
    pressed_key = 3; /* ENTER */
  } 
  // Check Col 5 (PA5) for ESC
  else if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL5_PIN) == GPIO_PIN_SET) {
    pressed_key = 4; /* ESC */
  } 
  // Check Col 2 (PA1) and Col 1 (PA0) simultaneously for LEFT + RIGHT
  else if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL2_PIN) == GPIO_PIN_SET &&
           HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL1_PIN) == GPIO_PIN_SET) {
    pressed_key = 7; /* BOTH_LEFT_RIGHT */
  }
  // Check Col 2 (PA1) for LEFT
  else if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL2_PIN) == GPIO_PIN_SET) {
    pressed_key = 5; /* LEFT */
  } 
  // Check Col 1 (PA0) for RIGHT
  else if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL1_PIN) == GPIO_PIN_SET) {
    pressed_key = 6; /* RIGHT */
  }
  HAL_GPIO_WritePin(KEYPAD_ST_PORT_2, KEYPAD_ST_PIN_2, GPIO_PIN_RESET);

  return pressed_key;
}
