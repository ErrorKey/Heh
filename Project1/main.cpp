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
#include "npc.h"
#include "drawing_layers.h"
#include "menu.h"
#include "state.h"

std::multimap <int, sf::Sprite *> draw_layers;

enum state current_state;

int main()
{
	sf::RenderWindow window(sf::VideoMode(view_width, view_height), "Anyway"/*, sf::Style::Fullscreen*/);
	view.reset(sf::FloatRect(0, 0, view_width/2, view_height/2));

	Inventory inventory;
	Item item2(2);
	inventory.placeItem(item2);
	Item item0(0);
	inventory.placeItem(item0);
	Item item1(1);
	inventory.placeItem(item1);
	sf::Clock clock; //привязка времени не к процессору, а к машинному времени
	sf::Vector2f vect;
	Hero hero(150, 150);
	Map map;
	
	NpcSpace npcspase;
	Menu menu;

	current_state = MENU;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); // перезапускаем таймер с нуля
		time = time / 1300; //скорость игры

		sf::Event event;
		window.setKeyRepeatEnabled(false); //запрещает создавать много событий при нажатии и удержании клавиши
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Tab) {
				if (current_state == INVENTORY) {
					current_state = NORM;
				} else {
					current_state = INVENTORY;
				}
			}
			
			if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Escape) {
				if (current_state == MENU) {
					current_state = NORM;
				}
				else {
					current_state = MENU;
				}
			}
			if (sf::Event::KeyPressed == event.type) {
				if (current_state == MENU)
				{
					menu.event_handle(event, current_state, window);
				}
			}
			if (sf::Event::KeyPressed == event.type) {
				if (current_state == INVENTORY)
				{
					inventory.event_handle(event);
				}
			}
			if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::X) {
				if (current_state == DIALOG) {
					current_state = NORM;
				}
				else {
					current_state = DIALOG;
				}
			}
			if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::X) {
				if (current_state == DIALOG)
				{
					int res = npcspase.check_id(sf::Vector2f(hero.x, hero.y));
					if (-1 == res)
						current_state = NORM;
				}
			}
			
		}

///СОСТОЯНИЕ "ИГРЫ"
		if (current_state == NORM)
		{
			hero.event_handle(); // передвижение героя
		}

		getplayercoordinateforview(hero.getplayercoordinateX(), hero.getplayercoordinateY());	
		menu.get_center_view(sf::Vector2f(hero.getplayercoordinateX(), hero.getplayercoordinateY()));
		hero.update(time, map);
		inventory.cursor_ani->update(time);
		window.clear(sf::Color::Color(197,159,208,255));
		map.draw_map(window, time);
		enqueue_drawable(&hero.current_anim->sprite, hero.getplayercoordinateY());
		npcspase.draw_npcs(time, window);

		draw_queue(window);
		
		if (current_state == INVENTORY) 
		{ 
			inventory.drawinventory(sf::Vector2f(hero.getplayercoordinateX(), hero.getplayercoordinateY()), window);
		}
		if (current_state == DIALOG)
		{
			if (-1 != npcspase.current_npc) {
				npcspase.list_npc[npcspase.current_npc]->draw_npc_text(window, sf::Vector2f(hero.getplayercoordinateX(), hero.getplayercoordinateY()));
			}
		}
		if (current_state == MENU)
		{
			menu.draw_menu(window);
		}
		window.display();
		window.setView(view);
		draw_layers.clear();
	}
	return 0;
}	