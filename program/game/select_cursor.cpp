#include <stdlib.h>
#include <time.h>
#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include"game_manager.h"
#include"select_cursor.h"
#include <time.h>
#include<list>
#include<math.h>


extern Game_manager* game_manager_;


Select_cusor::Select_cusor(int controller_type) {
	controller = controller_type;
	cusor_1 = game_manager_->imgLoadGraph("graphics/1p.png");
	cusor_2 = game_manager_->imgLoadGraph("graphics/2p.png");
	label_img[0] = game_manager_->imgLoadGraph("graphics/red_label_layer1.png");
	label_img[1] = game_manager_->imgLoadGraph("graphics/blue_label_layer1.png");
	label_img[2] = game_manager_->imgLoadGraph("graphics/green_label_layer1.png");
	label_img[4] = game_manager_->imgLoadGraph("graphics/yellow_label_layer1.png");
	label_img[5] = game_manager_->imgLoadGraph("graphics/brak_label_layer1.png");
	label_img2[0] = game_manager_->imgLoadGraph("graphics/red_label_layer2.png");
	label_img2[1] = game_manager_->imgLoadGraph("graphics/blue_label_layer2.png");
	label_img2[2] = game_manager_->imgLoadGraph("graphics/green_label_layer2.png");
	label_img2[4] = game_manager_->imgLoadGraph("graphics/yellow_label_layer2.png");
	label_img2[5] = game_manager_->imgLoadGraph("graphics/brak_label_layer2.png");
	label_img3[0] = game_manager_->imgLoadGraph("graphics/red_label_layer3.png");
	label_img3[1] = game_manager_->imgLoadGraph("graphics/blue_label_layer3.png");
	label_img3[2] = game_manager_->imgLoadGraph("graphics/green_label_layer3.png");
	label_img3[4] = game_manager_->imgLoadGraph("graphics/yellow_label_layer3.png");
	label_img3[5] = game_manager_->imgLoadGraph("graphics/brak_label_layer3.png");
	chara_img[0] = game_manager_->imgLoadGraph("graphics/select_red.png");
	chara_img[1] = game_manager_->imgLoadGraph("graphics/select_blue.png");
	chara_img[2] = game_manager_->imgLoadGraph("graphics/select_green.png");
	chara_img[4] = game_manager_->imgLoadGraph("graphics/select_yellow.png");
	chara_img[5] = game_manager_->imgLoadGraph("graphics/select_black.png");
	label_text[0] = game_manager_->imgLoadGraph("graphics/tatenoonnakisi.png");
	label_text[1] = game_manager_->imgLoadGraph("graphics/eikokunotyounouryoku.png");
	label_text[2] = game_manager_->imgLoadGraph("graphics/kazenomajyutusi.png");
	label_text[4] = game_manager_->imgLoadGraph("graphics/senkounomegami.png");
	label_text[5] = game_manager_->imgLoadGraph("graphics/ryuuzinnoteiou.png");
	setumei_img[0] = game_manager_->imgLoadGraph("graphics/chara_red_setumei.png");
	setumei_img[2] = game_manager_->imgLoadGraph("graphics/chara_green_setumei.png");
	select_img = game_manager_->imgLoadGraph("graphics/char_select2.png");
	standby_img = game_manager_->imgLoadGraph("graphics/jyunbikanryou.png");
	big_ok1 = game_manager_->imgLoadGraph("graphics/big_ok1.png");
	big_ok2 = game_manager_->imgLoadGraph("graphics/big_ok2.png");
	standby_label = game_manager_->imgLoadGraph("graphics/standby_efect.png");
	speed_ = 3;
	pos_.x = 600;
	pos_.y = 260;
	game_manager_->chara_type1 = -1;
	game_manager_->chara_type2 = -1;
	text_move = t2k::Vector3::transformCoord(text_move, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(20)));
	text_move2 = t2k::Vector3::transformCoord(text_move2, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(-37)));
	text_move3 = t2k::Vector3::transformCoord(text_move3, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(18)));
	
}


