#include "units.h"
#include "creatures.h"
#include <iostream>

// Creature

void Creature::Collision(bool dir, Object*** TileMap) {
/*	for (size_t i = y / 32; i < (y + rect.height) / 32; ++i) {
		for (size_t j = x / 32; j < (x + rect.width) / 32; ++j) {
			if (TileMap[i][j] != '`') {
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
		}
	}*/
}

	void Creature::update(float time, Object*** TileMap) {
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
	
	//void Creature::display() {
//
	//}

// Plumber
	Plumber::Plumber(sf::Texture &image) {
		sprite.setTexture(image);
		x = 100;
		y = 244;
		rect = sf::FloatRect(100, 260, 73, 80);
		dx = dy = 0;
		currentFrame = 0;
		startHealth = 1;
		curHealth = startHealth;
		spriteDirection = true; // true -> right, false -> left
		onGround = false;
	}

	void Plumber::Collision(bool dir, Object*** &TileMap) {
		// неподвижные объекты
		for (size_t i = y/32; i < (y+rect.height)/32; ++i) {
			for (size_t j = x/32; j < (x+rect.width)/32; ++j) {
				if (TileMap[i][j]->isSolid()) {
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
				if (TileMap[i][j]->isKilling()) {
					curHealth -= TileMap[i][j]->getDamageValue();
					std::cout << curHealth << "\n";
					if (curHealth <= 0) { 
						dy = -0.5; 
						dx = 0.0f;
					}
				}
			}
		}
		// подвижные объекты
	}

	void Plumber::update(float time, Object*** &TileMap) {
		if (isLiving()) {
			x += dx * time;
			Collision(false, TileMap);
			if (!onGround) dy += 0.0005 * time;
			y += dy * time;
			onGround = false;
			Collision(true, TileMap);
			//std::cout << dx << " " << dy << "\n";
			if (isLiving()) movingAnimation(time);
			//if (y > 32 * 35) { y = ground; dy = 0; onGround = true; }
			else deathAnimation(time);

			sprite.setPosition(x - offsetX, y - offsetY);
			dx = 0;
		}
		else {
			deathAnimation(time);
			if (y > 500) {
				dy = 0;
			}
			else {
				y += dy * time;
				if (dy < 0.5) dy += 0.0005 * time;
				// std::cout << dy << "\n";
			}
			sprite.setPosition(x - offsetX, y - offsetY);
		}
	}

	void Plumber::movingAnimation(float time){ 
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;

		if (dx < 0) {
			spriteDirection = false;
			if (dy > 0 || dy < 0) {
				sprite.setTextureRect(sf::IntRect(88 * 3 + rect.width + 88, rect.top, -rect.width, rect.height));
			}
			else sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + rect.width + 88, rect.top, -rect.width, rect.height));
		}
		if (dx > 0) {
			spriteDirection = true;
			if (dy > 0 || dy < 0) {
				sprite.setTextureRect(sf::IntRect(88 * 3 + 88, rect.top, rect.width, rect.height));
			}	
			else sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 88, rect.top, rect.width, rect.height));
		}
		if (dx == 0) {
			if (spriteDirection) {
				if (dy > 0 || dy < 0) {
					sprite.setTextureRect(sf::IntRect(88 * 3 + 88, rect.top, rect.width, rect.height));
				}
				else {
					currentFrame = 0;
					sprite.setTextureRect(sf::IntRect(10, rect.top, rect.width, rect.height));
				}
			}
			else {
				if (dy > 0 || dy < 0) {
					sprite.setTextureRect(sf::IntRect(88 * 3 + rect.width + 88, rect.top, -rect.width, rect.height));
				}
				else {
					currentFrame = 0;
					sprite.setTextureRect(sf::IntRect(83, rect.top, -rect.width, rect.height));
				}

			}
			 
		}
		
	}

	void Plumber::deathAnimation(float time) {
		sprite.setTextureRect(sf::IntRect(88 * 6, rect.top, rect.width, rect.height));
		currentFrame += 0.005 * time;
		if (currentFrame > 3) {
			std::cout << "Game Over" << "\n";
			//Plumber::~Plumber();
		}
	}

	void Plumber::damageAnimation(float time) {

	}

	void Plumber::moveWithKeyboard() { // перемещение при нажатии нужной клавиши
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			(*this).moveToTheLeft(0.1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			(*this).moveToTheRight(0.1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			(*this).jump(0.5);
		}
	}

/*
class Mob : public Creature {
	// поведение в режиме ожидания

	// движение по заданой траетории
};

*/