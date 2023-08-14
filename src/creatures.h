#pragma once

#include "units.h"
#include "objects.h"

/*class Visitor {
public:
	void visit() {}
};

class DeathAnimation : public Visitor {
	void visit(Plumber* ptr) {}
};
*/

class Creature : public Unit { // живые существа
public:

	void Collision(bool, Object*** TileMap); // столкновение

	void update(float time, Object*** TileMap); // анимация

	bool isLiving(); // живой или нет

	void deathAnimation(); // анимация смерти

	void movingAnimation(); // анимация движения и покоя

	void moveToTheLeft(float acceleration);

	void moveToTheRight(float acceleration);

	void jump(float acceleration);

	void offsetting(float left, float right);

	float getOffsetX();

	float getOffsetY();

	sf::Sprite getSprite();

	//void display();
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

	void deathAnimation(float); // анимация смерти

	void movingAnimation(float); // анимация движения и покоя

	void moveWithKeyboard(); // перемещение при нажатии нужной клавиши
private: 
	bool spriteDirection;
};

class Mob : public Creature {
	// поведение в режиме ожидания

	// движение по заданой траетории
};
