#pragma once

#include <SFML/Graphics.hpp>

class Unit {
public:
	Unit() {};
	virtual ~Unit() {};
protected:
	
	float x; // ���������
	float y; //	�������

	int textureX;
	int textureY;

private:
	// general Tile map 
	static char** TileMap;
};
