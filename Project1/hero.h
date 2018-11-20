#pragma once
#include "animation.h"

enum Direction { //перечисление 
	RIGHT = 0,
	LEFT = 1,
	TOP = 2,
	BOTTOM = 3
};
class Hero {
private:
	float x, y;
public:
	float w, height, dx, dy, speed; //координаты игрока х и у, высота ширина, ускорение (по х и по у)
	Direction dir; //направление (direction) движения игрока

	Animation *current_anim;

	void update(float time);
	Hero(float X, float Y);
	float getplayercoordinateX();
	float getplayercoordinateY();
};