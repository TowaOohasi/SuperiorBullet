#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "menyu.h"
#include <time.h>
#include<list>
#include<math.h>

extern Game_manager* game_manager_;

Menyu::Menyu() {
	left_img = game_manager_->imgLoadGraph("graphics/menyu_hidari.png");
	right_img[0] = game_manager_->imgLoadGraph("graphics/menyu_migi.png");
	right_img[1] = game_manager_->imgLoadGraph("graphics/menyu_story.png");
	sentaku_box_img = game_manager_->imgLoadGraph("graphics/sentaku_box.png");
}


void Menyu::update(float deltatime) {
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (input.ThumbLY < 0) {
		right_number = 1;
	}

	if (input.ThumbLY>0) {
		right_number = 0;
	}
}

void Menyu::draw(float deltatime) {
	DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, left_img, true);
	DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, right_img[right_number], true);
	DrawRotaGraph(1280 / 2, pos_y[right_number], 1, 0, sentaku_box_img, true);
	SetFontSize(15);
	DrawStringEx(120, 320, -1, "相手のライフを先に０にした方の勝ちです");
	DrawStringEx(90, 500, -1, "オプションです。操作方法の確認ができます");
}