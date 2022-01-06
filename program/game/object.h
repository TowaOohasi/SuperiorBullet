#pragma once
#include "../library/t2klib.h"

class Object {
public:
	Object();
	virtual ~Object() {}
	t2k::Vector3 pos_;
	float speed_ = 0;
	bool is_alive_ = true;

	bool a = true;

	virtual void update(float deltatime) {}
	virtual void draw(float deltatime) {}
};