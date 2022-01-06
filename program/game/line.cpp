#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include <time.h>
#include<list>
#include<math.h>
#include "line.h"
#include "game_manager.h"

extern Game_manager* game_manager_;

Line::Line() {
	pos_ = { 0,0,0 };
	pos_2 = { 1280,720,0 };
	speed_ = 2;
}


void Line::update(float deltatime) {
	pos_.x = game_manager_->field_->pos_.x;
	pos_2.x = game_manager_->field_->pos_2.x;

	pos_ += move_dir_d * speed_;
	pos_2 += move_dir_u * speed_;

	if (pos_.y > 1280||pos_2.y<-100) {
		is_alive_ = false;
	}

	

}


void Line::draw(float deltatime) {
	DrawStringEx(pos_.x, pos_.y, -1, "|");
	DrawStringEx(pos_2.x, pos_2.y, -1, "|");
}