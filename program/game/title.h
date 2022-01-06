#pragma once
#include "object.h"

class Title :public Object {
public:
	Title();

	int title_img = 0;
	int psyu_img = 0;
	int title_movie = 0;
	int rogo_img = 0;
	int dannkonn_img = 0;
	int feid_count = 0;

	int jyuu_sound = 0;
	int psyu_feid_count = 0;


	float time_count = 0;

	float jyuu_flag = false;

	bool feid_flag = false;
	bool title_flag = false;
	bool change = false;

	void update(float deltatime) override;
	void draw(float deltatime) override;

};