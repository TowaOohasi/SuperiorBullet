#pragma once
#include "object.h"


class Explanation :public Object {
public:
	Explanation(int controller_type);

	XINPUT_STATE input;

	int controller = 0;

	int chara_number = 0;

	int state = -1;

	int setumei_img[6] = { 0 };

	int number_hoz1=-1;
	int number_hoz2=-1;
	int box = 0;

	int feid_count = 0;


	bool setumei = false;
	bool stanby = false;
	bool not_flag = false;

	bool feid_flag = false;
	bool feid_count_flag = false;
	/*bool chara_flag1 = false;
	bool chara_flag2 = false;*/

	float not_count = 0;
	float slide_count = 0;


	enum {
		push,
		hold,
		enpty
	};


	void slide_type(float deltatime);
	void update(float deltatime) override;
	void draw(float deltatime) override;
};