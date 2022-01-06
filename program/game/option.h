#pragma once
#include "object.h"


class Option :public Object {
public:
	Option();


	int setumei_img = 0;


	void update(float deltatime) override;
	void draw(float deltatime) override;
};