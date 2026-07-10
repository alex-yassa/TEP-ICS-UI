/*
 * pc_simulator_hw.c
 *
 * Provides mock implementations of hardware-dependent symbols referenced by
 * the shared UI code when building for the host PC target.
 *
 * On the real STM32H7 target these are implemented in:
 *   CM4/Core/Src/main.c  (HAL_Delay, HSEM, NVIC callbacks)
 *   Common/shared_memory.h (SHARED_BUFFER mapped to 0x30040000)
 *
 * On the PC simulator we replace hardware addresses with a statically
 * allocated struct populated with realistic telemetry values so the UI
 * renders data without requiring actual hardware.
 */

#include "shared_memory.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* -----------------------------------------------------------------------
 * Mock Shared Buffer
 * Populated with realistic startup values so widgets show meaningful data.
 * CM4 main.c accesses this via the SHARED_BUFFER macro; we redefine the
 * macro target below so it points to this struct instead of 0x30040000.
 * ----------------------------------------------------------------------- */
SharedBuffer_t sim_shared_buffer = {
    .grid_volt_ln = {230.1f, 230.5f, 229.8f},
    .grid_curr = {10.2f, 9.8f, 10.5f},
    .grid_act_p = 6.8f,
    .grid_react_q = 1.2f,
    .grid_freq = 50.02f,
    .grid_cos_phi = 0.98f,

    .load_off_act_p = 2.5f,
    .load_off_react_q = 0.6f,
    .load_lab_act_p = 3.5f,
    .load_lab_react_q = 0.8f,

    .cfg_grid_max_p_import = 25.0f,
    .cfg_bat_backup_soc = 30.0f,
    .cfg_bat_max_volt = 58.4f,
    .cfg_bat_min_volt = 44.0f,
    .cfg_target_cos_phi = 0.98f,

    .ems_temp = 38.5f,
    .active_fault_word = 0,

    .bat_clusters = {
        {
            .grid_p = {3.5f, 3.4f, 3.6f},
            .grid_q = {0.1f, 0.1f, 0.2f},
            .grid_i = {15.2f, 14.8f, 15.6f},
            .batt_u = 52.1f,
            .batt_i = 33.5f,
            .batt_soc = 88.0f,
            .batt_soh = 98.0f,
            .batt_temp = 28.5f,
            .batt_alarm = 0,
            .batt_fault = 0,
            .dci_temp = 24.0f,
            .acr_temp = 25.0f,
            .bsi_status_flags = 4194304,
            .bsi_st = 1 /* BSI_STATE_GRID_FOLLOW_IDLE */
        },
        {
            .grid_p = {3.3f, 3.2f, 3.4f},
            .grid_q = {0.2f, 0.1f, 0.2f},
            .grid_i = {14.8f, 14.3f, 15.1f},
            .batt_u = 52.0f,
            .batt_i = 31.7f,
            .batt_soc = 85.0f,
            .batt_soh = 97.0f,
            .batt_temp = 29.2f,
            .batt_alarm = 0,
            .batt_fault = 0,
            .dci_temp = 24.5f,
            .acr_temp = 25.3f,
            .bsi_status_flags = 4194304,
            .bsi_st = 1 /* BSI_STATE_GRID_FOLLOW_IDLE */
        }
    },
    .pv_clusters = {
        {
            .inp_u = {569.0f, 422.0f},
            .inp_i = {8.5f, 8.2f},
            .inp_p = {4.84f, 3.46f},
            .grid_u = {232.0f, 229.0f, 232.0f},
            .grid_i = {11.2f, 10.8f, 11.5f},
            .grid_p = {2.6f, 2.5f, 2.6f},
            .grid_q = {0.05f, 0.05f, 0.06f},
            .grid_p_total = 7.7f,
            .grid_q_total = 0.16f,
            .grid_freq = 50.0f,
            .inv_temp = 42.0f,
            .r_izo = 254.0f,
            .prod_en = 20625.0f,
            .runtime = 9458.0f,
            .flags1 = 16948,
            .flags2 = 0,
            .pv_st = 2 /* PV_STATE_GRID_TIED_MPPT */
        },
        {
            .inp_u = {571.0f, 425.0f},
            .inp_i = {8.3f, 8.0f},
            .inp_p = {4.74f, 3.40f},
            .grid_u = {231.0f, 230.0f, 231.0f},
            .grid_i = {11.0f, 10.6f, 11.3f},
            .grid_p = {2.5f, 2.4f, 2.5f},
            .grid_q = {0.05f, 0.04f, 0.05f},
            .grid_p_total = 7.4f,
            .grid_q_total = 0.14f,
            .grid_freq = 50.0f,
            .inv_temp = 43.0f,
            .r_izo = 260.0f,
            .prod_en = 18450.0f,
            .runtime = 8120.0f,
            .flags1 = 16948,
            .flags2 = 0,
            .pv_st = 2 /* PV_STATE_GRID_TIED_MPPT */
        }
    },

    /* --- 2-byte Aligned Fields --- */
    .cfg_grid_nom_volt = 230,
    .cfg_grid_nom_freq = 50,
    .rtc_year = 2026,

    /* --- 1-byte Aligned Fields --- */
    .rtc_hours = 10,
    .rtc_minutes = 20,
    .rtc_seconds = 30,
    .rtc_day = 8,
    .rtc_month = 6,

    .ems_op_mode = 1,          /* EMS_MODE_ON_GRID_AUTO */
    .ems_island_state = 0,     /* ISLAND_STATE_GRID_CONNECTED */

    .contactor_grid_st = 1,    /* CONTACTOR_STATE_CLOSED */
    .contactor_grid_cmd = 1,   /* CONTACTOR_CMD_CLOSE */
    .contactor_off_st = 1,     /* CONTACTOR_STATE_CLOSED */
    .contactor_off_cmd = 1,    /* CONTACTOR_CMD_CLOSE */
    .contactor_lab_st = 1,     /* CONTACTOR_STATE_CLOSED */
    .contactor_lab_cmd = 1,    /* CONTACTOR_CMD_CLOSE */

    .cfg_tou_chg_start_h = 22,
    .cfg_tou_chg_start_m = 0,
    .cfg_tou_chg_end_h = 6,
    .cfg_tou_chg_end_m = 0,
    .cfg_tou_disch_start_h = 8,
    .cfg_tou_disch_start_m = 0,
    .cfg_tou_disch_end_h = 16,
    .cfg_tou_disch_end_m = 0,

    .cm7_cpu_load = 45,
    .cm4_cpu_load = 25,
};

