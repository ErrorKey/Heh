#pragma once
/*
 * 1. ������� ������ ����� ������ ������ � ���������
 * ������� ��� � ��� ���� � ���������� �� �� ������
 * � ������� �� �����
 * 2. ��� ������� ������������ �� ������ ������ ������ ���������
 * 3. !!!����� ��� � ����� �������� �� ������ �����
 * 4. ��� ������ ������ ������� ���� � ��� � ���������� � �����������
 * 5. ����������� ��������� ������ �� ������
 * 6. ����������� ���� �������� � ���� ���������!!!!
 */
#include <SFML/Graphics.hpp>
#include <vector>
#include "item.h"

class CellItem
{
public:
	sf::Vector2f coord; //2f ������ �� ���� ����� float
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
	std::vector <CellItem> list_cells; // ������ ������ �����
	sf::Image image;
	sf::Texture texture;
	sf::Sprite inv_sprite;

	Inventory() {
		list_cells.push_back(CellItem(125, 11)); 
		// ������� ���������� ���� ������ (� ������������ ) � ��������� � � ������
		list_cells.push_back(CellItem(149, 11)); 
		// CellItem(x, y) - ����� ������������, �.�. �������� 
		// ���������� ���� CellItem �� ��������, ��������� � ������������
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
			// list_cells - ��� ������ � ��������
			// list_cells[0] - ��� ������
			if (!list_cells[i].cell_empty)
			{
				list_cells[i].cell_number;
				// ����� ������ �����
				list_cells[i].item->sprite.setPosition(inv_sprite.getPosition() + list_cells[i].coord);
 				// ���������  � ������ �����
				window_where.draw(list_cells[i].item->sprite);
			    // ���������� � ����
			}
		}
	}

	 bool placeItem(Item &item) {
		//�������� � ������ ��������� �������
		 // ������� ��� ��� ������
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

			void by_value(int i) { i = i + 1; }; �������� ���������� �� �������� (�����������)
			void by_ref(int &t)  { t = t + 1; };  �������� ���������� �������

			void main () {
				int a = 5;
				by_value(a); // value - �������� (����.)
				print(a);
				by_ref(a); // ref - reference - ������ (����.)
				print(a);
			}
			*/
			// int y;
			// int * i; - ��������� �� int
			// int * const j; - ���������� ��������� ��  int
			// int & z = y; - ������ �� int
			// y = 5;
			// z = 2;
			// print(y); - ����� 2, ������ ��� � z � y ��� ���� � ��� �� "�����" � ������
 // int a;
				 // int *b; �������
				 // b = &a; ������ ������ (��������� ��) ����������(��) 
				 // a = 2;
				 // *b = 5; // *b - ������������� ���������
				 // print(a) - ������� 5, ������ ��� b ��������� �� a