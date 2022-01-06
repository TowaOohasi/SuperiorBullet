#pragma once
#include "../library/t2klib.h"
#include "object.h"






class BackGround :public Object {
public:
	
	BackGround();
	~BackGround();
	int layer_1 = 0;
	int layer_2 = 0;

	int tokei_img = 0;
	int hari_img = 0;

	const int bx = 1280 / 2, by = 720 / 2;

	float angle = 0;
	float angle2 = 0;
	float tokei_angle = 0;

	float time_count = 0;

	bool haike_draw_flag = true;


	void update(float deltatime) override;
	void draw(float deltatime) override;
};
