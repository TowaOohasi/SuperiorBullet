#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_manager.h"
#include "bullet.h"
#include <time.h>

extern Game_manager* game_manager_;

Bullet::Bullet(bullet_status desc) {
	pos_ = desc.start_pos_;
	move_dir2 = desc.start_pos_;
	move_dir = desc.move_dir_;
	speed_ = desc.speed_;
	radius = desc.radius;
	img_size = desc.img_size;
	bullet_pas = desc.bullet_pas;
	coller = desc.collar;
	change_hit = desc.change_hit;
	angle = desc.angle;
	change_angle = desc.change_angle;
	angle_sum = desc.angle_sum;
	circle_move_change = desc.circle_move_change;

	//bullet_test = LoadGraph("graphics/bullet_a.png");

}

//弾幕用
SpiralBullet::SpiralBullet(bullet_status desc, int angle) {
	pos_ = desc.start_pos_;
	move_keep = desc.start_pos_;
	rotation = angle;
	move_dir = desc.move_dir_;
	speed_ = desc.speed_;
	radius = desc.radius;
	img_size = desc.img_size;
	bullet_pas = desc.bullet_pas;
	coller = desc.collar;
	angle = desc.angle;
	change_angle = desc.change_angle;

}



Reiza::Reiza(bullet_status desc) {
	pos_ = desc.start_pos_;
	pos_ = desc.start_pos_;
	l_pos = desc.start_pos_;
	line_pos_ = desc.line_pos_;
	reiza_img = desc.bullet_pas;
	bullet_pas = desc.bullet_pas;
	angle = desc.angle;
	l_width = 0.02;
	l_pos_end = l_pos + line_pos_ * 1000;


}



void Bullet::update(float deltatime) {
	sequence_.update(deltatime);
}




void Bullet::erase_check() {
	if (pos_.y > 0) change_hit = true;


	if (change_hit) {
		if (pos_.y < 0 || pos_.y>768 || pos_.x < 0 || pos_.x>1280) is_alive_ = false;
	}
}


void Bullet::draw(float deltatime) {
	if (judge == false) {
		DrawCircle(pos_.x, pos_.y, radius, coller, judge);
	}
	else if (judge) {
		DrawRotaGraph(pos_.x, pos_.y, img_size, angle, bullet_pas, true);
	}

}



bool Bullet::seqActionMove(const float delta_time) {
	pos_ += move_dir * speed_;
	t2k::Vector3 test = pos_;

	if (change_angle) {
		angle += angle_sum;
	}

	if (game_manager_->is_all_bullet_erase) {
		sequence_.change(&Bullet::seqActionErase);
	}

	if (change_circle) {
		sequence_.change(&Bullet::circleMoveSecond);
	}

	if (circle_move_change) {
		sequence_.change(&Bullet::graduallyGettingLouder);
	}

	return true;
}




bool Bullet::seqActionErase(const float delta_time) {

	img_size *= 0.9f;
	if (img_size < 0.01f) {
		is_alive_ = false;
	}

	return true;
}




//chara_yellowのAボタンの処理
bool Bullet::circleMoveSecond(const float deltatime) {
	if (game_manager_->is_all_bullet_erase) {
		sequence_.change(&Bullet::seqActionErase);
	}

	standby_time_count += deltatime;
	if (standby_time_count > 2) {
		img_size *= 1.1f;
		radius *= 1.1;
		if (img_size > 0.5) {
			is_alive_ = false;
		}
	}

	return true;
}



//chara_yellowのYボタンの処理
bool Bullet::graduallyGettingLouder(const float deltatime) {
	if (game_manager_->is_all_bullet_erase) {
		sequence_.change(&Bullet::seqActionErase);
	}

	if (change_angle) {
		angle += angle_sum;
	}

	time_count += deltatime;
	if (img_size < 0.1 && !graduallygettinglouder) {
		img_size *= 1.1f;
		radius *= 1.1f;
	}

	if (time_count > 10) {
		graduallygettinglouder = true;
	}

	if (graduallygettinglouder) {
		img_size *= 0.9;
		radius *= 0.9;
		if (img_size < 0.01) {
			is_alive_ = false;
		}
	}


	return true;
}





