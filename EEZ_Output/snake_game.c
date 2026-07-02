#include "snake_game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define BOARD_COLS 22
#define BOARD_ROWS 22
#define CELL_SIZE 20
#define MAX_SNAKE_LEN (BOARD_COLS * BOARD_ROWS)

typedef struct {
    int x;
    int y;
} point_t;

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} direction_t;

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_GAME_OVER
} game_state_t;

// Game state variables
static point_t snake[MAX_SNAKE_LEN];
static int snake_len = 0;
static direction_t current_dir = DIR_RIGHT;
static direction_t next_dir = DIR_RIGHT;
static point_t food;
static int score = 0;
static int high_score = 0;
static game_state_t game_state = STATE_IDLE;

static lv_timer_t *game_timer = NULL;
static lv_obj_t *game_board_obj = NULL;
static lv_obj_t *score_label = NULL;
static lv_obj_t *high_score_label = NULL;
static lv_obj_t *status_label = NULL;
static lv_obj_t *btn_start_label = NULL;
static lv_obj_t *game_container = NULL;

static void update_score_labels(void) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Score: %d", score);
    lv_label_set_text(score_label, buf);

    snprintf(buf, sizeof(buf), "High Score: %d", high_score);
    lv_label_set_text(high_score_label, buf);
}

static void update_status_label(void) {
    switch (game_state) {
        case STATE_IDLE:
            lv_label_set_text(status_label, "Press START to play");
            lv_obj_set_style_text_color(status_label, lv_color_hex(0x94a3b8), LV_PART_MAIN);
            break;
        case STATE_RUNNING:
            lv_label_set_text(status_label, "Playing... Use Arrows/D-pad");
            lv_obj_set_style_text_color(status_label, lv_color_hex(0x10b981), LV_PART_MAIN);
            break;
        case STATE_PAUSED:
            lv_label_set_text(status_label, "Game Paused");
            lv_obj_set_style_text_color(status_label, lv_color_hex(0xf59e0b), LV_PART_MAIN);
            break;
        case STATE_GAME_OVER:
            lv_label_set_text(status_label, "GAME OVER! Try again");
            lv_obj_set_style_text_color(status_label, lv_color_hex(0xef4444), LV_PART_MAIN);
            break;
    }
}

static void spawn_food(void) {
    bool on_snake = true;
    while (on_snake) {
        food.x = rand() % BOARD_COLS;
        food.y = rand() % BOARD_ROWS;
        on_snake = false;
        for (int i = 0; i < snake_len; i++) {
            if (snake[i].x == food.x && snake[i].y == food.y) {
                on_snake = true;
                break;
            }
        }
    }
}

static void game_reset(void) {
    snake_len = 4;
    // Initial snake position in the middle, heading right
    snake[0].x = 10; snake[0].y = 10;
    snake[1].x = 9;  snake[1].y = 10;
    snake[2].x = 8;  snake[2].y = 10;
    snake[3].x = 7;  snake[3].y = 10;

    current_dir = DIR_RIGHT;
    next_dir = DIR_RIGHT;
    score = 0;
    spawn_food();
    update_score_labels();
}

static void change_direction(direction_t dir) {
    if (dir == DIR_UP && current_dir != DIR_DOWN) next_dir = DIR_UP;
    if (dir == DIR_DOWN && current_dir != DIR_UP) next_dir = DIR_DOWN;
    if (dir == DIR_LEFT && current_dir != DIR_RIGHT) next_dir = DIR_LEFT;
    if (dir == DIR_RIGHT && current_dir != DIR_LEFT) next_dir = DIR_RIGHT;
}

static void game_tick_cb(lv_timer_t *timer) {
    (void)timer;

    if (game_state != STATE_RUNNING) return;

    current_dir = next_dir;

    // Calculate new head position
    point_t new_head = snake[0];
    switch (current_dir) {
        case DIR_UP:    new_head.y--; break;
        case DIR_DOWN:  new_head.y++; break;
        case DIR_LEFT:  new_head.x--; break;
        case DIR_RIGHT: new_head.x++; break;
    }

    // Check boundary collisions
    if (new_head.x < 0 || new_head.x >= BOARD_COLS || new_head.y < 0 || new_head.y >= BOARD_ROWS) {
        game_state = STATE_GAME_OVER;
        update_status_label();
        lv_label_set_text(btn_start_label, "START");
        return;
    }

    // Check self collisions
    for (int i = 0; i < snake_len; i++) {
        if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
            game_state = STATE_GAME_OVER;
            update_status_label();
            lv_label_set_text(btn_start_label, "START");
            return;
        }
    }

    // Check food consumption
    bool ate_food = (new_head.x == food.x && new_head.y == food.y);

    if (ate_food) {
        score += 10;
        if (score > high_score) {
            high_score = score;
        }
        update_score_labels();
        spawn_food();
        // Shift and grow snake
        snake_len++;
    }

    // Shift body segments backward
    for (int i = snake_len - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] = new_head;

    // Request board redraw
    lv_obj_invalidate(game_board_obj);
}

