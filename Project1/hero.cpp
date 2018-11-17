#include <SFML/Graphics.hpp>
#include "Hero.h"


	void Hero::update(float time)
	{

		switch (dir)//реализуем поведение в зависимости от направлени€.
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
		sprite.setPosition(x, y);
	}

	float Hero::getplayercoordinateX() {
		return x;
	}
	float Hero::getplayercoordinateY() {
		return y;
	}

	Hero::Hero(sf::String F, float X, float Y, float W, float H) {
		dx = 0;
		dy = 0;
		speed = 0;
		dir = LEFT;
		File = F; 
		w = W;
		height = H; 
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(sf::IntRect(0, 0, w, height)); //«адаем спрайту один пр€моугольник дл€ вывода одного персонажа
	}
/*		case 4: dx = -(pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13; dy = -(pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			break;
		case 5:dx = (pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13; dy = -(pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			break;
		case 6:
			dx = (pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			dy = (pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			break;
		case 7:
			dx = -(pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			dy = (pow(pow(speed, 2) + pow(speed, 2), 1 / 2)) / 13;
			break;
			*/