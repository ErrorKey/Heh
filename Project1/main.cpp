#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "tinyxml2.h" 
#include "inventory.h"
#include "hero.h" 
#include "item.h"
#include "view.h"
#include "map.h"
#include "dialog_window.h"
#include <iostream>

int main()
{

	sf::RenderWindow window(sf::VideoMode(view_width, view_height), "403++", sf::Style::Fullscreen);
	view.reset(sf::FloatRect(0, 0, view_width/2, view_height/2));

	Inventory inventory;
	Item item2(2);
	inventory.placeItem(item2);
	Item item0(0);
	inventory.placeItem(item0);
	sf::Clock clock; //�������� ������� �� � ����������, � � ��������� �������
	sf::Vector2f vect;
	Hero hero(150, 150);
	Map map;

	bool sost_inventory_open = false; //��������� ��������� ��������� 
	bool sost_null = true; //��������� �������� ������
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); // ������������� ������ � ����
		time = time / 1300; //�������� ����

		sf::Event event;
		window.setKeyRepeatEnabled(false); //��������� ��������� ����� ������� ��� ������� � ��������� �������
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
///������� ���������
			if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Tab) {
				if (sost_inventory_open) {
					sost_inventory_open = false;
					sost_null = true;
				} else {
					sost_inventory_open = true;
					sost_null = false;
				}
			}
			if (sf::Event::KeyPressed == event.type) {
				if (sost_inventory_open)
				{
					inventory.event_handle(event);
				}
			}
		}

///��������� "����"
		if (sost_null)
		{
			hero.event_handle();
		}

		getplayercoordinateforview(hero.getplayercoordinateX(), hero.getplayercoordinateY());	
		hero.update(time, map);
		inventory.cursor_ani->update(time);
		window.clear(sf::Color::Color(197,159,208,255));
		map.draw_map(window, time);
		window.draw(hero.current_anim->sprite);
		if (sost_inventory_open) 
		{ 
			inventory.drawinventory(sf::Vector2f(hero.getplayercoordinateX(), hero.getplayercoordinateY()), window);
		}
		window.display();
		window.setView(view);
	}
	return 0;
}	

//������� ���� �����
//������ ��������

//NPC: ������ ��� ������� X - �������
//������� ���-�� ���, ����� ���� ������ 
//������� ��� 