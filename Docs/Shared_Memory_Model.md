# Shared Memory Model Specification for Enterprise AC-Coupled Cluster Microgrid

This document describes the shared memory data structure (`SharedBuffer_t`) stored in SRAM3 (address `0x30040000`) of the dual-core STM32H757 microcontroller. This buffer acts as the Inter-Core Communication (IPC) boundary between:
- **Cortex-M7 Core (Master Controller):** Responsible for executing Modbus TCP clients/servers, real-time control algorithms (arbitrage, peak shaving, STATCOM mode, black-start), contactor sequencing, and reading the hardware RTC.
- **Cortex-M4 Core (Graphics/UI Engine):** Responsible for running the LVGL graphics stack, processing touch/keypad inputs, displaying real-time telemetry, and allowing operator configurations.

---

## 1. Synchronization and Caching Rules

Because this structure resides in SRAM3 (shared D2 domain memory), the following rules are enforced to prevent race conditions and cache incoherency:
1. **Hardware Semaphore (HSEM):** Any read or write operation to the shared memory must be wrapped by taking the Hardware Semaphore with ID `HSEM_ID_SHARED_MEM` (Semaphore 1).
2. **D-Cache Clean (Cortex-M7):** After writing variables, the Cortex-M7 must call `SCB_CleanDCache_by_Addr((uint32_t *)SHARED_BUFFER, sizeof(SharedBuffer_t))` to flush the data cache and ensure the physical SRAM3 is updated.
3. **D-Cache Invalidate (Cortex-M7):** Before reading variables modified by Cortex-M4, the Cortex-M7 must call `SCB_InvalidateDCache_by_Addr((uint32_t *)SHARED_BUFFER, sizeof(SharedBuffer_t))` to fetch the latest values from physical SRAM3.
4. **Cortex-M4 Caching:** The Cortex-M4 has no D-cache, so it reads directly from physical SRAM3. It only requires taking the HSEM to avoid reading partial or inconsistent states.

---

## 2. Array-of-Structures Cluster Layout

To support flexible addition and removal of units, the storage (BESS) and generation (PV) clusters are modeled as arrays of structures. The maximum size of these arrays is configured via preprocessor definitions:
- `MAX_BATTERY_CLUSTERS` (Default = 2)
- `MAX_PV_CLUSTERS` (Default = 2)

The structure definitions have been updated to align directly with the modbus parameters collected from the physical **BSI1000** and **PS300-PV** devices.

### A. Battery Storage Cluster Struct (`BatteryStorageCluster_t`)
Size: 80 bytes (naturally aligned to 4-byte boundaries).

