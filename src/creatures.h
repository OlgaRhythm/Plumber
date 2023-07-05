#pragma once

#include "units.h"


class Creature : public Unit { // живые существа
public:
	// столкновение с блоками (class Object)

	// анимация движения

	// анимация смерти

	// здоровье

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
	//char** TileMap;
};

class Mob : public Creature {
	// поведение в режиме ожидания

	// движение по заданой траетории
};