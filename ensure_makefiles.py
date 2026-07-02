#!/usr/bin/env python3
import os
import sys
import subprocess
import glob

PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))
CM4_MAKEFILE = os.path.join(PROJECT_ROOT, "STM32CubeIDE/CM4/Release/makefile")
CM7_MAKEFILE = os.path.join(PROJECT_ROOT, "STM32CubeIDE/CM7/Release/makefile")

def find_cubeide():
    # 1. Check in PATH
    try:
        import shutil
        path = shutil.which("stm32cubeide")
        if path:
            return path
    except Exception:
        pass

    # 2. Check standard Linux install paths
    standard_paths = [
        "/opt/st/stm32cubeide_2.2.0/stm32cubeide",
    ]
    for p in standard_paths:
        if os.path.exists(p):
            return p

    # 3. Wildcard search in /opt/st/
    opt_paths = glob.glob("/opt/st/stm32cubeide_*/stm32cubeide")
    if opt_paths:
        return opt_paths[0]

    return None

def main():
    if os.path.exists(CM4_MAKEFILE) and os.path.exists(CM7_MAKEFILE):
        print("STM32CubeIDE Makefiles already exist. Proceeding...")
        return

    print("STM32CubeIDE Makefiles are missing (likely due to a clean clone).")
    cubeide = find_cubeide()
    if not cubeide:
        print("ERROR: STM32CubeIDE executable not found on the host system.")
        print("Please either:")
        print("  1. Open the project in STM32CubeIDE GUI to generate the build files.")
        print("  2. Ensure 'stm32cubeide' is in your PATH.")
        sys.exit(1)

    print(f"Found STM32CubeIDE at: {cubeide}")
    print("Generating Makefiles via headless build (this may take a few seconds)...")

    workspace_dir = os.path.join(PROJECT_ROOT, "build_workspace")
    os.makedirs(workspace_dir, exist_ok=True)

    cmd = [
        cubeide,
        "-nosplash",
        "--launcher.suppressErrors",
        "-application", "org.eclipse.cdt.managedbuilder.core.headlessbuild",
        "-data", workspace_dir,
        "-import", os.path.join(PROJECT_ROOT, "STM32CubeIDE/CM4"),
        "-import", os.path.join(PROJECT_ROOT, "STM32CubeIDE/CM7"),
        "-cleanBuild", "all"
    ]

    try:
        # Run headless build
        result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode != 0:
            print("WARNING: Headless build returned non-zero exit code.")
            print(result.stdout)
            print(result.stderr)
        
        # Verify if makefiles were generated
        if os.path.exists(CM4_MAKEFILE) and os.path.exists(CM7_MAKEFILE):
            print("STM32CubeIDE Makefiles successfully generated!")
        else:
            print("ERROR: Headless build ran but did not generate the makefiles.")
            sys.exit(1)
            
    except Exception as e:
        print(f"ERROR: Failed to run headless build: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
