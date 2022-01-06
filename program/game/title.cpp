#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "title.h"
#include <time.h>
#include<list>
#include<math.h>

extern Game_manager* game_manager_;

Title::Title() {
	title_img = game_manager_->imgLoadGraph("graphics/taitoru.png");
	psyu_img = game_manager_->imgLoadGraph("graphics/botann.png");
	rogo_img = game_manager_->imgLoadGraph("graphics/vantan.png");
	dannkonn_img = game_manager_->imgLoadGraph("graphics/dankon.png");
	rogo_img = game_manager_->imgLoadGraph("graphics/vantan.png");
	jyuu_sound = LoadSoundMem("sound/jyuu.mp3");

	
}


void Title::update(float deltatime) {

	if (feid_flag == false) {
		feid_count++;
		if (feid_count > 300) {
			feid_flag = true;
		}
	}

	if (feid_count > -100) {
		if (feid_flag) {
			feid_count--;
		}
	}

	if (feid_count < -99) {
		title_flag = true;
	}

	if (title_flag) {
		time_count += deltatime;
		if (time_count > 2) {
			jyuu_flag = true;
			if (jyuu_sound != 0 && !CheckSoundMem(jyuu_sound)) {
				PlaySoundMem(jyuu_sound, DX_PLAYTYPE_LOOP);
			}
		}
		if (time_count > 3) {
			StopSoundMem(jyuu_sound);
			game_manager_->title_sound_flag = true;
		}

	}


	

	if (game_manager_->psyu_feid_flag) {
		if (change==false) {
			psyu_feid_count += 2;
			if (psyu_feid_count > 255) {
				change = true;
			}
		}

		if (change) {
			psyu_feid_count -= 2;
			if (psyu_feid_count < 0) {
				change = false;
			}
		}
	}


}



void Title::draw(float deltatime) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, feid_count);
	DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, rogo_img, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);


	if (title_flag) {
		DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, title_img, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, psyu_feid_count);
		DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, psyu_img, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		if (jyuu_flag) {
			DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, dannkonn_img, true);
		}
	}

}