#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "life.h"
//#include"player.h"

extern Game_manager* game_manager_;
//extern Player* player_1;
//extern Player* player_2;

//int imgLoadGraph(/* à¯êîéwíËÇµÇΩÇ¢ */)
//{
//	// îªíË
//
//	return LoadGraph("graphics/toranp.png");
//}




Life::Life() {
	life_img = game_manager_->imgLoadGraph("graphics/HP_frame.png");
	player_1_hp_img1 = game_manager_->imgLoadGraph("graphics/player_1_hp_1.png");
	player_1_hp_img2 = game_manager_->imgLoadGraph("graphics/player_1_hp_2.png");
	player_1_hp_img3 = game_manager_->imgLoadGraph("graphics/player_1_hp_3.png");
	player_1_hp_img4 = game_manager_->imgLoadGraph("graphics/player_1_hp_4.png");
	player_2_hp_img1 = game_manager_->imgLoadGraph("graphics/player_2_hp_1.png");
	player_2_hp_img2 = game_manager_->imgLoadGraph("graphics/player_2_hp_2.png");
	player_2_hp_img3 = game_manager_->imgLoadGraph("graphics/player_2_hp_3.png");
	player_2_hp_img4 = game_manager_->imgLoadGraph("graphics/player_2_hp_4.png");
	life_effect = game_manager_->imgLoadGraph("graphics/life_efect.png");
	toranp_sound = LoadSoundMem("sound/toranp1.mp3");
	ChangeVolumeSoundMem(100, toranp_sound);
}

void Life::hit_player_get(Player* hit_player) {
	get_player = hit_player;

}


void Life::draw_hpimg() {
	if (game_manager_->player_2->hp > 0) {
		if (game_manager_->player_2->life == 1) {
			DrawRotaGraph(sx, sy, 1, 0, player_2_hp_img1, true);
		}
		else if (game_manager_->player_2->life == 2) {
			DrawRotaGraph(sx, sy, 1, 0, player_2_hp_img2, true);
		}
		else if (game_manager_->player_2->life == 3) {
			DrawRotaGraph(sx, sy, 1, 0, player_2_hp_img3, true);
		}
		else if (game_manager_->player_2->life == 4) {
			DrawRotaGraph(sx, sy, 1, 0, player_2_hp_img4, true);
		}
	}

	if (game_manager_->player_1->hp > 0) {
		if (game_manager_->player_1->life == 1) {
			DrawRotaGraph(sx, sy, 1, 0, player_1_hp_img1, true);
		}
		else if (game_manager_->player_1->life == 2) {
			DrawRotaGraph(sx, sy, 1, 0, player_1_hp_img2, true);
		}
		else if (game_manager_->player_1->life == 3) {
			DrawRotaGraph(sx, sy, 1, 0, player_1_hp_img3, true);
		}
		else if (game_manager_->player_1->life == 4) {
			DrawRotaGraph(sx, sy, 1, 0, player_1_hp_img4, true);
		}
	}
}



void Life::go_text(float deltatime) {
	if (text_flag) {
		text_time_count += deltatime;
		if (text_time_count < 2) {
			ChangeFont("Enchants", DX_CHARSET_DEFAULT);
			SetFontSize(700);
			DrawStringEx(300, 50, -1, "GO");
		}
		else {
			game_manager_->is_all_bullet_erase = false;
			text_time_count = 0;
			text_flag = false;
		}
	}
}







Life::~Life() {
	//auto it = game_manager_->img.find("graphics/toranp.png");
	auto it = game_manager_->img.find(game_manager_->delete_img);
	if (it != game_manager_->img.end()) {
		DeleteGraph(it->second);
		game_manager_->img.erase(it);
	}
}

void Life::update(float deltatime) {
	
	

}

void Life::draw(float deltatime) {
	if (life_draw_flag) {
		draw_hpimg();
		//DrawRotaGraph(100, 100, 0.5, 0, hp_img, true);
		DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, life_img, true);
		ChangeFont("a dripping marker", DX_CHARSET_DEFAULT);
		SetFontSize(80);
		DrawStringEx(24, 12, -1, "%d", game_manager_->player_1->hp);
		DrawStringEx(1218, 12, 0, "%d", game_manager_->player_2->hp);
		SetFontSize(13);
		ChangeFont("ÇlÇr ÉSÉWÉbÉN", DX_CHARSET_DEFAULT);

		if (change_effect) {
			time_count += deltatime;
			if (toranp_sound != 0 && !CheckSoundMem(toranp_sound)) {
				PlaySoundMem(toranp_sound, DX_PLAYTYPE_LOOP);
			}
			if (time_count < 3) {
				standby_count = 3 - time_count;
				DrawRotaGraph(sx, sy, 1, 0, life_effect, true);
				SetFontSize(180);
				for (int i = 0; i <= 1; i++) {
					DrawStringEx(slide_x + (i * x_correction), 380, 0, "Standby ladyÅ@%.2f", standby_count);
				}
				SetFontSize(13);
				slide_x += 3;
			}
			else {
				text_flag = true;
				time_count = 0;
				change_effect = false;
				game_manager_->is_all_bullet_erase = false;
				StopSoundMem(toranp_sound);

			}
		}
		go_text(deltatime);
	}

}