void Select_cusor::push_type(float deltatime) {
	if (input.ThumbLY < 0|| input.ThumbLY > 0) {
		state = push;
		stick_count += deltatime;
		if (stick_count > 0.02) {
			state = hold;
		}
	}
	else {
		state = enpty;
	}
	


}







void Select_cusor::update(float deltatime) {
	GetJoypadXInputState(controller, &input);


	is_input_a_prev_ = is_input_a_now_;
	is_input_a_now_ = input.Buttons[XINPUT_BUTTON_A];

	if (is_start_) {
		is_start_ = false;
		return;
	}

	/*if (input.ThumbLX > 0) {
		pos_.x += speed_;
	}
	

	if (input.ThumbLX < 0) {
		pos_.x -= speed_;
	}*/
	
	if (standby == false) {

		if (input.ThumbLY < 0) {
			push_type(deltatime);
			if (state == push) {
				if (cusor_status < 5) {
					cusor_status++;
					if (controller == DX_INPUT_PAD1) {
						game_manager_->get_chara_1 = cusor_status;
					}
					if (controller == DX_INPUT_PAD2) {
						game_manager_->get_chara_2 = cusor_status;
					}
				}
			}


		}


		if (input.ThumbLY > 0) {
			push_type(deltatime);
			if (state == push) {
				if (cusor_status > 0) {
					cusor_status--;
					if (controller == DX_INPUT_PAD1) {
						game_manager_->get_chara_1 = cusor_status;
					}
					if (controller == DX_INPUT_PAD2) {
						game_manager_->get_chara_2 = cusor_status;
					}
				}
			}

		}

	}

	if (input.ThumbLY == 0) {
		stick_count = 0;
	}

	if (controller == DX_INPUT_PAD1) {
		//if (input.Buttons[XINPUT_BUTTON_A]) {
		if (is_input_a_now_ && !is_input_a_prev_) {
				game_manager_->chara_type1 = cusor_status;
				if (game_manager_->chara_type1 != game_manager_->chara_type2) {
					standby = true;
				}
		}
		else if (input.Buttons[XINPUT_BUTTON_B]) {
			standby = false;
			game_manager_->chara_type1 = -1;
		}
	}


	if (controller == DX_INPUT_PAD2) {
		if (input.Buttons[XINPUT_BUTTON_A]) {
			game_manager_->chara_type2 = cusor_status;
			if (game_manager_->chara_type1 != game_manager_->chara_type2) {
				standby = true;
			}
		}
		else if (input.Buttons[XINPUT_BUTTON_B]) {
			standby = false;
			game_manager_->chara_type2 = -1;

		}
	}

	/*if (input.Buttons[XINPUT_BUTTON_A]) {
		if (game_manager_->chara_type1 == game_manager_->chara_type2) {
			not_flag = true;
		}
	}

	if (not_flag) {
		not_count += deltatime;
		if (not_count > 3) {
			not_flag = false;
			not_count = 0;
		}
	}*/


	/*if (input.Buttons[XINPUT_BUTTON_Y]) {
		setumei = true;
	}
	else {
		setumei = false;
	}*/



	/*if (input.Buttons[XINPUT_BUTTON_A]) {
		g++;
	}*/

	
	
	pos_ += text_move * speed_;
	move_pos_3[0] += text_move3 * speed_;
	move_pos_2[0] += text_move2 * speed_;
	player2_pos_1[0] += text_move * speed_;
	player2_pos_2[0] += text_move2 * (speed_+0.5);
	player2_pos_3[0] += text_move3 * speed_;
	//電光掲示板的な処理

	/*label_move(pos_, text_flag, move_pos_, text_move,speed_);*/
	{
		if (pos_.x < 200) {
			text_flag = true;
		}

		if (move_pos_.x < -200) {
			move_pos_ = { 600,260,0 };
		}

		if (text_flag) {
			move_pos_ += text_move * speed_;
		}


		if (pos_.x < -200) {
			pos_.x = 600;
			pos_.y = 260;
		}
	}



	{
		if (move_pos_3[0].x < 200) {
			text_flag3 = true;
		}

		if (move_pos_3[1].x < -200) {
			move_pos_3[1] = { 600,625,0 };
		}

		if (text_flag3) {
			move_pos_3[1] += text_move3 * speed_;
		}

		if (move_pos_3[0].x < -200) {
			move_pos_3[0] = { 600,625,0 };
		}
	}


	{
		if (move_pos_2[0].y > 360) {
			text_flag2 = true;
		}

		if (move_pos_2[1].y > 720) {
			move_pos_2[1] = { 740,20,0 };
		}

		if (text_flag2) {
			move_pos_2[1] += text_move2 * speed_;
		}

		if (move_pos_2[0].y > 720) {
			move_pos_2[0] = { 740,20,0 };
		}
	}


	{
		if (player2_pos_3[0].x < 1050) {
			player2_flag3 = true;
		}

		if (player2_pos_3[1].x < 640) {
			player2_pos_3[1] = { 1480,700,0 };
		}

		if (player2_flag3) {
			player2_pos_3[1] += text_move3 * speed_;
		}

		if (player2_pos_3[0].x < 640) {
			player2_pos_3[0] = { 1480,700,0 };
		}
	}


	{
		if (player2_pos_1[0].x < 1000) {
			player2_flag = true;
		}

		if (player2_pos_1[1].x < 730) {
			player2_pos_1[1] = { 1580,390,0 };
		}

		if (player2_flag) {
			player2_pos_1[1] += text_move * speed_;
		}

		if (player2_pos_1[0].x < 730) {
			player2_pos_1[0] = { 1580,390,0 };
		}
	}


	{
		if (player2_pos_2[0].y > 360) {
			player2_flag2 = true;
		}

		if (player2_pos_2[1].y > 780) {
			player2_pos_2[1] = { 1500,-70,0 };
		}

		if (player2_flag2) {
			player2_pos_2[1] += text_move2 * (speed_ + 0.5);
		}

		if (player2_pos_2[0].y > 780) {
			player2_pos_2[0] = { 1500,-70,0 };
		}
	}




}
	







