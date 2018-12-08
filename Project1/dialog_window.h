#pragma once
#include <SFML/Graphics.hpp>
#include "item.h"
#include "view.h"
#include <string>
#include <iostream>

class DialogOkno
{
public:
	std::string current_text; //текущий текст
	
	void set_text(std::string str) {
		current_text = str;
	}

	void show_text(sf::Vector2f center_view, sf::RenderWindow & window_where) 
	{
		float current_view_height = view_height / 2.0;
		float current_view_width = view_width / 2.0;
		sf::RectangleShape rectangle(sf::Vector2f(current_view_width, current_view_height / 4));
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setPosition(center_view + sf::Vector2f( (-0.5) * current_view_width , (0.25) * current_view_height));

		sf::Text text;

		sf::Font font;
		if (!font.loadFromFile("OpenSans.ttf"))
		{
			std::cout << "ERROR FONT";
		}
		text.setFont(font);
		text.setString(current_text);
		text.setCharacterSize(20); 
		text.setFillColor(sf::Color::White);
		text.setPosition(rectangle.getPosition() + sf::Vector2f(rectangle.getSize().x * 0.05, rectangle.getSize().y * 0.05));

		window_where.draw(rectangle);
		window_where.draw(text);
	};
};


