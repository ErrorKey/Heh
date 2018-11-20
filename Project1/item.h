#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "tinyxml2.h"

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

	/*
	открываем xml
	находим нужный предмет
	запихиваем значение его тегов в параметры Item
	*/
	void infoItem(int ID) {
		using namespace tinyxml2;
		XMLDocument doc;
		doc.LoadFile("items.txt");
		XMLNode* root = doc.FirstChild(); //входим в главный тег
		//if (!root) return;
		XMLElement* item_root = root->FirstChildElement("item");
		//if (!item_root) return;
		while (item_root != NULL)
		{
			int id_from_xml = std::stoi(item_root->FirstChildElement("id")->GetText());
			if (id_from_xml == id) {
				name = item_root->FirstChildElement("name")->GetText();
				info = item_root->FirstChildElement("info")->GetText();
			}
			item_root = root->NextSiblingElement("item");
		}

	}
};	  
/* 
<?xml version="1.0" encoding="utf-8"?>
<items_list>
	<item>
		<id>0</id>
		<name>pipiska</name>
		<info>long</name>
	</item>

	<item>
		<id>1</id>
		<name>ass</name>
		<info>sweet</name>
	</item>
</items_list>
*/
