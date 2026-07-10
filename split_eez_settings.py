import json
import uuid
import sys

project_path = "EEZ/Riverdi-template/Riverdi-template.eez-project"

print(f"Reading project from {project_path}")
with open(project_path, "r", encoding="utf-8") as f:
    project = json.load(f)

def find_widget(node, identifier):
    if isinstance(node, dict):
        if node.get("identifier") == identifier:
            return node
        for val in node.values():
            res = find_widget(val, identifier)
            if res: return res
    elif isinstance(node, list):
        for item in node:
            res = find_widget(item, identifier)
            if res: return res
    return None

def find_parent(node, target_widget):
    if isinstance(node, dict):
        for val in node.values():
            if val is target_widget:
                return node
            if isinstance(val, (dict, list)):
                res = find_parent(val, target_widget)
                if res: return res
    elif isinstance(node, list):
        for item in node:
            if item is target_widget:
                return node
            if isinstance(item, (dict, list)):
                res = find_parent(item, target_widget)
                if res: return res
    return None

tab7 = find_widget(project, "tab7")
if not tab7:
    print("Error: Could not find tab7 in project!")
    sys.exit(1)

obj6 = find_widget(project, "obj6")
if not obj6:
    print("Error: Could not find parent obj6 of tab7!")
    sys.exit(1)

# Find settings_scroll_container in tab7 children
scroll_container = find_widget(tab7, "settings_scroll_container")
if not scroll_container:
    print("Error: Could not find settings_scroll_container inside tab7!")
    sys.exit(1)

# Retrieve all row items (excluding fake ones which we will regenerate)
all_rows = []
for child in scroll_container.get("children", []):
    ident = child.get("identifier", "")
    if "fake" not in ident:
        all_rows.append(child)

print(f"Retrieved {len(all_rows)} real settings elements (labels and textareas).")

# We want 9 rows of parameters:
# Page 1: Rows 0 to 4 (battery_count, pv_count, max_import, backup_soc, max_volt)
# Page 2: Rows 5 to 8 (min_volt, cos_phi, nom_volt, nom_freq)
# Page 3: Fake Rows 0 to 5

page1_widgets = []
page2_widgets = []
page3_widgets = []

for widget in all_rows:
    ident = widget.get("identifier", "")
    # Check row index from label_row_X or settings_..._ta
    # label_row_0 -> Row 0, settings_battery_count_ta -> Row 0
    # Map them by index:
    is_p1 = False
    is_p2 = False
    
    if ident in ["label_row_0", "settings_battery_count_ta",
                 "label_row_1", "settings_pv_count_ta",
                 "label_row_2", "settings_max_import_ta",
                 "label_row_3", "settings_backup_soc_ta",
                 "label_row_4", "settings_max_volt_ta"]:
        is_p1 = True
    elif ident in ["label_row_5", "settings_min_volt_ta",
                   "label_row_6", "settings_cos_phi_ta",
                   "label_row_7", "settings_nom_volt_ta",
                   "label_row_8", "settings_nom_freq_ta"]:
        is_p2 = True
    
    # Adjust position for absolute layout inside the page tab (y offset shifts to y = 80 + index*50)
    # Inside tab, original was y_pos relative to container which had top=60.
    # Let's clean top unit positioning.
    if is_p1:
        page1_widgets.append(widget)
    elif is_p2:
        page2_widgets.append(widget)

# Set absolute vertical positions inside page tabs
def position_widgets(widgets, indices_mapping):
    # indices_mapping maps identifier to page-relative index (0, 1, 2, ...)
    for w in widgets:
        ident = w.get("identifier")
        idx = indices_mapping.get(ident)
        if idx is not None:
            y_pos = 80 + idx * 50
            if w.get("type") == "LVGLLabelWidget":
                w["top"] = y_pos + 4
            else:
                w["top"] = y_pos

