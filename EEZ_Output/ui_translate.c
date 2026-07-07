#include "ui_translate.h"
#include "screens.h"
#include <string.h>

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
    { "Sys Settings View",      { "Widok ustawień systemowych", "Sys Settings View",      "Системні налаштування" } },

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
    if (objects.label_seventh_view) lv_label_set_text(objects.label_seventh_view, translate("Sys Settings View", lang));

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
