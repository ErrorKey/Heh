#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
class Solid //плотное тело
{
public:
	//Создать список текстур, например, дерева с уже описанным прямоугольником
	sf::Vector2f coord; //координаты обьектов в пространстве
	sf::RectangleShape rectangle; //"прямоугольник" плотного объекта
	Animation *animation;
	Solid(sf::Vector2f _coord, sf::Vector2f size_rectangle, sf::Vector2f offset_rectangle, sf::String file) { //для тел без анимации
		coord = _coord;
		animation = new Animation(file, 1, 1, 0, false);
		rectangle.setSize(size_rectangle);
		//rectangle.setSize(sf::Vector2f(animation->texture.getSize()));
		rectangle.setPosition(coord + offset_rectangle);
		animation->sprite.setPosition(coord);
	}
	Solid(sf::Vector2f _coord, int num_of_line) { //для NPC
		coord = _coord;
		sf::Vector2f offset(3, 28);
		animation = new Animation("npc.png", 2, 2, num_of_line, false);
		rectangle.setSize(sf::Vector2f(10, 5));
		rectangle.setPosition(coord + offset);
		animation->sprite.setPosition(coord);
	}

	Solid(sf::Vector2f _coord, sf::Vector2f _size) { //для "НЕВИДИМЫХ" тел
		coord = _coord;
		animation = new Animation("0.png", 1, 1, 0, false);
		rectangle.setSize(_size);
		rectangle.setPosition(coord);
		animation->sprite.setPosition(coord);
	}

	void draw_solid(sf::RenderWindow & window_where, float time_where) {
		window_where.draw(animation->sprite);
		animation->update(time_where / 2);
		//window_where.draw(rectangle); //посмотреть solids
	}
};
