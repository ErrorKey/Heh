#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	double current_frame = 0;
	float width, hieght;
	bool flip;
	int num_fr, num_line;

	Animation(sf::String File, int sum_colums, int sum_lines, int num_of_line , bool flip_hor) {
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		hieght = texture.getSize().x / sum_colums;
		width = texture.getSize().y / sum_lines;
		flip =  flip_hor;
		num_fr =  sum_colums;
		num_line =  num_of_line;
		sprite.setTextureRect(sf::IntRect(0, width*num_line, hieght, width));

	}
	void update(float time) {
		current_frame += 0.005 * time;
		if (!flip)
		{
			if (current_frame > num_fr) { current_frame -= num_fr; }
			sprite.setTextureRect(sf::IntRect(hieght*(int)current_frame, width*num_line, hieght, width));
		}
		else
		{
			if (current_frame > num_fr) { current_frame -= num_fr; }
			sprite.setTextureRect(sf::IntRect(hieght*(int)current_frame + hieght, width*num_line, -hieght, width));
		}
}
};