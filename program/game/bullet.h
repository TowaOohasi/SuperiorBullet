#pragma once
#include "../library/t2klib.h"
#include "object.h"


struct bullet_status {
	t2k::Vector3 start_pos_;
	t2k::Vector3 move_dir_;
	t2k::Vector3 line_pos_;
	int bullet_pas = 0;
	int collar = 0;
	float speed_=0;
	float radius=20;
	float img_size = 1;
	float angle = 0;
	float angle_sum = 0.1;
	bool change_hit = true;
	bool change_angle = false;  //bullet‚Ì‰æ‘œ‚ÌŠp“x‚ğí•Ï‚¦‚é
	bool circle_move_change = false;  //chara_yellow‚ÌYƒ{ƒ^ƒ“‚ğg‚¤‚½‚ß‚Ìƒtƒ‰ƒO
	enum {
		reza
	};
};



class Bullet:public Object {
public:
	Bullet() {}
	Bullet(bullet_status desc);
	int bullet_pas = 0;
	t2k::Vector3 move_dir;
	t2k::Vector3 move_dir2;
	float distance = 0;
	float radius = 0 ;
	float time_count = 0;
	float standby_time_count = 0;
	float angle_count = 0;
	float img_size = 0;
	float angle_sum = 0;
	t2k::Vector3 get_pos_;  //player‚Ìpos‚ğ•Û‘¶
	bool judge=false;
	bool change_hit;
	bool change_angle;
	bool change_circle = false;
	bool circle_move_change = false;
	bool  graduallygettinglouder = false;

	int discriminant = 0;

	int coller = 0;

	float angle = 0;

	t2k::Sequence<Bullet*> sequence_ = t2k::Sequence<Bullet*>(this, &Bullet::seqActionMove);

	bool seqActionMove(const float delta_time);
	bool seqActionErase(const float delta_time);
	bool circleMoveSecond(const float deltartime);
	bool graduallyGettingLouder(const float deltatime);


	

	/*enum {
		player_1,
		player_2
	};

	enum {
		bullet_A,
		bullet_B,
		bullet_X
	};

	int bullet_type = -1;*/



	void erase_check();

	/*void create_bullet_A();
	void create_bullet_B();
	void create_bullet_X();*/
	void update(float deltatime) override;
	void draw(float deltatime) override;
};



//—†ù’e–‹—p---------------------------------------------------------------------------------------------------------------------------------------------
class SpiralBullet :public Bullet {
public:

	SpiralBullet(bullet_status desc, int angle = 0);
	t2k::Vector3 move_keep;
	int rotation;  //—†ù’e–‹‚ğ‰½“x‰ñ“]‚³‚¹‚é‚©‚ğŠi”[‚·‚é



	t2k::Sequence<SpiralBullet*> sequence_s = t2k::Sequence<SpiralBullet*>(this, &SpiralBullet::seqActionMove_s);

	bool seqActionMove_s(const float delta_time);
	bool seqActionErase_s(const float delta_time);

	void erase_check();
	void update(float deltatime) override;
	void draw(float deltatime) override;
};


class Reiza :public Object {
public:

	Reiza(bullet_status desc);

	int reiza_img = 0;
	float l_width = 1.0;
	int bullet_pas = 0;
	t2k::Vector3 l_pos = { 0, 0, 0 };
	t2k::Vector3 l_pos_end = { 0, 0, 0 };
	t2k::Vector3 line_pos_ = { 0, 0, 0 };
	t2k::Vector3 cross = { 0, 0, 0 };
	t2k::Vector3 cross2 = { 0, 0, 0 };
	t2k::Vector3 bottom_l_pos = { 0, 0, 0 };
	t2k::Vector3 bottom_l_pos_end = { 0, 0, 0 };
	t2k::Vector3 bottom_cross = { 0, 0, 0 };
	t2k::Vector3 bottom_l_pos2 = { 0, 0, 0 };
	t2k::Vector3 bottom_l_pos_end2 = { 0, 0, 0 };
	t2k::Vector3 bottom_cross2 = { 0, 0, 0 };
	float time_count = 0;

	float dot = 0;
	float dot2 = 0;
	float dot3 = 0;
	float angle = 0;

	bool reiza_falsg = true;
	bool reiza_hit_falsg = true;


	void update(float deltatime) override;
	void draw(float deltatime) override;
};
