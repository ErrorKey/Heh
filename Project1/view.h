#pragma once
#include <SFML/Graphics.hpp>

sf::View view; //�������� sfml ������ "���", ������� � �������� �������

int view_height = 768 * 4 / 5; //������ ������
int view_width =  1366 * 4 / 5; //������ ������

void getplayercoordinateforview(float x, float y) { // ������� ��� ���������� ��������� ������
	view.setCenter(x, y); // ������ �� �������, ��������� ��� ���������� ������
}