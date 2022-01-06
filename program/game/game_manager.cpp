#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "player.h"
#include "bullet.h"
#include "life.h"
#include "haike.h"
#include"chara_select.h"
#include "select_cursor.h"
#include "explanation.h"
#include "hint.h"
#include "title.h"
#include <time.h>
#include<list>
#include<math.h>



Game_manager::Game_manager() {

}

void Game_manager::initialize() {
	SetMainWindowText("SuperiorBullet");
	sen = imgLoadGraph("graphics/text.png");
	label = imgLoadGraph("graphics/label_efect.png");
	win_img = imgLoadGraph("graphics/you_win.png");
	chara_img[0] = imgLoadGraph("graphics/character_red.png");
	chara_img[1] = imgLoadGraph("graphics/character_blre.png");
	chara_img[2] = imgLoadGraph("graphics/character_green.png");
	chara_img[4] = imgLoadGraph("graphics/character_yellow.png");
	chara_img[5] = imgLoadGraph("graphics/character_blak.png");
	box_img = imgLoadGraph("graphics/white_box.png");
	title_sound = LoadSoundMem("sound/title.mp3");
	SetWindowIconID(chara_img[0]);
}





int Game_manager::imgLoadGraph(std::string img_pas) {
	int hoz_img;
	//delete_img = img_pas;
	auto it = img.find(img_pas);
	if (it == img.end()) {
		hoz_img = LoadGraph(img_pas.c_str());
		img.insert(std::make_pair(img_pas, hoz_img));
	}
	else {
		hoz_img = it->second;
	}

	return hoz_img;
}






void Game_manager::life_calculation(float deltatime, Player* get_hit_player, Player* get_hit_bullet) {
	get_hit_player->hp -= 1;
	is_all_bullet_erase = true;
	StartJoypadVibration(get_hit_player->controller_type, 1000, 500, -1);
	if (get_hit_player->hp > 0 && get_hit_player->life > 0) {
		get_hit_player->count_flag = true;

	}
	if (get_hit_player->hp <= 0 && get_hit_player->life > 0) {
		life->hit_player_get(get_hit_player);
		get_hit_player->count_flag = true;
		get_hit_player->three_effect = true;
		get_hit_player->life--;
		get_hit_player->hp = 4;
	}
	if (get_hit_player->life == 0) {
		non_batlle = true;
		get_hit_player->hp = 0;
		win_player = get_hit_bullet;
		get_hit_bullet->execution_up = false;
		chara_hoz = get_hit_bullet->chara_type;
		move_dir = standby_pos_ - win_player->pos_;
		move_dir.normalize();


		/*	bullet_status desc;
			desc.radius = 20;
			desc.speed_ = 5;
			desc.collar = -1;
			desc.start_pos_ = get_hit_player->pos_;
			t2k::Vector3 aaa = { 1,0,0 };

			for (int i = 0; i < 360; i += 18) {
				desc.move_dir_ = t2k::Vector3::transformCoord(aaa, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(i)));
				Bullet* p = new Bullet(desc);
			}*/
		get_hit_player->a = false;
	}
}



