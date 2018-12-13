#pragma once
#include <SFML\Graphics.hpp>
#include "animation.h"
#include "hero.h"
#include "solid.h"


class Map {
public:
	const int HEIGHT_MAP = 15; //ширина карты
	const int WIDTH_MAP = 20; //высота карты
	sf::String *TileMap; //массив карты
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;	
	std::vector <Solid*> list_solids; //лист плотных тел

	Map() {
		TileMap = new sf::String[HEIGHT_MAP];
		TileMap[ 0] = "0##################0";
		TileMap[ 1] = "<      x         x >";
		TileMap[ 2] = "<          .       >";
		TileMap[ 3] = "<          l  x    >";
		TileMap[ 4] = "< x        l       >";
		TileMap[ 5] = "<          l       >";
		TileMap[ 6] = "<   x      ,       >";
		TileMap[ 7] = "<     u            >";
		TileMap[ 8] = "<                  >";
		TileMap[ 9] = "<           x  u   >";
		TileMap[10] = "<       u          >";
		TileMap[11] = "<        x         >";
		TileMap[12] = "<                  >";
		TileMap[13] = "<           x      >";
		TileMap[14] = "0[________________]0";
		list_solids.push_back(new Solid(sf::Vector2f(300.0, 300.0), sf::Vector2f(12, 10), sf::Vector2f(18, 54), "tree.png"));
		list_solids.push_back(new Solid(sf::Vector2f(50.0, 20.0), sf::Vector2f(12, 10), sf::Vector2f(18, 54), "tree.png"));
		list_solids.push_back(new Solid(sf::Vector2f(500.0, 200.0), sf::Vector2f(12, 10), sf::Vector2f(18, 54), "tree.png"));
		list_solids.push_back(new Solid(sf::Vector2f(280.0 - 28, 90.0), sf::Vector2f(35, 10), sf::Vector2f(-2, 17), "fence.png"));
		list_solids.push_back(new Solid(sf::Vector2f(280.0, 90.0), sf::Vector2f(35, 10), sf::Vector2f(-2, 17), "fence.png"));
		list_solids.push_back(new Solid(sf::Vector2f(310.0, -30.0), sf::Vector2f(105, 46), sf::Vector2f(4, 81), "house.png"));

		//list_solids.push_back(new Solid(sf::Vector2f(90.0, 80.0), 0));
		//list_solids.push_back(new Solid(sf::Vector2f(512.0, 118.0), 1));

		list_solids.push_back(new Solid(sf::Vector2f(0, 0), sf::Vector2f(32 * WIDTH_MAP, 32)));
		list_solids.push_back(new Solid(sf::Vector2f(0, 0), sf::Vector2f(32, 32 * HEIGHT_MAP)));
		list_solids.push_back(new Solid(sf::Vector2f(0, (HEIGHT_MAP - 1) * 32), sf::Vector2f(32 * WIDTH_MAP, 32)));
		list_solids.push_back(new Solid(sf::Vector2f((WIDTH_MAP - 1) * 32, 0), sf::Vector2f(32, 32 * HEIGHT_MAP))); 
	}

	void draw_map(sf::RenderWindow& window_where, float time_where)
	{
		sf::Image map_image;
		map_image.loadFromFile("images/grass_and_stone.png");
		sf::Texture map;
		map.loadFromImage(map_image);
		sf::Sprite s_map;
		s_map.setTexture(map);

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
				if (TileMap[i][j] == 'u')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
				if ((TileMap[i][j] == 'x')) s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '[')) s_map.setTextureRect(sf::IntRect(0, 64, 32, 32));
				if ((TileMap[i][j] == ']')) s_map.setTextureRect(sf::IntRect(64, 64, 32, 32));
				if ((TileMap[i][j] == '_')) s_map.setTextureRect(sf::IntRect(32, 64, 32, 32));
				if ((TileMap[i][j] == '.')) s_map.setTextureRect(sf::IntRect(64, 32, 32, 32));
				if ((TileMap[i][j] == 'l')) s_map.setTextureRect(sf::IntRect(0, 32, 32, 32));
				if ((TileMap[i][j] == ',')) s_map.setTextureRect(sf::IntRect(32, 32, 32, 32));
				if ((TileMap[i][j] == '#')) s_map.setTextureRect(sf::IntRect(96, 64, 32, 32));
				if ((TileMap[i][j] == '<')) s_map.setTextureRect(sf::IntRect(32, 96, 32, 32));
				if ((TileMap[i][j] == '>')) s_map.setTextureRect(sf::IntRect(64, 96, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(sf::IntRect(96, 96, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window_where.draw(s_map);
			}
		for (size_t i = 0; i < list_solids.size(); i++)
		{
			if (list_solids[i] == NULL)
			{
				continue;
			}
			else
			{
				list_solids[i]->draw_solid(window_where, time_where);

			}
		}
	}

	bool check_solid(sf::Vector2f _coord) { //проверка: входит ли герой в плотное тело
		for (size_t i = 0; i < list_solids.size(); i++)
		{
			if (list_solids[i] == NULL) 
			{
				continue;
			}
			if (list_solids[i]->rectangle.getGlobalBounds().contains(_coord)) //contains проверяет входит ли точка в прямоугольник
			{
				return true;
			}
		}
		return false;
	};
};