//螺旋弾幕用--------------------------------------------------------------------------------------------------------------------------------------------------

void SpiralBullet::update(float deltatime) {
	sequence_s.update(deltatime);
	/*pos_ += move_dir * speed_;
	t2k::Vector3 test = pos_;
	move_dir = t2k::Vector3::transformCoord(test - move_keep, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(rotation))).normalize();*/
}

bool SpiralBullet::seqActionMove_s(const float delta_time) {
	pos_ += move_dir * speed_;
	t2k::Vector3 test = pos_;
	move_dir = t2k::Vector3::transformCoord(test - move_keep, t2k::Matrix::createRotationAxis(t2k::Vector3(0, 0, 1), t2k::toRadian(rotation))).normalize();

	if (game_manager_->is_all_bullet_erase) {
		sequence_s.change(&SpiralBullet::seqActionErase_s);
	}

	return true;
}

bool SpiralBullet::seqActionErase_s(const float delta_time) {

	img_size *= 0.9f;
	if (img_size < 0.01f) {
		is_alive_ = false;
	}

	return true;
}

//void SpiralBullet::erase_check() {
//	if (pos_.y < 0 || pos_.y>768 || pos_.x < 0 || pos_.x>1280) is_alive_ = false;
//}

void SpiralBullet::draw(float deltatime) {
	//DrawCircle(pos_.x, pos_.y, radius, collar,judge);
	DrawRotaGraph(pos_.x, pos_.y, img_size, 0, bullet_pas, true);

}




//laserクラスーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
void Reiza::update(float deltatime) {
	if (reiza_falsg) {
		if (l_width < 1) {
			l_width *= 1.4;
		}
		else {
			reiza_falsg = false;
		}
	}
	else {
		l_width *= 0.9;
	}

	if (l_width < 0.01) {
		is_alive_ = false;
	}

	int w, h;
	GetGraphSize(bullet_pas, &w, &h);
	h -= 250;

	//中心線の外積を算出
	cross = t2k::Vector3::cross((l_pos_end - l_pos).normalize(), { 0,0,1 });
	cross2 = t2k::Vector3::cross((l_pos_end - l_pos).normalize(), { 0,0,1 });


	//下側の線を算出
	bottom_l_pos = l_pos + cross * (-h / 2) * l_width;
	bottom_l_pos_end = l_pos_end + cross * (-h / 2) * l_width;
	bottom_l_pos2 = l_pos + cross2 * (h / 2) * l_width;
	bottom_l_pos_end2 = l_pos_end + cross2 * (h / 2) * l_width;


	// 下側の線に直行するベクトル
	bottom_cross = t2k::Vector3::cross((bottom_l_pos_end - bottom_l_pos).normalize(), { 0, 0, 1 });
	bottom_cross2 = t2k::Vector3::cross((bottom_l_pos_end2 - bottom_l_pos2).normalize(), { 0, 0, -1 });


	

}


void Reiza::draw(float deltatime) {
	int w, h;
	GetGraphSize(bullet_pas, &w, &h);

	DrawRotaGraph3F(l_pos.x, l_pos.y, 0, h / 2, 1.0, l_width, t2k::toRadian(angle), bullet_pas, true);

	/*DrawLine(l_pos.x, l_pos.y, l_pos_end.x, l_pos_end.y, 0xffff0000);

	DrawLine(bottom_l_pos.x, bottom_l_pos.y, bottom_l_pos_end.x, bottom_l_pos_end.y, 0xffff0000);
	DrawLine(bottom_l_pos2.x, bottom_l_pos2.y, bottom_l_pos_end2.x, bottom_l_pos_end2.y, 0xffff0000);*/



}