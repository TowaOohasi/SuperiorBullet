#pragma once
#include "object.h"



class Line :public Object {
public:
	Line();
	t2k::Vector3 pos_2;
	t2k::Vector3 move_dir_u{ 0,-1,0 };
	t2k::Vector3 move_dir_d{ 0,1,0 };


	void update(float deltatime) override;
	void draw(float deltatime) override;

};