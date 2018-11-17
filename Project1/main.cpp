//состояния игры
// процедура ходьбы
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h" 
#include "inventory.h"
#include "hero.h" 
#include <iostream>

sf::View view; //объявили sfml объект "вид", который и является камерой

void getplayercoordinateforview(float x, float y) { // функция для считывания координат игрока
	view.setCenter(x, y); // следим за игроком, передавая его координаты камеру
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1300, 700), "403++");
	view.reset(sf::FloatRect(0, 0, 650, 350));
//map рисовка
	sf::Image map_image;// объект изображения для карты
	map_image.loadFromFile("images/tile.png");// загружаем файл для карты
	sf::Texture map;// текстура карты
	map.loadFromImage(map_image);// заряжаем текстуру картинкой
	sf::Sprite s_map;// создаём спрайт для карты
	s_map.setTexture(map);// заливаем текстуру спрайтом
//inventory рисовка
	sf::Image inv_image;
	inv_image.loadFromFile("images/inventory.png");
	sf::Texture inv_texture;
	inv_texture.loadFromImage(inv_image);
	sf::Sprite sprite_inv;
	sprite_inv.setTexture(inv_texture);
//items
	sf::Image iitem;
	iitem.loadFromFile("images/items.png");
	sf::Texture titem;
	titem.loadFromImage(iitem);
	sf::Sprite sitem;
	sitem.setTexture(titem);
	sitem.setTextureRect(sf::IntRect(0, 0, 16, 16));



	sf::Clock clock; //привязка времени не к процессору, а к машинному времени
	double CurrentFrame = 0;//хранит текущий кадр

	Hero h("player.png", 150, 150, 16.0, 32.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение,
	//далее координата Х,У, ширина, высота.
	bool inventory_open = false;

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
//event инвентарь
			if (sf::Event::KeyPressed == event.type && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		
			sitem.setPosition((h.getplayercoordinateX() - inv_texture.getSize().x / 2) +125, (h.getplayercoordinateY() - inv_texture.getSize().y / 2)+11);

				if (inventory_open) {
					inventory_open = false;
				} else {
					inventory_open = true;
	
				}
			}
		}


//walk and stand
		bool pressed = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			h.dir = LEFT;
			h.speed = 0.1;
			CurrentFrame += 0.003 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			h.sprite.setTextureRect(sf::IntRect(16 * int(CurrentFrame) + 16, 64, -16, 31));
			getplayercoordinateforview(h.getplayercoordinateX(), h.getplayercoordinateY());
			pressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			h.dir = RIGHT;
			h.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			h.sprite.setTextureRect(sf::IntRect(16 * int(CurrentFrame), 64, 16, 31));
			getplayercoordinateforview(h.getplayercoordinateX(), h.getplayercoordinateY());
			pressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			h.dir = BOTTOM;
			h.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			h.sprite.setTextureRect(sf::IntRect(16 * int(CurrentFrame), 96, 16, 31));
			getplayercoordinateforview(h.getplayercoordinateX(), h.getplayercoordinateY());
			pressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			h.dir = TOP;
			h.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			h.sprite.setTextureRect(sf::IntRect(16 * int(CurrentFrame), 32, 16, 31));
			getplayercoordinateforview(h.getplayercoordinateX(), h.getplayercoordinateY());
			pressed = true;
		}
		if (!pressed) {
			h.dir = BOTTOM;
			h.speed = 0;
			CurrentFrame += 0.002 * time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			h.sprite.setTextureRect(sf::IntRect(16 * int(CurrentFrame), 0, 16, 31));
			getplayercoordinateforview(h.getplayercoordinateX(), h.getplayercoordinateY());
		}

		window.clear();

//draw map
		for (int i = 0; i < HEIGHT_MAP; i++){
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == 's')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));

				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		}
		
		h.update(time);
		window.draw(h.sprite); 
		sprite_inv.setPosition(h.getplayercoordinateX() - inv_texture.getSize().x/2, h.getplayercoordinateY() - inv_texture.getSize().y / 2);
		if (inventory_open) 
		{ 
			window.draw(sprite_inv);
			window.draw(sitem);
		}

		window.display(); 
		window.setView(view);
	}
	return 0;
}
