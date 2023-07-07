#pragma once

#include <SFML/Graphics.hpp>

class Unit {
public:
	Unit() {};
	virtual ~Unit() {};
protected:
	
	int x; // начальная
	int y; //	позиция

	int textureX;
	int textureY;

private:
	// general Tile map 
	static char** TileMap;
};
