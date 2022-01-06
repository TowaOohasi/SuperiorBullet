#include "DxLib.h"
#include "player.h"
#include "game_manager.h"
#include "../support/Support.h"
#include "../library/t2klib.h"
#include "bullet.h"
#include"life.h"

extern Game_manager* game_manager_;
extern Bullet* bullet_;
//extern Life* life;

Player::Player(t2k::Vector3 coordinate, int controller, int wa) {
	pos_ = coordinate;
	speed_ = 4;
	test = { 1,0,0 };
	controller_type = controller;
	chara_type = wa;
	bullet_img_a = game_manager_->imgLoadGraph("graphics/bullet_a.png");
	bullet_img_b = game_manager_->imgLoadGraph("graphics/bullet_b2.png");
	bullet_img_x = game_manager_->imgLoadGraph("graphics/bullet_x.png");
	bullet_red_shield = game_manager_->imgLoadGraph("graphics/bullet_red.png");
	bullet_red_a = game_manager_->imgLoadGraph("graphics/bullet_reda.png");
	bullet_blue_a = game_manager_->imgLoadGraph("graphics/blue_bullet_a.png");
	bullet_blue_b = game_manager_->imgLoadGraph("graphics/blue_bullet_b.png");
	bullet_blue_x = game_manager_->imgLoadGraph("graphics/blue_bullet_x.png");
	bullet_blue_y = game_manager_->imgLoadGraph("graphics/blue_bullet_y.png");
	cursor = game_manager_->imgLoadGraph("graphics/yazirusi.png");
	chara_img_red = game_manager_->imgLoadGraph("graphics/character_red1.png");
	chara_img_blue = game_manager_->imgLoadGraph("graphics/character_blre1.png");
	chara_img_green = game_manager_->imgLoadGraph("graphics/character_green1.png");
	chara_img_yellow = game_manager_->imgLoadGraph("graphics/character_yellow1.png");
	chara_img_black = game_manager_->imgLoadGraph("graphics/character_black1.png");
	bullet_yellow_a = game_manager_->imgLoadGraph("graphics/yellow_bullet_a.png");
	bullet_yellow_b = game_manager_->imgLoadGraph("graphics/yellow_bullet_b.png");
	bullet_yellow_x = game_manager_->imgLoadGraph("graphics/laser2.png");
	bullet_yellow_y = game_manager_->imgLoadGraph("graphics/yellow_bullet_y.png");
	icon_red = game_manager_->imgLoadGraph("graphics/bullet_icon_red.png");
	icon_red_time_img[0] = game_manager_->imgLoadGraph("graphics/bullet_icon_red_a.png");
	icon_red_time_img[1] = game_manager_->imgLoadGraph("graphics/bullet_icon_red_b.png");
	icon_red_time_img[2] = game_manager_->imgLoadGraph("graphics/bullet_icon_red_x.png");
	icon_red_time_img[3] = game_manager_->imgLoadGraph("graphics/bullet_icon_red_y.png");
	icon_green = game_manager_->imgLoadGraph("graphics/bullet_icon_green.png");
	icon_green_time_img[0] = game_manager_->imgLoadGraph("graphics/bullet_icon_green_a.png");
	icon_green_time_img[1] = game_manager_->imgLoadGraph("graphics/bullet_icon_green_b.png");
	icon_green_time_img[2] = game_manager_->imgLoadGraph("graphics/bullet_icon_green_x.png");
	icon_green_time_img[3] = game_manager_->imgLoadGraph("graphics/bullet_icon_green_y.png");
	icon_blue = game_manager_->imgLoadGraph("graphics/bullet_icon_blue.png");
	icon_blue_time_img[0] = game_manager_->imgLoadGraph("graphics/bullet_icon_blue_a.png");
	icon_blue_time_img[1] = game_manager_->imgLoadGraph("graphics/bullet_icon_blue_b.png");
	icon_blue_time_img[2] = game_manager_->imgLoadGraph("graphics/bullet_icon_blue_x.png");
	icon_blue_time_img[3] = game_manager_->imgLoadGraph("graphics/bullet_icon_blue_y.png");
	icon_yellow = game_manager_->imgLoadGraph("graphics/bullet_icon_yellow.png");
	icon_yellow_time_img[0] = game_manager_->imgLoadGraph("graphics/bullet_icon_yellow_a.png");
	icon_yellow_time_img[1] = game_manager_->imgLoadGraph("graphics/bullet_icon_yellow_b.png");
	icon_yellow_time_img[2] = game_manager_->imgLoadGraph("graphics/bullet_icon_yellow_x.png");
	icon_yellow_time_img[3] = game_manager_->imgLoadGraph("graphics/bullet_icon_yellow_y.png");

	if (chara_type == chara_green) {
		get_collar = 0x00ff00;

	}
	else if (chara_type == chara_red) {
		get_collar = 0x0000ff;

	}


}




