#include "../../../lvgl/lvgl.h"
#include "../theme/theme.h"
#if(0)
extern lv_indev_t * lv_win32_keypad_device_object;

lv_obj_t *btn[4];
lv_obj_t *btn_label[4];
static uint8_t cnt[4] = {0, 0, 0, 0};
lv_group_t *group;

static void btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    //lv_obj_t *target = lv_event_get_target(e);  //optional target(object)

    if(1)//(code == LV_EVENT_KEY)
    {
        uint8_t key = lv_event_get_key(e);
        printf("\r\n0x%X",key);
        lv_obj_t *label;

        if(key == 0x11)
        {
            cnt[0] ++;
            label = lv_obj_get_child(btn[0], 0);
            lv_label_set_text_fmt(label, "top : %d", cnt[0]);
        }
        else if(key == 0x12)
        {
            cnt[1] ++;
            label = lv_obj_get_child(btn[1], 0);
            lv_label_set_text_fmt(label, "bottom : %d", cnt[1]);
        }
        else if(key == 0x14)
        {
            cnt[2] ++;
            label = lv_obj_get_child(btn[2], 0);
            lv_label_set_text_fmt(label, "left : %d", cnt[2]);
        }
        else if(key == 0x13)
        {
            cnt[3] ++;
            label = lv_obj_get_child(btn[3], 0);
            lv_label_set_text_fmt(label, "right : %d", cnt[3]);
        }
    }

}

static lv_obj_t *create_rootpage(lv_obj_t *parent)
{
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme.theme_main_page_bg_color), 0);

    return obj;
}

static void create_button(lv_obj_t *parent)
{
    int i;
    for(i=0;i<4;i++)
    {
        btn[i] = lv_btn_create(parent);
        btn_label[i] = lv_label_create(btn[i]);
        lv_obj_set_style_bg_color(btn[i], lv_color_hex(0xff0000), 0);
    }

    lv_label_set_text(btn_label[0], "top : 0");
    lv_obj_align(btn[0], LV_ALIGN_TOP_MID, 0, 0);
    lv_group_add_obj(group, btn[0]);

    lv_label_set_text(btn_label[1], "bottum : 0");
    lv_obj_align(btn[1], LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_label_set_text(btn_label[2], "left : 0");
    lv_obj_align(btn[2], LV_ALIGN_LEFT_MID, 0, 0);

    lv_label_set_text(btn_label[3], "right : 0");
    lv_obj_align(btn[3], LV_ALIGN_RIGHT_MID, 0, 0);

}

void ui_main(void)
{
    /* add keypad to group */
    group = lv_group_create();
    lv_indev_set_group(lv_win32_keypad_device_object, group);

    /* initial theme */
    theme_init(THEME_DARK);
    //theme_init(THEME_LIGHT);

    lv_obj_t *root_page = create_rootpage(lv_scr_act());
    create_button(root_page);

    lv_obj_add_event_cb(btn[0], btn_event_cb, LV_EVENT_KEY, NULL);

}

#else
#define MY_DISP_HOR_RES 240
#define MY_DISP_VER_RES 240

const uint16_t loc[12][2] = {
    {0, 30},
    {30,40},
    {40,45},
    {45,50},
    {50,60},
    {60,90},
    {90,120},
    {120,130},
    {130,135},
    {135,140},
    {140,150},
    {150,180},
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

static lv_obj_t *obj_background; 
static lv_obj_t *obj_instrument_profile;
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

lv_obj_t *create_arc(lv_obj_t *parent, uint16_t index)
{
    lv_obj_t *arc;


    arc = lv_arc_create(parent);
    lv_obj_set_size(arc,200,200);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_arc_set_rotation(arc, 180);
    lv_arc_set_bg_angles(arc, loc[index][0],loc[index][1]);
    lv_arc_set_value(arc, 0);
    lv_obj_add_style(arc, &style_array[index], 0);

    lv_obj_set_pos(arc, 20, 81);

    return arc;
}

void select_arc_area(uint16_t index, uint8_t select)
{
    printf("\r\n%d", index);
    if(select)
    {
        lv_style_set_arc_width(&style_array[index], 50);
        lv_style_set_arc_color(&style_array[index], lv_color_hex(color_array[index][1]));
        lv_obj_move_foreground(obj_arc[index]);
    }
    else
    {
        lv_style_set_arc_width(&style_array[index], 40);
        lv_style_set_arc_color(&style_array[index], lv_color_hex(color_array[index][0]));
        lv_obj_move_foreground(obj_instrument_profile);
    }
}
#if(1)
void select_arc_area_a()
{
    static uint16_t add = 1;
    static uint16_t select = 1;
    static uint16_t index = 0;

    if(select)
    {
        lv_style_set_arc_width(&style_array[index], 50);
        lv_style_set_arc_color(&style_array[index], lv_color_hex(color_array[index][1]));
        lv_obj_move_foreground(obj_arc[index]);
    }
    else
    {
        lv_style_set_arc_width(&style_array[index], 40);
        lv_style_set_arc_color(&style_array[index], lv_color_hex(color_array[index][0]));
        lv_obj_move_background(obj_arc[index]);
    }

    printf("\r\n%d, %d, %d",index, select, add);
    if(add)
        index ++;
    else
        index --;
    if(index == 12)
    {
        select = 1 - select;
        add = 0;
        index = 11;
    }
    else if(index > 12)
    {
        add = 1;
        select = 1 - select;
        index = 0;
    }
}
#endif
void ui_main(void)
{
    uint8_t i;


    obj_background = create_background(lv_scr_act());

    for(i=0;i<12;i++)
    {
        lv_style_init(&style_array[i]);
        lv_style_set_arc_color(&style_array[i], lv_color_hex(color_array[i][0]));
        lv_style_set_arc_rounded(&style_array[i], false);
        lv_style_set_arc_width(&style_array[i], 40);

        obj_arc[i] = create_arc(obj_background, i);
    }

    obj_instrument_profile = creatr_imstrument_profile(obj_background);

    //i = 5;
    //select_arc_area(i, 1);
    #if(1)
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

#endif