void Game_manager::hit_judge(float deltatime, Player* hit_bullet, Player* hit_player) {
	if (hit_player->count_flag == false) {
		for (auto b : hit_bullet->bullet_) {
			if (b->judge == false) continue;
			if (t2k::isIntersectSphere(b->pos_, b->radius,
				hit_player->pos_, hit_player->radius)) {
				b->is_alive_ = false;
				PlaySoundMem(hit_sound, DX_PLAYTYPE_BACK);
				life_calculation(deltatime, hit_player, hit_bullet);
				//is_all_bullet_erase = true;
				for (auto yf : hit_bullet->yellow_a) {
					yf->change_circle = false;

				}



			}
			for (auto b2 : hit_player->bullet_red) {
				if (t2k::isIntersectSphere(b->pos_, b->radius,
					b2->pos_, b2->radius)) {
					b->is_alive_ = false;
				}
			}

			if (hit_player->chara_type == chara_red) {
				if (hit_player->range == false) continue;
				if (t2k::isIntersectSphere(b->pos_, b->judge,
					hit_player->pos_, 200)) {
					b->is_alive_ = false;
				}
			}



		}


		for (auto yl : hit_bullet->yellow) {
			if (yl->judge == false) continue;
			if (t2k::isIntersectSphere(yl->pos_, yl->radius,
				hit_player->pos_, hit_player->radius)) {
				yl->is_alive_ = false;
				PlaySoundMem(hit_sound, DX_PLAYTYPE_BACK);
				life_calculation(deltatime, hit_player, hit_bullet);
				//is_all_bullet_erase = true;
				for (auto yf : hit_bullet->yellow_a) {
					yf->change_circle = false;

				}



			}
		}



		if (hit_bullet->chara_type == chara_green) {
			if (hit_bullet->range == false) return;
			if (t2k::isIntersectSphere(hit_bullet->pos_, 100,
				hit_player->pos_, hit_player->radius)) {
				PlaySoundMem(hit_sound, DX_PLAYTYPE_BACK);
				life_calculation(deltatime, hit_player, hit_bullet);

			}
		}
	}

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		hit_bullet->a = true;
		for (auto b : hit_player->bullet_) {
			b->is_alive_ = false;
		}
		hit_player->a = true;
		for (auto b : hit_bullet->bullet_) {
			b->is_alive_ = false;
		}

	}


	for (auto b_yb : hit_bullet->yellow_b) {
		// 下側の線に直行するベクトルと敵座標で内積
		b_yb->dot = t2k::Vector3::dot(b_yb->bottom_cross, hit_player->pos_ - b_yb->bottom_l_pos);
		b_yb->dot2 = t2k::Vector3::dot(b_yb->bottom_cross2, hit_player->pos_ - b_yb->bottom_l_pos2);
		b_yb->dot3 = t2k::Vector3::dot(b_yb->line_pos_, hit_player->pos_ - hit_bullet->pos_);
		GetJoypadXInputState(DX_INPUT_PAD1, &input);
		if (b_yb->dot > 0 && b_yb->dot2 > 0 && b_yb->dot3 > 0) {
			DrawStringEx(600, 500, -1, "hit");
			if (b_yb->reiza_hit_falsg) {
				PlaySoundMem(hit_sound, DX_PLAYTYPE_BACK);
				life_calculation(deltatime, hit_player, hit_bullet);
				b_yb->reiza_hit_falsg = false;
			}
		}
	}


}




