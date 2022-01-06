#pragma once
#include "explanation.h"
#include"object.h"


class Select_cusor :public Object {
public:

	Select_cusor(int controller_type);


	Explanation* explanation_1_ = nullptr;
	Explanation* explanation_2_ = nullptr;


	XINPUT_STATE input;
	int g = 0;

	int controller = 0;
	int cusor_1 = 0;
	int cusor_2 = 0;
	int label_img[6] = { 0 };
	int label_img2[6] = { 0 };
	int label_img3[6] = { 0 };
	int label_text[6] = { 0 };
	int chara_img[6] = { 0 };
	t2k::Vector3 cusor_pos[6] = { t2k::Vector3{640,360,0},t2k::Vector3{600,481,0},t2k::Vector3{560,602,0},t2k::Vector3{520,723,0},t2k::Vector3{480,844,0},t2k::Vector3{440,965,0} };
	int standby_img = 0;
	int cusor_status = 0;
	int select_img = 0;
	int big_ok1 = 0;
	int big_ok2 = 0;
	int standby_label = 0;
	int blend_count = 0;
	int setumei_img[6] = { 0 };
	

	t2k::Vector3 text_move = { -1,0,0 };
	t2k::Vector3 text_move2 = { -1,0,0 };
	t2k::Vector3 text_move3 = { -1,0,0 };
	t2k::Vector3 move_pos_ = { 600,260,0 };
	t2k::Vector3 move_pos_2[2] = { t2k::Vector3{740,20,0},t2k::Vector3{740,20,0} };
	t2k::Vector3 move_pos_3[2] = { t2k::Vector3{600,625,0},t2k::Vector3{600,625,0} };
	t2k::Vector3 player2_pos_1[2] = { t2k::Vector3{1450,340,0},t2k::Vector3{1450,340,0} };
	t2k::Vector3 player2_pos_2[2] = { t2k::Vector3{1500,-70,0},t2k::Vector3{1500,-70,0} };
	t2k::Vector3 player2_pos_3[2] = { t2k::Vector3{1480,700,0},t2k::Vector3{1480,700,0} };


	bool text_flag = false;
	bool text_flag2 = false;
	bool text_flag3 = false;

	bool player2_flag = false;
	bool player2_flag2 = false;
	bool player2_flag3 = false;

	bool standby = false;


	bool is_start_ = true;

	bool is_input_a_prev_ = false;
	bool is_input_a_now_ = false;
	

	float stick_count = 0;
	float not_count = 0;
	int state = -1;

	enum {
		push,
		hold,
		enpty
	};


	void push_type(float deltatime);
	void update(float deltatie) override;
	void draw(float deltatime) override;
	void label_move(t2k::Vector3 pos, bool flag, t2k::Vector3 move_pos, t2k::Vector3 text_move, float speed);
	void standby_text(float deltatime);
};