void Player::push_type(int a, float deltatime) {
	if (input.Buttons[a]) {
		state = push;
		push_count += deltatime;
		if (push_count > 0.02) {
			state = hold;
		}
	}
	else {
		state = enpty;
	}



}



int Player::all_push(int buttan) {
	for (int i = 0; i < 17; i++) {
		if (buttan == i) {
			ago_push[i] = now_push[i];
			now_push[i] = input.Buttons[i];
			if (now_push[i] && !ago_push[i]) {
				//push_number = push;
				state = push;
			}
			else if (now_push[i] && ago_push[i]) {
				//push_number = hold;
				state = hold;
			}
			else {
				//push_number = enpty;
				state = enpty;

			}


		}
	}
	return state;
}





void Player::erase_has_players_bullet() {
	std::list<Bullet*>::iterator it = bullet_.begin();
	while (it != bullet_.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = bullet_.erase(it);
			continue;
		}
		it++;
	}

	it = bullet_b.begin();
	while (it != bullet_b.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = bullet_b.erase(it);
			continue;
		}
		it++;
	}

	it = bullet_x.begin();
	while (it != bullet_x.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = bullet_x.erase(it);
			continue;
		}
		it++;
	}


	it = red_a.begin();
	while (it != red_a.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = red_a.erase(it);
			continue;
		}
		it++;
	}

	it = red_a_2.begin();
	while (it != red_a_2.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = red_a_2.erase(it);
			continue;
		}
		it++;
	}

	it = red_b.begin();
	while (it != red_b.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = red_b.erase(it);
			continue;
		}
		it++;
	}

	it = bullet_red.begin();
	while (it != bullet_red.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = bullet_red.erase(it);
			continue;
		}
		it++;
	}


	it = red_x.begin();
	while (it != red_x.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = red_x.erase(it);
			continue;
		}
		it++;
	}


	it = blue_a.begin();
	while (it != blue_a.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = blue_a.erase(it);
			continue;
		}
		it++;
	}


	it = blue_b.begin();
	while (it != blue_b.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = blue_b.erase(it);
			continue;
		}
		it++;
	}


	it = blue_x.begin();
	while (it != blue_x.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = blue_x.erase(it);
			continue;
		}
		it++;
	}


	it = blue_y.begin();
	while (it != blue_y.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = blue_y.erase(it);
			continue;
		}
		it++;
	}


	it = yellow_a.begin();
	while (it != yellow_a.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = yellow_a.erase(it);
			continue;
		}
		it++;
	}
	
	
	it = yellow.begin();
	while (it != yellow.end()) {
		(*it)->erase_check();
		if (!(*it)->is_alive_) {
			it = yellow.erase(it);
			continue;
		}
		it++;
	}



}



void Player::character_green(float deltatime) {
	{  //‚`ƒ{ƒ^ƒ“‚ÌŒ‚‚Âˆ—
		shot_count_A += deltatime;
		if (input.Buttons[XINPUT_BUTTON_A]) {
			if (shot_count_A > cooltime_green_a) {
				get_player_A(pos_);
				shot_count_A = 0;
			}
		}

	}


	//{  //B’e–‹¶¬
	//	shot_count_B += deltatime;
	//	if (input.Buttons[XINPUT_BUTTON_B]) {
	//		push_type(XINPUT_BUTTON_B, deltatime);
	//		if (state == 0) {
	//			if (shot_count_B > cooltime_green_b) {
	//				get_player_B(pos_);
	//				shot_count_B = 0;
	//			}
	//		}
	//	}
	//	else {
	//		state = enpty;
	//	}
	//}

	{  //B’e–‹¶¬
		shot_count_B += deltatime;
		if (all_push(XINPUT_BUTTON_B) == push) {
			if (shot_count_B > cooltime_green_b) {
				get_player_B(pos_);
				shot_count_B = 0;
			}
		}
	}


	{  //X’e–‹¶¬
		shot_count_X += deltatime;
		if (input.Buttons[XINPUT_BUTTON_X]) {
			push_type(XINPUT_BUTTON_X, deltatime);
			if (state == 0) {
				if (shot_count_X > cooltime_green_x) {
					get_player_X(pos_);
					shot_count_X = 0;
				}
			}
		}
	}


	{  //Yƒ{ƒ^ƒ“@‘ŠŽè‚Ìƒ‰ƒCƒt‚ðí‚éƒT[ƒNƒ‹‚ÌƒXƒCƒbƒ`
		shot_count_Y += deltatime;
		if (input.Buttons[XINPUT_BUTTON_Y]) {
			if (shot_count_Y > cooltime_green_y) {
				suiti = true;
			}
		}
		if (suiti) {
			lag_count += deltatime;
			range = true;
			suiti = false;
			shot_count_Y = 0;
		}
		else {
			range = false;

		}

	}
}




