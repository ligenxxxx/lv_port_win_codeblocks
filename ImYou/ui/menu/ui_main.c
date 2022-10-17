#include "../../../lvgl/lvgl.h"
#include "../theme/theme.h"

lv_obj_t *btn[4];
lv_obj_t *btn_label[4];

static void btn_event_cb(lv_event_t *e)
{
    static uint8_t cnt = 0;

    lv_obj_t *btn_cur = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn_cur, 0);
    cnt ++;
    lv_label_set_text_fmt(label, "top : %d", cnt);

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
    lv_obj_add_event_cb(btn[0], btn_event_cb, LV_EVENT_PRESSED, NULL);

    lv_label_set_text(btn_label[1], "bottum");
    lv_obj_align(btn[1], LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_label_set_text(btn_label[2], "left");
    lv_obj_align(btn[2], LV_ALIGN_LEFT_MID, 0, 0);

    lv_label_set_text(btn_label[3], "right");
    lv_obj_align(btn[3], LV_ALIGN_RIGHT_MID, 0, 0);

}

void ui_main(void)
{
    theme_init(THEME_DARK);
    //theme_init(THEME_LIGHT);

    lv_obj_t *root_page = create_rootpage(lv_scr_act());
    create_button(root_page);

}

