#pragma once

#include <SFML/Graphics.hpp>

class Unit {
public:
	//Unit() {};
	virtual ~Unit() {};
	virtual void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {}; // �������� � ����� �� �����
	sf::Sprite getSprite() {}; // ��������� ������� ��� ������ �� �������
protected:
	
	float x; // ���������
	float y; //	�������
	sf::FloatRect rect; //left, top, wigth, height
	sf::Sprite sprite;
	float currentFrame;
private:
	// general Tile map 
	static char** TileMap;
};
