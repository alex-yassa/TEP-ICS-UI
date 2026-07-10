#include "ui_translate.h"
#include "screens.h"
#include <string.h>
#include <stdio.h>

int g_current_language = 0; // Default to index 0 (PL)

typedef struct {
    const char *key;
    const char *translations[LANG_COUNT];
} translation_entry_t;

static const translation_entry_t translation_table[] = {
    { "Dashboard",        { "Panel główny",      "Dashboard",        "Панель" } },
    { "Grid",             { "Sieć",              "Grid",             "Мережа" } },
    { "Storage clusters", { "Magazyny energii",  "Storage clusters", "Накопичувачі" } },
    { "Gen clusters",     { "Generatory",        "Gen clusters",     "Генерація" } },
    { "Load Management",  { "Zarządzanie obc.",  "Load Management",  "Керування нав." } },
    { "Diagnostics",      { "Diagnostyka",       "Diagnostics",      "Діагностика" } },
    { "Sys settings",     { "Ustawienia sys.",   "Sys settings",     "Налаштув. сист." } },

    { "Dashboard view",         { "Widok panelu głównego",      "Dashboard view",         "Панель приладів" } },
    { "Grid view",              { "Widok sieci",                "Grid view",              "Перегляд мережі" } },
    { "Storage clusters view",  { "Widok magazynów energii",    "Storage clusters view",  "Накопичувачі" } },
    { "Gen Clusters View",      { "Widok generatorów",          "Gen Clusters View",      "Перегляд генерації" } },
    { "Load Management View",   { "Widok zarządzania obc.",     "Load Management View",   "Керування навантаженням" } },
    { "Diagnostics View",       { "Widok diagnostyki",          "Diagnostics View",       "Діагностика" } },
    { "SYSTEM CONFIGURATION",   { "KONFIGURACJA SYSTEMU",       "SYSTEM CONFIGURATION",   "КОНФІГУРАЦІЯ СИСТЕМИ" } },

    { "Battery Clusters Count (Max 2)",         { "Liczba modułów baterii (Maks 2)",        "Battery Clusters Count (Max 2)",         "Кількість батарейних кластерів (Макс 2)" } },
    { "PV Clusters Count (Max 2)",              { "Liczba modułów PV (Maks 2)",             "PV Clusters Count (Max 2)",              "Кількість фотоелектричних кластерів (Макс 2)" } },
    { "Peak Shaving Import Limit (kW)",         { "Limit importu mocy szczytowej (kW)",     "Peak Shaving Import Limit (kW)",         "Ліміт зрізання піків споживання (кВт)" } },
    { "Backup Battery SoC Threshold (%)",       { "Próg SoC baterii rezerwowej (%)",        "Backup Battery SoC Threshold (%)",       "Порогове значення заряду АКБ (%)" } },
    { "Battery Max Charge Voltage (V)",         { "Maks. napięcie ładowania baterii (V)",   "Battery Max Charge Voltage (V)",         "Макс. напруга заряду АКБ (В)" } },
    { "Battery Min Discharge Voltage (V)",       { "Min. napięcie rozładowania baterii (V)", "Battery Min Discharge Voltage (V)",       "Мін. напруга розряду АКБ (В)" } },
    { "STATCOM Target Power Factor (cos phi)",  { "Docelowy współczynnik mocy STATCOM",     "STATCOM Target Power Factor (cos phi)",  "Цільовий коефіцієнт потужності STATCOM" } },
    { "Nominal Grid Voltage (V)",               { "Nominalne napięcie sieci (V)",           "Nominal Grid Voltage (V)",               "Номінальна напруга мережі (В)" } },
    { "Nominal Grid Frequency (Hz)",            { "Nominalna częstotliwość sieci (Hz)",     "Nominal Grid Frequency (Hz)",            "Номінальна частота мережі (Гц)" } },

    { "Apply",             { "Zastosuj",              "Apply",             "Застосувати" } },
    { "Reset Changes",     { "Resetuj zmiany",        "Reset Changes",     "Скинути zmiany" } },

    { "USER SIGN IN",      { "LOGOWANIE UŻYTKOWNIKA", "USER SIGN IN",      "ВХІД КОРИСТУВАЧА" } },
    { "Enter Password",    { "Wpisz hasło",           "Enter Password",    "Введіть пароль" } },
    { "Invalid Password!", { "Błędne hasło!",         "Invalid Password!", "Невірний пароль!" } },
    { "Cancel",            { "Anuluj",                "Cancel",            "Скасувати" } },
    { "Sign In",           { "Zaloguj",               "Sign In",           "Увійти" } },
    { "Login",             { "Zaloguj",               "Login",             "Увійти" } },
    { "Logout",            { "Wyloguj",               "Logout",            "Вийти" } },
    { "Guest",             { "Gość",                  "Guest",             "Гість" } },
    { "%s (Admin)",        { "%s (Admin)",            "%s (Admin)",        "%s (Адмін)" } },
    { "%s (Oper)",         { "%s (Oper)",             "%s (Oper)",         "%s (Оператор)" } },
    { "%s (View)",         { "%s (Podgląd)",          "%s (View)",         "%s (Переглядач)" } }
};

const char *translate(const char *key, lang_t lang) {
    if (!key) return "";
    if (lang < 0 || lang >= LANG_COUNT) lang = LANG_EN;

    int num_entries = sizeof(translation_table) / sizeof(translation_entry_t);
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(translation_table[i].key, key) == 0) {
            return translation_table[i].translations[lang];
        }
    }
    return key;
}

