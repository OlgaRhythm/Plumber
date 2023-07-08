#pragma once

#include "units.h"

/*class Visitor {
public:
	void visit() {}
};

class DeathAnimation : public Visitor {
	void visit(Plumber* ptr) {}
};
*/

class Creature : public Unit { // ����� ��������
public:

	void Collision(bool, char** TileMap); // ������������

	void update(float time, char** TileMap); // ��������

	bool isLiving(); // ����� ��� ���

	void deathAnimation(); // �������� ������

	void movingAnimation(); // �������� �������� � �����

	void moveToTheLeft(float acceleration);

	void moveToTheRight(float acceleration);

	void jump(float acceleration);

	void offsetting(float left, float right);

	float getOffsetX();

	float getOffsetY();

	sf::Sprite getSprite();

protected:
	int curHealth;
	int startHealth;
	sf::FloatRect rect; //left, top, wigth, height
	bool onGround;
	float dx, dy;
	float currentFrame;
	sf::Sprite sprite;
	float offsetX = 0, offsetY = 0;

};

class Plumber : public Creature { // keybord control
public:
	Plumber(sf::Texture& image, char **TileMap);

	void update(float time, char** TileMap);

	void Collision(bool, char** TileMap);

	void deathAnimation(float); // �������� ������

	void movingAnimation(float); // �������� �������� � �����
private: 
	bool spriteDirection;
};

class Mob : public Creature {
	// ��������� � ������ ��������

	// �������� �� ������� ���������
};
