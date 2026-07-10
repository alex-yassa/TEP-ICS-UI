#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <stdint.h>

/* Shared Memory Address: SRAM3 in D2 domain is visible to both CM7 and CM4 */
#define SHARED_SRAM_ADDR          ((uint32_t)0x30040000)

/* Hardware Semaphore ID for protecting shared buffer access */
#define HSEM_ID_SHARED_MEM        (1)

#define MAX_BATTERY_CLUSTERS      2
#define MAX_PV_CLUSTERS           2

typedef enum {
  EMS_MODE_INIT = 0,
  EMS_MODE_ON_GRID_AUTO = 1,
  EMS_MODE_ON_GRID_PEAK_SHAVING = 2,
  EMS_MODE_ON_GRID_TOU_ARBITRAGE = 3,
  EMS_MODE_ISLAND_BACKUP = 4,
  EMS_MODE_GRID_RESYNC = 5,
  EMS_MODE_EMERGENCY_STOP = 6
} EmsOpMode_t;

typedef enum {
  ISLAND_STATE_GRID_CONNECTED = 0,
  ISLAND_STATE_OUTAGE_DETECTED = 1,
  ISLAND_STATE_BLACK_START = 2,
  ISLAND_STATE_STABILIZED = 3,
  ISLAND_STATE_LOAD_SHEDDING = 4,
  ISLAND_STATE_RESYNCING = 5
} EmsIslandState_t;

typedef enum {
  BSI_STATE_OFFLINE = 0,
  BSI_STATE_GRID_FOLLOW_IDLE = 1,
  BSI_STATE_GRID_FOLLOW_CHARGE = 2,
  BSI_STATE_GRID_FOLLOW_DISCHARGE = 3,
  BSI_STATE_GRID_FORMING = 4,
  BSI_STATE_STATCOM = 5,
  BSI_STATE_FAULT = 6
} BsiState_t;

typedef enum {
  PV_STATE_OFFLINE = 0,
  PV_STATE_STANDBY = 1,
  PV_STATE_GRID_TIED_MPPT = 2,
  PV_STATE_DERATED = 3,
  PV_STATE_FAULT = 4
} PvState_t;

typedef enum {
  CONTACTOR_STATE_OPEN = 0,
  CONTACTOR_STATE_CLOSED = 1,
  CONTACTOR_STATE_FAULT = 2
} ContactorState_t;

typedef enum {
  CONTACTOR_CMD_OPEN = 0,
  CONTACTOR_CMD_CLOSE = 1
} ContactorCmd_t;

typedef enum {
  ACCESS_LEVEL_GUEST = 0,
  ACCESS_LEVEL_OPERATOR = 1,
  ACCESS_LEVEL_ADMIN = 2
} AccessLevel_t;

/* Unified battery bank and BESS inverter cluster structure aligned with BSI1000 */
typedef struct {
  /* --- 4-byte Aligned Fields --- */
  float grid_p[3];            /* BSI AC Active Power per phase [kW] (GridP1..3) */
  float grid_q[3];            /* BSI AC Reactive Power per phase [kVAR] (GridQ1..3) */
  float grid_i[3];            /* BSI AC Current per phase [A] (GridI1..3) */

  float batt_u;               /* Battery DC Voltage [V] (BattU) */
  float batt_i;               /* Battery DC Current [A] (BattI) */
  float batt_soc;              /* Battery State of Charge [%] (SoCBatt) */
  float batt_soh;              /* Battery State of Health [%] (from BMS CANbus) */
  float batt_temp;             /* Battery average cell temperature [°C] (BattTemp) */
  uint32_t batt_alarm;         /* Battery BMS alarm flags bitmask */
  uint32_t batt_fault;         /* Battery BMS fault flags bitmask */

  float dci_temp;             /* BSI DCI board heatsink temperature [°C] (DCITemp) */
  float acr_temp;             /* BSI ACR board heatsink temperature [°C] (AcRTemp) */
  uint32_t bsi_status_flags;  /* BSI1000 internal status register (Status) */

  /* --- 1-byte Aligned Fields --- */
  uint8_t bsi_st;             /* BSI operational state (BsiState_t) */
  uint8_t reserved[3];        /* Alignment padding */
} BatteryStorageCluster_t;     /* Size: 80 bytes */

/* Unified PV array and grid-tied solar inverter structure aligned with PS300-PV */
typedef struct {
  /* --- 4-byte Aligned Fields --- */
  float inp_u[2];             /* PV DC input voltages per tracker [V] (InpU1, InpU2) */
  float inp_i[2];             /* PV DC input currents per tracker [A] (InpI1, InpI2) */
  float inp_p[2];             /* PV DC input power per tracker [kW] (InpP1, InpP2) */

  float grid_u[3];            /* PS300 AC output phase voltages [V] (GridU1..3) */
  float grid_i[3];            /* PS300 AC output phase currents [A] (GridI1..3) */
  float grid_p[3];            /* PS300 AC output active power per phase [kW] (GridP1..3) */
  float grid_q[3];            /* PS300 AC output reactive power per phase [kVAR] (GridQ1..3) */
  float grid_p_total;         /* PS300 AC output total active power [kW] (GridP) */
  float grid_q_total;         /* PS300 AC output total reactive power [kVAR] (GridQ) */
  float grid_freq;            /* PS300 AC output frequency [Hz] (GridFreq) */

  float inv_temp;             /* PS300 internal inverter temperature [°C] (InvTemp) */
  float r_izo;                /* PS300 isolation resistance [kΩ] (RIzo) */
  float prod_en;              /* PS300 total generated energy [kWh] (ProdEn) */
  float runtime;              /* PS300 total running hours [h] (RunTime) */

  uint32_t flags1;            /* PS300 status flags register 1 (Flags1) */
  uint32_t flags2;            /* PS300 status flags register 2 (Flags2) */

  /* --- 1-byte Aligned Fields --- */
  uint8_t pv_st;              /* PS300 inverter operational state (PvState_t) */
  uint8_t reserved[3];        /* Alignment padding */
} PvGenerationCluster_t;      /* Size: 112 bytes */

