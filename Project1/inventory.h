#pragma once
/*
 * 1. функци€ должна вз€ть список итемов в инвентаре
 * которые уже в нем есть и нарисовать их на экране
 * в пор€дке их €чеек
 * 2. она сначала отрисовывает на экране спрайт самого инвентар€
 * 3. !!!затем она в цикле проходит по списку €чеек
 * 4. дл€ каждой €чейки беретс€ вещь в ней и получаетс€ еЄ изображение
 * 5. вычисл€етс€ положение €чейки на экране
 * 6. изображение вещи рисуетс€ в этом положении!!!!
 */
#include <SFML/Graphics.hpp>
#include <vector>
#include "item.h"

class CellItem
{
public:
	sf::Vector2f coord; //2f вектор из двух коорд float
	bool cell_empty = true;
	int cell_number;
	Item *item;

	CellItem(int X, int Y) {
		coord.x = X;
		coord.y = Y;
	}
};

class Inventory
{
public:
	std::vector <CellItem> list_cells; // вектор вектор я„≈≈ 
	sf::Image image;
	sf::Texture texture;
	sf::Sprite inv_sprite;

	Inventory() {
		list_cells.push_back(CellItem(125, 11)); 
		// создать переменную типа ячейка (с координатами ) и запихнуть еЄ в вектор
		list_cells.push_back(CellItem(149, 11)); 
		// CellItem(x, y) - вызов конструктора, т.е. создание 
		// переменной типа CellItem по правилам, описанным в конструкторе
		list_cells.push_back(CellItem(172, 11));
		list_cells.push_back(CellItem(125, 34));
		list_cells.push_back(CellItem(149, 34));
		list_cells.push_back(CellItem(172, 34));
		list_cells.push_back(CellItem(125, 56));
		list_cells.push_back(CellItem(149, 56));
		list_cells.push_back(CellItem(172, 56));
	}

	void drawinventory(sf::Vector2f where_to_draw, sf::RenderWindow & window_where) {
		image.loadFromFile("images/inventory.png");
		texture.loadFromImage(image);
		inv_sprite.setTexture(texture);
		
		inv_sprite.setPosition(where_to_draw.x - texture.getSize().x / 2,
						   where_to_draw.y - texture.getSize().y / 2);
		window_where.draw(inv_sprite);


		for (size_t i = 0; i < 9; i++)
		{
			// list_cells - тип ¬≈ “ќ– с я„≈… јћ»
			// list_cells[0] - тип я„≈… ј
			if (!list_cells[i].cell_empty)
			{
				list_cells[i].cell_number;
				// вз€ть спрайт итема
				list_cells[i].item->sprite.setPosition(inv_sprite.getPosition() + list_cells[i].coord);
 				// поставить  в нужное место
				window_where.draw(list_cells[i].item->sprite);
			    // отрисовать в окне
			}
		}
	}

	 bool placeItem(Item &item) {
		//положить в €чейку инвентар€ предмет
		 // указать что она зан€та
		 for (size_t i = 0; i < 9; i++)
		 {
			 if (list_cells[i].cell_empty) {
				 list_cells[i].item = &item; 
				 list_cells[i].cell_empty = false;
				 return true;
			 }
		 }	
		 return false;
	}

};
/*

			void by_value(int i) { i = i + 1; }; передача параметров по значению (копирование)
			void by_ref(int &t)  { t = t + 1; };  передача параметров ссылкой

			void main () {
				int a = 5;
				by_value(a); // value - значение (англ.)
				print(a);
				by_ref(a); // ref - reference - ссылка (англ.)
				print(a);
			}
			*/
			// int y;
			// int * i; - указатель на int
			// int * const j; - посто€нный указатель на  int
			// int & z = y; - ссылка на int
			// y = 5;
			// z = 2;
			// print(y); - пишет 2, потому что и z и y это один и тот же "домик" в пам€ти
 // int a;
				 // int *b; секундк
				 // b = &a; вз€тие адреса (указател€ на) переменной(ую) 
				 // a = 2;
				 // *b = 5; // *b - разыменование указател€
				 // print(a) - выведет 5, потому что b указывает на a