/*
 * Override the SHARED_BUFFER macro so any code that calls
 *   SHARED_BUFFER->pv_voltage
 * actually reads/writes sim_shared_buffer on the host instead of
 * dereferencing the raw SRAM3 address (0x30040000).
 *
 * This is done via a compiler -D flag in CMakeLists.txt:
 *   add_compile_definitions(SHARED_BUFFER=((volatile SharedBuffer_t*)&sim_shared_buffer))
 *
 * The definition is repeated here as documentation. The CMakeLists.txt
 * passes it at build time so it applies to every translation unit.
 */

/* -----------------------------------------------------------------------
 * HAL stub — HAL_Delay is called from some init paths.
 * On the simulator we simply do nothing.
 * ----------------------------------------------------------------------- */
void HAL_Delay(uint32_t Delay)
{
    (void)Delay;
    /* No-op on PC simulator */
}

/* -----------------------------------------------------------------------
 * Logging stub — called optionally from UI tick code.
 * Prints to stdout so it is visible during development.
 * ----------------------------------------------------------------------- */
void sim_log(const char *msg)
{
    printf("[PC SIM] %s\n", msg);
}

void app_set_inverter_state(bool run)
{
    printf("[PC SIMULATOR] Inverter state command: %s\n", run ? "START" : "STOP");
}

void app_log_event(const char *message)
{
    printf("[PC SIMULATOR EVENT LOG] %s\n", message);
}

void app_set_login_state(const char *username, uint8_t access_level)
{
    strncpy((char*)sim_shared_buffer.login_username, username, sizeof(sim_shared_buffer.login_username) - 1);
    sim_shared_buffer.login_username[sizeof(sim_shared_buffer.login_username) - 1] = '\0';
    sim_shared_buffer.login_access_level = access_level;
    printf("[PC SIMULATOR AUTH] User logged in: %s (level %d)\n", username, access_level);
}
