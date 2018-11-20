#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "animation.h"

void Hero::update(float time)
{

	switch (dir)//реализуем поведение в зависимости от направления.
	{
	case RIGHT:
		dx = speed;
		dy = 0;
		break;
	case LEFT:
		dx = -speed;
		dy = 0;
		break;
	case TOP:
		dx = 0;
		dy = speed;
		break;
	case BOTTOM:
		dx = 0;
		dy = -speed;
		break;
	}
	x += dx * time;
	y += dy * time;
	speed = 0;
	current_anim->sprite.setPosition(x, y);
}

float Hero::getplayercoordinateX() {
	return x;
}

float Hero::getplayercoordinateY() {
	return y;
}

Hero::Hero(float X, float Y) {
	x = X;
	y = Y;
	dx = 0;
	dy = 0;
	speed = 0;
	dir = LEFT;
	//new создать новый обьект в динамической память вернуть его указатель
	current_anim = new Animation("player.png", 4, 4, 0, false); 
}
