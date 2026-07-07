#!/usr/bin/env python3
import os
import sys
import shutil
import glob

# Constants
PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))
TARGET_SRC_DIR = os.path.join(PROJECT_ROOT, "CM4/Core/Src/eez_ui")
RELEASE_DIR = os.path.join(PROJECT_ROOT, "STM32CubeIDE/CM4/Release")
SUBDIR_MK_PATH = os.path.join(RELEASE_DIR, "Application/User/Core/eez_ui/subdir.mk")

def preprocess_and_patch():
    src_project_ui = os.path.join(PROJECT_ROOT, "EEZ/Riverdi-template/src/ui")
    eez_output_dir = os.path.join(PROJECT_ROOT, "EEZ_Output")
    
    if not os.path.exists(src_project_ui):
        return
        
    print(f"Syncing and patching generated UI files from {src_project_ui} to {eez_output_dir}...")
    
    # 1. Copy files
    files_to_sync = ["screens.c", "screens.h", "images.c", "images.h", "ui.c", "ui.h", "vars.c", "vars.h", "styles.c", "styles.h"]
    for f in files_to_sync:
        src_path = os.path.join(src_project_ui, f)
        dest_path = os.path.join(eez_output_dir, f)
        if os.path.exists(src_path):
            shutil.copy2(src_path, dest_path)
            
    # Also sync generated images and fonts
    for filepath in glob.glob(os.path.join(src_project_ui, "ui_image_*.c")) + glob.glob(os.path.join(src_project_ui, "ui_font_*.c")):
        filename = os.path.basename(filepath)
        dest_path = os.path.join(eez_output_dir, filename)
        shutil.copy2(filepath, dest_path)
            
    # 2. Patch images.h
    images_h_path = os.path.join(eez_output_dir, "images.h")
    if os.path.exists(images_h_path):
        with open(images_h_path, "r") as f:
            content = f.read()
        
        # Remove ico declarations
        import re
        content = re.sub(r'extern const lv_img_dsc_t img_ico_[\w_]+;\n', '', content)
        
        # Add img_splash_logo
        if "img_splash_logo" not in content:
            content = content.replace(
                'extern const lv_img_dsc_t img_twerd_energo_plus_logo;',
                'extern const lv_img_dsc_t img_twerd_energo_plus_logo;\nextern const lv_img_dsc_t img_splash_logo;'
            )
            
        # Change size of images array to 3
        content = re.sub(r'extern const ext_img_desc_t images\[\d+\];', 'extern const ext_img_desc_t images[3];', content)
        
        with open(images_h_path, "w") as f:
            f.write(content)
            
    # 3. Patch images.c
    images_c_path = os.path.join(eez_output_dir, "images.c")
    if os.path.exists(images_c_path):
        new_images_c = """#include "images.h"

const ext_img_desc_t images[3] = {
    { "twerd-energo-plus-logo", &img_twerd_energo_plus_logo },
    { "splash-logo", &img_splash_logo },
    { "control-system-label", &img_control_system_label },
};
"""
        with open(images_c_path, "w") as f:
            f.write(new_images_c)
            
    # 4. Patch screens.h
    screens_h_path = os.path.join(eez_output_dir, "screens.h")
    if os.path.exists(screens_h_path):
        with open(screens_h_path, "r") as f:
            content = f.read()
            
        # Add SCREEN_ID_MAIN
        if "SCREEN_ID_MAIN" not in content:
            content = content.replace(
                'SCREEN_ID_DASHBOARD = 1,',
                'SCREEN_ID_MAIN = 1,\n    SCREEN_ID_DASHBOARD = 2,'
            )
            content = content.replace(
                '_SCREEN_ID_LAST = 1',
                '_SCREEN_ID_LAST = 2'
            )
            
        # Add splash variables to objects_t
        if "splash_obj0" not in content:
            content = content.replace(
                'typedef struct _objects_t {\n    lv_obj_t *dashboard;',
                'typedef struct _objects_t {\n    lv_obj_t *main;\n    lv_obj_t *dashboard;\n    \n    // Splash screen components\n    lv_obj_t *splash_obj0;\n    lv_obj_t *splash_obj1;'
            )
            
        # Add main screen functions
        if "create_screen_main" not in content:
            content = content.replace(
                'void create_screen_dashboard();',
                'void create_screen_main();\nvoid tick_screen_main();\n\nvoid create_screen_dashboard();'
            )
            
        with open(screens_h_path, "w") as f:
            f.write(content)
            
    # 5. Patch screens.c
    screens_c_path = os.path.join(eez_output_dir, "screens.c")
    if os.path.exists(screens_c_path):
        with open(screens_c_path, "r") as f:
            content = f.read()
            
        # Replace tick_screen logic
        old_tick_funcs = """typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_dashboard,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 1) {
        tick_screen_funcs[screen_index]();
    }
}"""
        new_tick_funcs = """extern const lv_img_dsc_t img_splash_logo;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.splash_obj0 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 600);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x030088), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.splash_obj1 = obj;
            lv_obj_set_pos(obj, 306, 265);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_splash_logo);
            lv_obj_set_style_img_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_dashboard,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 2) {
        tick_screen_funcs[screen_index]();
    }
}"""
        if "create_screen_main" not in content:
            content = content.replace(old_tick_funcs, new_tick_funcs)
            
        # Replace screens creation
        if "create_screen_main();" not in content:
            content = content.replace(
                'create_screen_dashboard();',
                'create_screen_main();\n    create_screen_dashboard();'
            )
            
        with open(screens_c_path, "w") as f:
            f.write(content)
            
    # 6. Patch ui.c
    ui_c_path = os.path.join(eez_output_dir, "ui.c")
    if os.path.exists(ui_c_path):
        custom_ui_c = """#include "ui.h"
#include "screens.h"
#include "images.h"
#include "actions.h"
#include "vars.h"
#include "lvgl/lvgl.h"
#include "app_hardware.h"

#include <string.h>

static int16_t currentScreen = -1;
static uint32_t splash_start_time = 0;
static bool splash_done = false;

static lv_obj_t *getLvglObjectFromIndex(int32_t index) {
    if (index == -1) {
        return 0;
    }
    return ((lv_obj_t **)&objects)[index];
}

void loadScreen(enum ScreensEnum screenId) {
    currentScreen = screenId - 1;
    lv_obj_t *screen = getLvglObjectFromIndex(currentScreen);
    lv_scr_load(screen);

    // If dashboard is loaded, check if we should show/hide keyboard test panel
    if (screenId == SCREEN_ID_DASHBOARD) {
#if defined(KEYBOARD_TEST_ENABLE) && KEYBOARD_TEST_ENABLE
        if (objects.keyboard_test) {
            lv_obj_clear_flag(objects.keyboard_test, LV_OBJ_FLAG_HIDDEN);
        }
#else
        if (objects.keyboard_test) {
            lv_obj_add_flag(objects.keyboard_test, LV_OBJ_FLAG_HIDDEN);
        }
#endif
    }
}

void ui_init() {
    create_screens();
    loadScreen(SCREEN_ID_MAIN);
    splash_start_time = lv_tick_get();
}

#if defined(KEYBOARD_TEST_ENABLE) && KEYBOARD_TEST_ENABLE
#ifndef PC_SIMULATOR
#include "main.h"
static uint16_t scan_keypad_matrix(void) {
    uint16_t pressed_mask = 0;

    // Scan Strobe 1 (PC6)
    HAL_GPIO_WritePin(KEYPAD_ST_PORT_1, KEYPAD_ST_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEYPAD_ST_PORT_2, KEYPAD_ST_PIN_2, GPIO_PIN_RESET);
    for (volatile int i = 0; i < 50; i++); 
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL1_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 0); // START_LEFT (K11)
    }
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL2_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 1); // START_RIGHT (K12)
    }
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL3_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 4); // DOWN (K22)
    }
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL4_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 3); // UP (K12)
    }
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL5_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 2); // STOP (K11)
    }
    HAL_GPIO_WritePin(KEYPAD_ST_PORT_1, KEYPAD_ST_PIN_1, GPIO_PIN_RESET);

    // Scan Strobe 2 (PB0)
    HAL_GPIO_WritePin(KEYPAD_ST_PORT_1, KEYPAD_ST_PIN_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEYPAD_ST_PORT_2, KEYPAD_ST_PIN_2, GPIO_PIN_SET);
    for (volatile int i = 0; i < 50; i++); 
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL1_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 6); // RIGHT (K32)
    }
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL2_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 5); // LEFT (K21)
    }
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL3_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 7); // ENTER (K31)
    }
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL4_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 9); // FUNCTION (K32)
    }
    if (HAL_GPIO_ReadPin(KEYPAD_COL_PORT, KEYPAD_COL5_PIN) == GPIO_PIN_SET) {
        pressed_mask |= (1 << 8); // ESCAPE (K31)
    }
    HAL_GPIO_WritePin(KEYPAD_ST_PORT_2, KEYPAD_ST_PIN_2, GPIO_PIN_RESET);

    return pressed_mask;
}

static uint16_t g_pressed_keys_mask = 0;
#define IS_UP_PRESSED()    (g_pressed_keys_mask & (1 << 3))
#define IS_DOWN_PRESSED()  (g_pressed_keys_mask & (1 << 4))
#define IS_LEFT_PRESSED()  (g_pressed_keys_mask & (1 << 5))
#define IS_RIGHT_PRESSED() (g_pressed_keys_mask & (1 << 6))
#define IS_ENTER_PRESSED() (g_pressed_keys_mask & (1 << 7))
#define IS_BACK_PRESSED()  (g_pressed_keys_mask & (1 << 8))
#else
extern bool sim_key_up, sim_key_down, sim_key_left, sim_key_right, sim_key_enter, sim_key_back;
#define IS_UP_PRESSED()    sim_key_up
#define IS_DOWN_PRESSED()  sim_key_down
#define IS_LEFT_PRESSED()  sim_key_left
#define IS_RIGHT_PRESSED() sim_key_right
#define IS_ENTER_PRESSED() sim_key_enter
#define IS_BACK_PRESSED()  sim_key_back
#endif

static void update_keyboard_test_button_states(void) {
    if (objects.keyboard_test) {
#ifndef PC_SIMULATOR
        g_pressed_keys_mask = scan_keypad_matrix();
#endif
        if (IS_UP_PRESSED()) {
            lv_obj_add_state(objects.btn_up, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_up, LV_STATE_PRESSED);
        }
        if (IS_DOWN_PRESSED()) {
            lv_obj_add_state(objects.btn_down, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_down, LV_STATE_PRESSED);
        }
        if (IS_LEFT_PRESSED()) {
            lv_obj_add_state(objects.btn_left, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_left, LV_STATE_PRESSED);
        }
        if (IS_RIGHT_PRESSED()) {
            lv_obj_add_state(objects.btn_right, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_right, LV_STATE_PRESSED);
        }
        if (IS_ENTER_PRESSED()) {
            lv_obj_add_state(objects.btn_enter, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_enter, LV_STATE_PRESSED);
        }
        if (IS_BACK_PRESSED()) {
            lv_obj_add_state(objects.btn_backspace, LV_STATE_PRESSED);
        } else {
            lv_obj_clear_state(objects.btn_backspace, LV_STATE_PRESSED);
        }
    }
}
#endif

bool is_keyboard_test_active(void) {
#if defined(KEYBOARD_TEST_ENABLE) && KEYBOARD_TEST_ENABLE
    if (objects.keyboard_test && !lv_obj_has_flag(objects.keyboard_test, LV_OBJ_FLAG_HIDDEN)) {
        return true;
    }
#endif
    return false;
}

void ui_tick() {
    tick_screen(currentScreen);

#if defined(KEYBOARD_TEST_ENABLE) && KEYBOARD_TEST_ENABLE
    update_keyboard_test_button_states();
#endif

    if (!splash_done && currentScreen == (SCREEN_ID_MAIN - 1)) {
        if (lv_tick_elaps(splash_start_time) >= 2000) {
            splash_done = true;
            loadScreen(SCREEN_ID_DASHBOARD);
        }
    }
}
"""
        with open(ui_c_path, "w") as f:
            f.write(custom_ui_c)

    # 7. Patch vars.c
    vars_c_path = os.path.join(eez_output_dir, "vars.c")
    if os.path.exists(vars_c_path):
        custom_vars_c = """#include "vars.h"
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
"""
        with open(vars_c_path, "w") as f:
            f.write(custom_vars_c)

