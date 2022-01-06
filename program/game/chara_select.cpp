#include "game_manager.h"
#include "player.h"
#include "bullet.h"
#include "life.h"
#include "haike.h"
#include"chara_select.h"
#include <time.h>
#include<list>
#include<math.h>


extern Game_manager* game_manager_;

Chara_select::Chara_select() {
	background_img = game_manager_->imgLoadGraph("graphics/chara_select.png");
	
}


void Chara_select::update(float deltatime) {

}


void Chara_select::draw(float deltatime) {
	DrawRotaGraph(sx, sy, 1, 0, background_img, true);
}