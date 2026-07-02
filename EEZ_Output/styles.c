#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: btn_menu_style
//

void init_style_btn_menu_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_shadow_width(style, 0);
    lv_style_set_shadow_ofs_x(style, 0);
    lv_style_set_shadow_ofs_y(style, 0);
    lv_style_set_bg_color(style, lv_color_hex(0x121212));
    lv_style_set_radius(style, 2);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_pad_row(style, 0);
    lv_style_set_pad_column(style, 0);
    lv_style_set_layout(style, LV_LAYOUT_FLEX);
    lv_style_set_flex_flow(style, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_main_place(style, LV_FLEX_ALIGN_START);
    lv_style_set_flex_cross_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_flex_track_place(style, LV_FLEX_ALIGN_CENTER);
    {
        static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
        lv_style_set_grid_row_dsc_array(style, dsc);
    }
    {
        static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
        lv_style_set_grid_column_dsc_array(style, dsc);
    }
};

lv_style_t *get_style_btn_menu_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_menu_style_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_menu_style_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x685efc));
};

lv_style_t *get_style_btn_menu_style_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_menu_style_MAIN_PRESSED(style);
    }
    return style;
};

void init_style_btn_menu_style_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x121212));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_line_width(style, 2);
    lv_style_set_line_color(style, lv_color_hex(0xffffff));
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_color(style, lv_color_hex(0x3b3b3b));
};

lv_style_t *get_style_btn_menu_style_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_menu_style_MAIN_FOCUSED(style);
    }
    return style;
};

void add_style_btn_menu_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_menu_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_menu_style_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_btn_menu_style_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

void remove_style_btn_menu_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_menu_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_menu_style_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_btn_menu_style_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

//
// Style: pannel_style
//

void init_style_pannel_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0x121212));
    lv_style_set_line_width(style, 1);
    lv_style_set_line_color(style, lv_color_hex(0xff3333));
    lv_style_set_arc_width(style, 2);
    lv_style_set_arc_rounded(style, true);
    lv_style_set_radius(style, 2);
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_color(style, lv_color_hex(0x565656));
    lv_style_set_border_width(style, 0);
};

lv_style_t *get_style_pannel_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_pannel_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_pannel_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_pannel_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_pannel_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_pannel_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: tab_view_stayle
//

void init_style_tab_view_stayle_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_color(style, lv_color_hex(0x565656));
    lv_style_set_radius(style, 2);
};

lv_style_t *get_style_tab_view_stayle_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_tab_view_stayle_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_tab_view_stayle(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_tab_view_stayle_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_tab_view_stayle(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_tab_view_stayle_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: button_ico_container_style
//

void init_style_button_ico_container_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_layout(style, LV_LAYOUT_FLEX);
    lv_style_set_flex_main_place(style, LV_FLEX_ALIGN_START);
    lv_style_set_pad_left(style, 3);
};

lv_style_t *get_style_button_ico_container_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_ico_container_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_ico_container_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_button_ico_container_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_ico_container_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_button_ico_container_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: ico-custom
//

void init_style_ico_custom_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xa4a4a4));
    lv_style_set_text_font(style, &ui_font_ico_custom);
};

lv_style_t *get_style_ico_custom_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_ico_custom_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_ico_custom_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
    lv_style_set_text_font(style, &ui_font_ico_custom);
};

lv_style_t *get_style_ico_custom_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_ico_custom_MAIN_FOCUSED(style);
    }
    return style;
};

void add_style_ico_custom(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_ico_custom_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_ico_custom_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

void remove_style_ico_custom(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_ico_custom_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_ico_custom_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

//
// Style: ico-big
//

void init_style_ico_big_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_font(style, &ui_font_ico_big);
    lv_style_set_text_color(style, lv_color_hex(0xd7d7d7));
};

lv_style_t *get_style_ico_big_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_ico_big_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_ico_big(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_ico_big_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_ico_big(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_ico_big_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: btn-label
//

void init_style_btn_label_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xa4a4a4));
};

lv_style_t *get_style_btn_label_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_label_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_label_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
};

lv_style_t *get_style_btn_label_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_label_MAIN_FOCUSED(style);
    }
    return style;
};

void add_style_btn_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_label_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

void remove_style_btn_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_label_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

//
// Style: pinpad_label
//

void init_style_pinpad_label_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_flex_flow(style, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_main_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_flex_cross_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xffffff));
    lv_style_set_text_font(style, &lv_font_montserrat_24);
};

lv_style_t *get_style_pinpad_label_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_pinpad_label_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_pinpad_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_pinpad_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_pinpad_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_pinpad_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: pinpad_btn
//

void init_style_pinpad_btn_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_layout(style, LV_LAYOUT_FLEX);
    lv_style_set_flex_flow(style, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_main_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_flex_cross_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_bg_color(style, lv_color_hex(0x121212));
    lv_style_set_outline_width(style, 1);
    lv_style_set_outline_color(style, lv_color_hex(0x909090));
};

lv_style_t *get_style_pinpad_btn_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_pinpad_btn_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_pinpad_btn(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_pinpad_btn_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_pinpad_btn(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_pinpad_btn_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_btn_menu_style,
        add_style_pannel_style,
        add_style_tab_view_stayle,
        add_style_button_ico_container_style,
        add_style_ico_custom,
        add_style_ico_big,
        add_style_btn_label,
        add_style_pinpad_label,
        add_style_pinpad_btn,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_btn_menu_style,
        remove_style_pannel_style,
        remove_style_tab_view_stayle,
        remove_style_button_ico_container_style,
        remove_style_ico_custom,
        remove_style_ico_big,
        remove_style_btn_label,
        remove_style_pinpad_label,
        remove_style_pinpad_btn,
    };
    remove_style_funcs[styleIndex](obj);
}