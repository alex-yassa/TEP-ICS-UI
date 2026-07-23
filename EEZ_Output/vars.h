#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_LOGGED_USER = 0
};

// Native global variables

extern const char *get_var_header_date();
extern void set_var_header_date(const char *value);
extern const char *get_var_header_time();
extern void set_var_header_time(const char *value);
extern int32_t get_var_battery_clusters_count();
extern void set_var_battery_clusters_count(int32_t value);
extern int32_t get_var_pv_clusters_count();
extern void set_var_pv_clusters_count(int32_t value);
extern double get_var_cfg_grid_max_p_import();
extern void set_var_cfg_grid_max_p_import(double value);
extern double get_var_cfg_bat_backup_soc();
extern void set_var_cfg_bat_backup_soc(double value);
extern double get_var_cfg_bat_max_volt();
extern void set_var_cfg_bat_max_volt(double value);
extern double get_var_cfg_bat_min_volt();
extern void set_var_cfg_bat_min_volt(double value);
extern double get_var_cfg_target_cos_phi();
extern void set_var_cfg_target_cos_phi(double value);
extern int32_t get_var_cfg_grid_nom_volt();
extern void set_var_cfg_grid_nom_volt(int32_t value);
extern int32_t get_var_cfg_grid_nom_freq();
extern void set_var_cfg_grid_nom_freq(int32_t value);
extern const char *get_var_logged_user();
extern void set_var_logged_user(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/