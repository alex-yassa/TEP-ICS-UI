#include "sdl_port.h"
#include <stdio.h>
#include "screens.h"

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 600

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static uint32_t texture_buffer[WINDOW_WIDTH * WINDOW_HEIGHT];

/* LVGL display buffers */
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf1[WINDOW_WIDTH * WINDOW_HEIGHT];

/* Keypad input tracking */
static uint32_t last_key = 0;
static bool key_pressed = false;
static lv_indev_drv_t indev_drv;
static lv_indev_t *keypad_indev = NULL;

/* Simulator keyboard state tracking for keyboard test screen */
bool sim_key_up = false;
bool sim_key_down = false;
bool sim_key_left = false;
bool sim_key_right = false;
bool sim_key_enter = false;
bool sim_key_back = false;

/* SDL Display Flush Callback */
static void sdl_disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
  int32_t x, y;
  for (y = area->y1; y <= area->y2; y++)
  {
    for (x = area->x1; x <= area->x2; x++)
    {
      lv_color_t c = *color_p;
      /* Convert RGB565 to 32-bit ARGB8888 for SDL */
      uint32_t r = ((c.full >> 11) & 0x1F) * 255 / 31;
      uint32_t g = ((c.full >> 5) & 0x3F) * 255 / 63;
      uint32_t b = (c.full & 0x1F) * 255 / 31;
      
      texture_buffer[y * WINDOW_WIDTH + x] = (0xFF << 24) | (r << 16) | (g << 8) | b;
      color_p++;
    }
  }

  if (lv_disp_flush_is_last(disp_drv))
  {
    SDL_UpdateTexture(texture, NULL, texture_buffer, WINDOW_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  lv_disp_flush_ready(disp_drv);
}

void sdl_disp_init(void)
{
  /* Initialize SDL video */
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  /* Create Window */
  window = SDL_CreateWindow("Riverdi 1024x600 Inverter GUI Simulator",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  /* Create Renderer */
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
  {
    fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  /* Create Texture for pixel transfers */
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                              WINDOW_WIDTH, WINDOW_HEIGHT);
  if (texture == NULL)
  {
    fprintf(stderr, "Texture could not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  /* Initialize display buffers */
  lv_disp_draw_buf_init(&disp_buf, buf1, NULL, WINDOW_WIDTH * WINDOW_HEIGHT);

  /* Register display driver in LVGL */
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.draw_buf = &disp_buf;
  disp_drv.flush_cb = sdl_disp_flush;
  disp_drv.hor_res = WINDOW_WIDTH;
  disp_drv.ver_res = WINDOW_HEIGHT;
  lv_disp_drv_register(&disp_drv);
}

/* SDL Keypad Input Read Callback */
static void sdl_keypad_read(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
  (void)drv;
  if (key_pressed)
  {
    data->state = LV_INDEV_STATE_PR;
    data->key = last_key;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void sdl_indev_init(void)
{
  /* Register keypad driver in LVGL */
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv.read_cb = sdl_keypad_read;
  keypad_indev = lv_indev_drv_register(&indev_drv);

  /* Set default group to match key actions */
  lv_group_t * g = lv_group_create();
  lv_group_set_default(g);
  lv_indev_set_group(keypad_indev, g);
}

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

void sdl_handle_key_event(SDL_Event *event)
{
  static bool left_held = false;
  static bool right_held = false;

  if (event->type == SDL_KEYDOWN)
  {
    key_pressed = true;

    switch (event->key.keysym.sym) {
      case SDLK_UP:     sim_key_up = true; break;
      case SDLK_DOWN:   sim_key_down = true; break;
      case SDLK_LEFT:   sim_key_left = true; break;
      case SDLK_RIGHT:  sim_key_right = true; break;
      case SDLK_RETURN:
      case SDLK_KP_ENTER: sim_key_enter = true; break;
      case SDLK_ESCAPE: sim_key_back = true; break;
    }

    if (event->key.keysym.sym == SDLK_LEFT) left_held = true;
    if (event->key.keysym.sym == SDLK_RIGHT) right_held = true;

    // Detect simultaneous Left + Right arrow press
    if (left_held && right_held) {
      extern void snake_game_toggle_visibility(void);
      snake_game_toggle_visibility();
      left_held = false;
      right_held = false;
      key_pressed = false;
      return;
    }

    // Check if snake game is currently active/visible and route key events to it
    extern bool snake_game_is_visible(void);
    if (snake_game_is_visible()) {
      uint32_t key = 0;
      switch (event->key.keysym.sym) {
        case SDLK_UP:     key = LV_KEY_UP; break;
        case SDLK_DOWN:   key = LV_KEY_DOWN; break;
        case SDLK_LEFT:   key = LV_KEY_LEFT; break;
        case SDLK_RIGHT:  key = LV_KEY_RIGHT; break;
        case SDLK_RETURN:
        case SDLK_KP_ENTER: key = LV_KEY_ENTER; break;
        case SDLK_ESCAPE: key = LV_KEY_ESC; break;
      }
      if (key != 0) {
        if (key == LV_KEY_ESC) {
          extern void snake_game_toggle_visibility(void);
          snake_game_toggle_visibility();
        } else {
          extern void snake_game_handle_key(uint32_t key);
          snake_game_handle_key(key);
        }
        key_pressed = false;
        return;
      }
    }

    switch (event->key.keysym.sym)
    {
      case SDLK_UP:
        last_key = should_use_up_down_keys() ? LV_KEY_UP : LV_KEY_PREV; /* Map Up Arrow */
        break;
      case SDLK_DOWN:
        last_key = should_use_up_down_keys() ? LV_KEY_DOWN : LV_KEY_NEXT; /* Map Down Arrow */
        break;
      case SDLK_LEFT:
        last_key = LV_KEY_LEFT; /* Map Left Arrow */
        break;
      case SDLK_RIGHT:
        last_key = LV_KEY_RIGHT; /* Map Right Arrow */
        break;
      case SDLK_RETURN:
      case SDLK_KP_ENTER:
        last_key = LV_KEY_ENTER; /* Map Enter to LVGL Enter */
        break;
      case SDLK_ESCAPE:
        last_key = LV_KEY_ESC; /* Map Escape to LVGL Escape (Back) */
        break;
      default:
        key_pressed = false; /* Ignore other keys */
        break;
    }
    if (key_pressed) {
      printf("[SDL DEBUG] sym=%d, mapped to=%d (UP=%d, DOWN=%d, LEFT=%d, RIGHT=%d, ENTER=%d, ESC=%d, PREV=%d, NEXT=%d)\n",
             event->key.keysym.sym, last_key, LV_KEY_UP, LV_KEY_DOWN, LV_KEY_LEFT, LV_KEY_RIGHT, LV_KEY_ENTER, LV_KEY_ESC, LV_KEY_PREV, LV_KEY_NEXT);
    }
  }
  else if (event->type == SDL_KEYUP)
  {
    key_pressed = false;
    switch (event->key.keysym.sym) {
      case SDLK_UP:     sim_key_up = false; break;
      case SDLK_DOWN:   sim_key_down = false; break;
      case SDLK_LEFT:   sim_key_left = false; break;
      case SDLK_RIGHT:  sim_key_right = false; break;
      case SDLK_RETURN:
      case SDLK_KP_ENTER: sim_key_enter = false; break;
      case SDLK_ESCAPE: sim_key_back = false; break;
    }
    if (event->key.keysym.sym == SDLK_LEFT) left_held = false;
    if (event->key.keysym.sym == SDLK_RIGHT) right_held = false;
  }
}