void Select_cusor::draw(float deltatime) {
	if (controller == DX_INPUT_PAD1) {
		if (standby == false) {
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, label_img[cusor_status], true);
			DrawRotaGraph(pos_.x, pos_.y, 1, t2k::toRadian(20), label_text[cusor_status], true);
			DrawRotaGraph(move_pos_.x, move_pos_.y, 1, t2k::toRadian(20), label_text[cusor_status], true);
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, label_img2[cusor_status], true);
			DrawRotaGraph(move_pos_2[0].x, move_pos_2[0].y, 1, t2k::toRadian(-36), label_text[cusor_status], true);
			DrawRotaGraph(move_pos_2[1].x, move_pos_2[1].y, 1, t2k::toRadian(-36), label_text[cusor_status], true);
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, label_img3[cusor_status], true);
			DrawRotaGraph(move_pos_3[0].x, move_pos_3[0].y, 1, t2k::toRadian(18), label_text[cusor_status], true);
			DrawRotaGraph(move_pos_3[1].x, move_pos_3[1].y, 1, t2k::toRadian(18), label_text[cusor_status], true);
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, chara_img[cusor_status], true);
		}

		if (standby) {
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, label_img[cusor_status], true);
			DrawRotaGraph(pos_.x, pos_.y, 1, t2k::toRadian(20), standby_img, true);
			DrawRotaGraph(move_pos_.x, move_pos_.y, 1, t2k::toRadian(20), standby_img, true);
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, label_img2[cusor_status], true);
			DrawRotaGraph(move_pos_2[0].x, move_pos_2[0].y, 1, t2k::toRadian(-36), standby_img, true);
			DrawRotaGraph(move_pos_2[1].x, move_pos_2[1].y, 1, t2k::toRadian(-36), standby_img, true);
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, label_img3[cusor_status], true);
			DrawRotaGraph(move_pos_3[0].x, move_pos_3[0].y, 1, t2k::toRadian(18), standby_img, true);
			DrawRotaGraph(move_pos_3[1].x, move_pos_3[1].y, 1, t2k::toRadian(18), standby_img, true);
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, chara_img[cusor_status], true);
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, big_ok1, true);
		}

		DrawRotaGraph(cusor_pos[cusor_status].x, cusor_pos[cusor_status].y, 1, 0, cusor_1, true);
	}
	if(controller == DX_INPUT_PAD2){
		if (standby == false) {
			DrawRotaGraph(1280, 720 / 2, 1, 0, label_img[cusor_status], true);
			DrawRotaGraph(player2_pos_1[0].x, player2_pos_1[0].y, 1, t2k::toRadian(20), label_text[cusor_status], true);
			DrawRotaGraph(player2_pos_1[1].x, player2_pos_1[1].y, 1, t2k::toRadian(20), label_text[cusor_status], true);
			DrawRotaGraph(1280, 720 / 2, 1, 0, label_img2[cusor_status], true);
			DrawRotaGraph(player2_pos_2[0].x, player2_pos_2[0].y, 1, t2k::toRadian(-36), label_text[cusor_status], true);
			DrawRotaGraph(player2_pos_2[1].x, player2_pos_2[1].y, 1, t2k::toRadian(-36), label_text[cusor_status], true);
			DrawRotaGraph(1280, 720 / 2, 1, 0, label_img3[cusor_status], true);
			DrawRotaGraph(player2_pos_3[0].x, player2_pos_3[0].y, 1, t2k::toRadian(18), label_text[cusor_status], true);
			DrawRotaGraph(player2_pos_3[1].x, player2_pos_3[1].y, 1, t2k::toRadian(18), label_text[cusor_status], true);
			DrawTurnGraph(0, 0, chara_img[cusor_status], true);
		}

		if (standby) {
			DrawRotaGraph(1280, 720 / 2, 1, 0, label_img[cusor_status], true);
			DrawRotaGraph(player2_pos_1[0].x, player2_pos_1[0].y, 1, t2k::toRadian(20), standby_img, true);
			DrawRotaGraph(player2_pos_1[1].x, player2_pos_1[1].y, 1, t2k::toRadian(20), standby_img, true);
			DrawRotaGraph(1280, 720 / 2, 1, 0, label_img2[cusor_status], true);
			DrawRotaGraph(player2_pos_2[0].x, player2_pos_2[0].y, 1, t2k::toRadian(-36), standby_img, true);
			DrawRotaGraph(player2_pos_2[1].x, player2_pos_2[1].y, 1, t2k::toRadian(-36), standby_img, true);
			DrawRotaGraph(1280, 720 / 2, 1, 0, label_img3[cusor_status], true);
			DrawRotaGraph(player2_pos_3[0].x, player2_pos_3[0].y, 1, t2k::toRadian(18), standby_img, true);
			DrawRotaGraph(player2_pos_3[1].x, player2_pos_3[1].y, 1, t2k::toRadian(18), standby_img, true);
			DrawTurnGraph(0, 0, chara_img[cusor_status], true);
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, big_ok2, true);

		}
		DrawRotaGraph(cusor_pos[cusor_status].x, cusor_pos[cusor_status].y, 1, 0, cusor_2, true);

	}
	SetFontSize(50);
	
	DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, select_img, true);

	/*if (setumei) {
		if (controller == DX_INPUT_PAD1) {
			DrawRotaGraph(320, 720/2, 1, 0, setumei_img[cusor_status], true);
		}
		if (controller == DX_INPUT_PAD2) {
			DrawRotaGraph(960, 720 / 2, 1, 0, setumei_img[cusor_status], true);
		}
	
	}*/


	if (game_manager_->non_select_flag) {
		DrawRotaGraph(1280/2, 720/2, 1, 0, standby_label, true);
		
	}
	
	/*if (not_flag) {
		SetFontSize(40);
		DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, box, true);
		DrawStringEx(50, 720 / 2, 0x0000ff, "このキャラクターは相手に選択されています。選択できません。");
		SetFontSize(15);
	}*/
	

}

