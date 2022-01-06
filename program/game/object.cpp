#include "object.h"
#include "game_manager.h"

extern Game_manager* game_manager_;

Object::Object() {
	game_manager_->object_.emplace_back(this);
}
