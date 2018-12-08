#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "tinyxml2.h"
#include <iostream>

class Item
{
public:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	int const item_spritelist_wigth = 5; // ширина карты вещей в текстурах
	int const item_size = 16; // ширина вещи в пикселях
	int id;
	std::string name;
	std::string info;


	Item(int ID)
	{
		id = ID;
		image.loadFromFile("images/items.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		int x = 16 * (ID % item_spritelist_wigth);
		int y = 16 * (ID / item_spritelist_wigth);
		sprite.setTextureRect(sf::IntRect(x, y, item_size, item_size));
		infoItem(ID);
	}

	void infoItem(int ID) {
		using namespace tinyxml2;
		XMLDocument doc;
		doc.LoadFile("items.txt");
		XMLNode* root = doc.FirstChild(); //входим в главный тег
		XMLElement* item_root = root->FirstChildElement("item");
		while (item_root != NULL)
		{
			int id_from_xml = std::stoi(item_root->FirstChildElement("id")->GetText());
			if (id_from_xml == id) {
				name = item_root->FirstChildElement("name")->GetText();
				info = item_root->FirstChildElement("info")->GetText();
			}
			item_root = item_root->NextSiblingElement("item");
		}

	}
};	  

