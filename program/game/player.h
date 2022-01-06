#pragma once
#include "object.h"
#include "../library/t2klib.h"
#include "bullet.h"
#include "life.h"
#include<list>


class Player : public Object {
public:
	Player(t2k::Vector3 coordinate, int controller, int wa);


	std::list<Bullet*>bullet_b;
	std::list<Bullet*>bullet_x;
	std::list<Bullet*>bullet_;
	std::list<Bullet*>red_a;
	std::list<Bullet*>red_a_2;
	std::list<Bullet*>red_b;
	std::list<Bullet*>red_x;
	std::list<Bullet*>bullet_red; //弾と弾の当たり判定用のリスト
	std::list<Bullet*>blue_a;
	std::list<Bullet*>blue_b;
	std::list<Bullet*>blue_x;
	std::list<Bullet*>blue_y;
	std::list<Bullet*>yellow; //chara_yellowのyボタンのリスト（通常弾ではない）
	std::list<Bullet*>yellow_a;
	//std::list<Bullet*>yellow_b;
	std::list< Reiza*>yellow_b;
	std::list<Bullet*>yellow_x;
	std::list<Bullet*>yellow_y;



	const int radius = 5;

	float shot_count_A = 0;
	float shot_count_B = 0;
	float shot_count_X = 0;
	float shot_count_Y = 0;

	float push_count = 0;

	float time_count = 0;
	float time_count2 = 0;
	float yellow_count = 0;
	float red_a_count = 0;
	float red_b_count = 0;
	float red_x_count = 0;
	float red_y_count = 0;
	float cooltime_red_a = 1.5;
	float cooltime_red_b = 3;
	float cooltime_red_x = 2;
	float cooltime_red_y = 5;

	float green_a_count = 0;
	float green_b_count = 0;
	float green_x_count = 0;
	float green_y_count = 0;
	float cooltime_green_a = 0.7;
	float cooltime_green_b = 2;
	float cooltime_green_x = 7;
	float cooltime_green_y = 10;

	float blue_a_count = 0;
	float blue_b_count = 0;
	float blue_x_count = 0;
	float blue_y_count = 0;
	float cooltime_blue_a = 0.3;
	float cooltime_blue_b = 0.5;
	float cooltime_blue_x = 0.5;
	float cooltime_blue_y = 10;

	float yellow_a_count = 0;
	float yellow_b_count = 0;
	float yellow_x_count = 0;
	float yellow_y_count = 0;
	float cooltime_yellow_a = 0.5;
	float cooltime_yellow_b = 3;
	float cooltime_yellow_x = 7;
	float cooltime_yellow_y = 15;






	float alpha = 255;



	float angle;


	float lag_count = 0;
	bool suiti = false;


	bool range = false;

	bool change = false;

	bool execution_up = true;
	bool execution_draw = true;

	bool count_flag = false;


	bool three_effect = false;

	bool yellow_flag = false;
	bool draw_flag = true;


	int button_type = -1;
	int chara_type = -1;

	int get_collar = 0;

	float img_size = 1;

	int hp = 4;
	int life = 1;


	int now_push[16];
	int ago_push[16];

	
	


	int bullet_img_a = 0;
	int bullet_img_b = 0;
	int bullet_img_x = 0;
	int bullet_img_y = 0;
	int bullet_red_shield = 0;
	int bullet_red_a = 0;
	int bullet_blue_a = 0;
	int bullet_blue_b = 0;
	int bullet_blue_x = 0;
	int bullet_blue_y = 0;
	int bullet_yellow_a = 0;
	int bullet_yellow_b = 0;
	int bullet_yellow_x = 0;
	int bullet_yellow_y = 0;
	int cursor = 0;




	int chara_img_red = 0;
	int chara_img_blue = 0;
	int chara_img_green = 0;
	int chara_img_yellow = 0;
	int chara_img_black = 0;

	int icon_red = 0;
	int icon_red_time_img[4] = { 0 };

	int icon_green = 0;
	int icon_green_time_img[4] = { 0 };

	int icon_blue = 0;
	int icon_blue_time_img[4] = { 0 };

	int icon_yellow = 0;
	int icon_yellow_time_img[4] = { 0 };



	float shot_wait_time_count_ = 0;
	int bx = 0, by = 0;
	int bx2 = 0, by2 = 0;
	int controller_type;
	t2k::Vector3 shot;
	t2k::Vector3 spl = shot;
	t2k::Vector3 spl2;
	t2k::Vector3 test = { bx2,by2,0 };
	t2k::Vector3 v1;
	t2k::Vector3 pos;
	t2k::Vector3 get_pos_;
	t2k::Vector3 icon_pos_1= { 193, 637, 0 };
	t2k::Vector3 icon_pos_2= { 1086, 637, 0 };


	enum {
		push,
		hold,
		enpty,
		push_x,
		hold_x,
		enpty_x
	};


	enum {
		chara_red,
		chara_blue,
		chara_green,
		random,
		chara_yellow,
		chara_black
	};
	
	int state = enpty;
	int state2 = enpty;
	int push_number = enpty;

	bool sky = false;
	XINPUT_STATE input;

	void erase_has_players_bullet();

	void push_type(int bottun_no,float deltatime);

	

	void get_player_A(t2k::Vector3 get_pos);
	void get_player_B(t2k::Vector3 get_pos);
	void get_player_X(t2k::Vector3 get_pos);
	void get_red_A(t2k::Vector3 get_pos);
	void get_red_B(t2k::Vector3 get_pos);
	void get_red_X(t2k::Vector3 get_pos);
	void get_blue_A(t2k::Vector3 get_pos);
	void get_blue_B(t2k::Vector3 get_pos);
	void get_blue_X(t2k::Vector3 get_pos);
	void get_blue_Y(t2k::Vector3 get_pos);
	void get_yellow_A(t2k::Vector3 get_pos);
	void get_yellow_B(t2k::Vector3 get_pos);
	void get_yellow_X(t2k::Vector3 get_pos);
	void get_yellow_Y(t2k::Vector3 get_pos);

	void flashing(float deltatime);
	void hit_number(std::list<Bullet*> bullet_tyep);
	void character_green(float deltatime);
	void character_red(float deltatime);
	void character_blue(float deltatime);
	void character_yellow(float deltatime);
	void button_push(int button, float deltatime);
	int all_push(int buttan);


	void update(float deltatime) override;
	void draw(float deltatime) override;
	
};

class Controller {
public:

};
