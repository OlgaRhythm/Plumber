#pragma once
#include "units.h"
#include "creatures.h"
// 5 ����
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
	Plumber* player; // ��������� �� ������
	int player_x, player_y; //� ����� ����������� ������ ��������� ��������
	char color = 0; // 0 - Black, 1 - Blue
	char** backgroundAndSolid = nullptr; // backgroung � solid (pipe, tap); ������������
	char** solidObjects = nullptr; // coin, destructible; ���������� (������������)
	Unit** unicObjects = nullptr;  //moving, boilingWater, raft, jet, valve, teleport, Creature, triggers

};