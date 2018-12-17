#pragma once
#include <SFML/Graphics.hpp>
#include <map>

extern std::multimap <int,sf::Sprite *> draw_layers;

void enqueue_drawable( sf::Sprite* sprite_draw, int num_layer) {
		draw_layers.insert(std::pair<int, sf::Sprite *>(num_layer, sprite_draw));
	}

void draw_queue(sf::RenderWindow &window) {
	for (auto it = draw_layers.begin(); it != draw_layers.end(); ++it)///вывод на экран
	{
		window.draw(*it->second);
	}
}



