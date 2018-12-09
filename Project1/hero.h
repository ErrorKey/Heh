#pragma once
#include "animation.h"
#include "map.h"
#include <SFML/Graphics.hpp>
#include <iostream>

enum Direction { //перечисление направленией
	RIGHT = 0,
	LEFT = 1,
	TOP = 2,
	BOTTOM = 3,
	CLOCK10 = 4,
	CLOCK2 = 5,
	CLOCK4 = 6,
	CLOCK7 = 7
};
class Hero {
public:
	float x, y; //координаты x,y героя
	bool sost_life; //состояние жизни игрока
	float w, height, dx, dy, speed; //координаты игрока х и у, высота ширина, ускорение (по х и по у)
	Direction dir; //направление (direction) движения игрока
	Animation * current_anim;
	Animation * anim_hero_0;
	Animation * anim_hero_down;
	Animation * anim_hero_right;
	Animation * anim_hero_left;
	Animation * anim_hero_up;

	Animation * anim_npc_1;
	Animation * anim_npc_2;

	Hero(float X, float Y) {
		x = X;
		y = Y;
		dx = 0;
		dy = 0;
		speed = 0;
		dir = LEFT;
		sost_life = true;

		anim_hero_0 = new Animation("hero.png", 4, 4, 0, false);
		anim_hero_down = new Animation("hero.png", 4, 4, 1, false);
		anim_hero_right = new Animation("hero.png", 4, 4, 2, false);
		anim_hero_left = new Animation("hero.png", 4, 4, 2, true);
		anim_hero_up = new Animation("hero.png", 4, 4, 3, false);
		current_anim = anim_hero_0;
	}

	void update(float time, Map & map) //реализуем направление и ходьбу
	{
		switch (dir)
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
		case CLOCK10:
			dx = -(pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			dy = -(pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			break;
		case CLOCK2:
			dx = (pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			dy = -(pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			break;
		case CLOCK4:
			dx = (pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			dy = (pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			break;
		case CLOCK7:
			dx = -(pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			dy = (pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			break;
		}

		x += dx * time;
		y += dy * time;
		speed = 0;
		if (map.check_solid(sf::Vector2f(x,y))) 
		{
			x -= dx * time;
			y -= dy * time;
		}
		current_anim->sprite.setPosition(x- 8, y-32); //смещаем центр персонажа из левого верхнего угла, в "центр" нижнего, для адекватного столкновения с прямоугольниками
		current_anim->update(time);
	}

	float getplayercoordinateX() {
		return x;
	}

	float getplayercoordinateY() {
		return y;
	}
	void event_handle() //движение персонажа
	{

		bool pressed = false;
		if (sost_life) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				dir = LEFT;
				speed = 0.1;
				current_anim = anim_hero_left;
				pressed = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
					dir = CLOCK10;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
					dir = CLOCK7;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				dir = RIGHT;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
					dir = CLOCK2;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
					dir = CLOCK4;
				};
				speed = 0.1;
				current_anim = anim_hero_right;
				pressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				current_anim = anim_hero_up;
				dir = BOTTOM;
				speed = 0.1;
				pressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				dir = TOP;
				speed = 0.1;
				current_anim = anim_hero_down;
				pressed = true;
			}
			if (!pressed) {
				dir = BOTTOM;
				speed = 0;
				current_anim = anim_hero_0;

			}
		}
	}
};

