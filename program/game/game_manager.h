#pragma once
#include "DxLib.h"
#include "../support/Support.h"
#include "../library/t2klib.h"
#include "object.h"
#include "player.h"
#include "bullet.h"
#include"chara_select.h"
#include "select_cursor.h"
#include"field.h"
#include"life.h"
#include"line.h"
#include "haike.h"
#include "explanation.h"
#include "menyu.h"
#include "title.h"
#include "option.h"
#include"hint.h"
#include<list>


class Game_manager {
public:
	Game_manager();
	std::list<Object*>object_;
	std::unordered_map<std::string, int>img;
	
	
	//Bullet* bullet_B = nullptr;
	Player* player_1= nullptr;
	Player* player_2= nullptr;
	Select_cusor* cusor1_ = nullptr;
	Select_cusor* cusor2_ = nullptr;
	Field* field_ = nullptr;
	Life* life = nullptr;
	Line* line_ = nullptr;
	BackGround* background_ = nullptr;

	Chara_select* chara_select_ = nullptr;

	Explanation* explanation_1_ = nullptr;
	Explanation* explanation_2_ = nullptr;

	Hint* hint_ = nullptr;
	Title* title_ = nullptr;

	Menyu* menyu_ = nullptr;

	Option* option_ = nullptr;



	XINPUT_STATE input;


	Player* win_player;

	int controller_type = -1;

	int chara_type1 = -1;
	int chara_type2 = -1;
	int get_chara_1 = 0;
	int get_chara_2 = 0;
	

	int start_count = 0;

	int title_sound = 0;



	float time_count = 0;
	float line_time_count = 0;
	float text_move = 0;
	float text_move2 =300;
	float push_count;
	



	float distance = 0;  //bulletÇÃãóó£Çë™ÇÈïœêî
	t2k::Vector3 get_b_pos;

	
	std::string delete_img;
	bool change = false;
	bool bullet_fly = true;

	bool is_all_bullet_erase = false;

	bool non_select_flag = false;

	bool non_batlle = false;

	bool menyu_flag = false;

	bool win_flag = false;

	bool menyu_move_flag = false;

	bool result_flag = false;

	bool change_effect_flag = false;

	bool ok_flag_1 = false;
	bool ok_flag_2 = false;

	bool title_sound_flag = false;

	bool psyu_feid_flag = false;

	bool mae = false;
	bool ima = false;

	

	int sen = 0;

	int battle_sound = 0;
	int select_sound = 0;
	int hit_sound = 0;
	int label = 0;
	int win_img = 0;
	int box_count = 0;
	int chara_hoz = -1;


	int chara_img[6] = { 0 };

	int box_img = 0;

	


	void initialize();


	t2k::Vector3 nanika;
	t2k::Vector3 standby_pos_ = { 900,360,0 };
	t2k::Vector3 move_dir = { 0,0,0 };
	t2k::Vector3 label_size = { 0,1,0 };
	t2k::Vector3 box_size = { 1,1,0 };
	t2k::Vector3 label_pos_ = { -600,800,0 };
	t2k::Vector3 label_pos_2 = { 480,1320,0 };
	t2k::Vector3 text_move_dir_ = { 1,-1,0 };
	t2k::Vector3 text_pos_1 = { -100,300,0 };
	t2k::Vector3 text_pos_2 = { -350,550,0 };
	t2k::Vector3 text_pos_3 = { 980,820,0 };
	t2k::Vector3 text_pos_4 = { 730,1070,0 };
	t2k::Vector3 chara_pos_ = { 900,360,0 };
	t2k::Vector3 box_pos[2] = { t2k::Vector3(425,315,0),t2k::Vector3(425,415,0) };


	bool a = false;

	enum {
		chara_red,
		chara_blue,
		chara_green,
		random,
		chara_yellow,
		chara_black
	};




	t2k::Sequence<Game_manager*> change_scene = t2k::Sequence<Game_manager*>(this, &Game_manager::title_play);



	
	int imgLoadGraph(std::string img_pas);
	void get_player2_pos(t2k::Vector3 get_playet_pos);
	//void hit_judge(Game_manager test,Game_manager test2,int shot_pos_x, int shot_pos_y, int shot_radius, int player_pos_x, int player_pos_y, int player_radius);
	void hit_judge(float deltatiem,Player* hit_bullet,Player* hit_player);
	void hit_sull(float deltatime);
	void bullet_judge(Player* main_player,Player* sub_player,float deltatime);
	void life_calculation(float deltatime,Player* get_hit_player,Player* get_hit_bullet);  //ÉâÉCÉtÇ∆HPÇÃåvéZÇÇ∑ÇÈä÷êî
	bool title_play(float deltatime);
	bool menyu_play(float deltatime);
	bool option_play(float deltatim);
	bool select_scene(float deltatime);
	bool battle_scene(float deltatime);
	bool eye_catch(float deltatime);
	void menyu_update(float deltatime);
	void menyu_draw(float deltatime);
	void update(float deltatime);
	void draw(float deltatime);
};