static void update_button_text(lv_obj_t *btn, const char *key, lang_t lang) {
    if (btn) {
        lv_obj_t *lbl = lv_obj_get_child(btn, 1);
        if (lbl) {
            lv_label_set_text(lbl, translate(key, lang));
        }
    }
}

void ui_translate_update(void) {
    lang_t lang = (lang_t)g_current_language;

    // 1. Sidebar menu navigation buttons
    update_button_text(objects.dashboard_button, "Dashboard", lang);
    update_button_text(objects.view_1_button, "Grid", lang);
    update_button_text(objects.view_2_button, "Storage clusters", lang);
    update_button_text(objects.gen_clusters_button, "Gen clusters", lang);
    update_button_text(objects.load_management_button, "Load Management", lang);
    update_button_text(objects.diagnostics_button, "Diagnostics", lang);
    update_button_text(objects.sys_settings_button, "Sys settings", lang);

    // 2. View titles inside tabs
    if (objects.label_dashboard_title) lv_label_set_text(objects.label_dashboard_title, translate("Dashboard view", lang));
    if (objects.label_second_view) lv_label_set_text(objects.label_second_view, translate("Grid view", lang));
    if (objects.label_third_view) lv_label_set_text(objects.label_third_view, translate("Storage clusters view", lang));
    if (objects.label_fourth_view) lv_label_set_text(objects.label_fourth_view, translate("Gen Clusters View", lang));
    if (objects.label_fifth_view) lv_label_set_text(objects.label_fifth_view, translate("Load Management View", lang));
    if (objects.label_sixth_view) lv_label_set_text(objects.label_sixth_view, translate("Diagnostics View", lang));
    if (objects.label_settings_title) {
        char buf[64];
        snprintf(buf, sizeof(buf), "%s (1/3)", translate("SYSTEM CONFIGURATION", lang));
        lv_label_set_text(objects.label_settings_title, buf);
    }
    if (objects.label_settings_title_2) {
        char buf[64];
        snprintf(buf, sizeof(buf), "%s (2/3)", translate("SYSTEM CONFIGURATION", lang));
        lv_label_set_text(objects.label_settings_title_2, buf);
    }
    if (objects.label_settings_title_3) {
        char buf[64];
        snprintf(buf, sizeof(buf), "%s (3/3)", translate("SYSTEM CONFIGURATION", lang));
        lv_label_set_text(objects.label_settings_title_3, buf);
    }

    // Settings rows
    if (objects.label_row_0) lv_label_set_text(objects.label_row_0, translate("Battery Clusters Count (Max 2)", lang));
    if (objects.label_row_1) lv_label_set_text(objects.label_row_1, translate("PV Clusters Count (Max 2)", lang));
    if (objects.label_row_2) lv_label_set_text(objects.label_row_2, translate("Peak Shaving Import Limit (kW)", lang));
    if (objects.label_row_3) lv_label_set_text(objects.label_row_3, translate("Backup Battery SoC Threshold (%)", lang));
    if (objects.label_row_4) lv_label_set_text(objects.label_row_4, translate("Battery Max Charge Voltage (V)", lang));
    if (objects.label_row_5) lv_label_set_text(objects.label_row_5, translate("Battery Min Discharge Voltage (V)", lang));
    if (objects.label_row_6) lv_label_set_text(objects.label_row_6, translate("STATCOM Target Power Factor (cos phi)", lang));
    if (objects.label_row_7) lv_label_set_text(objects.label_row_7, translate("Nominal Grid Voltage (V)", lang));
    if (objects.label_row_8) lv_label_set_text(objects.label_row_8, translate("Nominal Grid Frequency (Hz)", lang));

    // Settings buttons
    if (objects.settings_apply_btn_label) lv_label_set_text(objects.settings_apply_btn_label, translate("Apply", lang));
    if (objects.settings_apply_btn_label_2) lv_label_set_text(objects.settings_apply_btn_label_2, translate("Apply", lang));
    if (objects.settings_apply_btn_label_3) lv_label_set_text(objects.settings_apply_btn_label_3, translate("Apply", lang));
    if (objects.settings_reset_btn_label) lv_label_set_text(objects.settings_reset_btn_label, translate("Reset Changes", lang));
    if (objects.settings_reset_btn_label_2) lv_label_set_text(objects.settings_reset_btn_label_2, translate("Reset Changes", lang));
    if (objects.settings_reset_btn_label_3) lv_label_set_text(objects.settings_reset_btn_label_3, translate("Reset Changes", lang));

    // 3. Login modal texts
    if (objects.login_title_label) lv_label_set_text(objects.login_title_label, translate("USER SIGN IN", lang));
    if (objects.login_cancel_btn_label) lv_label_set_text(objects.login_cancel_btn_label, translate("Cancel", lang));
    if (objects.login_signin_btn_label) lv_label_set_text(objects.login_signin_btn_label, translate("Sign In", lang));
    if (objects.login_password_ta) {
        const char *curr_placeholder = lv_textarea_get_placeholder_text(objects.login_password_ta);
        if (curr_placeholder && (strcmp(curr_placeholder, translate("Invalid Password!", LANG_EN)) == 0 ||
                                 strcmp(curr_placeholder, translate("Invalid Password!", LANG_PL)) == 0 ||
                                 strcmp(curr_placeholder, translate("Invalid Password!", LANG_UA)) == 0)) {
            lv_textarea_set_placeholder_text(objects.login_password_ta, translate("Invalid Password!", lang));
        } else {
            lv_textarea_set_placeholder_text(objects.login_password_ta, translate("Enter Password", lang));
        }
    }

    // 4. Update login status and button text
    update_login_status_translations(lang);
}
