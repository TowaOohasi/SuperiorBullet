#pragma once
#include "../library/t2klib.h"
#include"object.h"



class Chara_select:public Object{
public:
	Chara_select();

	const int sx = 1280 / 2;
	const int sy = 720 / 2;

	int background_img = 0;
	

	void update(float deltatime) override;
	void draw(float deltatime) override;
};