#include "vars.h"
#include <time.h>
#include <stdio.h>

#ifdef STM32H757xx
#include "main.h"
#endif

static char date_buf[32] = "Jun. 08.2026";
static char time_buf[32] = "10:20:55";

const char *get_var_header_date() {
#ifdef STM32H757xx
    snprintf(date_buf, sizeof(date_buf), "Jun. 12.2026");
#else
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (timeinfo) {
        strftime(date_buf, sizeof(date_buf), "%b. %d.%Y", timeinfo);
    }
#endif
    return date_buf;
}

void set_var_header_date(const char *value) {
    (void)value;
}

const char *get_var_header_time() {
#ifdef STM32H757xx
    uint32_t ticks = HAL_GetTick();
    uint32_t total_seconds = 14 * 3600 + 34 * 60 + 47 + (ticks / 1000);
    uint32_t seconds = total_seconds % 60;
    uint32_t minutes = (total_seconds / 60) % 60;
    uint32_t hours = (total_seconds / 3600) % 24;
    snprintf(time_buf, sizeof(time_buf), "%02u:%02u:%02u", (unsigned int)hours, (unsigned int)minutes, (unsigned int)seconds);
#else
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (timeinfo) {
        strftime(time_buf, sizeof(time_buf), "%H:%M:%S", timeinfo);
    }
#endif
    return time_buf;
}

void set_var_header_time(const char *value) {
    (void)value;
}
