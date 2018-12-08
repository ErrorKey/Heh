#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "item.h"
#include "animation.h"
#include "dialog_window.h"

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
	std::vector <CellItem> list_cells; // вектор я„≈≈ 
	sf::Image image;
	sf::Texture texture;
	sf::Sprite inv_sprite;
	int current_cursor = 0;
	Animation* cursor_ani;
	DialogOkno dialog_okno;

	Inventory() { 
		list_cells.push_back(CellItem(125, 11)); 
		list_cells.push_back(CellItem(149, 11)); 
		list_cells.push_back(CellItem(172, 11));
		list_cells.push_back(CellItem(125, 34));
		list_cells.push_back(CellItem(149, 34));
		list_cells.push_back(CellItem(172, 34));
		list_cells.push_back(CellItem(125, 56));
		list_cells.push_back(CellItem(149, 56));
		list_cells.push_back(CellItem(172, 56));
		cursor_ani = new Animation("cursor_inv.png",2,1,0,false);
		cursor_ani->sprite.setPosition(inv_sprite.getPosition() + list_cells[current_cursor].coord - sf::Vector2f(1, 1));
	}

	void drawinventory(sf::Vector2f where_to_draw, sf::RenderWindow & window_where) {
		image.loadFromFile("images/inventory.png");
		texture.loadFromImage(image);
		inv_sprite.setTexture(texture);
		
		inv_sprite.setPosition(where_to_draw.x - texture.getSize().x / 2,
						   where_to_draw.y - texture.getSize().y / 2);

		cursor_ani->sprite.setPosition(inv_sprite.getPosition() + list_cells[current_cursor].coord - sf::Vector2f(1, 1));
		
		if (!list_cells[current_cursor].cell_empty) {
			dialog_okno.set_text(list_cells[current_cursor].item->name + '\n' + list_cells[current_cursor].item->info);
			dialog_okno.show_text(where_to_draw, window_where);
		}

		window_where.draw(inv_sprite);
		window_where.draw(cursor_ani->sprite);


		for (size_t i = 0; i < 9; i++)
		{
			if (!list_cells[i].cell_empty)
			{
				list_cells[i].cell_number;
				list_cells[i].item->sprite.setPosition(inv_sprite.getPosition() + list_cells[i].coord);
				window_where.draw(list_cells[i].item->sprite);
			}
		}
	}

	 bool placeItem(Item &item) {
		 for (size_t i = 0; i < 9; i++)
		 {
			 if (list_cells[i].cell_empty) 
			 {
				 list_cells[i].item = &item; 
				 list_cells[i].cell_empty = false;
				 return true;
			 }
		 }	
		 return false;
	}
	 void event_handle(sf::Event& event) { //event дл€ проверки кака€ клавиша была нажата
		 if (event.key.code == sf::Keyboard::Left) { //если была
			 current_cursor--;
			 if (current_cursor < 0)
			 {
				 current_cursor = 8;
			 }
		 }
		 if (event.key.code == sf::Keyboard::Right) {
			 current_cursor++;
			 if (current_cursor > 8)
			 {
				 current_cursor = 0;
			 }
		 }
		 if (event.key.code == sf::Keyboard::Up) {
			 current_cursor = current_cursor - 3;
			 if (current_cursor < 0) 
			 { 
				 current_cursor = current_cursor + 9; 
			 }
		 }		
		 if (event.key.code == sf::Keyboard::Down) {
			 current_cursor = current_cursor + 3;
			 if (current_cursor > 8)
			 {
				 current_cursor = current_cursor - 9;
			 }
		 }
		 cursor_ani->sprite.setPosition(inv_sprite.getPosition() + list_cells[current_cursor].coord - sf::Vector2f(1, 1));
		 }
};