/* Telemetry data layout shared between CM7 (Math/Comms) and CM4 (Graphics) */
typedef struct {
  /* --- 4-byte Aligned Fields --- */
  float grid_volt_ln[3];      /* Grid L1, L2, L3 phase voltage [V] */
  float grid_curr[3];         /* Grid L1, L2, L3 phase current [A] */
  float grid_act_p;           /* Grid boundary total active power [kW] */
  float grid_react_q;         /* Grid boundary total reactive power [kVAR] */
  float grid_freq;            /* Grid boundary frequency [Hz] */
  float grid_cos_phi;         /* Grid displacement power factor */

  float load_off_act_p;       /* Office Active Power [kW] */
  float load_off_react_q;     /* Office Reactive Power [kVAR] */
  float load_lab_act_p;       /* Lab Active Power [kW] */
  float load_lab_react_q;     /* Lab Reactive Power [kVAR] */

  float cfg_grid_max_p_import;/* Peak Shaving Limit [kW] */
  float cfg_bat_backup_soc;   /* Backup/Load-shedding threshold [%] */
  float cfg_bat_max_volt;     /* Battery max charge voltage [V] */
  float cfg_bat_min_volt;     /* Battery min discharge voltage [V] */
  float cfg_target_cos_phi;   /* STATCOM target power factor */

  float ems_temp;             /* EMS heatsink/controller temperature [°C] */
  uint32_t active_fault_word; /* System diagnostics fault flags word */

  /* Storage & Generation cluster arrays */
  BatteryStorageCluster_t bat_clusters[MAX_BATTERY_CLUSTERS];
  PvGenerationCluster_t pv_clusters[MAX_PV_CLUSTERS];

  /* --- 2-byte Aligned Fields --- */
  uint16_t cfg_grid_nom_volt; /* Nominal Grid Voltage [V] (e.g. 230/400) */
  uint16_t cfg_grid_nom_freq; /* Nominal Grid Frequency [Hz] (e.g. 50/60) */
  uint16_t rtc_year;          /* Current RTC Year (e.g. 2026) */

  /* --- 1-byte Aligned Fields --- */
  uint8_t rtc_hours;          /* Current RTC Hour (0-23) */
  uint8_t rtc_minutes;        /* Current RTC Minute (0-59) */
  uint8_t rtc_seconds;        /* Current RTC Second (0-59) */
  uint8_t rtc_day;            /* Current RTC Day (1-31) */
  uint8_t rtc_month;          /* Current RTC Month (1-12) */

  uint8_t ems_op_mode;        /* EmsOpMode_t */
  uint8_t ems_island_state;   /* EmsIslandState_t */

  uint8_t contactor_grid_st;  /* ContactorState_t */
  uint8_t contactor_grid_cmd; /* ContactorCmd_t */
  uint8_t contactor_off_st;   /* ContactorState_t */
  uint8_t contactor_off_cmd;  /* ContactorCmd_t */
  uint8_t contactor_lab_st;   /* ContactorState_t */
  uint8_t contactor_lab_cmd;  /* ContactorCmd_t */

  uint8_t cfg_tou_chg_start_h;   /* ToU charging window start hour */
  uint8_t cfg_tou_chg_start_m;   /* ToU charging window start minute */
  uint8_t cfg_tou_chg_end_h;     /* ToU charging window end hour */
  uint8_t cfg_tou_chg_end_m;     /* ToU charging window end minute */
  uint8_t cfg_tou_disch_start_h; /* ToU discharging window start hour */
  uint8_t cfg_tou_disch_start_m; /* ToU discharging window start minute */
  uint8_t cfg_tou_disch_end_h;   /* ToU discharging window end hour */
  uint8_t cfg_tou_disch_end_m;   /* ToU discharging window end minute */

  uint8_t cm7_cpu_load;       /* Cortex-M7 Core CPU utilization [%] */
  uint8_t cm4_cpu_load;       /* Cortex-M4 Core CPU utilization [%] */

  char login_username[32];    /* Authenticated user name */
  uint8_t login_access_level; /* AccessLevel_t */
} SharedBuffer_t;

/* Helper macros for accessing the shared buffer pointer.
 * On the PC Simulator (PC_SIMULATOR=1) this macro is supplied via CMake
 * target_compile_definitions, pointing to the mock struct in pc_simulator_hw.c.
 * On the real STM32H7 target it maps directly to the SRAM3 hardware address. */
#ifndef PC_SIMULATOR
#define SHARED_BUFFER             ((volatile SharedBuffer_t *)SHARED_SRAM_ADDR)
#endif

#endif /* SHARED_MEMORY_H */
