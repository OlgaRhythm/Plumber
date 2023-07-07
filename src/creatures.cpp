#include "units.h"
#include "creatures.h"
#include <iostream>

// Creature

void Creature::Collision(bool dir, char** TileMap) {
	for (size_t i = (rect.top) / 32; i < (rect.top + rect.height) / 32; ++i) {
		for (size_t j = rect.left / 32; j < (rect.left + rect.width) / 32; ++j) {
			if (TileMap[i][j] == 'B') {
				if (dx > 0 && !dir) rect.left = j * 32 - rect.width; // right
				if (dx < 0 && !dir) rect.left = j * 32 + 32; // left
				if (dy > 0 && dir) { // down
					rect.top = i * 32 - rect.height;
					dy = 0;
					onGround = true;
				}
				if (dy < 0 && dir) { // up
					rect.top = i * 32 + 32;
					dy = 0;
				}
			}
			if (TileMap[i][j] == '0') {
				std::cout << TileMap << " " << TileMap[i][j] << std::endl;
				TileMap[i][j] = ' ';
				std::cout << "yes" << std::endl;
			}
		}
	}
}

	void Creature::update(float time, char** TileMap) {
		rect.left += dx * time;
		Collision(false, TileMap);
		if (!onGround) dy += 0.0005 * time;
		rect.top += dy * time;
		onGround = false;
		Collision(true, TileMap);

		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		
		if (dx < 0) sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 73 + 88, 244, -rect.width, rect.height));
		if (dx > 0) sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 88, 244, rect.width, rect.height));
		if (dx == 0) { currentFrame = 0; sprite.setTextureRect(sf::IntRect(10, 244, rect.width, rect.height)); }
	
		//if (rect.top > 32 * 35) { rect.top = ground; dy = 0; onGround = true; }

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}

	bool Creature::isLiving() {
		if (curHealth > 0) return true;
		else return false;
	}

	void Creature::deathAnimation() {

	}

	void Creature::movingAnimation() {

	}

	void Creature::moveToTheLeft(float a) {
		dx = -a;
	}

	void Creature::moveToTheRight(float a) {
		dx = a;
	}

	void Creature::jump(float a) {
		if (onGround) {
			dy = -a;
			onGround = false;
		}
	}

	void Creature::offsetting(float left, float top) {
		if (rect.left > left) offsetX = rect.left - left;
		if (rect.top < top) offsetY = rect.top - top;
	}

	float Creature::getOffsetX() {
		return offsetX;
	}

	float Creature::getOffsetY() {
		return offsetY;
	}

	sf::Sprite Creature::getSprite() {
		return sprite;
	}
	

// Plumber
	Plumber::Plumber(sf::Texture &image, char** TileMap) {
		sprite.setTexture(image);
		rect = sf::FloatRect(100, 244, 73, 80);
		dx = dy = 0;
		currentFrame = 0;
		startHealth = 1;
		curHealth = startHealth;
	}

	void Plumber::Collision(bool dir, char** TileMap) {
		for (size_t i = (rect.top )/32; i < (rect.top+rect.height)/32; ++i) {
			for (size_t j = rect.left/32; j < (rect.left+rect.width)/32; ++j) {
				if (TileMap[i][j] == 'B') {
					if (dx > 0 && !dir) rect.left = j * 32 - rect.width; // right
					if (dx < 0 && !dir) rect.left = j * 32 + 32; // left
					if (dy > 0 && dir) { // down
						rect.top = i * 32 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && dir) { // up
						rect.top = i * 32 + 32;
						dy = 0; 
					}
				}
				if (TileMap[i][j] == '0') {
					std::cout << TileMap << " " << TileMap[i][j] << std::endl;
					TileMap[i][j] = ' ';
					std::cout << "yes" << std::endl;
				}
			}
		}
	}

	void Plumber::update(float time, char** TileMap) {
		rect.left += dx * time;
		Collision(false, TileMap);
		if (!onGround) dy += 0.0005 * time;
		rect.top += dy * time;
		onGround = false;
		Collision(true, TileMap);

		if (isLiving()) movingAnimation(time);
		//if (rect.top > 32 * 35) { rect.top = ground; dy = 0; onGround = true; }
		else deathAnimation(time);

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}

	void Plumber::movingAnimation(float time){ 
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;

		if (dx < 0) sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 73 + 88, 244, -rect.width, rect.height));
		if (dx > 0) sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 88, 244, rect.width, rect.height));
		if (dx == 0) { currentFrame = 0; sprite.setTextureRect(sf::IntRect(10, 244, rect.width, rect.height)); }
	}

	void Plumber::deathAnimation(float time) {
		currentFrame += 0.005 * time;
		if (currentFrame > 3) {
			std::cout << "Game Over" << "\n";
			Plumber::~Plumber();
		}
	}

/*
class Mob : public Creature {
	// поведение в режиме ожидания

	// движение по заданой траетории
};

*/