def main():
    # 0. Sync and patch files before copying
    preprocess_and_patch()

    # 1. Parse command-line args for source directory
    source_dir = ""
    if len(sys.argv) > 1:
        source_dir = sys.argv[1]
    else:
        source_dir = os.path.join(PROJECT_ROOT, "EEZ_Output")

    if not os.path.exists(source_dir):
        print(f"Source directory '{source_dir}' does not exist. Creating it...")
        os.makedirs(source_dir, exist_ok=True)

    print(f"Porting EEZ Studio project from: {source_dir}")
    print(f"Target UI directory: {TARGET_SRC_DIR}")

    c_files = []
    if os.path.abspath(source_dir) != os.path.abspath(TARGET_SRC_DIR):
        if os.path.exists(TARGET_SRC_DIR):
            shutil.rmtree(TARGET_SRC_DIR)
        os.makedirs(TARGET_SRC_DIR, exist_ok=True)

        for root_dir, dirs, files in os.walk(source_dir):
            for file in files:
                if file.endswith((".c", ".h")):
                    src_path = os.path.join(root_dir, file)
                    dest_path = os.path.join(TARGET_SRC_DIR, file)
                    shutil.copy2(src_path, dest_path)
                    if file.endswith(".c"):
                        c_files.append(file)
    else:
        # Just scan the target directory directly
        if os.path.exists(TARGET_SRC_DIR):
            for file in os.listdir(TARGET_SRC_DIR):
                if file.endswith(".c"):
                    c_files.append(file)

    print(f"Copied {len(c_files)} source files to {TARGET_SRC_DIR}")

    if not c_files:
        print("No EEZ UI files found in source. Generating default placeholder screen...")
        write_placeholder_files()
        c_files = ["ui.c"]

    # 4. Generate build directory if it does not exist
    eez_build_dir = os.path.dirname(SUBDIR_MK_PATH)
    os.makedirs(eez_build_dir, exist_ok=True)

    # 5. Generate subdir.mk
    generate_subdir_mk(c_files)
    print(f"Generated {SUBDIR_MK_PATH}")

    # 6. Update objects.list
    update_objects_list(c_files)

    # 7. Update sources.mk
    update_sources_mk()

    # 8. Update makefile
    update_makefile()

    print("EEZ project successfully ported to the CM4 firmware build environment!")