void Game_manager::bullet_judge(Player* main_player, Player* sub_player, float deltatime) {
	if (main_player->state == 0) {
		main_player->pos = main_player->pos_;
		if (main_player->change == true) {
			main_player->range = true;
			main_player->change = false;
		}
		sub_player->get_pos_ = sub_player->pos_ - main_player->pos_;  //相手のポジションのベクトルを出している
		sub_player->v1 = sub_player->pos_;
		sub_player->v1.y = 0;
		sub_player->v1 = sub_player->v1 - main_player->pos_;
		sub_player->v1.normalize();
		sub_player->get_pos_.normalize();
		//v1.y = -1;
		for (auto b : main_player->bullet_b) {
			b->judge = false;
		}
		for (auto x : main_player->bullet_x) {
			x->judge = false;
		}
		for (auto by : main_player->blue_y) {

			by->move_dir = sub_player->pos_ - by->pos_;
			by->move_dir.normalize();
		}


	}

	if (main_player->state == 1) {
		main_player->range = false;
		for (auto b : main_player->bullet_b) {
			b->move_dir = t2k::Vector3::transformCoord(b->pos_ - main_player->pos, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(30))).normalize();
			b->judge = false;
		}
		for (auto x : main_player->bullet_x) {
			x->move_dir = sub_player->v1;
			x->judge = false;
		}

		for (auto r_b : main_player->red_b) {
			r_b->move_dir = sub_player->get_pos_;
		}

		for (auto a : main_player->red_a_2) {
			//t2k::Vector3 v1 = main_player->pos_;
			t2k::Vector3 v2 = a->pos_;
			a->move_dir = t2k::Vector3::transformCoord(v2 - main_player->pos, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(80))).normalize();
		}




	}



	if (main_player->state == 2) {
		main_player->range = false;

		for (auto b : main_player->bullet_b) {
			b->speed_ = 1;
			b->judge = true;
		}

		for (auto x : main_player->bullet_x) {
			x->move_dir = { 0,1,0 };
			x->speed_ = 5;
			x->judge = true;
		}


		//red弾幕Ｂボタンを話したときの処理
		for (auto r_b : main_player->red_b) {
			r_b->is_alive_ = false;
		}


		for (auto b_x : main_player->blue_x) {
			t2k::Vector3 teleport_pos = b_x->pos_;
			main_player->pos_ = teleport_pos;
			b_x->is_alive_ = false;

		}

		main_player->bullet_b.clear();
		main_player->bullet_x.clear();
		main_player->red_a_2.clear();
		main_player->red_b.clear();
		main_player->blue_x.clear();
		main_player->blue_y.clear();


	}


	{//blueの弾Aの処理

		int start_size = main_player->blue_a.size();
		std::list<Bullet*>::iterator it = main_player->blue_a.begin();
		while (it != main_player->blue_a.end()) {

			(*it)->distance += 0.5f;
			if ((*it)->distance < 50.0f) {
				it++;
				continue;
			}

			get_b_pos = (*it)->pos_;
			bullet_status desc;
			desc.radius = 25;
			desc.speed_ = 3;
			desc.start_pos_ = get_b_pos;
			desc.img_size = 0.05;
			desc.bullet_pas = main_player->bullet_blue_a;
			desc.move_dir_ = t2k::Vector3::transformCoord((*it)->move_dir, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(30)));
			Bullet* bullet_blue = new Bullet(desc);
			main_player->bullet_.emplace_back(bullet_blue);
			main_player->blue_a.emplace_back(bullet_blue);
			bullet_blue->judge = true;
			desc.move_dir_ = t2k::Vector3::transformCoord((*it)->move_dir, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(-30)));
			bullet_blue = new Bullet(desc);
			main_player->bullet_.emplace_back(bullet_blue);
			main_player->blue_a.emplace_back(bullet_blue);
			bullet_blue->judge = true;

			it = main_player->blue_a.erase(it);
		}

	}



	std::list<Bullet*>::iterator it = main_player->blue_b.begin();
	while (it != main_player->blue_b.end()) {

		(*it)->time_count += deltatime;
		if ((*it)->time_count < 0.5) {
			it++;
			continue;
		}
		(*it)->speed_ = 0;

		if ((*it)->angle_count < 360) {
			(*it)->pos_ = (*it)->get_pos_ + t2k::Vector3::transformCoord((*it)->pos_ - (*it)->get_pos_, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(5)));
			(*it)->angle_count += 5;
			(*it)->angle += t2k::toRadian(5);
			it++;
		}
		else {
			(*it)->angle_count = 0;
			(*it)->time_count = 0;
			(*it)->is_alive_ = false;
			it = main_player->blue_b.erase(it);
		}

	}
}


bool Game_manager::title_play(float deltatime) {
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	if (change_scene.isStart()) {
		title_ = new Title;

	}
	mae = ima;
	ima = input.Buttons[XINPUT_BUTTON_A];

	if (title_sound_flag) {
		if (title_sound != 0 && !CheckSoundMem(title_sound)) {
			PlaySoundMem(title_sound, DX_PLAYTYPE_LOOP);
			ChangeVolumeSoundMem(100, title_sound);
		}
		title_sound_flag = false;
		psyu_feid_flag = true;


	}

	if (ima && !mae) {
		change_scene.change(&Game_manager::menyu_play);
		title_->is_alive_ = false;
		title_sound_flag = false;
		psyu_feid_flag = false;
		title_ = nullptr;
	}

	return true;
}



bool Game_manager::menyu_play(float deltatime) {
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	if (change_scene.isStart()) {
		menyu_ = new Menyu;
	}
	mae = ima;
	ima = input.Buttons[XINPUT_BUTTON_A];

	if (ima && !mae) {
		if (menyu_->right_number == 0) {
			change_scene.change(&Game_manager::select_scene);
			menyu_->is_alive_ = false;
			StopSoundMem(title_sound);
		}

		if (menyu_->right_number == 1) {
			change_scene.change(&Game_manager::option_play);
			menyu_->is_alive_ = false;

		}
	}

	return true;
}


bool Game_manager::option_play(float deltatime) {
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	if (change_scene.isStart()) {
		option_ = new Option;
	}

	if (input.Buttons[XINPUT_BUTTON_B]) {
		change_scene.change(&Game_manager::menyu_play);
		option_->is_alive_ = false;
	}
	return true;

}



