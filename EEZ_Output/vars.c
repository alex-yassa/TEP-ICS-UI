#include "vars.h"
#include "ui_translate.h"
#include <time.h>
#include <stdio.h>

#ifndef PC_SIMULATOR
#include "main.h"
#include "shared_memory.h"
#endif

static const char *months_translated[LANG_COUNT][13] = {
    // PL
    { "???", "Sty", "Lut", "Mar", "Kwi", "Maj", "Cze", "Lip", "Sie", "Wrz", "Paź", "Lis", "Gru" },
    // EN
    { "???", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" },
    // UA
    { "???", "Січ", "Лют", "Бер", "Кві", "Тра", "Чер", "Лип", "Сер", "Вер", "Жов", "Лис", "Гру" }
};

static char date_buf[32] = "Jun. 08.2026";
static char time_buf[32] = "10:20:55";

const char *get_var_header_date() {
#ifndef PC_SIMULATOR
    if (HAL_HSEM_Take(HSEM_ID_SHARED_MEM, 0) == HAL_OK) {
        volatile SharedBuffer_t *shared = SHARED_BUFFER;
        uint8_t month = shared->rtc_month;
        const char *month_str = (month >= 1 && month <= 12) ? months_translated[g_current_language][month] : "???";
        snprintf(date_buf, sizeof(date_buf), "%s. %02u.%u", month_str, shared->rtc_day, shared->rtc_year);
        HAL_HSEM_Release(HSEM_ID_SHARED_MEM, 0);
    }
#else
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (timeinfo) {
        int month = timeinfo->tm_mon + 1; // tm_mon is 0-11
        const char *month_str = (month >= 1 && month <= 12) ? months_translated[g_current_language][month] : "???";
        snprintf(date_buf, sizeof(date_buf), "%s. %02d.%d", month_str, timeinfo->tm_mday, timeinfo->tm_year + 1900);
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
        snprintf(time_buf, sizeof(time_buf), "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    }
#endif
    return time_buf;
}

void set_var_header_time(const char *value) {
    (void)value;
}

static char logged_user_buf[32] = "";

const char *get_var_logged_user() {
    return logged_user_buf;
}

void set_var_logged_user(const char *value) {
    if (value) {
        snprintf(logged_user_buf, sizeof(logged_user_buf), "%s", value);
    } else {
        logged_user_buf[0] = '\0';
    }
}
