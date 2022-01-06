#pragma once
#include"object.h"


class Hint :public Object {
public:

	Hint();


	float time_count = 0;
	float lag_count = 0;

	int hint_img[4] = { 0 };  //‰æ‘œŠi”[
	int hint_number = 0;
	int hint_music = 0;  //ƒWƒ“ƒOƒ‹Ši”[
	int feid_numeric_value = 0;
	int random_number = 0;

	bool feid_flag = false;



	void update(float deltatime) override;
	void draw(float deltatime) override;
};