def generate_subdir_mk(c_files):
    c_srcs_lines = []
    objs_lines = []
    c_deps_lines = []
    rules_lines = []

    for f in sorted(c_files):
        src_path = f"{PROJECT_ROOT}/CM4/Core/Src/eez_ui/{f}"
        obj_name = f.replace(".c", ".o")
        dep_name = f.replace(".c", ".d")
        
        c_srcs_lines.append(f"{src_path} \\")
        objs_lines.append(f"./Application/User/Core/eez_ui/{obj_name} \\")
        c_deps_lines.append(f"./Application/User/Core/eez_ui/{dep_name} \\")

        # Explicit compile rule for this file
        rule = f"""Application/User/Core/eez_ui/{obj_name}: {src_path} Application/User/Core/eez_ui/subdir.mk
\tarm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../../../CM4/Core/Inc -I../../../CM4/Core/Src/eez_ui -I../../../Middlewares/Third_Party/lvgl -I../../../Middlewares/Third_Party -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/CMSIS/Include -I../../../Common -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" """
        rules_lines.append(rule)

    # Remove trailing backslash from the last item
    if c_srcs_lines:
        c_srcs_lines[-1] = c_srcs_lines[-1].rstrip(" \\")
    if objs_lines:
        objs_lines[-1] = objs_lines[-1].rstrip(" \\")
    if c_deps_lines:
        c_deps_lines[-1] = c_deps_lines[-1].rstrip(" \\")

    c_srcs_str = "\n".join(c_srcs_lines)
    objs_str = "\n".join(objs_lines)
    c_deps_str = "\n".join(c_deps_lines)
    rules_str = "\n".join(rules_lines)

    content = f"""################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \\
{c_srcs_str}

OBJS += \\
{objs_str}

C_DEPS += \\
{c_deps_str}


# Each subdirectory must supply rules for building sources it contributes
{rules_str}

clean: clean-Application-2f-User-2f-Core-2f-eez_ui

clean-Application-2f-User-2f-Core-2f-eez_ui:
\t-$(RM) ./Application/User/Core/eez_ui/*.cyclo ./Application/User/Core/eez_ui/*.d ./Application/User/Core/eez_ui/*.o ./Application/User/Core/eez_ui/*.su

.PHONY: clean-Application-2f-User-2f-Core-2f-eez_ui
"""
    with open(SUBDIR_MK_PATH, "w") as f:
        f.write(content)

