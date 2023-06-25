#include "main.h"
#include "selection.h"
#include "globals/globals.hpp"

static const char *btnmMap[] = {"test", "solo AWP", "prog skills", "\n", "alliance auto close", 
	"alliance auto far", "\n", "Do Nothing", ""};



lv_res_t redBtnmAction(lv_obj_t *btnm, const char *txt){
	printf("red button: %s released\n", txt);
	lv_theme_t *th = lv_theme_nemo_init(0, NULL);
	lv_theme_set_current(th);
	if (strcmp(txt, "test") == 0)
	{
		autonSelection = S_RED5;
	}
	if (strcmp(txt, "solo AWP") == 0)
	{
		autonSelection = S_RED7;
	}
	if (strcmp(txt, "prog skills") == 0)
	{
		autonSelection = S_RED8;
	}
	if (strcmp(txt, "alliance auto close") == 0)
	{
		autonSelection = B_RED3;
	}
	if (strcmp(txt, "alliance auto far") == 0)
	{
		autonSelection = B_RED6_C;
	}
	if (strcmp(txt, "Do Nothing") == 0)
	{
		autonSelection = NOTHING;
	}

	return LV_RES_OK; // return OK because the button matrix is not deleted
}

lv_res_t blueBtnmAction(lv_obj_t *btnm, const char *txt)
{
	printf("blue button: %s released\n", txt);

	lv_theme_t *th = lv_theme_nemo_init(230, NULL);
	lv_theme_set_current(th);

	if (strcmp(txt, "test") == 0)
	{
		autonSelection = S_BLUE5;
	}
	if (strcmp(txt, "solo AWP") == 0)
	{
		autonSelection = S_BLUE7;
	}
	if (strcmp(txt, "prog skills") == 0)
	{
		autonSelection = S_BLUE8;
	}
	if (strcmp(txt, "alliance auto close") == 0)
	{
		autonSelection = B_BLUE3;
	}
	if (strcmp(txt, "alliance auto far") == 0)
	{
		autonSelection = B_BLUE6_C;
	}
	if (strcmp(txt, "Do Nothing") == 0)
	{
		autonSelection = NOTHING;
	}

	return LV_RES_OK;
}

lv_res_t skillsBtnAction(lv_obj_t *btn)
{
	// lvgl theme
	lv_theme_t *th = lv_theme_nemo_init(286, NULL); //make purple because purple good
	lv_theme_set_current(th);
	
	lv_style_scr.body.main_color = LV_COLOR_BLACK; 
	
	printf("skills pressed");
	autonSelection = SKILLS;
	return LV_RES_OK;
}

void selectorInit(){
	// lvgl theme
	lv_theme_t *th = lv_theme_nemo_init(286, NULL); //make purple because purple good
	lv_theme_set_current(th);



	// create a tab view object
	lv_obj_t *tabview;
	tabview = lv_tabview_create(lv_scr_act(), NULL);


	// add 3 tabs (the tabs are page (lv_page) and can be scrolled
	lv_obj_t *redTab = lv_tabview_add_tab(tabview, "Red");
	lv_obj_t *blueTab = lv_tabview_add_tab(tabview, "Blue");
	lv_obj_t *skillsTab = lv_tabview_add_tab(tabview, "Skills");

	// add content to the tabs
	// button matrix
	lv_obj_t *redBtnm = lv_btnm_create(redTab, NULL);
	lv_btnm_set_map(redBtnm, btnmMap);
	lv_btnm_set_action(redBtnm, redBtnmAction);
	lv_btnm_set_toggle(redBtnm, true, 3);//3
	lv_obj_set_size(redBtnm, 450, 130);
	lv_obj_set_pos(redBtnm, 0, 100);
	lv_obj_align(redBtnm, NULL, LV_ALIGN_CENTER, 0, 0);

	// blue tab
	lv_obj_t *blueBtnm = lv_btnm_create(blueTab, NULL);
	lv_btnm_set_map(blueBtnm, btnmMap);
	lv_btnm_set_action(blueBtnm, blueBtnmAction);
	lv_btnm_set_toggle(blueBtnm, true, 3);
	lv_obj_set_size(blueBtnm, 450, 130);
	lv_obj_set_pos(blueBtnm, 0, 100);
	lv_obj_align(blueBtnm, NULL, LV_ALIGN_CENTER, 0, 0);


	// skills tab
	lv_obj_t *skillsBtn = lv_btn_create(skillsTab, NULL);
	lv_obj_t *label = lv_label_create(skillsBtn, NULL);
	lv_label_set_text(label, "Skills");
	lv_btn_set_action(skillsBtn, LV_BTN_ACTION_CLICK, skillsBtnAction);
	// lv_btn_set_state(skillsBtn, LV_BTN_STATE_TGL_REL);
	lv_obj_set_size(skillsBtn, 450, 50);
	lv_obj_set_pos(skillsBtn, 0, 100);
	lv_obj_align(skillsBtn, NULL, LV_ALIGN_CENTER, 0, 0);
}
