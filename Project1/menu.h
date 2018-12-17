#include <SFML/Graphics.hpp>
#include "view.h"
#include "state.h"
#pragma once
class Menu
{
public:
	sf::RectangleShape rectangle;
	sf::Text text1;
	sf::Text text2;
	int current_cursor = 0;
	float current_view_height = view_height;
	float current_view_width = view_width;
	sf::Vector2f current_view_center;
	Menu()
	{
		text1.setFillColor(sf::Color::White);
		text2.setFillColor(sf::Color::Color(50, 50, 50, 255));
	};

	void get_center_view(sf::Vector2f center_view) {
		current_view_center = center_view;
	}



	void event_handle(sf::Event& event, enum state& current_state, sf::RenderWindow& window) {
		if (event.key.code == sf::Keyboard::Up) {
			current_cursor--;
			if (current_cursor == 0)
			{
				text1.setFillColor(sf::Color::White);
				text2.setFillColor(sf::Color::Color(50, 50, 50, 255));
			}
			if (current_cursor < 0) current_cursor = 0;
		}
		if (event.key.code == sf::Keyboard::Down) {
			current_cursor++;
			if (current_cursor == 1)
			{
				text2.setFillColor(sf::Color::White);
				text1.setFillColor(sf::Color::Color(50, 50, 50, 255));
			}
			if (current_cursor > 1) current_cursor = 1;
		}
		if (event.key.code == sf::Keyboard::Enter) {
			switch (current_cursor)
			{
			case 0:
				current_state = NORM;
				break;
			case 1:
				window.close();
				break;
			}
		}
	}
	void draw_menu(sf::RenderWindow &window) {

		rectangle.setSize(sf::Vector2f(current_view_height, current_view_width));
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setPosition(current_view_center + sf::Vector2f((-0.5) * current_view_height, (-0.5) * current_view_width));

		sf::Font font;
		font.loadFromFile("fonts/9041.ttf");

		text1.setFont(font);
		text2.setFont(font);

		text1.setString("GAME");
		text2.setString("EXIT");

		text1.setCharacterSize(50);
		text2.setCharacterSize(50);

		text1.setPosition(rectangle.getPosition() + sf::Vector2f(rectangle.getSize().x * 0.44, rectangle.getSize().y * 0.45));
		text2.setPosition(rectangle.getPosition() + sf::Vector2f(rectangle.getSize().x * 0.44, rectangle.getSize().y * 0.50));

		window.draw(rectangle);
		window.draw(text1);
		window.draw(text2);
	}
};