void Player::character_red(float deltatime) {
	//{  //‚`ƒ{ƒ^ƒ“‚ÌŒ‚‚Âˆ—
	//	shot_count_A += deltatime;
	//	if (input.Buttons[XINPUT_BUTTON_A]) {
	//		push_type(XINPUT_BUTTON_A, deltatime);
	//		if (state == 0) {
	//			if (shot_count_A > cooltime_red_a) {
	//				get_red_A(pos_);
	//				shot_count_A = 0;
	//			}
	//		}
	//	}
	//	else {
	//		state = enpty;
	//	}
	//}

	{  //‚`ƒ{ƒ^ƒ“‚ÌŒ‚‚Âˆ—
		shot_count_A += deltatime;
		if (all_push(XINPUT_BUTTON_A) == push) {
			if (shot_count_A > cooltime_red_a) {
				get_red_A(pos_);
				shot_count_A = 0;
			}
		}


	}


	//{  //B’e–‹¶¬
	//	shot_count_B += deltatime;
	//	if (input.Buttons[XINPUT_BUTTON_B]) {
	//		push_type(XINPUT_BUTTON_B, deltatime);
	//		if (state == 0) {
	//			if (shot_count_B > cooltime_red_b) {
	//				get_red_B(pos_);
	//				shot_count_B = 0;
	//			}
	//		}
	//	}
	//}


	{  //B’e–‹¶¬
		shot_count_B += deltatime;
		if (all_push(XINPUT_BUTTON_B) == hold) {
			if (shot_count_B > cooltime_red_b) {
				get_red_B(pos_);
				shot_count_B = 0;
			}
		}
	}


	{  //X’e–‹¶¬
		shot_count_X += deltatime;
		if (input.Buttons[XINPUT_BUTTON_X]) {
			push_type(XINPUT_BUTTON_X, deltatime);
			if (state == 0) {
				if (shot_count_X > cooltime_red_x) {
					get_red_X(pos_);
					shot_count_X = 0;
				}
			}
		}
	}


	{  //Yƒ{ƒ^ƒ“@’e–‹–³Œø‰»ƒT[ƒNƒ‹‚ÌƒXƒCƒbƒ`
		shot_count_Y += deltatime;
		if (input.Buttons[XINPUT_BUTTON_Y]) {
			if (shot_count_Y > cooltime_red_y) {
				suiti = true;
			}
		}
		if (suiti) {
			lag_count += deltatime;
			range = true;
			suiti = false;
			shot_count_Y = 0;
		}
		else {
			range = false;

		}

	}

}


//chara_blue‚Ìƒ{ƒ^ƒ““ü—Í
void Player::character_blue(float deltatime) {
	{  //‚`ƒ{ƒ^ƒ“‚ÌŒ‚‚Âˆ—
		shot_count_A += deltatime;
		if (input.Buttons[XINPUT_BUTTON_A]) {
			if (shot_count_A > cooltime_blue_a) {
				get_blue_A(pos_);
				shot_count_A = 0;
			}
		}

	}


	{  //B’e–‹¶¬
		shot_count_B += deltatime;
		if (all_push(XINPUT_BUTTON_B) == push) {
			if (shot_count_B > cooltime_blue_b) {
				get_blue_B(pos_);
				shot_count_B = 0;
			}
		}

	}


	{  //X’e–‹¶¬
		shot_count_X += deltatime;
		if (all_push(XINPUT_BUTTON_X) == push) {
			if (shot_count_X > cooltime_blue_x) {
				get_blue_X(pos_);
				shot_count_X = 0;
			}
		}
	}


	{  //Y’e–‹¶¬
		shot_count_Y += deltatime;
		if (input.Buttons[XINPUT_BUTTON_Y]) {
			push_type(XINPUT_BUTTON_Y, deltatime);
			if (state == 0) {
				if (shot_count_Y > cooltime_blue_y) {
					get_blue_Y(pos_);
					shot_count_Y = 0;
				}
			}
		}
	}
}

//chara_yellow‚Ìƒ{ƒ^ƒ““ü—Í
void Player::character_yellow(float deltatime) {
	//{  //‚`ƒ{ƒ^ƒ“‚ÌŒ‚‚Âˆ—
	//	shot_count_A += deltatime;
	//	if (input.Buttons[XINPUT_BUTTON_A]) {
	//		push_type(XINPUT_BUTTON_A, deltatime);
	//		if (state == 0) {
	//			yellow_flag = true;
	//			if (shot_count_A > 0.7) {
	//				get_yellow_A(pos_);
	//				shot_count_A = 0;
	//			}
	//		}
	//	}

	//}

	{  //‚`ƒ{ƒ^ƒ“‚ÌŒ‚‚Âˆ—
		shot_count_A += deltatime;
		if (all_push(XINPUT_BUTTON_A) == push) {
			if (shot_count_A > cooltime_yellow_a) {
				get_yellow_A(pos_);
				shot_count_A = 0;
			}
		}


	}

	{  //B’e–‹¶¬
		shot_count_B += deltatime;
		if (all_push(XINPUT_BUTTON_B) == push) {
			if (shot_count_B > cooltime_yellow_b) {
				yellow_flag = true;
				get_yellow_B(pos_);
				shot_count_B = 0;
			}
		}
	}


	{ //X’e–‹¶¬
		shot_count_X += deltatime;
		if (game_manager_->is_all_bullet_erase == false) {
			if (input.Buttons[XINPUT_BUTTON_X]) {
				if (shot_count_X > cooltime_yellow_x) {
					get_yellow_X(pos_);
					shot_count_X = 0;
				}
			}
		}
	}



	{ //Y’e–‹¶¬
		shot_count_Y += deltatime;
		if (all_push(XINPUT_BUTTON_Y)==push) {
			if (shot_count_Y > cooltime_yellow_y) {
				get_yellow_Y(pos_);
				shot_count_Y = 0;
			}
		}
	}
}