p1_map = {
    "label_row_0": 0, "settings_battery_count_ta": 0,
    "label_row_1": 1, "settings_pv_count_ta": 1,
    "label_row_2": 2, "settings_max_import_ta": 2,
    "label_row_3": 3, "settings_backup_soc_ta": 3,
    "label_row_4": 4, "settings_max_volt_ta": 4
}
p2_map = {
    "label_row_5": 0, "settings_min_volt_ta": 0,
    "label_row_6": 1, "settings_cos_phi_ta": 1,
    "label_row_7": 2, "settings_nom_volt_ta": 2,
    "label_row_8": 3, "settings_nom_freq_ta": 3
}

position_widgets(page1_widgets, p1_map)
position_widgets(page2_widgets, p2_map)

# Extract shared widgets template from tab7
title_template = find_widget(tab7, "label_settings_title")
apply_btn_template = find_widget(tab7, "settings_apply_btn")
reset_btn_template = find_widget(tab7, "settings_reset_btn")

def create_project_nav_button(identifier, text, x_pos):
    # Clone from apply_btn_template
    btn = json.loads(json.dumps(apply_btn_template))
    btn["objID"] = str(uuid.uuid4())
    btn["identifier"] = identifier
    btn["left"] = x_pos
    btn["width"] = 150
    btn["height"] = 40
    btn["top"] = 465
    btn["eventHandlers"] = []
    
    # Update label inside the button
    lbl = btn["children"][0]
    lbl["objID"] = str(uuid.uuid4())
    lbl["identifier"] = identifier + "_label"
    lbl["text"] = text
    lbl["width"] = 150
    
    # Slate style definition to make it look nice and modern
    btn["localStyles"] = {
        "objID": str(uuid.uuid4()),
        "definition": {
            "MAIN": {
                "DEFAULT": {
                    "bg_color": "#334155",
                    "border_color": "#475569",
                    "border_width": 1,
                    "radius": 4
                }
            }
        }
    }
    return btn

# Page 1: Next (left 40, width 150), Apply (left 390, width 180), Reset (left 590, width 180)
btn_next1 = create_project_nav_button("settings_next_btn", "Next >", 40)

# Modify original tab7 (Page 1) children to contain page 1 widgets directly
title_template["text"] = "SYSTEM CONFIGURATION (1/3)"
tab7["children"] = [title_template] + page1_widgets + [btn_next1, apply_btn_template, reset_btn_template]

# Create tab8 (Page 2)
tab8 = json.loads(json.dumps(tab7))
tab8["objID"] = str(uuid.uuid4())
tab8["identifier"] = "tab8"
tab8["tabName"] = "tab8"

# Update title and button identifiers/IDs on tab8
t2 = find_widget(tab8, "label_settings_title")
t2["objID"] = str(uuid.uuid4())
t2["identifier"] = "label_settings_title_2"
t2["text"] = "SYSTEM CONFIGURATION (2/3)"

a2 = find_widget(tab8, "settings_apply_btn")
a2["objID"] = str(uuid.uuid4())
a2["identifier"] = "settings_apply_btn_2"
a2["eventHandlers"][0]["objID"] = str(uuid.uuid4())
# update label inside button
a2_lbl = a2["children"][0]
a2_lbl["objID"] = str(uuid.uuid4())
a2_lbl["identifier"] = "settings_apply_btn_label_2"

r2 = find_widget(tab8, "settings_reset_btn")
r2["objID"] = str(uuid.uuid4())
r2["identifier"] = "settings_reset_btn_2"
r2["eventHandlers"][0]["objID"] = str(uuid.uuid4())
r2_lbl = r2["children"][0]
r2_lbl["objID"] = str(uuid.uuid4())
r2_lbl["identifier"] = "settings_reset_btn_label_2"

# Navigation buttons for Page 2: Prev (left 40), Next (left 210)
btn_prev2 = create_project_nav_button("settings_prev_btn_2", "< Prev", 40)
btn_next2 = create_project_nav_button("settings_next_btn_2", "Next >", 210)

