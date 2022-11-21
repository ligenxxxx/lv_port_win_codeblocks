#include "../../../lvgl/lvgl.h"
#include "../theme/theme.h"

#define MY_DISP_HOR_RES 240
#define MY_DISP_VER_RES 240

static lv_obj_t *obj_background; 
static lv_obj_t *obj_instrument_profile;
static lv_obj_t *obj_meter;
static lv_meter_scale_t *scale[2];
static lv_meter_indicator_t *indic[2];

int angle;
const int16_t loc[12][2] = {
    {-90, -60},
    {-60, -50},
    {-50, -45},
    {-45, -40},
    {-40, -30},
    {-30,  0 },
    { 0 ,  30},
    { 30,  40},
    { 40,  45},
    { 45,  50},
    { 50,  60},
    { 60,  90},
};

uint32_t color_array[12][2] = {
    {0x851a01,0x851a01},
    {0xc44b00,0xff6c11},
    {0x8a5500,0xea9100},
    {0xa89c00,0xffed09},
    {0x586a0a,0xb4d915},
    {0x055b01,0x23fc18},
    {0x055b01,0x23fc18},
    {0x586a0a,0xb4d915},
    {0xa89c00,0xffed09},
    {0x8a5500,0xea9100},
    {0xc44b00,0xff6c11},
    {0x851a01,0x851a01},
};

static lv_style_t style_array[16];
static lv_obj_t *obj_arc[16];

static lv_obj_t *create_background(lv_obj_t *parent)
{
    lv_obj_t *obj;

    LV_IMG_DECLARE(image_background);
    obj = lv_img_create(parent);
    lv_img_set_src(obj, &image_background);
    lv_obj_center(obj);
    lv_obj_set_size(obj, MY_DISP_HOR_RES, MY_DISP_VER_RES);

    return obj;
}

static lv_obj_t *creatr_imstrument_profile(lv_obj_t *parent)
{
    lv_obj_t *obj;

    LV_IMG_DECLARE(image_instrument_profile);
    obj = lv_img_create(parent);
    lv_img_set_src(obj, &image_instrument_profile);
    lv_obj_center(obj);
    lv_obj_set_size(obj, MY_DISP_HOR_RES, MY_DISP_VER_RES);

    return obj;
}

static lv_obj_t *create_meter(lv_obj_t *parent)
{
    lv_obj_t *meter;

    meter = lv_meter_create(parent);
    lv_obj_set_size(meter, 194, 194);
    lv_obj_set_pos(meter, 23,82);

    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    //left
    scale[0] = lv_meter_add_scale(meter);
    lv_meter_set_scale_range(meter, scale[0], -90, 0, 90, 180);
    lv_meter_set_scale_ticks(meter, scale[0], 7, 2, 8, lv_color_black());
    indic[0] = lv_meter_add_arc(meter,scale[0], 30, lv_color_hex(color_array[5][0]), 10);
    lv_meter_set_indicator_start_value(meter, indic[0], -90);
    lv_meter_set_indicator_end_value(meter, indic[0], 0); //lock


    //right
    scale[1] = lv_meter_add_scale(meter);
    lv_meter_set_scale_range(meter, scale[1], 0, 90, 90, 270);
    lv_meter_set_scale_ticks(meter, scale[1], 7, 2, 8, lv_color_black());
    indic[1] = lv_meter_add_arc(meter,scale[1], 30, lv_color_hex(color_array[5][0]), 10);
    lv_meter_set_indicator_start_value(meter, indic[1], 0); //lock
    lv_meter_set_indicator_end_value(meter, indic[1],90);
    return meter;
}

static lv_obj_t *create_indicator(lv_obj_t *parent)
{
    
}

void ui_main(void)
{
    uint8_t i;


    obj_background = create_background(lv_scr_act());

    obj_meter = create_meter(obj_background);

    obj_instrument_profile = creatr_imstrument_profile(obj_background);

    //i = 5;
    //select_arc_area(i, 1);
    #if(0)
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, select_arc_area_a);
    lv_anim_set_time(&a, 10000);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_playback_time(&a, 300);
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
    #endif
}