//chara‚ª“G‚Ì’e–‹‚É“–‚½‚Á‚½ŽžŽ©•ª‚ª“_–Å‚·‚éŠÖ”
void Player::flashing(float deltatime) {
	if (execution_draw) {
		execution_draw = false;
	}
	else {
		execution_draw = true;
	}

}





void Player::update(float deltatime) {

	if (execution_up) {


		GetJoypadXInputState(controller_type, &input);


		{	//ƒvƒŒƒCƒ„[‚ÌˆÚ“®ˆ—

			if (input.ThumbLX > 30000) {
				pos_.x += speed_;
			}
			else if (input.ThumbLX <= 30000 && input.ThumbLX > 0) {
				pos_.x += speed_ - 4;
			}

			if (input.ThumbLX < -30000) {
				pos_.x -= speed_;
			}
			else if (input.ThumbLX >= -30000 && input.ThumbLX < 0) {
				pos_.x -= speed_ - 4;
			}

			if (input.ThumbLY < -30000) {
				pos_.y += speed_;
			}
			else if (input.ThumbLY >= -30000 && input.ThumbLY < 0) {
				pos_.y += speed_ - 4;
			}

			if (input.ThumbLY > 30000) {
				pos_.y -= speed_;
			}
			else if (input.ThumbLY <= 30000 && input.ThumbLY > 0) {
				pos_.y -= speed_ - 4;
			}


		}



		if (input.ThumbRX != 0 || input.ThumbRY != 0) {
			test.x = input.ThumbRX;
			test.y = input.ThumbRY * -1;
			test.normalize();
		}

		if (input.LeftTrigger != 0) {
			test = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(-2)));
		}
		if (input.RightTrigger != 0) {
			test = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(2)));
		}


		if (chara_type == chara_green) {
			character_green(deltatime);
		}
		else if (chara_type == chara_red) {
			character_red(deltatime);
		}
		else if (chara_type == chara_blue) {
			character_blue(deltatime);
		}
		else if (chara_type == chara_yellow) {
			character_yellow(deltatime);
		}




	}



	if (pos_.y < 0) {
		pos_.y = 0;
	}
	else if (pos_.y > 720) {
		pos_.y = 720;
	}
	else if (pos_.x < game_manager_->field_->pos_.x) {
		pos_.x = game_manager_->field_->pos_.x;
	}
	else if (pos_.x > game_manager_->field_->pos_2.x) {
		pos_.x = game_manager_->field_->pos_2.x;
	}



	if (count_flag) {
		time_count += deltatime;
		time_count2 += deltatime;
		if (time_count2 < 3) {
			DrawStringEx(pos_.x - 50, pos_.y + 50, -1, "Hit");
			if (time_count > 0.1) {
				flashing(deltatime);
				time_count = 0;
			}
		}
		else {
			time_count = 0;
			time_count2 = 0;
			count_flag = false;
			if (three_effect) {
				game_manager_->life->change_effect = true;
				three_effect = false;
			}
			else {
				game_manager_->life->text_flag = true;
			}
			execution_draw = true;
		}
	}


	if (yellow_flag) {
		yellow_count += 5;
		if (yellow_count > 200) {
			for (auto yf : yellow_a) {
				yf->change_circle = true;
				//yellow_flag = false;
				//yellow_count = 0;
			}
			yellow_flag = false;
			yellow_count = 0;
		}


	}


	//alpha = 637 - pos_.y;


}