# Assign Page 2 widgets
tab8["children"] = [t2] + page2_widgets + [btn_prev2, btn_next2, a2, r2]


# Create tab9 (Page 3)
tab9 = json.loads(json.dumps(tab7))
tab9["objID"] = str(uuid.uuid4())
tab9["identifier"] = "tab9"
tab9["tabName"] = "tab9"

# Update title and button identifiers/IDs on tab9
t3 = find_widget(tab9, "label_settings_title")
t3["objID"] = str(uuid.uuid4())
t3["identifier"] = "label_settings_title_3"
t3["text"] = "SYSTEM CONFIGURATION (3/3)"

a3 = find_widget(tab9, "settings_apply_btn")
a3["objID"] = str(uuid.uuid4())
a3["identifier"] = "settings_apply_btn_3"
a3["eventHandlers"][0]["objID"] = str(uuid.uuid4())
a3_lbl = a3["children"][0]
a3_lbl["objID"] = str(uuid.uuid4())
a3_lbl["identifier"] = "settings_apply_btn_label_3"

r3 = find_widget(tab9, "settings_reset_btn")
r3["objID"] = str(uuid.uuid4())
r3["identifier"] = "settings_reset_btn_3"
r3["eventHandlers"][0]["objID"] = str(uuid.uuid4())
r3_lbl = r3["children"][0]
r3_lbl["objID"] = str(uuid.uuid4())
r3_lbl["identifier"] = "settings_reset_btn_label_3"

# Navigation button for Page 3: Prev (left 40)
btn_prev3 = create_project_nav_button("settings_prev_btn_3", "< Prev", 40)

# Generate 6 fake parameters for tab9 (Page 3)
fake_widgets = []
# We use label_row_0 and settings_battery_count_ta as templates
label_tpl = json.loads(json.dumps(find_widget(project, "label_row_0")))
ta_tpl = json.loads(json.dumps(find_widget(project, "settings_battery_count_ta")))

for j in range(6):
    y_pos = 80 + j * 50
    
    # Fake Label
    fl = json.loads(json.dumps(label_tpl))
    fl["objID"] = str(uuid.uuid4())
    fl["identifier"] = f"label_fake_row_{j}"
    fl["text"] = f"Fake Test Parameter {j+1}"
    fl["top"] = y_pos + 4
    fl["localStyles"] = {
        "objID": str(uuid.uuid4()),
        "definition": {
            "MAIN": {
                "DEFAULT": {
                    "text_color": "#64748B",
                    "text_font": "MONTSERRAT_16"
                }
            }
        }
    }
    
    # Fake Textarea
    ft = json.loads(json.dumps(ta_tpl))
    ft["objID"] = str(uuid.uuid4())
    ft["identifier"] = f"fake_settings_ta_{j}"
    ft["top"] = y_pos
    ft["placeholderText"] = ""
    ft["localStyles"] = {
        "objID": str(uuid.uuid4()),
        "definition": {
            "MAIN": {
                "DEFAULT": {
                    "bg_color": "#0F172A",
                    "text_color": "#64748B",
                    "border_color": "#334155",
                    "radius": 4,
                    "text_font": "MONTSERRAT_16"
                }
            }
        }
    }

    fake_widgets.extend([fl, ft])

tab9["children"] = [t3] + fake_widgets + [btn_prev3, a3, r3]


# Now update the children of obj6 to insert tab8 and tab9 immediately after tab7
old_children = obj6["children"]
new_children = []
for child in old_children:
    new_children.append(child)
    if child.get("identifier") == "tab7":
        new_children.append(tab8)
        new_children.append(tab9)

obj6["children"] = new_children

# Save the updated project back
print(f"Writing updated project to {project_path}")
with open(project_path, "w", encoding="utf-8") as f:
    json.dump(project, f, indent=2)

print("Split completed successfully!")
