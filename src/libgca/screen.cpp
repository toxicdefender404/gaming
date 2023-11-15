/**#include "main.h"
lv_obj_t * screen = lv_obj_create(NULL, NULL);
lv_style_t buttonrel;
lv_style_t buttonpr;
lv_style_t textstyle;
lv_obj_t * redbtn = lv_btn_create(lv_scr_act(), NULL);
void scrinit(){
    screen->style_p->body.main_color = LV_COLOR_CYAN;
    screen->style_p->body.grad_color = LV_COLOR_CYAN;
    screen->style_p->body.border.color = LV_COLOR_BLACK;
    screen->style_p->body.border.width = 5;

    lv_style_copy(&buttonrel,&lv_style_plain);
    buttonrel.body.border.color = LV_COLOR_BLACK;
    buttonrel.body.border.width = 2;
    buttonrel.body.radius = 5;
    buttonrel.body.shadow.type = LV_SHADOW_FULL;
    buttonrel.body.shadow.width = 5;
    buttonrel.body.shadow.color = LV_COLOR_GRAY;

    lv_style_copy(&buttonpr,&buttonrel);
    buttonrel.body.main_color = LV_COLOR_RED;
    buttonrel.body.grad_color = LV_COLOR_RED;

    textstyle.text.letter_space = 2;
    textstyle.text.font = &lv_font_monospace_8;
    textstyle.text.color = LV_COLOR_BLACK;
    textstyle.text.line_space = 5;
    textstyle.text.opa = 255;
}
	lv_obj_set_size(redbtn,80,50);
	lv_obj_set_pos(redbtn,10,10);
	lv_btn_set_style(redbtn, LV_BTN_STYLE_REL,&buttonrel);
	lv_btn_set_style(redbtn, LV_BTN_STYLE_PR, &buttonpr); 
	redbtn->style_p->body.grad_color = LV_COLOR_RED;
	redbtn->style_p->body.main_color = LV_COLOR_RED;
	lv_obj_t * redtxt = lv_label_create(redbtn, NULL);
	lv_label_set_style(redtxt, &textstyle);
	lv_label_set_text(redtxt, "Red");
	//lv_btn_set_action(redbtn, LV_BTN_ACTION_PR,lv_res_t);
	lv_btn_set_action(redbtn,LV_BTN_ACTION_PR,amogus);**/