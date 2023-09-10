#pragma once
#include "units.h"

class Object;


class Creature : public Unit { // ����� ��������
public:

	void Collision(bool, Object*** TileMap); // ������������

	void update(float time, Object*** TileMap); // ��������

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

	float getDX();
	float getDY();
	float getX();
	float getY();

	void setDX(float);
	void setDY(float);
	void setX(float);
	void setY(float);

	bool isOnGround();

	void setOnGround(bool);

	sf::FloatRect getRect();

	int getCurHealth();

	void setCurHealth(int);

	void decreaseCurHealth(int);

protected:
	int curHealth;
	int startHealth;
	bool onGround;
	float dx, dy;
	float offsetX = 0, offsetY = 0;

};

class Plumber : public Creature { // keybord control
public:
	Plumber(sf::Texture& image);

	void update(float time, Object*** &TileMap);

	void Collision(bool, Object*** &TileMap);

	void deathAnimation(float); // �������� ������

	void movingAnimation(float); // �������� �������� � �����

	void damageAnimation(float); // �������� �����

	void moveWithKeyboard(); // ����������� ��� ������� ������ �������
private: 
	
	bool spriteDirection;

};

class Mob : public Creature {
	// ��������� � ������ ��������

	// �������� �� ������� ���������
};
