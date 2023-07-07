#pragma once

#include "units.h"


class Creature : public Unit { // живые существа
public:
	void Collision(bool, char** TileMap); // столкновение

	void update(float time, char** TileMap); // анимация

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

protected:
	int curHealth;
	int startHealth;
	sf::FloatRect rect;
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

	void deathAnimation(float); // анимация смерти

	void movingAnimation(float); // анимация движения и покоя



//private: 
};

class Mob : public Creature {
	// поведение в режиме ожидания

	// движение по заданой траетории
};