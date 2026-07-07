import re
import os
import sys

# Paths to map files relative to workspace root
CM7_MAP_PATHS = [
    "STM32CubeIDE/CM7/Release/riverdi-70-stm32h7-lvgl_CM7.map",
    "STM32CubeIDE/CM7/Debug/riverdi-70-stm32h7-lvgl_CM7.map"
]

CM4_MAP_PATHS = [
    "STM32CubeIDE/CM4/Release/riverdi-70-stm32h7-lvgl_CM4.map",
    "STM32CubeIDE/CM4/Debug/riverdi-70-stm32h7-lvgl_CM4.map"
]

OUTPUT_PATH = "Docs/Memory_Usage_Report.md"

def parse_map_file(file_path):
    if not os.path.exists(file_path):
        return None

    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    # List of section names to exclude (debug info, comments, symbols, etc.)
    exclude_sections = [
        '.comment', '.ARM.attributes', '.debug_line', '.debug_info', 
        '.debug_abbrev', '.debug_aranges', '.debug_ranges', '.debug_str', 
        '.debug_loc', '.debug_frame', '.debug_macinfo', '.debug_weaknames', 
        '.debug_gnu_pubnames', '.debug_gnu_pubtypes', '.debug_elftemplates',
        '.debug_typename', '.debug_srcinfo', '.debug_pubnames', '.debug_pubtypes'
    ]

    def should_exclude(sec_name):
        for excl in exclude_sections:
            if sec_name.startswith(excl):
                return True
        return False

    # 1. Parse Memory Configuration
    regions = []
    mem_config_idx = content.find("Memory Configuration")
    if mem_config_idx == -1:
        return None

    lines = content[mem_config_idx:].splitlines()
    parsing_regions = False
    for line in lines:
        if "Name" in line and "Origin" in line and "Length" in line:
            parsing_regions = True
            continue
        if parsing_regions:
            if not line.strip():
                continue
            if "Linker script" in line:
                break
            parts = line.split()
            if len(parts) >= 3:
                name = parts[0]
                if name == "*default*":
                    continue
                try:
                    origin = int(parts[1], 16)
                    length = int(parts[2], 16)
                    regions.append({
                        'name': name,
                        'origin': origin,
                        'length': length,
                        'vma_used': 0,
                        'lma_used': 0,
                        'sections': []
                    })
                except ValueError:
                    pass

    # Helper function to find region for VMA
    def find_region(addr):
        for r in regions:
            if r['origin'] <= addr < (r['origin'] + r['length']):
                return r
        return None

    # 2. Parse Linker script and memory map
    map_idx = content.find("Linker script and memory map")
    if map_idx == -1:
        return None

    lines = content[map_idx:].splitlines()
    i = 0
    output_sections = []
    object_usage = {} # filename -> {region_name -> size}

    current_output_section = None

    def process_input_section(in_name, in_addr, in_size, in_file):
        if should_exclude(in_name):
            return
        if in_size == 0:
            return
        if not (in_file.endswith('.o') or '.a(' in in_file or in_file.endswith('.obj')):
            return

        # Track VMA usage
        vma_region = find_region(in_addr)
        if vma_region:
            vrname = vma_region['name']
            if in_file not in object_usage:
                object_usage[in_file] = {}
            object_usage[in_file][vrname] = object_usage[in_file].get(vrname, 0) + in_size

        # Track LMA usage
        if current_output_section and current_output_section['load_address'] is not None:
            offset = in_addr - current_output_section['address']
            in_lma = current_output_section['load_address'] + offset
            lma_region = find_region(in_lma)
            if lma_region and lma_region != vma_region:
                lrname = lma_region['name'] + " (LMA)"
                if in_file not in object_usage:
                    object_usage[in_file] = {}
                object_usage[in_file][lrname] = object_usage[in_file].get(lrname, 0) + in_size

    while i < len(lines):
        line = lines[i]

        m = re.match(r'^([.a-zA-Z_0-9\-]+)\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)(?:\s+load address\s+(0x[0-9a-fA-F]+))?', line)
        if m:
            name = m.group(1)
            if not should_exclude(name):
                addr = int(m.group(2), 16)
                size = int(m.group(3), 16)
                load_addr = int(m.group(4), 16) if m.group(4) else None
                current_output_section = {
                    'name': name,
                    'address': addr,
                    'size': size,
                    'load_address': load_addr
                }
                output_sections.append(current_output_section)
            else:
                current_output_section = None
        else:
            m1 = re.match(r'^([.a-zA-Z_0-9\-]+)\s*$', line)
            if m1:
                name = m1.group(1)
                if not should_exclude(name):
                    if i + 1 < len(lines):
                        next_line = lines[i+1]
                        m2 = re.match(r'^\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)(?:\s+load address\s+(0x[0-9a-fA-F]+))?', next_line)
                        if m2:
                            addr = int(m2.group(1), 16)
                            size = int(m2.group(2), 16)
                            load_addr = int(m2.group(3), 16) if m2.group(3) else None
                            current_output_section = {
                                'name': name,
                                'address': addr,
                                'size': size,
                                'load_address': load_addr
                            }
                            output_sections.append(current_output_section)
                            i += 1
                else:
                    current_output_section = None

        if current_output_section:
            im = re.match(r'^\s+([.a-zA-Z_0-9\-*]+)\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s+(.+)', line)
            if im:
                in_name = im.group(1)
                in_addr = int(im.group(2), 16)
                in_size = int(im.group(3), 16)
                in_file = im.group(4).strip()
                process_input_section(in_name, in_addr, in_size, in_file)
            else:
                im1 = re.match(r'^\s+([.a-zA-Z_0-9\-*]+)\s*$', line)
                if im1 and not line.strip().startswith('*fill*') and i + 1 < len(lines):
                    next_line = lines[i+1]
                    im2 = re.match(r'^\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s+(.+)', next_line)
                    if im2:
                        in_name = im1.group(1)
                        in_addr = int(im2.group(1), 16)
                        in_size = int(im2.group(2), 16)
                        in_file = im2.group(3).strip()
                        process_input_section(in_name, in_addr, in_size, in_file)
                        i += 1

        i += 1

    for sec in output_sections:
        if sec['size'] == 0:
            continue
        vma_region = find_region(sec['address'])
        if vma_region:
            vma_region['vma_used'] += sec['size']
            vma_region['sections'].append(sec)

        if sec['load_address'] is not None:
            lma_region = find_region(sec['load_address'])
            if lma_region and lma_region != vma_region:
                lma_region['lma_used'] += sec['size']
                lma_region['sections'].append({
                    'name': f"{sec['name']} (LMA load)",
                    'address': sec['load_address'],
                    'size': sec['size'],
                    'load_address': None
                })

    return regions, object_usage

