#include "units.h"
#include "creatures.h"
#include <iostream>

// Creature

void Creature::Collision(bool dir, char** TileMap) {
	/*for (size_t i = y / 32; i < (y + rect.height) / 32; ++i) {
		for (size_t j = x / 32; j < (x + rect.width) / 32; ++j) {
			if (TileMap[i][j] == 'B') {
				if (dx > 0 && !dir) x = j * 32 - rect.width; // right
				if (dx < 0 && !dir) x = j * 32 + 32; // left
				if (dy > 0 && dir) { // down
					y = i * 32 - rect.height;
					dy = 0;
					onGround = true;
				}
				if (dy < 0 && dir) { // up
					y = i * 32 + 32;
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
	*/
}

	void Creature::update(float time, char** TileMap) {
		/*x += dx * time;
		Collision(false, TileMap);
		if (!onGround) dy += 0.0005 * time;
		y += dy * time;
		onGround = false;
		Collision(true, TileMap);

		if (isLiving()) movingAnimation();
		//if (y > 32 * 35) { y = ground; dy = 0; onGround = true; }
		else deathAnimation(time);

		sprite.setPosition(x - offsetX, y - offsetY);
		dx = 0;
		*/
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
		if (x > left) offsetX = x - left;
		if (y < top) offsetY = y - top;
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
		x = 100;
		y = 244;
		rect = sf::FloatRect(100, 260, 73, 80);
		dx = dy = 0;
		currentFrame = 0;
		startHealth = 1;
		curHealth = startHealth;
	}

	void Plumber::Collision(bool dir, char** TileMap) {
		for (size_t i = y/32; i < (y+rect.height)/32; ++i) {
			for (size_t j = x/32; j < (x+rect.width)/32; ++j) {
				if (TileMap[i][j] == 'B') {
					if (dx > 0 && !dir) x = j * 32 - rect.width; // right
					if (dx < 0 && !dir) x = j * 32 + 32; // left
					if (dy > 0 && dir) { // down
						y = i * 32 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && dir) { // up
						y = i * 32 + 32;
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
		x += dx * time;
		Collision(false, TileMap);
		if (!onGround) dy += 0.0005 * time;
		y += dy * time;
		onGround = false;
		Collision(true, TileMap);

		if (isLiving()) movingAnimation(time);
		//if (y > 32 * 35) { y = ground; dy = 0; onGround = true; }
		else deathAnimation(time);

		sprite.setPosition(x - offsetX, y - offsetY);
		dx = 0;
	}

	void Plumber::movingAnimation(float time){ 
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;

		if (dx < 0) sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 73 + 88, rect.top, -rect.width, rect.height));
		if (dx > 0) sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 88, rect.top, rect.width, rect.height));
		if (dx == 0) { currentFrame = 0; sprite.setTextureRect(sf::IntRect(10, rect.top, rect.width, rect.height)); }
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