void Player::draw(float deltatime) {
	if (execution_draw) {



		if (chara_type == chara_red) {
			if (draw_flag) {
				DrawCircle(pos_.x, pos_.y, 200, -1, range);
			}
			DrawRotaGraph(pos_.x, pos_.y, img_size, 0, chara_img_red, true);

		}
		else if (chara_type == chara_green) {
			if (draw_flag) {
				DrawCircle(pos_.x, pos_.y, 100, -1, range);
			}
			DrawRotaGraph(pos_.x, pos_.y, img_size, 0, chara_img_green, true);
		}
		else if (chara_type == chara_blue) {
			DrawRotaGraph(pos_.x, pos_.y, img_size, 0, chara_img_blue, true);
		}
		else if (chara_type == chara_yellow) {
			DrawRotaGraph(pos_.x, pos_.y, img_size, 0, chara_img_yellow, true);
		}



		DrawRotaGraph(pos_.x, pos_.y, 1, t2k::toRadian(angle), cursor, true);
		DrawCircle(pos_.x, pos_.y, radius, 0xffffff, true);
		DrawCircle(pos_.x, pos_.y, 40, 0xffffff, false);

		//DrawStringEx(100, 100, -1, "x = %f, y = %f", test.x, test.y);
		angle = std::atan2(test.x, test.y);
		angle = angle * 180 / 3.14159265358979 * -1;
		angle += 90;









		DrawLine(pos_.x, pos_.y, pos_.x + test.x * 30, pos_.y + test.y * 30, -1);

	}


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (draw_flag) {
		if (chara_type == chara_red) {
			if (controller_type == DX_INPUT_PAD1) {
				DrawRotaGraph(194, 637, 1, 0, icon_red, true);


				if (shot_count_A < cooltime_red_a) {
					DrawRotaGraph(194, 637, 1, 0, icon_red_time_img[0], true);
					red_a_count = cooltime_red_a - shot_count_A;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(40, 633, -1, "%.1f", red_a_count);
				}


				if (shot_count_B < cooltime_red_b) {
					DrawRotaGraph(194, 637, 1, 0, icon_red_time_img[1], true);
					red_b_count = cooltime_red_b - shot_count_B;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(130, 633, -1, "%.1f", red_b_count);
				}


				if (shot_count_X < cooltime_red_x) {
					DrawRotaGraph(194, 637, 1, 0, icon_red_time_img[2], true);
					red_x_count = cooltime_red_x - shot_count_X;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(220, 633, -1, "%.1f", red_x_count);
				}


				if (shot_count_Y < cooltime_red_y) {
					DrawRotaGraph(194, 637, 1, 0, icon_red_time_img[3], true);
					red_y_count = cooltime_red_y - shot_count_Y;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(310, 633, -1, "%.1f", red_y_count);
				}



			}
			else {
				DrawRotaGraph(1086, 637, 1, 0, icon_red, true);



				if (shot_count_A < cooltime_red_a) {
					DrawRotaGraph(1086, 637, 1, 0, icon_red_time_img[0], true);
					red_a_count = cooltime_red_a - shot_count_A;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(930, 633, -1, "%.1f", red_a_count);
				}


				if (shot_count_B < cooltime_red_b) {
					DrawRotaGraph(1086, 637, 1, 0, icon_red_time_img[1], true);
					red_b_count = cooltime_red_b - shot_count_B;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1020, 633, -1, "%.1f", red_b_count);
				}


				if (shot_count_X < cooltime_red_x) {
					DrawRotaGraph(1086, 637, 1, 0, icon_red_time_img[2], true);
					red_x_count = cooltime_red_x - shot_count_X;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1110, 633, -1, "%.1f", red_x_count);
				}


				if (shot_count_Y < cooltime_red_y) {
					DrawRotaGraph(1086, 637, 1, 0, icon_red_time_img[3], true);
					red_y_count = cooltime_red_y - shot_count_Y;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1200, 633, -1, "%.1f", red_y_count);
				}
			}
		}

		if (chara_type == chara_green) {
			if (controller_type == DX_INPUT_PAD1) {
				DrawRotaGraph(194, 637, 1, 0, icon_green, true);

				if (shot_count_A < cooltime_green_a) {
					DrawRotaGraph(194, 637, 1, 0, icon_green_time_img[0], true);
					green_a_count = cooltime_green_a - shot_count_A;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(40, 633, -1, "%.1f", green_a_count);
				}


				if (shot_count_B < cooltime_green_b) {
					DrawRotaGraph(194, 637, 1, 0, icon_green_time_img[1], true);
					green_b_count = cooltime_green_b - shot_count_B;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(130, 633, -1, "%.1f", green_b_count);
				}


				if (shot_count_X < cooltime_green_x) {
					DrawRotaGraph(194, 637, 1, 0, icon_green_time_img[2], true);
					green_x_count = cooltime_green_x - shot_count_X;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(220, 633, -1, "%.1f", green_x_count);
				}


				if (shot_count_Y < cooltime_green_y) {
					DrawRotaGraph(194, 637, 1, 0, icon_green_time_img[3], true);
					green_y_count = cooltime_green_y - shot_count_Y;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(310, 633, -1, "%.1f", green_y_count);
				}



			}
			else {
				DrawRotaGraph(1086, 637, 1, 0, icon_green, true);

				if (shot_count_A < cooltime_green_a) {
					DrawRotaGraph(1086, 637, 1, 0, icon_green_time_img[0], true);
					green_a_count = cooltime_green_a - shot_count_A;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(930, 633, -1, "%.1f", green_a_count);
				}


				if (shot_count_B < cooltime_green_b) {
					DrawRotaGraph(1086, 637, 1, 0, icon_green_time_img[1], true);
					green_b_count = cooltime_green_b - shot_count_B;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1020, 633, -1, "%.1f", green_b_count);
				}


				if (shot_count_X < cooltime_green_x) {
					DrawRotaGraph(1086, 637, 1, 0, icon_green_time_img[2], true);
					green_x_count = cooltime_green_x - shot_count_X;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1110, 633, -1, "%.1f", green_x_count);
				}


				if (shot_count_Y < cooltime_green_y) {
					DrawRotaGraph(1086, 637, 1, 0, icon_green_time_img[3], true);
					green_y_count = cooltime_green_y - shot_count_Y;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1200, 633, -1, "%.1f", green_y_count);
				}
			}
		}

		if (chara_type == chara_blue) {
			if (controller_type == DX_INPUT_PAD1) {
				DrawRotaGraph(194, 637, 1, 0, icon_blue, true);

				if (shot_count_A < cooltime_blue_a) {
					DrawRotaGraph(194, 637, 1, 0, icon_blue_time_img[0], true);
					blue_a_count = cooltime_blue_a - shot_count_A;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(40, 633, -1, "%.1f", blue_a_count);
				}


				if (shot_count_B < cooltime_blue_b) {
					DrawRotaGraph(194, 637, 1, 0, icon_blue_time_img[1], true);
					blue_b_count = cooltime_blue_b - shot_count_B;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(130, 633, -1, "%.1f", blue_b_count);
				}


				if (shot_count_X < cooltime_blue_x) {
					DrawRotaGraph(194, 637, 1, 0, icon_blue_time_img[2], true);
					blue_x_count = cooltime_blue_x - shot_count_X;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(220, 633, -1, "%.1f", blue_x_count);
				}


				if (shot_count_Y < cooltime_blue_y) {
					DrawRotaGraph(194, 637, 1, 0, icon_blue_time_img[3], true);
					blue_y_count = cooltime_blue_y - shot_count_Y;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(310, 633, -1, "%.1f", blue_y_count);
				}



			}
			else {
				DrawRotaGraph(1086, 637, 1, 0, icon_blue, true);

				if (shot_count_A < cooltime_blue_a) {
					DrawRotaGraph(1086, 637, 1, 0, icon_blue_time_img[0], true);
					blue_a_count = cooltime_blue_a - shot_count_A;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(930, 633, -1, "%.1f", blue_a_count);
				}


				if (shot_count_B < cooltime_blue_b) {
					DrawRotaGraph(1086, 637, 1, 0, icon_blue_time_img[1], true);
					blue_b_count = cooltime_blue_b - shot_count_B;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1020, 633, -1, "%.1f", blue_b_count);
				}


				if (shot_count_X < cooltime_blue_x) {
					DrawRotaGraph(1086, 637, 1, 0, icon_blue_time_img[2], true);
					blue_x_count = cooltime_blue_x - shot_count_X;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1110, 633, -1, "%.1f", blue_x_count);
				}


				if (shot_count_Y < cooltime_blue_y) {
					DrawRotaGraph(1086, 637, 1, 0, icon_blue_time_img[3], true);
					blue_y_count = cooltime_blue_y - shot_count_Y;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1200, 633, -1, "%.1f", blue_y_count);
				}
			}
		}






		if (chara_type == chara_yellow) {
			if (controller_type == DX_INPUT_PAD1) {
				DrawRotaGraph(194, 637, 1, 0, icon_yellow, true);

				if (shot_count_A < cooltime_yellow_a) {
					DrawRotaGraph(194, 637, 1, 0, icon_yellow_time_img[0], true);
					yellow_a_count = cooltime_yellow_a - shot_count_A;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(40, 633, -1, "%.1f", yellow_a_count);
				}


				if (shot_count_B < cooltime_yellow_b) {
					DrawRotaGraph(194, 637, 1, 0, icon_yellow_time_img[1], true);
					yellow_b_count = cooltime_yellow_b - shot_count_B;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(130, 633, -1, "%.1f", yellow_b_count);
				}


				if (shot_count_X < cooltime_yellow_x) {
					DrawRotaGraph(194, 637, 1, 0, icon_yellow_time_img[2], true);
					yellow_x_count = cooltime_yellow_x - shot_count_X;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(220, 633, -1, "%.1f", yellow_x_count);
				}


				if (shot_count_Y < cooltime_yellow_y) {
					DrawRotaGraph(194, 637, 1, 0, icon_yellow_time_img[3], true);
					yellow_y_count = cooltime_yellow_y - shot_count_Y;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(310, 633, -1, "%.1f", yellow_y_count);
				}



			}
			else {
				DrawRotaGraph(1086, 637, 1, 0, icon_yellow, true);

				if (shot_count_A < cooltime_yellow_a) {
					DrawRotaGraph(1086, 637, 1, 0, icon_yellow_time_img[0], true);
					yellow_a_count = cooltime_yellow_a - shot_count_A;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(930, 633, -1, "%.1f", yellow_a_count);
				}


				if (shot_count_B < cooltime_yellow_b) {
					DrawRotaGraph(1086, 637, 1, 0, icon_yellow_time_img[1], true);
					yellow_b_count = cooltime_yellow_b - shot_count_B;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1020, 633, -1, "%.1f", yellow_b_count);
				}


				if (shot_count_X < cooltime_yellow_x) {
					DrawRotaGraph(1086, 637, 1, 0, icon_yellow_time_img[2], true);
					yellow_x_count = cooltime_yellow_x - shot_count_X;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1110, 633, -1, "%.1f", yellow_x_count);
				}


				if (shot_count_Y < cooltime_yellow_y) {
					DrawRotaGraph(1086, 637, 1, 0, icon_yellow_time_img[3], true);
					yellow_y_count = cooltime_yellow_y - shot_count_Y;
					ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
					SetFontSize(40);
					DrawStringEx(1200, 633, -1, "%.1f", yellow_y_count);
				}
			}
		}

	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);




	if (state == 0) {
		//	DrawStringEx(100, 200, -1, "0");
	}
	else if (state == 1) {
		//	DrawStringEx(100, 300, -1, "1");
	}
	else {
		//DrawStringEx(100, 400, -1, "2");
		push_count = 0;
	}


}





