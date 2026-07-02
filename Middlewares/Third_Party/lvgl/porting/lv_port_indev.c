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
  return false;
}

static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
  (void)indev_drv;
  static uint32_t last_key = 0;
  uint32_t act_key = keypad_get_key();

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
  * @brief Scan and read active-low GPIO pushbuttons
  */
static uint32_t keypad_get_key(void)
{
  /* Read buttons pins (active-low because of internal pull-ups) */
  if (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_UP_PIN) == GPIO_PIN_RESET) {
    return 1; /* Up Key pressed */
  }
  if (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_DOWN_PIN) == GPIO_PIN_RESET) {
    return 2; /* Down Key pressed */
  }
  if (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_LEFT_PIN) == GPIO_PIN_RESET) {
    return 5; /* Left Key pressed */
  }
  if (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_RIGHT_PIN) == GPIO_PIN_RESET) {
    return 6; /* Right Key pressed */
  }
  if (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_ENTER_PIN) == GPIO_PIN_RESET) {
    return 3; /* Enter Key pressed */
  }
  if (HAL_GPIO_ReadPin(BTN_GPIO_PORT, BTN_BACK_PIN) == GPIO_PIN_RESET) {
    return 4; /* Back Key pressed */
  }
  return 0; /* No keys pressed */
}