static void game_board_draw_cb(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);

    // Render configuration
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_opa = LV_OPA_COVER;

    // Draw snake body segments
    rect_dsc.radius = 4;
    rect_dsc.bg_color = lv_color_hex(0x059669); // Emerald-600
    for (int i = 1; i < snake_len; i++) {
        lv_area_t cell_area;
        cell_area.x1 = obj->coords.x1 + snake[i].x * CELL_SIZE + 1;
        cell_area.y1 = obj->coords.y1 + snake[i].y * CELL_SIZE + 1;
        cell_area.x2 = cell_area.x1 + CELL_SIZE - 2;
        cell_area.y2 = cell_area.y1 + CELL_SIZE - 2;
        lv_draw_rect(draw_ctx, &rect_dsc, &cell_area);
    }

    // Draw snake head
    rect_dsc.radius = 6;
    rect_dsc.bg_color = lv_color_hex(0x10b981); // Emerald-500
    if (snake_len > 0) {
        lv_area_t head_area;
        head_area.x1 = obj->coords.x1 + snake[0].x * CELL_SIZE + 1;
        head_area.y1 = obj->coords.y1 + snake[0].y * CELL_SIZE + 1;
        head_area.x2 = head_area.x1 + CELL_SIZE - 2;
        head_area.y2 = head_area.y1 + CELL_SIZE - 2;
        lv_draw_rect(draw_ctx, &rect_dsc, &head_area);
    }

    // Draw food item
    rect_dsc.radius = CELL_SIZE / 2; // Circular
    rect_dsc.bg_color = lv_color_hex(0xef4444); // Red-500
    lv_area_t food_area;
    food_area.x1 = obj->coords.x1 + food.x * CELL_SIZE + 2;
    food_area.y1 = obj->coords.y1 + food.y * CELL_SIZE + 2;
    food_area.x2 = food_area.x1 + CELL_SIZE - 4;
    food_area.y2 = food_area.y1 + CELL_SIZE - 4;
    lv_draw_rect(draw_ctx, &rect_dsc, &food_area);
}

// Directional Control Handlers
static void btn_up_click_cb(lv_event_t *e) { (void)e; change_direction(DIR_UP); }
static void btn_down_click_cb(lv_event_t *e) { (void)e; change_direction(DIR_DOWN); }
static void btn_left_click_cb(lv_event_t *e) { (void)e; change_direction(DIR_LEFT); }
static void btn_right_click_cb(lv_event_t *e) { (void)e; change_direction(DIR_RIGHT); }

// Game State Control Handlers
static void btn_start_click_cb(lv_event_t *e) {
    (void)e;
    if (game_state == STATE_IDLE || game_state == STATE_GAME_OVER) {
        game_reset();
        game_state = STATE_RUNNING;
        lv_label_set_text(btn_start_label, "PAUSE");
    } else if (game_state == STATE_RUNNING) {
        game_state = STATE_PAUSED;
        lv_label_set_text(btn_start_label, "RESUME");
    } else if (game_state == STATE_PAUSED) {
        game_state = STATE_RUNNING;
        lv_label_set_text(btn_start_label, "PAUSE");
    }
    update_status_label();
}

static void btn_reset_click_cb(lv_event_t *e) {
    (void)e;
    game_reset();
    game_state = STATE_IDLE;
    lv_label_set_text(btn_start_label, "START");
    update_status_label();
    lv_obj_invalidate(game_board_obj);
}

// Keyboard input callback for simulator / direct input
void snake_game_handle_key(uint32_t key) {
    if (game_state == STATE_RUNNING) {
        switch (key) {
            case LV_KEY_UP:    change_direction(DIR_UP); break;
            case LV_KEY_DOWN:  change_direction(DIR_DOWN); break;
            case LV_KEY_LEFT:  change_direction(DIR_LEFT); break;
            case LV_KEY_RIGHT: change_direction(DIR_RIGHT); break;
        }
    } else if (key == LV_KEY_ENTER) {
        btn_start_click_cb(NULL);
    }
}

