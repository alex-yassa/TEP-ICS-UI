#include "vars.h"
#include <time.h>
#include <stdio.h>

#ifndef PC_SIMULATOR
#include "main.h"
#include "shared_memory.h"

static const char *months[] = {
    "???",
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
#endif

static char date_buf[32] = "Jun. 08.2026";
static char time_buf[32] = "10:20:55";

const char *get_var_header_date() {
#ifndef PC_SIMULATOR
    if (HAL_HSEM_Take(HSEM_ID_SHARED_MEM, 0) == HAL_OK) {
        volatile SharedBuffer_t *shared = SHARED_BUFFER;
        uint8_t month = shared->rtc_month;
        const char *month_str = (month >= 1 && month <= 12) ? months[month] : "???";
        snprintf(date_buf, sizeof(date_buf), "%s. %02u.%u", month_str, shared->rtc_day, shared->rtc_year);
        HAL_HSEM_Release(HSEM_ID_SHARED_MEM, 0);
    }
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
#ifndef PC_SIMULATOR
    if (HAL_HSEM_Take(HSEM_ID_SHARED_MEM, 0) == HAL_OK) {
        volatile SharedBuffer_t *shared = SHARED_BUFFER;
        snprintf(time_buf, sizeof(time_buf), "%02u:%02u:%02u", shared->rtc_hours, shared->rtc_minutes, shared->rtc_seconds);
        HAL_HSEM_Release(HSEM_ID_SHARED_MEM, 0);
    }
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
