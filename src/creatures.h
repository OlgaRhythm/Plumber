#pragma once

#include "units.h"


class Creature : public Unit { // ����� ��������
public:
	// ������������ � ������� (class Object)

	// �������� ��������

	// �������� ������

	// ��������

	// ��������� �������

	bool lived = true;

};

class Plumber : public Creature { // keybord control
public:
	Plumber(sf::Texture& image, char **TileMap);

	void update(float time, char** TileMap);

	void Collision(bool, char** TileMap);

//private:
	float dx, dy;
	sf::FloatRect rect;
	bool onGround;
	float currentFrame;
	sf::Sprite sprite;
	float offsetX = 0, offsetY = 0;
	//char** TileMap;
};

class Mob : public Creature {
	// ��������� � ������ ��������

	// �������� �� ������� ���������
};