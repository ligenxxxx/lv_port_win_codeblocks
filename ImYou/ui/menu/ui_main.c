#include "../../../lvgl/lvgl.h"
#include "../theme/theme.h"
#include <stdio.h>

#define MY_DISP_HOR_RES 800
#define MY_DISP_VER_RES 600

unsigned char *vtx_string_list[] = {
    "HDZero Race V1\n",
    "HDZero Race V2\n",
    "HDZero Whoop\n",
    "HDZero Whoop Lite\n",
    "HDZero Freestyle"
};

static lv_obj_t *obj_background;
static lv_obj_t *obj_target_string;
static lv_obj_t *obj_vtx_list;

static lv_obj_t *create_background(lv_obj_t *parent)
{
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_set_size(obj, MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_obj_set_style_radius(obj, LV_COORD_MIN, 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x303030), 0);

    return obj;
}

static lv_obj_t *create_target_label(lv_obj_t *parent)
{
    lv_obj_t *obj = lv_label_create(parent);

    lv_label_set_text(obj, "Target");
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), 0);
    lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 0, 30);
}

static lv_obj_t *create_target_list(lv_obj_t *parent, unsigned char vtx_string_list)
{
    lv_obj_t *dd = lv_dropdown_create(parent);
    lv_dropdown_set_options(dd, "HDZero Race v1\n"
    "HDZero Race V2\n"
    "HDZero Whoop\n"
    "HDZero Whoop Lite\n"
    "HDZero Freestyle");
    lv_obj_set_style_size(dd, 250, 40, 0);
    lv_obj_align(dd, LV_ALIGN_TOP_LEFT, 70, 20);
}

void ui_main_task(void)
{
    obj_background = create_background(lv_scr_act());
    obj_target_string = create_target_label(obj_background);
    obj_vtx_list = create_target_list(obj_background, vtx_string_list);

}