def _collect_all_objs_from_subdirs():
    """Parse OBJS += entries from all subdir.mk files in the Release tree."""
    import re
    objs = []
    for mk in glob.glob(RELEASE_DIR + '/**/subdir.mk', recursive=True):
        with open(mk) as f:
            content = f.read()
        in_objs = False
        for line in content.splitlines():
            stripped = line.strip()
            if re.match(r'^OBJS\s*\+=', stripped):
                in_objs = True
                continue
            if in_objs:
                cleaned = stripped.rstrip('\\').strip()
                if re.match(r'^\./.+\.o$', cleaned):
                    objs.append(cleaned)
                if not stripped.endswith('\\'):
                    in_objs = False
    return list(dict.fromkeys(objs))  # deduplicate, preserve order

def update_objects_list(c_files):
    objects_file = os.path.join(RELEASE_DIR, "objects.list")

    # Always rebuild from subdir.mk files — they are the authoritative source.
    # This is safe whether the file exists or not (e.g. after a manual clean).
    all_objs = _collect_all_objs_from_subdirs()

    # Remove any stale eez_ui entries; they will be added fresh below
    all_objs = [o for o in all_objs if 'eez_ui/' not in o]

    # Append fresh eez_ui entries
    for fname in sorted(c_files):
        obj_name = fname.replace(".c", ".o")
        all_objs.append(f'./Application/User/Core/eez_ui/{obj_name}')

    with open(objects_file, "w") as f:
        f.write(' '.join(all_objs))
    print(f"Updated {objects_file} ({len(all_objs)} objects)")