bool Game_manager::select_scene(float deltatime) {

	if (change_scene.isStart()) {
		chara_select_ = new Chara_select;
		cusor1_ = new  Select_cusor(DX_INPUT_PAD1);
		cusor2_ = new  Select_cusor(DX_INPUT_PAD2);
		explanation_1_ = new Explanation(DX_INPUT_PAD1);
		explanation_2_ = new Explanation(DX_INPUT_PAD2);
		select_sound = LoadSoundMem("sound/chara_select.mp3");
		PlaySoundMem(select_sound, DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(100, select_sound);
	}



	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	if (cusor1_->standby && cusor2_->standby) {
		non_select_flag = true;
		if (input.Buttons[XINPUT_BUTTON_X]) {
			change_scene.change(&Game_manager::battle_scene);
			StopSoundMem(select_sound);
			DeleteSoundMem(select_sound);
			chara_select_->is_alive_ = false;
			cusor1_->is_alive_ = false;
			cusor2_->is_alive_ = false;
			explanation_1_->is_alive_ = false;
			explanation_2_->is_alive_ = false;
			cusor1_ = nullptr;
			cusor2_ = nullptr;
			chara_select_ = nullptr;
			explanation_1_ = nullptr;
			explanation_2_ = nullptr;
		}
	}
	else {
		non_select_flag = false;
	}

	return true;
}



bool Game_manager::battle_scene(float deltatime) {
	if (change_scene.isStart()) {
		background_ = new BackGround;
		life = new Life;
		field_ = new Field;
		player_1 = new Player({ 100, 384, 0 }, DX_INPUT_PAD1, chara_type1);
		player_2 = new Player({ 1000, 384, 0 }, DX_INPUT_PAD2, chara_type2);
		battle_sound = LoadSoundMem("sound/bgm44.mp3");
		hit_sound = LoadSoundMem("sound/damage.wav");
		PlaySoundMem(battle_sound, DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(80, battle_sound);
	}

	line_time_count += deltatime;
	if (line_time_count > 0.5) {
		line_time_count = 0;
		line_ = new Line;
	}



	hit_judge(deltatime, player_1, player_2);
	hit_judge(deltatime, player_2, player_1);


	// alpha値いじってるところ
	// 横幅 = 1280
	// 縦幅 = 720



	float icon1_hypotenuse = ((player_1->pos_.x - 194) * (player_1->pos_.x - 194) + (player_1->pos_.y - 637) * (player_1->pos_.y - 637));
	float alpha_hoz1 = sqrt(icon1_hypotenuse);
	float icon2_hypotenuse = ((player_1->pos_.x - 1086) * (player_1->pos_.x - 1086) + (player_1->pos_.y - 637) * (player_1->pos_.y - 637));
	float alpha_hoz2 = sqrt(icon2_hypotenuse);
	float icon3_hypotenuse = ((player_2->pos_.x - 194) * (player_2->pos_.x - 194) + (player_2->pos_.y - 637) * (player_2->pos_.y - 637));
	float alpha_hoz3 = sqrt(icon3_hypotenuse);
	float icon4_hypotenuse = ((player_2->pos_.x - 1086) * (player_2->pos_.x - 1086) + (player_2->pos_.y - 637) * (player_2->pos_.y - 637));
	float alpha_hoz4 = sqrt(icon4_hypotenuse);
	if (alpha_hoz1 < alpha_hoz3) {
		player_1->alpha = alpha_hoz1;
	}
	if (alpha_hoz2 < alpha_hoz4) {
		player_2->alpha = alpha_hoz2;
	}
	if (alpha_hoz3 < alpha_hoz1) {
		player_1->alpha = alpha_hoz3;
	}
	if (alpha_hoz4 < alpha_hoz2) {
		player_2->alpha = alpha_hoz4;
	}




	bullet_judge(player_1, player_2, deltatime);
	bullet_judge(player_2, player_1, deltatime);

	player_1->erase_has_players_bullet();
	player_2->erase_has_players_bullet();
	return true;
}


bool Game_manager::eye_catch(float deltatime) {
	if (change_scene.isStart()) {
		hint_ = new Hint;
	}

	if (hint_->feid_numeric_value <= 0 && hint_->feid_flag && hint_->lag_count > 4) {
		change_scene.change(&Game_manager::select_scene);
		hint_->is_alive_ = false;
	}

	return true;
}



void Game_manager::update(float deltatime) {

	change_scene.update(deltatime);


	if (CheckSoundMem(hit_sound)) {
		int a = 0;
		++a;
	}






	{
		std::list<Object*>::iterator it = object_.begin();
		while (it != object_.end()) {
			if (!(*it)->a) {
				it++;
				continue;
			}
			(*it)->update(deltatime);
			if (!(*it)->is_alive_) {
				delete (*it);
				it = object_.erase(it);
				continue;
			}
			it++;
		}
	}






}

void Game_manager::draw(float deltatime) {

	for (auto obj : object_) {
		if (!obj->a) continue;
		obj->draw(deltatime);
	}

	if (non_batlle) {
		time_count += deltatime;
		if (time_count < 3) {
			//ChangeFont("ＭＳ 明朝", DX_CHARSET_DEFAULT);
			//SetFontSize(300);
			//DrawStringEx(0, 50, -1, "戦闘不能");
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, sen, true);
			SetFontSize(700);
			SetFontSize(15);
		}
		else if (time_count > 3) {
			menyu_flag = true;
			menyu_move_flag = true;
			non_batlle = false;
			win_player->draw_flag = false;
			background_->haike_draw_flag = false;
			life->life_draw_flag = false;
			time_count = 0;
		}

	}

	if (menyu_flag) {
		menyu_update(deltatime);
		menyu_draw(deltatime);
	}







}



void Game_manager::menyu_update(float deltatime) {
	{

		if (menyu_move_flag) {
			if (label_size.x < 1) {
				label_size.x += 0.1;
				label_size.y -= 0.1;
			}

			if (label_size.y < 1) {
				label_size.y += 0.05;
			}
			else {
				win_flag = true;
			}

			text_move += 2;
			text_move2 -= 2;

			if (text_move > 300) {
				win_flag = false;
				menyu_move_flag = false;
				label_size.y = 0;
			}
		}
		else if (menyu_move_flag == false) {
			if (label_size.x > 0) {
				label_size.x -= 0.1;
				label_size.y += 0.1;
			}

			if (label_size.y > 0) {
				label_size.y -= 0.05;
			}
			else {
				result_flag = true;
			}
		}

	}


	if (result_flag) {
		GetJoypadXInputState(DX_INPUT_PAD1, &input);
		if (label_pos_.x < -200) {
			label_pos_ += text_move_dir_ * 10;
			label_pos_2 += text_move_dir_ * 10;
		}
		else {
			win_player->execution_draw = false;
			text_pos_1 += text_move_dir_ * 3;
			text_pos_2 += text_move_dir_ * 3;
			text_pos_3 += text_move_dir_ * 3;
			text_pos_4 += text_move_dir_ * 3;
		}


		if (text_pos_1.x > 400) {
			text_pos_1 = { -100,300,0 };
		}
		if (text_pos_2.x > 400) {
			text_pos_2 = { -100,300,0 };
		}

		if (text_pos_3.x > 1480) {
			text_pos_3 = { 980,820,0 };
		}
		if (text_pos_4.x > 1480) {
			text_pos_4 = { 980,820,0 };
		}



		if (input.ThumbLY < 0) {
			box_count = 1;
		}

		if (input.ThumbLY > 0) {
			box_count = 0;
		}



		if (box_count == 0) {
			if (input.Buttons[XINPUT_BUTTON_A]) {
				change_effect_flag = true;

			}

			if (change_effect_flag) {
				if (box_size.x < 6) {
					box_size.x += 0.8;
				}
				if (box_size.y > 0) {
					box_size.y -= 0.1;
				}
				else {
					change_effect_flag = false;
					change_scene.change(&Game_manager::eye_catch);
					background_->is_alive_ = false;
					life->is_alive_ = false;
					field_->is_alive_ = false;
					player_1->is_alive_ = false;
					player_2->is_alive_ = false;
					result_flag = false;
					menyu_flag = false;
					StopSoundMem(battle_sound);
					DeleteSoundMem(battle_sound);
					battle_sound = 0;
					label_size = { 0,1,0 };
					label_pos_ = { -600,800,0 };
					label_pos_2 = { 480,1320,0 };
					text_move_dir_ = { 1,-1,0 };
					text_pos_1 = { -100,300,0 };
					text_pos_2 = { -350,550,0 };
					text_pos_3 = { 980,820,0 };
					text_pos_4 = { 730,1070,0 };
					chara_pos_ = { 900,360,0 };
					box_count = 0;
					text_move = 0;
					text_move2 = 300;
					box_size = { 1,1,0 };
				}
			}
		}

		if (box_count == 1) {
			if (input.Buttons[XINPUT_BUTTON_A]) {
				change_effect_flag = true;

			}

			if (change_effect_flag) {
				if (box_size.x < 6) {
					box_size.x += 0.8;
				}
				if (box_size.y > 0) {
					box_size.y -= 0.1;
				}
				else {
					change_effect_flag = false;
					change_scene.change(&Game_manager::menyu_play);
					PlaySoundMem(title_sound, DX_PLAYTYPE_LOOP);
					background_->is_alive_ = false;
					life->is_alive_ = false;
					field_->is_alive_ = false;
					player_1->is_alive_ = false;
					player_2->is_alive_ = false;
					result_flag = false;
					menyu_flag = false;
					StopSoundMem(battle_sound);
					DeleteSoundMem(battle_sound);
					battle_sound = 0;
					label_size = { 0,1,0 };
					label_pos_ = { -600,800,0 };
					label_pos_2 = { 480,1320,0 };
					text_move_dir_ = { 1,-1,0 };
					text_pos_1 = { -100,300,0 };
					text_pos_2 = { -350,550,0 };
					text_pos_3 = { 980,820,0 };
					text_pos_4 = { 730,1070,0 };
					chara_pos_ = { 900,360,0 };
					box_count = 0;
					text_move = 0;
					text_move2 = 300;
					box_size = { 1,1,0 };
				}
			}
		}



	}






}


void Game_manager::menyu_draw(float deltatime) {
	int w, h;
	int bw, bh;
	GetGraphSize(label, &w, &h);
	GetGraphSize(box_img, &bw, &bh);



	DrawRotaGraph3F(1280 / 2, 600, w / 2, h / 2, label_size.x, label_size.y, 0, label, true);
	DrawRotaGraph3F(1280 / 2, 120, w / 2, h / 2, label_size.x, label_size.y, 0, label, true);


	if (win_flag) {
		if (win_player == player_1) {
			ChangeFont("Enchants", DX_CHARSET_DEFAULT);
			SetFontSize(200);
			DrawStringEx(text_move, 530, 0, "player one win");
			DrawStringEx(text_move2, 50, 0, "player one win");
			SetFontSize(15);
		}
		else if (win_player == player_2) {
			ChangeFont("Enchants", DX_CHARSET_DEFAULT);
			SetFontSize(200);
			DrawStringEx(text_move, 530, 0, "player second win");
			DrawStringEx(text_move2, 50, 0, "player second win");
			SetFontSize(15);
		}
	}




	if (result_flag) {
		DrawRotaGraph3F(box_pos[box_count].x, box_pos[box_count].y, bw / 2, bh / 2, box_size.x, box_size.y, 0, box_img, true);
		DrawRotaGraph3F(label_pos_.x, label_pos_.y, w / 2, h / 2, 1, 0.5, t2k::toRadian(-45), label, true);
		DrawRotaGraph3F(label_pos_2.x, label_pos_2.y, w / 2, h / 2, 1, 0.5, t2k::toRadian(-45), label, true);
		DrawRotaGraph(text_pos_1.x, text_pos_1.y, 1, t2k::toRadian(-45), win_img, true);
		DrawRotaGraph(text_pos_2.x, text_pos_2.y, 1, t2k::toRadian(-45), win_img, true);
		DrawRotaGraph(text_pos_3.x, text_pos_3.y, 1, t2k::toRadian(-45), win_img, true);
		DrawRotaGraph(text_pos_4.x, text_pos_4.y, 1, t2k::toRadian(-45), win_img, true);
		DrawRotaGraph(chara_pos_.x, chara_pos_.y, 1, 0, chara_img[chara_hoz], true);
		SetFontSize(30);
		ChangeFont("ＭＳ　明朝", DX_CHARSET_DEFAULT);
		DrawStringEx(300, 300, 0, "キャラ選択に戻る");
		DrawStringEx(320, 400, 0, "ロビーに戻る");

	}

	//	DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, label, true);
}



void Game_manager::get_player2_pos(t2k::Vector3 get_player_pos) {
	//v1 = get_player_pos;
}

