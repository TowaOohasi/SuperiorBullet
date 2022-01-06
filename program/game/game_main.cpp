#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_main.h"
#include "game_manager.h"
#include <time.h>

bool init = false;
Game_manager* game_manager_ = nullptr;
void gameMain(float deltatime) {

	if (!init) {
		game_manager_ = new Game_manager();
		game_manager_->initialize();
		init = true;
	}
	game_manager_->update(deltatime);
	game_manager_->draw(deltatime);
}


