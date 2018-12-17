#pragma once

#include <SFML/Graphics.hpp>
#include "solid.h"
#include "dialog_window.h"
#include "tinyxml2.h"
#include "drawing_layers.h"

class Npc
{
public:
	int id; //id npc
	int num_text = 0; //номер текста
	sf::Vector2f coord; //координаты npc
	
	const float rad = 30;
	Animation * animation; //анимация и отрисовка npc
	DialogOkno dialog_okno;
	sf::CircleShape circle; //обьект "радиуса" взаимодействия с npc

	std::string name;
	std::vector<std::string> text;


	Npc(int _id, sf::Vector2f _coord)
	{
		id = _id;
		coord = _coord;
		animation = new Animation("npc.png", 2, 2, id, false);
		circle.setRadius(rad);
		load_text_npc(id);
	}

	void draw_npc (float _time, sf::RenderWindow &_window)
	{
		animation->update(_time);
		animation->sprite.setPosition(coord);
		circle.setPosition(coord - sf::Vector2f(rad / 2, rad / 2));
		//_window.draw(circle);
		enqueue_drawable(&animation->sprite, coord.y);
		//_window.draw(animation->sprite);
	}

	void draw_npc_text(sf::RenderWindow &_window, sf::Vector2f _coord_text) {
		dialog_okno.set_text(name + '\n' + text[num_text]);
		dialog_okno.show_text(_coord_text, _window);
	}

	void load_text_npc(int _id) { 
		using namespace tinyxml2;
		XMLDocument doc;
		doc.LoadFile("texts/npc.txt");
		XMLNode* root = doc.FirstChild(); //входим в главный тег
		XMLElement* item_root = root->FirstChildElement("npc");
		while (item_root != NULL)
		{
			int id_from_xml = std::stoi(item_root->FirstChildElement("id")->GetText());
			if (id_from_xml == id) {
				name = item_root->FirstChildElement("name")->GetText();
				text.push_back("DUMMY_TEXT");
				text.push_back(item_root->FirstChildElement("text")->GetText());
				text.push_back(item_root->FirstChildElement("text")->NextSiblingElement("text")->GetText());
				text.push_back(item_root->FirstChildElement("text")->NextSiblingElement("text")->NextSiblingElement("text")->GetText());
				text.push_back(item_root->FirstChildElement("text")->NextSiblingElement("text")->NextSiblingElement("text")->NextSiblingElement("text")->GetText());
			}
			item_root = item_root->NextSiblingElement("npc");
		}
	}
};
class NpcSpace {
public:
	std::vector <Npc *> list_npc;
	int current_npc = -1;
	
	NpcSpace() {
		list_npc.push_back(new Npc(0, sf::Vector2f(90.0, 80.0)));
		list_npc.push_back(new Npc(1, sf::Vector2f(512.0, 118.0)));
	}

	int check_id(sf::Vector2f _coord_hero) {
		int result = -1;
		for (int i = 0; i != list_npc.size(); ++i) {
			if (list_npc[i]->circle.getGlobalBounds().contains(_coord_hero)) {
				result = i;
			}
		}
		current_npc = result;
		if (-1 != result) {
			list_npc[current_npc]->num_text += 1;
			if (list_npc[current_npc]->num_text > 4) {
				list_npc[current_npc]->num_text = 1;
			}
		}
		return result;
	}
	void draw_npcs(float time, sf::RenderWindow &window) {
		for (int i = 0; i != list_npc.size(); ++i) {
			list_npc[i]->draw_npc(time, window);
		}
	}
};