void Player::get_player_A(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 25;
	desc.img_size = 0.5;
	desc.speed_ = 3;
	desc.start_pos_ = get_pos;
	desc.bullet_pas = bullet_img_a;
	desc.collar = get_collar;
	desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(30)));
	bullet_.emplace_back(new Bullet(desc));
	desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(-30)));
	bullet_.emplace_back(new Bullet(desc));
	desc.move_dir_ = t2k::Vector3(test.x, test.y, 0);
	bullet_.emplace_back(new Bullet(desc));
	for (auto n : bullet_) {
		n->judge = true;
	}
}

void Player::get_player_B(t2k::Vector3 get_pos) {

	bullet_status desc;
	desc.radius = 20;
	desc.speed_ = 5;
	desc.start_pos_ = get_pos;
	desc.img_size = 0.2;
	desc.bullet_pas = bullet_img_b;
	desc.collar = get_collar;
	for (int i = 0; i < 360; i += 18) {
		desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(i)));
		Bullet* p = new Bullet(desc);
		bullet_b.emplace_back(p);
		bullet_.emplace_back(p);
	}


}


void Player::get_player_X(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 200;
	desc.speed_ = 10;
	desc.start_pos_ = get_pos;
	desc.img_size = 2;
	desc.bullet_pas = bullet_img_x;
	desc.collar = get_collar;

	Bullet* px = new Bullet(desc);
	bullet_x.emplace_back(px);
	bullet_.emplace_back(px);
}


