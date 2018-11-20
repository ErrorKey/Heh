#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	double current_frame;
	float width, hieght;
	bool flip;
	int num_fr, num_line;

	Animation(sf::String File, int num_frames, int line_frames, int num_of_line , bool flip_hor) {
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		hieght = texture.getSize().x / num_frames;
		width = texture.getSize().y / line_frames;
		flip_hor = flip;
		num_frames = num_fr;
		num_of_line = num_line;

	}
	void update(float time) {
		current_frame += 0.005 * time;
		if (!flip)
		{
			if (current_frame > num_fr) { current_frame -= num_fr; }
			sprite.setTextureRect(sf::IntRect(hieght*current_frame, width*num_line, hieght, width));
		}
		else
			sprite.setTextureRect(sf::IntRect(hieght*current_frame + hieght, width*num_line, -hieght, width));
}
};