def update_sources_mk():
    sources_file = os.path.join(RELEASE_DIR, "sources.mk")
    if not os.path.exists(sources_file):
        return

    with open(sources_file, "r") as f:
        content = f.read()

    target_subdir = "Application/User/Core/eez_ui \\"
    if target_subdir not in content:
        # Insert it in the SUBDIRS list
        lines = content.splitlines()
        inserted = False
        for idx, line in enumerate(lines):
            if "SUBDIRS := \\" in line:
                lines.insert(idx + 1, target_subdir)
                inserted = True
                break
        if inserted:
            with open(sources_file, "w") as f:
                f.write("\n".join(lines) + "\n")
            print(f"Updated {sources_file}")

def update_makefile():
    makefile_file = os.path.join(RELEASE_DIR, "makefile")
    if not os.path.exists(makefile_file):
        return

    with open(makefile_file, "r") as f:
        lines = f.read().splitlines()

    target_include = "-include Application/User/Core/eez_ui/subdir.mk"
    if target_include not in lines:
        # Insert it after other -include lines
        inserted_idx = -1
        for idx, line in enumerate(lines):
            if line.startswith("-include") and "subdir.mk" in line:
                inserted_idx = idx
        
        if inserted_idx != -1:
            lines.insert(inserted_idx + 1, target_include)
            with open(makefile_file, "w") as f:
                f.write("\n".join(lines) + "\n")
            print(f"Updated {makefile_file}")

def write_placeholder_files():
    h_content = """#ifndef EEZ_LVGL_UI_GUI_H
#define EEZ_LVGL_UI_GUI_H

#ifdef __cplusplus
extern "C" {
#endif

void ui_init();
void ui_tick();

#ifdef __cplusplus
}
#endif

#endif // EEZ_LVGL_UI_GUI_H
"""
    c_content = """#include "ui.h"
#include "lvgl/lvgl.h"

void ui_init() {
    /* Create dark blue background and centered label with text 'TWERD ENERGO-PLUS' */
    lv_obj_t * scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x00003B), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_t * label = lv_label_create(scr);
    lv_label_set_text(label, "TWERD ENERGO-PLUS");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void ui_tick() {
    // Nothing to do in the dummy loop
}
"""
    with open(os.path.join(TARGET_SRC_DIR, "ui.h"), "w") as f:
        f.write(h_content)
    with open(os.path.join(TARGET_SRC_DIR, "ui.c"), "w") as f:
        f.write(c_content)

if __name__ == "__main__":
    main()
