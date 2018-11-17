#pragma once
enum Direction { //перечисление 
	RIGHT = 0,
	LEFT = 1,
	TOP = 2,
	BOTTOM = 3
};
class Hero {
private:
	float x, y;
public:
	float w, height, dx, dy, speed; //координаты игрока х и у, высота ширина, ускорение (по х и по у)
	Direction dir; //направление (direction) движения игрока
	sf::String File; //файл с расширением
	sf::Image image;// изображение
	sf::Texture texture;// текстура
	sf::Sprite sprite;// спрайт

	void update(float time);
	Hero(sf::String F, float X, float Y, float W, float H);
	float getplayercoordinateX();
	float getplayercoordinateY();
};