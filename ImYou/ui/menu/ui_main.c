#include "../../../lvgl/lvgl.h"
#include "../theme/theme.h"

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
    lv_obj_set_size(obj, 320, 176);
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

