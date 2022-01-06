#pragma once
#include"object.h"


class Field :public Object {
public:
	Field();

	t2k::Vector3 pos_2;

	void update(float deltatime) override;
	void draw(float deltatime) override;
};