def simplify_object_name(path):
    path = path.replace('\\', '/')
    archive_match = re.search(r'([^/]+\.a)\(([^)]+)\)', path)
    if archive_match:
        return f"{archive_match.group(1)} [{archive_match.group(2)}]"
    
    for marker in ['Application', 'Drivers', 'Middlewares', 'FATFS', 'EEZ', 'EEZ_Output']:
        idx = path.find(marker)
        if idx != -1:
            return path[idx:]
    return os.path.basename(path)

def generate_core_markdown(regions, object_usage, title, map_file):
    report = []
    report.append(f"## {title} Memory Usage\n")
    report.append(f"**Map file source:** `{map_file}`\n")
    
    # 1. Summary Table
    report.append("### Memory Regions Summary\n")
    report.append("| Region | Origin | Length | Used (Bytes) | Free (Bytes) | % Used |")
    report.append("| --- | --- | --- | --- | --- | --- |")
    
    for r in regions:
        used = r['vma_used'] + r['lma_used']
        free = r['length'] - used
        pct = (used / r['length']) * 100 if r['length'] > 0 else 0
        report.append(f"| **{r['name']}** | `0x{r['origin']:08X}` | {r['length']/1024:.1f} KB | {used:,} | {free:,} | {pct:.2f}% |")
    report.append("\n")

    # 2. Section Details
    report.append("### Section Details by Region\n")
    for r in regions:
        used = r['vma_used'] + r['lma_used']
        if used == 0:
            continue
        report.append(f"<details><summary><b>{r['name']} Sections ({len(r['sections'])} items)</b></summary>\n")
        report.append("| Section Name | Address | Size (Bytes) | Type |")
        report.append("| --- | --- | --- | --- |")
        sorted_sections = sorted(r['sections'], key=lambda s: s['size'], reverse=True)
        for s in sorted_sections:
            sec_type = "LMA (Load)" if "(LMA load)" in s['name'] else "VMA (Run)"
            report.append(f"| `{s['name']}` | `0x{s['address']:08X}` | {s['size']:,} | {sec_type} |")
        report.append("</details>\n\n")

    # 3. Object Files Contribution
    report.append("### Top Object Files / Modules Contribution\n")
    for r in regions:
        used = r['vma_used'] + r['lma_used']
        if used == 0:
            continue
        
        rname = r['name']
        report.append(f"<details><summary><b>Top Contributors to {rname}</b></summary>\n")
        report.append("| Object File / Library Module | Size (Bytes) | % of Region |")
        report.append("| --- | --- | --- |")
        
        file_contrib = {}
        for file_path, usage in object_usage.items():
            size = usage.get(rname, 0)
            lma_key = rname + " (LMA)"
            size += usage.get(lma_key, 0)
            
            if size > 0:
                simplified = simplify_object_name(file_path)
                file_contrib[simplified] = file_contrib.get(simplified, 0) + size
                
        sorted_contrib = sorted(file_contrib.items(), key=lambda x: x[1], reverse=True)
        
        for name, size in sorted_contrib[:15]:
            pct = (size / used) * 100 if used > 0 else 0
            report.append(f"| `{name}` | {size:,} | {pct:.2f}% |")
        
        if len(sorted_contrib) > 15:
            other_size = sum(x[1] for x in sorted_contrib[15:])
            other_pct = (other_size / used) * 100 if used > 0 else 0
            report.append(f"| *Other ({len(sorted_contrib) - 15} files)* | {other_size:,} | {other_pct:.2f}% |")
            
        report.append("</details>\n\n")
        
    return "\n".join(report)