| Field Name | Data Type | Flow Direction | Unit | Matching Hardware Tag | Description |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `grid_p[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | kW | `GridP1`, `GridP2`, `GridP3` | AC Active Power per phase (Pos=Disch, Neg=Chg) |
| `grid_q[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | kVAR | `GridQ1`, `GridQ2`, `GridQ3` | AC Reactive Power per phase |
| `grid_i[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | A | `GridI1`, `GridI2`, `GridI3` | AC Current per phase |
| `batt_u` | `float` | CM7 $\rightarrow$ CM4 | V | `BattU` | Battery DC Voltage |
| `batt_i` | `float` | CM7 $\rightarrow$ CM4 | A | `BattI` | Battery DC Current (Positive = Disch, Negative = Chg) |
| `batt_soc` | `float` | CM7 $\rightarrow$ CM4 | % | `SoCBatt` | Battery State of Charge |
| `batt_soh` | `float` | CM7 $\rightarrow$ CM4 | % | - | Battery State of Health (read from BMS CANbus) |
| `batt_temp` | `float` | CM7 $\rightarrow$ CM4 | °C | `BattTemp` | Battery Average Temperature |
| `batt_alarm` | `uint32_t` | CM7 $\rightarrow$ CM4 | bits | - | Battery BMS Alarm Flags |
| `batt_fault` | `uint32_t` | CM7 $\rightarrow$ CM4 | bits | - | Battery BMS Fault Flags |
| `dci_temp` | `float` | CM7 $\rightarrow$ CM4 | °C | `DCITemp` | BSI DCI board heatsink temperature |
| `acr_temp` | `float` | CM7 $\rightarrow$ CM4 | °C | `AcRTemp` | BSI ACR board heatsink temperature |
| `bsi_status_flags` | `uint32_t` | CM7 $\rightarrow$ CM4 | bits | `Status` | BSI1000 Internal Status Word |
| `bsi_st` | `uint8_t` | CM7 $\rightarrow$ CM4 | enum | - | BSI Inverter operational state (BsiState_t) |
| `reserved[3]` | `uint8_t[3]` | - | - | - | Padding bytes for 4-byte alignment |

### B. PV Generation Cluster Struct (`PvGenerationCluster_t`)
Size: 112 bytes (naturally aligned to 4-byte boundaries).

| Field Name | Data Type | Flow Direction | Unit | Matching Hardware Tag | Description |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `inp_u[2]` | `float[2]` | CM7 $\rightarrow$ CM4 | V | `InpU1`, `InpU2` | PV DC Input Voltage per MPPT tracker |
| `inp_i[2]` | `float[2]` | CM7 $\rightarrow$ CM4 | A | `InpI1`, `InpI2` | PV DC Input Current per MPPT tracker |
| `inp_p[2]` | `float[2]` | CM7 $\rightarrow$ CM4 | kW | `InpP1`, `InpP2` | PV DC Input Power per MPPT tracker |
| `grid_u[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | V | `GridU1`, `GridU2`, `GridU3` | PS300 AC Output Phase Voltages |
| `grid_i[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | A | `GridI1`, `GridI2`, `GridI3` | PS300 AC Output Phase Currents |
| `grid_p[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | kW | `GridP1`, `GridP2`, `GridP3` | PS300 AC Output Active Power per phase |
| `grid_q[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | kVAR | `GridQ1`, `GridQ2`, `GridQ3` | PS300 AC Output Reactive Power per phase |
| `grid_p_total` | `float` | CM7 $\rightarrow$ CM4 | kW | `GridP` | PS300 AC Output Total Active Power |
| `grid_q_total` | `float` | CM7 $\rightarrow$ CM4 | kVAR | `GridQ` | PS300 AC Output Total Reactive Power |
| `grid_freq` | `float` | CM7 $\rightarrow$ CM4 | Hz | `GridFreq` | PS300 AC Frequency |
| `inv_temp` | `float` | CM7 $\rightarrow$ CM4 | °C | `InvTemp` | PS300 internal inverter temperature |
| `r_izo` | `float` | CM7 $\rightarrow$ CM4 | kΩ | `RIzo` | PS300 isolation resistance |
| `prod_en` | `float` | CM7 $\rightarrow$ CM4 | kWh | `ProdEn` | PS300 total generated energy |
| `runtime` | `float` | CM7 $\rightarrow$ CM4 | h | `RunTime` | PS300 total inverter run hours |
| `flags1` | `uint32_t` | CM7 $\rightarrow$ CM4 | bits | `Flags1` | PS300 status flags word 1 |
| `flags2` | `uint32_t` | CM7 $\rightarrow$ CM4 | bits | `Flags2` | PS300 status flags word 2 |
| `pv_st` | `uint8_t` | CM7 $\rightarrow$ CM4 | enum | - | PV Inverter operational state (PvState_t) |
| `reserved[3]` | `uint8_t[3]` | - | - | - | Padding bytes for 4-byte alignment |

---

## 3. Shared Memory Map (Data Layout)

Below is the structured layout of the global `SharedBuffer_t` structure.

| Section | Variable Name | Data Type | Flow Direction | Unit | Scale | Description |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **RTC (Clock)** | `rtc_hours` | `uint8_t` | CM7 $\rightarrow$ CM4 | hours | 1 | Current hour (0-23) |
| | `rtc_minutes` | `uint8_t` | CM7 $\rightarrow$ CM4 | mins | 1 | Current minute (0-59) |
| | `rtc_seconds` | `uint8_t` | CM7 $\rightarrow$ CM4 | secs | 1 | Current second (0-59) |
| | `rtc_day` | `uint8_t` | CM7 $\rightarrow$ CM4 | days | 1 | Day of month (1-31) |
| | `rtc_month` | `uint8_t` | CM7 $\rightarrow$ CM4 | months | 1 | Month (1-12) |
| | `rtc_year` | `uint16_t` | CM7 $\rightarrow$ CM4 | years | 1 | Full year (e.g. 2026) |
| **EMS Operations** | `ems_op_mode` | `uint8_t` | CM7 $\rightarrow$ CM4 | enum | 1 | Operational algorithm mode (see below) |
| | `ems_island_state`| `uint8_t` | CM7 $\rightarrow$ CM4 | enum | 1 | Island-mode phase status (see below) |
| | `ems_temp` | `float` | CM7 $\rightarrow$ CM4 | °C | 1 | Central controller internal/heatsink temperature |
| | `active_fault_word`| `uint32_t`| CM7 $\rightarrow$ CM4 | bits | 1 | Bitmask of active system-level faults |
| **Grid Boundary** | `grid_volt_ln[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | V | 1 | Grid phase-to-neutral voltages (L1, L2, L3) |
| | `grid_curr[3]` | `float[3]` | CM7 $\rightarrow$ CM4 | A | 1 | Grid phase currents (L1, L2, L3) |
| | `grid_act_p` | `float` | CM7 $\rightarrow$ CM4 | kW | 1 | Total grid active power (Positive = Import, Negative = Export) |
| | `grid_react_q` | `float` | CM7 $\rightarrow$ CM4 | kVAR | 1 | Total grid reactive power |
| | `grid_freq` | `float` | CM7 $\rightarrow$ CM4 | Hz | 1 | Grid frequency |
| | `grid_cos_phi` | `float` | CM7 $\rightarrow$ CM4 | - | 1 | Grid boundary power factor |
| | `contactor_grid_st`| `uint8_t` | CM7 $\rightarrow$ CM4 | enum | 1 | Actual state of Grid Contactor (0 = Open, 1 = Closed, 2 = Fault) |
| | `contactor_grid_cmd`| `uint8_t`| CM4 $\rightarrow$ CM7 | enum | 1 | Manual or override command for Grid Contactor |
| **Office Load** | `load_off_act_p` | `float` | CM7 $\rightarrow$ CM4 | kW | 1 | Office active power consumption (from Office Meter) |
| | `load_off_react_q`| `float` | CM7 $\rightarrow$ CM4 | kVAR | 1 | Office reactive power consumption (from Office Meter) |
| | `contactor_off_st`| `uint8_t` | CM7 $\rightarrow$ CM4 | enum | 1 | Actual state of Office Contactor (0 = Open, 1 = Closed, 2 = Fault) |
| | `contactor_off_cmd`| `uint8_t`| CM4 $\rightarrow$ CM7 | enum | 1 | Command status for Office Contactor (0 = Open, 1 = Close) |
| **Lab Load** | `load_lab_act_p` | `float` | CM7 $\rightarrow$ CM4 | kW | 1 | Laboratory active power consumption (from Lab Meter) |
| | `load_lab_react_q`| `float` | CM7 $\rightarrow$ CM4 | kVAR | 1 | Laboratory reactive power consumption (from Lab Meter) |
| | `contactor_lab_st`| `uint8_t` | CM7 $\rightarrow$ CM4 | enum | 1 | Actual state of Laboratory Contactor (0 = Open, 1 = Closed, 2 = Fault) |
| | `contactor_lab_cmd`| `uint8_t`| CM4 $\rightarrow$ CM7 | enum | 1 | Command status for Laboratory Contactor (0 = Open, 1 = Close) |
| **Clusters (Arrays)** | `bat_clusters` | `BatteryStorageCluster_t[MAX_BATTERY_CLUSTERS]` | CM7 $\rightarrow$ CM4 | struct | 1 | Array of battery storage cluster telemetry structures |
| | `pv_clusters` | `PvGenerationCluster_t[MAX_PV_CLUSTERS]` | CM7 $\rightarrow$ CM4 | struct | 1 | Array of PV generation cluster telemetry structures |
| **Configurations** | `cfg_grid_max_p_import`| `float`| CM4 $\rightarrow$ CM7 | kW | 1 | Active power import limit threshold (for Peak Shaving) |
| | `cfg_bat_backup_soc`| `float` | CM4 $\rightarrow$ CM7 | % | 1 | Backup SoC threshold (triggers load shedding if reached off-grid) |
| | `cfg_bat_max_volt` | `float` | CM4 $\rightarrow$ CM7 | V | 1 | Battery high voltage limit (per battery bank) |
| | `cfg_bat_min_volt` | `float` | CM4 $\rightarrow$ CM7 | V | 1 | Battery low voltage limit (per battery bank) |
| | `cfg_target_cos_phi`| `float` | CM4 $\rightarrow$ CM7 | - | 1 | Target grid power factor for STATCOM reactive power regulation |
| | `cfg_grid_nom_volt`| `uint16_t`| CM4 $\rightarrow$ CM7 | V | 1 | Grid nominal voltage configuration (e.g. 230 / 400) |
| | `cfg_grid_nom_freq`| `uint16_t`| CM4 $\rightarrow$ CM7 | Hz | 1 | Grid nominal frequency configuration (e.g. 50 / 60) |
| | `cfg_tou_chg_start_h`| `uint8_t`| CM4 $\rightarrow$ CM7 | hr | 1 | ToU battery charging window start hour (0-23) |
| | `cfg_tou_chg_start_m`| `uint8_t`| CM4 $\rightarrow$ CM7 | min | 1 | ToU battery charging window start minute (0-59) |
| | `cfg_tou_chg_end_h` | `uint8_t`| CM4 $\rightarrow$ CM7 | hr | 1 | ToU battery charging window end hour (0-23) |
| | `cfg_tou_chg_end_m` | `uint8_t`| CM4 $\rightarrow$ CM7 | min | 1 | ToU battery charging window end minute (0-59) |
| | `cfg_tou_disch_start_h`|`uint8_t`| CM4 $\rightarrow$ CM7 | hr | 1 | ToU battery discharging window start hour (0-23) |
| | `cfg_tou_disch_start_m`|`uint8_t`| CM4 $\rightarrow$ CM7 | min | 1 | ToU battery discharging window start minute (0-59) |
| | `cfg_tou_disch_end_h`| `uint8_t`| CM4 $\rightarrow$ CM7 | hr | 1 | ToU battery discharging window end hour (0-23) |
| | `cfg_tou_disch_end_m`| `uint8_t`| CM4 $\rightarrow$ CM7 | min | 1 | ToU battery discharging window end minute (0-59) |
| **System Diagnostics**| `cm7_cpu_load` | `uint8_t` | CM7 $\rightarrow$ CM4 | % | 1 | CPU utilization of Cortex-M7 core |
| | `cm4_cpu_load` | `uint8_t` | CM7 $\rightarrow$ CM4 | % | 1 | CPU utilization of Cortex-M4 core |
| **Authentication** | `login_username`| `char[32]`| CM4 $\rightarrow$ CM7 | text | 1 | Username of currently logged-in user |
| | `login_access_level`|`uint8_t`| CM4 $\rightarrow$ CM7 | enum | 1 | Active access level (0 = Guest, 1 = Operator, 2 = Admin) |

---

## 4. Enumerated Type Definitions

The definitions for operational modes and states remain the same (see enums `EmsOpMode_t`, `EmsIslandState_t`, `BsiState_t`, `PvState_t`, `ContactorState_t`, `ContactorCmd_t`, and `AccessLevel_t`).
