#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include <time.h>
#include<list>
#include<math.h>
#include "field.h"

Field::Field() {
	pos_ = { 0,0,0 };
	pos_2 = { 1280,0,0 };
}


void Field::update(float deltatime) {
	pos_.x += deltatime;
	pos_2.x -= deltatime;

	
}


void Field::draw(float deltatime) {

}