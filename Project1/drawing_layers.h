#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

extern std::vector <sf::Drawable *> draw_layers;

	void place_to_draw(sf::Vector2f _coord, sf::Drawable* sprite_draw, int num_layer) {
		float Y = _coord.y;
		draw_layers[num_layer] = sprite_draw;
		if (true)
		{

		}
	}

// 0 - ���
// 1 - �����
// 2, 3 - �����, ���������
// 4 - ���������
// 5 - �������� ���������
// 6 - ������ ���������
// 7 - ���������� ����
// 8 - ����� ����

//place_to_draw(sf::Vector(0,0), &Sprite, 1);
//windows.draw(draw_layers[i])