void Player::get_red_A(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 5;
	desc.speed_ = 5;
	desc.start_pos_ = get_pos;
	desc.collar = get_collar;
	desc.img_size = 0.1;
	desc.bullet_pas = bullet_red_a;
	for (int i = 0; i < 360; i += 90) {
		desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(i)));
		SpiralBullet* r = new SpiralBullet(desc, 80);
		bullet_.emplace_back(r);
	}

	for (int i = 0; i < 360; i += 90) {
		desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(i)));
		SpiralBullet* s = new SpiralBullet(desc, -80);
		red_a_2.emplace_back(s);
		bullet_.emplace_back(s);
	}

	for (auto n : bullet_) {
		n->judge = true;
	}
	for (auto n : red_a_2) {
		n->judge = true;
	}
}


void Player::get_red_B(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 100;
	desc.speed_ = 10;
	desc.start_pos_ = get_pos;
	desc.collar = get_collar;
	desc.img_size = 1;
	desc.bullet_pas = bullet_red_shield;
	Bullet* pb = new Bullet(desc);
	red_b.emplace_back(pb);
	bullet_red.emplace_back(pb);

	for (auto r_b : red_b) {
		r_b->judge = true;
	}
}


void Player::get_red_X(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 20;
	desc.speed_ = 30;
	desc.start_pos_ = get_pos;
	desc.collar == get_collar;
	desc.img_size = 0.2;
	desc.bullet_pas = bullet_red_shield;
	for (int i = 0; i < 360; i += 90) {
		desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(i)));
		SpiralBullet* r_x = new SpiralBullet(desc, 80);
		//red_x.emplace_back(r_x);
		bullet_red.emplace_back(r_x);


	}

	for (auto x : bullet_red) {
		x->judge = true;
	}
}


void Player::get_blue_A(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 25;
	desc.speed_ = 5;
	desc.start_pos_ = get_pos;
	desc.collar == get_collar;
	desc.move_dir_ = t2k::Vector3(test.x, test.y, 0);
	desc.img_size = 0.05;
	desc.bullet_pas = bullet_blue_a;
	Bullet* bullet_blue = new Bullet(desc);
	bullet_.emplace_back(bullet_blue);
	blue_a.emplace_back(bullet_blue);
	for (auto n : bullet_) {
		n->judge = true;
	}
}


