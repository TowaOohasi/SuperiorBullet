#pragma once
#include "object.h"


class Menyu :public Object {
public:

	Menyu();
	XINPUT_STATE input;

	int left_img = 0;
	int right_img[2] = { 0 };

	int right_number = 0;

	int sentaku_box_img = 0;

	int pos_y[2] = { 400,575 };

	void update(float deltatime) override;
	void draw(float deltatime) override;
};