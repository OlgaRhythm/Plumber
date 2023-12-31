//#include "units.h"
#include "objects.h"
#include <iostream>

// Creature

	void Creature::Collision(bool dir, Object*** TileMap) {

}

	void Creature::update(float time, Object*** TileMap) {

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

	float Creature::getDX() {
		return this->dx;
	}
	float Creature::getDY() {
		return this->dy;
	}
	float Creature::getX() {
		return this->x;
	}
	float Creature::getY() {
		return this->y;
	}

	void Creature::setDX(float new_dx) {
		this->dx = new_dx;
	}
	void Creature::setDY(float new_dy) {
		this->dy = new_dy;
	}
	void Creature::setX(float new_x) {
		this->x = new_x;
	}
	void Creature::setY(float new_y) {
		this->y = new_y;
	}

	bool Creature::isOnGround() {
		return this->onGround;
	}

	void Creature::setOnGround(bool value) {
		onGround = value;
	}

	sf::FloatRect Creature::getRect() {
		return this->rect;
	}

	int Creature::getCurHealth() {
		return curHealth;
	}

	void Creature::setCurHealth(int newCurHealth) {
		this->curHealth = newCurHealth;
	}

	void Creature::decreaseCurHealth(int damage) {
		curHealth -= damage;
	}

// Plumber
	Plumber::Plumber(sf::Texture &image) {
		sprite.setTexture(image);
		x = 100;
		y = 244;
		rect = sf::FloatRect(0, 0, 105, 128);
		dx = dy = 0;
		currentFrame = 0;
		startHealth = 1;
		curHealth = startHealth;
		spriteDirection = true; // true -> right, false -> left
		onGround = false;
	}

	void Plumber::Collision(bool dir, Object*** &TileMap) {
		// ����������� �������
		int tile = 32; // ������ ������
		if (TileMap[0][0] != nullptr) tile = TileMap[0][0]->getTileSize();
		float old_dy = dy, old_dx = dx;
		for (size_t i = y/ tile; i < (y+rect.height)/ tile; ++i) {
			for (size_t j = x/ tile; j < (x+rect.width)/ tile; ++j) {
				
				TileMap[i][j]->actionOnCollision(this, dir);

				/*
				if (TileMap[i][j]->isDestructible()) {
					if (TileMap[i][j]->actionOnCollision(old_dx, old_dy, x, y, spriteDirection)) {
						Object* ptr = TileMap[i][j]; 
						TileMap[i][j] = new Object();
						delete ptr;
						std::cout << Coin::getCoinsAmount() << "\n";
					}
				}

				*/
			}
		}

		if (curHealth <= 0) {
			dy = -0.5;
			dx = 0.0f;
			std::cout << "killing\n";
		}
		// ��������� �������
	}

	void Plumber::update(float time, Object*** &TileMap) {
		if (isLiving()) {
			x += dx * time;
			Collision(false, TileMap);
			if (!onGround) dy += 0.0005 * time;
			y += dy * time;
			onGround = false;
			Collision(true, TileMap);
			if (isLiving()) movingAnimation(time);
			else deathAnimation(time);

			sprite.setPosition(x - offsetX, y - offsetY);
			dx = 0;
		}
		else {
			deathAnimation(time);
		}
	}

	void Plumber::movingAnimation(float time){ 
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;

		if (dx < 0) {
			spriteDirection = false;
			if (dy > 0 || dy < 0) { // jump
				sprite.setTextureRect(sf::IntRect(rect.left + rect.width * 5 + rect.width, rect.top, -rect.width, rect.height));
			}
			else sprite.setTextureRect(sf::IntRect(rect.left + rect.width * (int(currentFrame) + 1) + rect.width, rect.top, -rect.width, rect.height));
		}
		if (dx > 0) {
			spriteDirection = true;
			if (dy > 0 || dy < 0) { // jump
				sprite.setTextureRect(sf::IntRect(rect.left + rect.width * 5, rect.top, rect.width, rect.height));
			}	
			else sprite.setTextureRect(sf::IntRect(rect.left + rect.width * (int(currentFrame) + 1), rect.top, rect.width, rect.height));
		}
		if (dx == 0) {
			if (spriteDirection) {
				if (dy > 0 || dy < 0) {
					sprite.setTextureRect(sf::IntRect(rect.left + rect.width * 5, rect.top, rect.width, rect.height));
				}
				else {
					currentFrame = 0;
					sprite.setTextureRect(sf::IntRect(rect.left + rect.left, rect.top, rect.width, rect.height));
				}
			}
			else {
				if (dy > 0 || dy < 0) {
					sprite.setTextureRect(sf::IntRect(rect.left + rect.width * 5 + rect.width, rect.top, -rect.width, rect.height));
				}
				else {
					currentFrame = 0;
					sprite.setTextureRect(sf::IntRect(rect.left + rect.width, rect.top, -rect.width, rect.height));
				}

			}
			 
		}
		
	}

	void Plumber::deathAnimation(float time) {
		sprite.setTextureRect(sf::IntRect(rect.width * 6, rect.top, rect.width, rect.height));
		currentFrame += 0.005 * time;
		if (currentFrame > 3) {
			//std::cout << "Game Over" << "\n";
			//Plumber::~Plumber();
		}
		if (y > 1200) {
			dy = 0;
			/*
			* ����� ������ �� ���������� ����� ���������
			* ������� (�����) ���������� �������
			*/
		}
		else {
			// std::cout << dy << "\n";
			y += dy * time;
			if (dy < 0.5) dy += 0.0005 * time;
		}
		sprite.setPosition(x - offsetX, y - offsetY);
	}

	void Plumber::damageAnimation(float time) {

	}

	void Plumber::moveWithKeyboard() { // ����������� ��� ������� ������ �������
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			(*this).moveToTheLeft(0.1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			(*this).moveToTheRight(0.1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			(*this).jump(0.6);
		}
	}


/*
class Mob : public Creature {
	// ��������� � ������ ��������

	// �������� �� ������� ���������
};

*/