def main():
    print("Analyzing memory map files...")
    
    # Locate CM7 Map File
    cm7_file = None
    for path in CM7_MAP_PATHS:
        if os.path.exists(path):
            cm7_file = path
            break
            
    # Locate CM4 Map File
    cm4_file = None
    for path in CM4_MAP_PATHS:
        if os.path.exists(path):
            cm4_file = path
            break

    if not cm7_file and not cm4_file:
        print("Error: Could not find any map files for CM7 or CM4 cores. Build the project first.")
        sys.exit(1)

    markdown_report = []
    markdown_report.append("# STM32H747 Dual-Core Memory Usage Report\n")
    markdown_report.append("This report is auto-generated by the project memory check task.\n")
    markdown_report.append("--- \n")

    # Parse CM7
    if cm7_file:
        print(f"Parsing CM7 map file: {cm7_file}...")
        parsed_cm7 = parse_map_file(cm7_file)
        if parsed_cm7:
            regions, object_usage = parsed_cm7
            cm7_md = generate_core_markdown(regions, object_usage, "Cortex-M7 (CM7) Core", cm7_file)
            markdown_report.append(cm7_md)
            markdown_report.append("\n---\n")
            
            # Print console summary
            print("\n--- Cortex-M7 Memory Summary ---")
            for r in regions:
                used = r['vma_used'] + r['lma_used']
                pct = (used / r['length']) * 100 if r['length'] > 0 else 0
                print(f"Region {r['name']:<10}: {used/1024:>6.1f} KB / {r['length']/1024:>6.1f} KB ({pct:.1f}% used)")
        else:
            print("Failed to parse CM7 map file.")
    else:
        print("Cortex-M7 map file not found. Skipping.")

    # Parse CM4
    if cm4_file:
        print(f"\nParsing CM4 map file: {cm4_file}...")
        parsed_cm4 = parse_map_file(cm4_file)
        if parsed_cm4:
            regions, object_usage = parsed_cm4
            cm4_md = generate_core_markdown(regions, object_usage, "Cortex-M4 (CM4) Core", cm4_file)
            markdown_report.append(cm4_md)
            
            # Print console summary
            print("\n--- Cortex-M4 Memory Summary ---")
            for r in regions:
                used = r['vma_used'] + r['lma_used']
                pct = (used / r['length']) * 100 if r['length'] > 0 else 0
                print(f"Region {r['name']:<10}: {used/1024:>6.1f} KB / {r['length']/1024:>6.1f} KB ({pct:.1f}% used)")
        else:
            print("Failed to parse CM4 map file.")
    else:
        print("Cortex-M4 map file not found. Skipping.")

    # Ensure output directory exists
    os.makedirs(os.path.dirname(OUTPUT_PATH), exist_ok=True)
    
    with open(OUTPUT_PATH, 'w', encoding='utf-8') as f:
        f.write("\n".join(markdown_report))

    print(f"\nSuccess! Full detailed report saved to: {OUTPUT_PATH}")

if __name__ == "__main__":
    main()
