#pragma once
enum Direction { //������������ 
	RIGHT = 0,
	LEFT = 1,
	TOP = 2,
	BOTTOM = 3
};
class Hero {
private:
	float x, y;
public:
	float w, height, dx, dy, speed; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �)
	Direction dir; //����������� (direction) �������� ������
	sf::String File; //���� � �����������
	sf::Image image;// �����������
	sf::Texture texture;// ��������
	sf::Sprite sprite;// ������

	void update(float time);
	Hero(sf::String F, float X, float Y, float W, float H);
	float getplayercoordinateX();
	float getplayercoordinateY();
};