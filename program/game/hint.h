#pragma once
#include"object.h"


class Hint :public Object {
public:

	Hint();


	float time_count = 0;
	float lag_count = 0;

	int hint_img[4] = { 0 };  //�摜�i�[
	int hint_number = 0;
	int hint_music = 0;  //�W���O���i�[
	int feid_numeric_value = 0;
	int random_number = 0;

	bool feid_flag = false;



	void update(float deltatime) override;
	void draw(float deltatime) override;
};