void Player::get_blue_B(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 10;
	desc.speed_ = 5;
	desc.start_pos_ = get_pos;
	desc.collar == get_collar;
	desc.img_size = 0.1;
	desc.bullet_pas = bullet_blue_b;

	for (int i = 0; i < 360; i += 120) {
		desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(i + 30)));
		desc.angle = t2k::toRadian(angle + i - 240);
		Bullet* b_p = new Bullet(desc);
		b_p->get_pos_ = pos_;
		blue_b.emplace_back(b_p);
		bullet_.emplace_back(b_p);
	}

	for (auto n : bullet_) {
		n->judge = true;
	}
}


void Player::get_blue_X(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 100;
	desc.speed_ = 10;
	desc.start_pos_ = get_pos;
	desc.collar = get_collar;
	desc.img_size = 0.1;
	desc.bullet_pas = bullet_blue_x;
	desc.angle_sum = 0.1;
	desc.change_angle = true;
	desc.move_dir_ = t2k::Vector3(test.x, test.y, 0);
	Bullet* pb = new Bullet(desc);
	blue_x.emplace_back(pb);
	desc.angle_sum = -0.1;
	desc.change_angle = true;
	pb = new Bullet(desc);
	blue_x.emplace_back(pb);

	for (auto r_b : blue_x) {
		r_b->judge = true;
	}
}




void Player::get_blue_Y(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 100;
	desc.speed_ = 25;
	desc.start_pos_ = get_pos;
	desc.start_pos_.y = -500;
	desc.img_size = 0.2;
	desc.bullet_pas = bullet_blue_y;
	desc.collar = get_collar;
	desc.change_hit = false;



	Bullet* px = new Bullet(desc);
	blue_y.emplace_back(px);
	bullet_.emplace_back(px);
	for (auto r_y : blue_y) {
		r_y->judge = true;
	}
}




void Player::get_yellow_A(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 25;
	desc.img_size = 0.05;
	desc.speed_ = 2.7;
	desc.start_pos_ = get_pos;
	desc.bullet_pas = bullet_yellow_a;
	desc.collar = get_collar;

	desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(8.7)));
	bullet_.emplace_back(new Bullet(desc));
	desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(10)));
	desc.speed_ = 2.3;
	bullet_.emplace_back(new Bullet(desc));

	desc.speed_ = 2.7;
	desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(-8.7)));
	bullet_.emplace_back(new Bullet(desc));
	desc.move_dir_ = t2k::Vector3::transformCoord(test, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(-10)));
	desc.speed_ = 2.3;
	bullet_.emplace_back(new Bullet(desc));

	desc.speed_ = 3;
	desc.move_dir_ = t2k::Vector3(test.x, test.y, 0);
	bullet_.emplace_back(new Bullet(desc));
	desc.speed_ = 2.5;
	bullet_.emplace_back(new Bullet(desc));
	desc.speed_ = 2;
	bullet_.emplace_back(new Bullet(desc));

	for (auto b : bullet_) {
		b->judge = true;
	}
}





void Player::get_yellow_B(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 50;
	desc.img_size = 0.1;
	desc.speed_ = 5;
	desc.start_pos_ = get_pos;
	desc.bullet_pas = bullet_yellow_b;
	desc.collar = get_collar;
	desc.move_dir_ = t2k::Vector3(test.x, test.y, 0);
	Bullet* yp = new Bullet(desc);
	bullet_.emplace_back(yp);
	yellow_a.emplace_back(yp);

	for (auto n : bullet_) {
		n->judge = true;
	}

}



void Player::get_yellow_X(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 50;
	desc.img_size = 0.1;
	desc.speed_ = 5;
	desc.start_pos_ = get_pos;
	desc.bullet_pas = bullet_yellow_x;
	desc.collar = get_collar;
	desc.move_dir_ = t2k::Vector3(test.x, test.y, 0);
	desc.line_pos_ = test;
	desc.angle = angle;
	Reiza* reiza = new Reiza(desc);
	yellow_b.emplace_back(reiza);
}






void Player::get_yellow_Y(t2k::Vector3 get_pos) {
	bullet_status desc;
	desc.radius = 0.5;
	desc.img_size = 0.001;
	desc.speed_ = 2.7;
	desc.start_pos_ = { 200,200,0 };
	desc.bullet_pas = bullet_yellow_y;
	desc.collar = get_collar;
	desc.circle_move_change = true;
	desc.change_angle = true;
	desc.angle_sum = t2k::toRadian(1);
	
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 200,520,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 400,360,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 600,130,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 600,660,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 800,250,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 800,580,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 700,400,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 1000,120,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 1000,680,0 };
	yellow.emplace_back(new Bullet(desc));
	desc.start_pos_ = { 1150,360,0 };
	yellow.emplace_back(new Bullet(desc));



	for (auto b : yellow) {
		b->judge = true;
	}
}