void snake_game_init(lv_obj_t *parent) {
    srand(time(NULL));

    // Main layout container (Slate dark scheme)
    lv_obj_t *container = lv_obj_create(parent);
    game_container = container;
    lv_obj_set_pos(container, 103, 50); // Centered on 1024x600 screen
    lv_obj_set_size(container, 818, 500);
    lv_obj_set_style_bg_color(container, lv_color_hex(0x0f172a), LV_PART_MAIN); // Slate-900
    lv_obj_set_style_border_color(container, lv_color_hex(0x1e293b), LV_PART_MAIN);
    lv_obj_set_style_border_width(container, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(container, 12, LV_PART_MAIN);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(container, LV_OBJ_FLAG_HIDDEN); // Hidden by default

    // Left Panel: Game Board
    game_board_obj = lv_obj_create(container);
    lv_obj_set_pos(game_board_obj, 15, 15);
    lv_obj_set_size(game_board_obj, BOARD_COLS * CELL_SIZE + 6, BOARD_ROWS * CELL_SIZE + 6); // Add size for borders
    lv_obj_set_style_bg_color(game_board_obj, lv_color_hex(0x1e293b), LV_PART_MAIN); // Slate-800
    lv_obj_set_style_border_color(game_board_obj, lv_color_hex(0x334155), LV_PART_MAIN); // Slate-700
    lv_obj_set_style_border_width(game_board_obj, 3, LV_PART_MAIN);
    lv_obj_set_style_radius(game_board_obj, 8, LV_PART_MAIN);
    lv_obj_clear_flag(game_board_obj, LV_OBJ_FLAG_SCROLLABLE);

    // Add drawing event listener
    lv_obj_add_event_cb(game_board_obj, game_board_draw_cb, LV_EVENT_DRAW_MAIN, NULL);

    // Right Panel: Dashboard Controls & Info (Width: 320, Height: 440)
    lv_obj_t *panel = lv_obj_create(container);
    lv_obj_set_pos(panel, 480, 15);
    lv_obj_set_size(panel, 310, 446);
    lv_obj_set_style_bg_color(panel, lv_color_hex(0x1e293b), LV_PART_MAIN); // Slate-800
    lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(panel, 8, LV_PART_MAIN);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

    // Score label
    score_label = lv_label_create(panel);
    lv_obj_set_pos(score_label, 15, 15);
    lv_obj_set_style_text_color(score_label, lv_color_hex(0xf1f5f9), LV_PART_MAIN);
    lv_obj_set_style_text_font(score_label, &lv_font_montserrat_18, LV_PART_MAIN);

    // High Score label
    high_score_label = lv_label_create(panel);
    lv_obj_set_pos(high_score_label, 15, 40);
    lv_obj_set_style_text_color(high_score_label, lv_color_hex(0x94a3b8), LV_PART_MAIN);
    lv_obj_set_style_text_font(high_score_label, &lv_font_montserrat_14, LV_PART_MAIN);

    // Game status label
    status_label = lv_label_create(panel);
    lv_obj_set_pos(status_label, 15, 75);
    lv_obj_set_style_text_font(status_label, &lv_font_montserrat_12, LV_PART_MAIN);

    // Game D-pad container (Center: x=155, y=230)
    lv_obj_t *dpad = lv_obj_create(panel);
    lv_obj_set_pos(dpad, 65, 120);
    lv_obj_set_size(dpad, 180, 180);
    lv_obj_set_style_bg_opa(dpad, 0, LV_PART_MAIN); // Transparent background
    lv_obj_set_style_border_width(dpad, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(dpad, 0, LV_PART_MAIN); // Reset padding to prevent button clipping
    lv_obj_clear_flag(dpad, LV_OBJ_FLAG_SCROLLABLE);

    // Common style macro helper for D-pad buttons
    #define STYLE_DPAD_BTN(btn, label_text) do { \
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x334155), LV_PART_MAIN); \
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x475569), LV_STATE_PRESSED); \
        lv_obj_set_style_border_color(btn, lv_color_hex(0x475569), LV_PART_MAIN); \
        lv_obj_set_style_border_width(btn, 1, LV_PART_MAIN); \
        lv_obj_set_style_radius(btn, 8, LV_PART_MAIN); \
        lv_obj_t *lbl = lv_label_create(btn); \
        lv_label_set_text(lbl, label_text); \
        lv_obj_center(lbl); \
        lv_obj_set_style_text_color(lbl, lv_color_hex(0xf1f5f9), LV_PART_MAIN); \
        lv_obj_set_style_text_font(lbl, &lv_font_montserrat_12, LV_PART_MAIN); \
    } while(0)

    // D-pad Up button
    lv_obj_t *btn_up = lv_btn_create(dpad);
    lv_obj_set_pos(btn_up, 60, 10);
    lv_obj_set_size(btn_up, 60, 50);
    lv_obj_add_event_cb(btn_up, btn_up_click_cb, LV_EVENT_CLICKED, NULL);
    STYLE_DPAD_BTN(btn_up, "UP");

    // D-pad Left button
    lv_obj_t *btn_left = lv_btn_create(dpad);
    lv_obj_set_pos(btn_left, 0, 65);
    lv_obj_set_size(btn_left, 60, 50);
    lv_obj_add_event_cb(btn_left, btn_left_click_cb, LV_EVENT_CLICKED, NULL);
    STYLE_DPAD_BTN(btn_left, "LEFT");

    // D-pad Right button
    lv_obj_t *btn_right = lv_btn_create(dpad);
    lv_obj_set_pos(btn_right, 120, 65);
    lv_obj_set_size(btn_right, 60, 50);
    lv_obj_add_event_cb(btn_right, btn_right_click_cb, LV_EVENT_CLICKED, NULL);
    STYLE_DPAD_BTN(btn_right, "RIGHT");

    // D-pad Down button
    lv_obj_t *btn_down = lv_btn_create(dpad);
    lv_obj_set_pos(btn_down, 60, 120);
    lv_obj_set_size(btn_down, 60, 50);
    lv_obj_add_event_cb(btn_down, btn_down_click_cb, LV_EVENT_CLICKED, NULL);
    STYLE_DPAD_BTN(btn_down, "DOWN");

    // Action Control Buttons: Start/Pause and Reset
    lv_obj_t *btn_start = lv_btn_create(panel);
    lv_obj_set_pos(btn_start, 25, 380);
    lv_obj_set_size(btn_start, 120, 45);
    lv_obj_set_style_bg_color(btn_start, lv_color_hex(0x059669), LV_PART_MAIN); // Emerald-600
    lv_obj_set_style_bg_color(btn_start, lv_color_hex(0x047857), LV_STATE_PRESSED);
    lv_obj_set_style_radius(btn_start, 6, LV_PART_MAIN);
    lv_obj_add_event_cb(btn_start, btn_start_click_cb, LV_EVENT_CLICKED, NULL);
    btn_start_label = lv_label_create(btn_start);
    lv_label_set_text(btn_start_label, "START");
    lv_obj_center(btn_start_label);
    lv_obj_set_style_text_font(btn_start_label, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_color(btn_start_label, lv_color_hex(0xffffff), LV_PART_MAIN);

    lv_obj_t *btn_reset = lv_btn_create(panel);
    lv_obj_set_pos(btn_reset, 165, 380);
    lv_obj_set_size(btn_reset, 120, 45);
    lv_obj_set_style_bg_color(btn_reset, lv_color_hex(0x475569), LV_PART_MAIN); // Slate-600
    lv_obj_set_style_bg_color(btn_reset, lv_color_hex(0x334155), LV_STATE_PRESSED);
    lv_obj_set_style_radius(btn_reset, 6, LV_PART_MAIN);
    lv_obj_add_event_cb(btn_reset, btn_reset_click_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *btn_reset_label = lv_label_create(btn_reset);
    lv_label_set_text(btn_reset_label, "RESET");
    lv_obj_center(btn_reset_label);
    lv_obj_set_style_text_font(btn_reset_label, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_color(btn_reset_label, lv_color_hex(0xffffff), LV_PART_MAIN);

    // Initial game status setup
    game_reset();
    game_state = STATE_IDLE;
    update_status_label();

    // Create the game loop timer (runs every 150ms)
    if (game_timer == NULL) {
        game_timer = lv_timer_create(game_tick_cb, 150, NULL);
    } else {
        lv_timer_resume(game_timer);
    }
}

void snake_game_toggle_visibility(void) {
    if (game_container == NULL) {
        // First time toggle: create container on the system-wide top layer
        snake_game_init(lv_layer_top());
    }

    if (lv_obj_has_flag(game_container, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(game_container, LV_OBJ_FLAG_HIDDEN);
        if (game_timer) {
            lv_timer_resume(game_timer);
        }
        update_status_label();
        lv_obj_invalidate(game_board_obj);
    } else {
        lv_obj_add_flag(game_container, LV_OBJ_FLAG_HIDDEN);
        if (game_state == STATE_RUNNING) {
            game_state = STATE_PAUSED;
            lv_label_set_text(btn_start_label, "RESUME");
            update_status_label();
        }
        if (game_timer) {
            lv_timer_pause(game_timer);
        }
    }
}

bool snake_game_is_visible(void) {
    return (game_container != NULL && !lv_obj_has_flag(game_container, LV_OBJ_FLAG_HIDDEN));
}
