#ifndef APP_HARDWARE_H
#define APP_HARDWARE_H

#include <stdbool.h>
#include <stdint.h>

/* Abstract hardware functions called by the UI logic */
void app_set_inverter_state(bool run);
void app_log_event(const char *message);
void app_set_login_state(const char *username, uint8_t access_level);

/* Post-init UI hook: call once after ui_init() to set up custom event bindings */
void app_ui_init(void);

#endif /* APP_HARDWARE_H */
