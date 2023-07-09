#pragma once
#include "units.h"

class Map {
public:
	Map() : background(nullptr), solidObjects(nullptr), unicObjects(nullptr) { }
	Map(char** charMap) {

	}
	Map(char const* fileName) {

	}
	void getBackground(size_t i, size_t j) {

	}
private:
	char** background = nullptr;
	char** solidObjects = nullptr; // solid, pipe, tap, teleport, coin, Creature. Взаимодействие с Creature в Creature::Collision
	Unit** unicObjects = nullptr;  // destructible, moving, boilingWater, raft, jet, valve

};