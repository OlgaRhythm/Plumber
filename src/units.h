#pragma once

#include <SFML/Graphics.hpp>

class Unit {
public:
	Unit() {};
	virtual ~Unit() {};
protected:
	
	float x; // начальная
	float y; //	позиция

private:
	// general Tile map 
	static char** TileMap;
};
