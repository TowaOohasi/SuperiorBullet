#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "haike.h"

extern Game_manager* game_manager_;

BackGround::BackGround() {
	layer_2 = LoadGraph("graphics/haikei1.png");
	layer_1 = LoadGraph("graphics/background_layer1.png");
	tokei_img = LoadGraph("graphics/tokei.png");
	hari_img = LoadGraph("graphics/hari.png");
}





BackGround::~BackGround() {
	auto it = game_manager_->img.find(game_manager_->delete_img);
	if (it != game_manager_->img.end()) {
		DeleteGraph(it->second);
		game_manager_->img.erase(it);
	}
}




void BackGround::update(float deltatime) {
	angle += 0.002;
	angle2 -= 0.001;

	time_count += deltatime;
	if (time_count > 1) {
		time_count = 0;
	tokei_angle += t2k::toRadian(0.5);
	}
}


void BackGround::draw(float deltatime) {
	DrawRotaGraph(bx, by, 1, 0, layer_1, true);
	if (haike_draw_flag) {
		DrawRotaGraph(bx, by, 1, angle, layer_2, true);
		DrawRotaGraph(bx, by, 0.923, angle2, layer_2, true);
		DrawRotaGraph(bx, by, 1, 0, tokei_img, true);
		DrawRotaGraph(bx, by, 1, tokei_angle, hari_img, true);
	}
	
}