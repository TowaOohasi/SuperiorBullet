#pragma once
#include "object.h"
//#include "player.h"

class Player;

class Life :public Object {
public:
	Life();
	~Life();

	float time_count = 0;
	float standby_count = 0.0;
	float text_time_count = 0;


	const int sx = 1280 / 2;
	const int sy = 720 / 2;
	int player_1_hp_img1 = 0;
	int player_1_hp_img2 = 0;
	int player_1_hp_img3 = 0;
	int player_1_hp_img4 = 0;
	int player_2_hp_img1 = 0;
	int player_2_hp_img2 = 0;
	int player_2_hp_img3 = 0;
	int player_2_hp_img4 = 0;
	int life_img = 0;
	int life_effect = 0;

	int slide_x = -800;
	int x_correction = -2500;
	
	int toranp_sound = 0;


	bool change_effect = true;
	bool text_flag = false;
	bool life_draw_flag = true;


	Player* get_player;
	

	int imgLoadGraph(std::string img_pas);
	void hit_player_get(Player* hit_player);
	void draw_hpimg();
	void go_text(float deltatime);
	void update(float deltatime) override;
	void draw(float deltatime) override;
};
