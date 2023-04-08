#include"Pages.h"

void Open_Screen_Cartoon()
{
    lv_style_t main_style;
    lv_style_init(&main_style);
    lv_style_set_bg_color(&main_style,lv_color_make(0x00, 0x00, 0x00));
    lv_obj_add_style(lv_scr_act(),&main_style, 0);

    lv_obj_t* label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);
    lv_label_set_recolor(label1, true);
    lv_label_set_text(label1, "#FF0000 w# #FFA500 e# #FFFF00 l# #008000 c# #00FFFF o# #0000FF m# #800080 e# ");
    lv_obj_set_width(label1, 200);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
}
