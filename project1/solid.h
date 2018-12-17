#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "drawing_layers.h"
class Solid //плотное тело
{
public:
	sf::Vector2f coord; //координаты обьектов в пространстве
	sf::RectangleShape rectangle; //"прямоугольник" плотного объекта
	Animation *animation;
	sf::Vector2f offset;

	Solid(sf::Vector2f _coord, sf::Vector2f size_rectangle, sf::Vector2f offset_rectangle, sf::String file) { //для тел без анимации
		coord = _coord;
		offset = offset_rectangle + coord;
		animation = new Animation(file, 1, 1, 0, false);
		rectangle.setSize(size_rectangle);
		rectangle.setPosition(offset);
		animation->sprite.setPosition(coord);
	}
	Solid(sf::Vector2f _coord, int num_of_line) { //для NPC
		coord = _coord;
		sf::Vector2f _offset(0, 16);
		offset = _offset + _coord;
		animation = new Animation("npc.png", 2, 2, num_of_line, false);
		rectangle.setSize(sf::Vector2f(16, 16));
		rectangle.setPosition(offset);
		animation->sprite.setPosition(coord);
	}

	Solid(sf::Vector2f _coord, sf::Vector2f _size) { //для "НЕВИДИМЫХ" тел
		coord = _coord;
		offset = coord;
		animation = new Animation("0.png", 1, 1, 0, false);
		rectangle.setSize(_size);
		rectangle.setPosition(offset);
		animation->sprite.setPosition(coord);
	}

	void draw_solid(sf::RenderWindow & window_where, float time_where) {
		enqueue_drawable(&animation->sprite, offset.y);
		animation->update(time_where / 2);
		//window_where.draw(rectangle); //посмотреть solids
	} 
	void move_solid(sf::Vector2f(_coord)) {
		offset -= coord;
		coord = _coord;
		offset += coord;
		//rectangle.setPosition(offset);
	};
};