#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "option.h"
#include <time.h>
#include<list>
#include<math.h>

extern Game_manager* game_manager_;


Option::Option() {
	setumei_img = game_manager_->imgLoadGraph("graphics/setumei.png");
}


void Option::update(float deltatime) {

}


void Option::draw(float deltatime) {
	DrawRotaGraph(1280 / 2, 720 / 2, 1, 0, setumei_img, true);
}