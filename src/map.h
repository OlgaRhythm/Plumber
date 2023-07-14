#pragma once
#include "units.h"
#include "creatures.h"
// 5 карт
class Map {
public:
	Map(char** charMap) {

	}
	Map(char const* fileName) {

	}

	bool showMap() {

	}

private:
	Map() {}
	Plumber* player; // указатель на игрока
	int player_x, player_y; //в каких координатах должен появиться персонаж
	char color = 0; // 0 - Black, 1 - Blue
	char** backgroundAndSolid = nullptr; // backgroung и solid (pipe, tap); неизменяемый
	char** solidObjects = nullptr; // coin, destructible; изменяемый (динамический)
	Unit** unicObjects = nullptr;  //moving, boilingWater, raft, jet, valve, teleport, Creature, triggers

};