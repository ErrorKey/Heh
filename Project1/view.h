#pragma once
#include <SFML/Graphics.hpp>

sf::View view; //объ€вили sfml объект "вид", который и €вл€етс€ камерой

int view_height = 768 * 4 / 5; //высота экрана
int view_width =  1366 * 4 / 5; //ширина экрана

void getplayercoordinateforview(float x, float y) { // функци€ дл€ считывани€ координат игрока
	view.setCenter(x, y); // следим за игроком, передава€ его координаты камеру
}