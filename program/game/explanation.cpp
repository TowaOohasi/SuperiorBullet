#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "explanation.h"
#include <time.h>
#include<list>
#include<math.h>


extern Game_manager* game_manager_;

Explanation::Explanation(int controller_type) {
	setumei_img[0] = game_manager_->imgLoadGraph("graphics/chara_red_setumei.png");
	setumei_img[1] = game_manager_->imgLoadGraph("graphics/chara_blue_setumei.png");
	setumei_img[2] = game_manager_->imgLoadGraph("graphics/chara_green_setumei.png");
	setumei_img[4] = game_manager_->imgLoadGraph("graphics/chara_yellow_setumei.png");
	box = game_manager_->imgLoadGraph("graphics/draw_box.png");
	controller = controller_type;

}


void Explanation::slide_type(float deltatime) {
	if (input.ThumbLY < 0 || input.ThumbLY > 0) {
		state = push;
		slide_count += deltatime;
		if (slide_count > 0.02) {
			state = hold;
		}
	}
	else {
		state = enpty;
	}



}





void Explanation::update(float deltatime) {
	GetJoypadXInputState(controller, &input);



	
	


	if (input.Buttons[XINPUT_BUTTON_A]) {
		if (controller == DX_INPUT_PAD1) {
			game_manager_->ok_flag_1 = true;
		}
		if (controller == DX_INPUT_PAD2) {
			game_manager_->ok_flag_2 = true;
		}
	}

	if (input.Buttons[XINPUT_BUTTON_B]) {
		if (controller == DX_INPUT_PAD1) {
			game_manager_->ok_flag_1 = false;
		}
		if (controller == DX_INPUT_PAD2) {
			game_manager_->ok_flag_2 = false;
		}
	}




	if (input.Buttons[XINPUT_BUTTON_A]) {
		if (game_manager_->get_chara_1 == game_manager_->get_chara_2&& game_manager_->ok_flag_1&& game_manager_->ok_flag_2) {
			not_flag = true;
			feid_flag = true;
			if (controller==DX_INPUT_PAD1) {
				game_manager_->ok_flag_1 = false;
			}
			if (controller == DX_INPUT_PAD2) {
				game_manager_->ok_flag_2 = false;
			}
		}
	}





	if (feid_flag) {
		if (feid_count_flag==false) {
			if (feid_count < 400) {
				feid_count += 3;
			}
			else {
				feid_count_flag = true;
			}
		}

		if (feid_count_flag) {
			if (feid_count > 0) {
				feid_count -= 3;
			}
			else {
				not_flag = false;
				feid_flag = false;
				feid_count_flag = false;
			}
		}
	}



		if (stanby == false) {
			if (input.Buttons[XINPUT_BUTTON_Y]) {
				setumei = true;
			}
			else {
				setumei = false;
			}


			if (input.ThumbLY == 0) {
				slide_count = 0;
			}

		}


}


	void Explanation::draw(float deltatime) {
		if (setumei) {
			if (controller == DX_INPUT_PAD1) {
				DrawRotaGraph(320, 720 / 2, 1, 0, setumei_img[game_manager_->get_chara_1], true);
			}
			if (controller == DX_INPUT_PAD2) {
				DrawRotaGraph(960, 720 / 2, 1, 0, setumei_img[game_manager_->get_chara_2], true);
			}

		}

		

		if (not_flag) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, feid_count);
			SetFontSize(40);
			DrawRotaGraph(1280 / 2, 390, 1, 0, box, true);
			DrawStringEx(50, 720 / 2, 0x0000ff, "このキャラクターは相手に選択されています。選択できません。");
			SetFontSize(15);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		}
	}


