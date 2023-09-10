#pragma once
#include "creatures.h"
#include <iostream>

// Object

class Object : public Unit {
public:
	sf::Sprite getSprite() {
		return sprite;
	}

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
		/*
			//!!! ��������
			int tile = 32;
			sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
			rectangle.setFillColor(sf::Color::Green);
			rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
			window.draw(rectangle);
		*/

		sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
		window.draw(sprite);
		//std::cout << "display\n";
	}

	bool isSolid() {
		return solid;
	}

	bool isKilling() { // delete it?
		return killing;
	}

	bool isDestructible() {
		return destructible;
	}

	int type = 0;

	static void setCommonTexture(sf::Texture& image) {
		texture = image;
	}

	int getDamageValue() {
		return damage;
	}

	int getTileSize() {
		return tile;
	}
	
	virtual bool actionOnCollision(Plumber* pl, bool& p_dir) { 
		if (this->isSolid()) {
			if (pl->getDX() > 0 && !p_dir) pl->setX(this->x * tile - pl->getRect().width); // right
			if (pl->getDX() < 0 && !p_dir) pl->setX(this->x * tile + tile); // left
			if (pl->getDY() > 0 && p_dir) { // down
				pl->setY(this->y * tile - pl->getRect().height);
				pl->setDY(0);
				pl->setOnGround(true);
			}
			if (pl->getDY() < 0 && p_dir) { // up
				pl->setY(this->y * tile + tile);
				pl->setDY(0);
			}
		}

		if (this->isKilling()) {
			pl->decreaseCurHealth(this->getDamageValue());
			std::cout << pl->getCurHealth() << "\n";
		}

		return false; 
	} // ��� ����������������� ��������

	void destructing() { } // ��� ����������� �������� (Coin, Destructible)

	virtual void setCurrentFrame(float frame) {
		currentFrame = frame;
	}

	float getCurrentFrame() {
		return currentFrame;
	}

protected:	
	int tile = 64;

	bool solid = false;
	bool destructible = false;
	bool killing = false;

	static sf::Texture texture;

private:
	//Units
		// float x; // ���������
		// float y; //	�������
		// sf::FloatRect rect; //left, top, wigth, height
		// sf::Sprite sprite; 
		// float currentFrame;
	

};

// �����, ������������, solid

class Solid : public Object { // S
public:
	Solid(float, float);

	bool actionOnCollision(Plumber* pl, bool& p_dir);
};

// �����, ������������, solid

class Pipe : public Object { // P
public:
	Pipe(float, float);

	bool actionOnCollision(Plumber* pl, bool& p_dir);

	void setCurrentFrame(float); // ������ ������� ��� � ����������� �� ��������� �� ��������� � ������ ����� �������� (������, ����������)
	// float currentFrame �������� �� ���
	
};


// �����, ������������, solid

class Tap : public Object { // T
public:
	Tap(float, float);

	bool actionOnCollision(Plumber* pl, bool& p_dir);

	void setCurrentFrame(float); // ������ ������� ��� � ����������� �� ��������� �� ��������� � ������ ����� �������� (������, ����������)
};

class Destructible : public Object { // D
public:

	Destructible(float x, float y);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	//bool actionOnCollision(float &dx, float &dy, float &x, float &y, bool& p_dir); // - ���� ������� �����, �� ����������

	bool actionOnCollision(Plumber* pl, bool& p_dir);

	//void setVisible(bool);

	//void setSolid(bool);
};




class Moving : public Object { // M <-> // m ^
public:
	Moving(float, float);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	// ��� ������� �������������� � Plumper, �� ����� ��������� � �������?
	// �������: ������� � ������ ����� �������

private:
	bool vertically; // ����������� (m) ��� ������������� (M)

	float speed; // ��������

};

class Raft : public Object { // R // ����� ��?
public:
	Raft(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������
};


class Teleport : public Object { // E - elevator
public:
	Teleport(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	// void actionOnCollision() - ���� ������� ������, �� ����� �����
	// ������ ������ � ����� �����, ���� Plumper ������� ������
};

class Coin : public Object { // C
public:
	Coin(float, float);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	void update(float &time); // �������� ����������!
	// ������� ���������� ��� �������� ����� �����������

	bool actionOnCollision(float &dx, float &dy, float &x, float &y, bool& p_dir); // �������� ��� ������������

	static void increaseCoinsAmount(); // ���������� �������� �����
	
	static int getCoinsAmount(); // ��������� �������� ���������� �����

	void destructing(); // �������� ����� �����������

private: 

	static int coinsAmount;
};

class BoilingWater : public Object { // Observer // B
public:
	BoilingWater(float, float);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	void update(float& time); // ��������� ��������

	// void setVisible(bool);
	/*
	* ������� �������� � ������� �������
	* ������� -- ��� Valve ������� �������, ������� �������� � ������ � ���������� ���������
	* � Valve �������� ������� ������� ���� ������ ���� �� �����
	* ��� ����������� �������� �� � Valve ����������� ����� changeVisible(false) �� ����� ������ ����.
	* ��� ���� �������� ������ ������� �� ��������� ���������, ������, �� ����� ������� �� 1 ����
	* 
	*/
};

class Jet : public Object { // Observer // J
public:
	//Jet(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	//void update(float& time); // ��������� ��������
};

class Valve : public Object { //Observable // V
public:
	//Valve(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

private:
	char rotation;

};

