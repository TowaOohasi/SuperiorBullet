#include <stdlib.h>
#include <time.h>
#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "hint.h"
#include <time.h>
#include<list>
#include<math.h>


extern Game_manager* game_manager_;

Hint::Hint() {
	srand(time(0));
	hint_img[0] = game_manager_->imgLoadGraph("graphics/hint.png");
	hint_img[1] = game_manager_->imgLoadGraph("graphics/hint2.png");
	hint_img[2] = game_manager_->imgLoadGraph("graphics/hint3.png");
	hint_img[3] = game_manager_->imgLoadGraph("graphics/hint4.png");
	hint_music = LoadSoundMem("sound/zingru.mp3");
	random_number = rand() % 4;
}



void Hint::update(float deltatime) {

	time_count += deltatime;
	if (time_count > 1) {
		if (feid_flag == false) {
			if (hint_music != 0 && !CheckSoundMem(hint_music)) {
				PlaySoundMem(hint_music, DX_PLAYTYPE_LOOP);
			}
			if (feid_numeric_value < 255) {
				feid_numeric_value += 3;
			}
			else {
				feid_flag = true;
			}
		}
	}

	if (time_count > 10) {
		StopSoundMem(hint_music);
		DeleteSoundMem(hint_music);
		if (feid_flag) {
			lag_count += deltatime;
			feid_numeric_value -= 3;
		}
		
		
	}
	
}


void Hint::draw(float deltatime) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, feid_numeric_value);
	DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, hint_img[random_number], true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

}