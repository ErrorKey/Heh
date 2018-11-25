//состояния игры
// процедура ходьбы
	// |-|-|-|-|-|
	// |0 1 2 3|4 
	// int a; <- переменная типа инт
	// int *b; <- адресс в памяти, по которому лежит переменная типа инт
	// class Imba { void Method(); 
	//				static int Seth(); };
	// Imba A;
	// Imba * B;
	// A.Method();
	// B->Method();
	// Imba::Seth();
//методы изменяют состояния обьектов
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "tinyxml2.h" 
#include "inventory.h"
#include "hero.h" 
#include "item.h"
#include <iostream>

sf::View view; //объявили sfml объект "вид", который и является камерой

void getplayercoordinateforview(float x, float y) { // функция для считывания координат игрока
	view.setCenter(x, y); // следим за игроком, передавая его координаты камеру
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1300, 700), "403++");
	view.reset(sf::FloatRect(0, 0, 650, 350));
	//window.setVerticalSyncEnabled(true); //вертикальная синхронизация

	Inventory inventory;
	Item item2(2);
	inventory.placeItem(item2);
	sf::Clock clock; //привязка времени не к процессору, а к машинному времени

	Hero hero(150, 150);
	Animation anim_0 ("player.png", 4, 4, 0, false);

	bool inventory_open = false; //состояние открытого инвентаря 
	bool sost_walk = true; //состояние движения игрока
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); // перезапускаем таймер с нуля
		time = time / 1300; //скорость игры

		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
//события инвентарь
			if (sf::Event::KeyPressed == event.type && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {

				if (inventory_open) {
					inventory_open = false;
					sost_walk = true;
				} else {
					inventory_open = true;
					sost_walk = false;
	
				}
			}
		}

//walk and stand
		bool pressed = false;
		if (sost_walk) {
			hero.current_anim = &anim_0;
			getplayercoordinateforview(hero.getplayercoordinateX(), hero.getplayercoordinateY());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				hero.dir = LEFT;
				hero.speed = 0.1;
				hero.current_anim = &anim_0;
				pressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				hero.dir = RIGHT;
				hero.speed = 0.1;
				hero.current_anim = &anim_0;
				pressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				hero.dir = BOTTOM;
				hero.speed = 0.1;
				hero.current_anim = &anim_0;
				pressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				hero.dir = TOP;
				hero.speed = 0.1;
				hero.current_anim = &anim_0;
				pressed = true;
			}
			if (!pressed) {
				hero.dir = BOTTOM;
				hero.speed = 0;
				hero.current_anim = &anim_0;

			}
		}
		window.clear();
		
		hero.update(time);
		window.draw(hero.current_anim->sprite);

		if (inventory_open) 
		{ 
			inventory.drawinventory(sf::Vector2f(hero.getplayercoordinateX(), hero.getplayercoordinateY()), window);
		}
		window.display(); 
		window.setView(view);
	}
	return 0;
}
//Взаимодействие с solid (плотными телами)
//Взаимодейтсвие с инвентарём
//диалоговое окно
//Различные реакции на нажатия кнопок в зависимости от состояния
//Массив с индексацией состояний
//