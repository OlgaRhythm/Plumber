#pragma once

#include <SFML/Graphics.hpp>

class Unit {
public:
	Unit() {};
	virtual ~Unit() {};
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
