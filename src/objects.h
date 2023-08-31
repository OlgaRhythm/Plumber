#pragma once
#include "units.h"
#include <iostream>

//// ������� ����������� (�����������)
class IObserver {
public:
	virtual void act() = 0;
};

class Observable {
public:
	Observable() : list(nullptr), size(0) {}

	Observable(IObserver* obs) : list(new IObserver* [1]), size(1) {
		list[0] = obs;
	}

	virtual ~Observable() {
		delete[] list;
		list = nullptr;
	}
	void addObserver(IObserver* obs) {
		++size;
	}

	void removeObserver(IObserver* obs) {
		--size;
	}

	void notifyObservers() {
		for (size_t i = 0; i < size; ++i) list[i]->act();
	}

private:
	IObserver** list;
	int size;
};



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

	bool isKilling() {
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
	
	virtual bool actionOnCollision(float &dx, float &dy, float &x, float &y, bool& p_dir) { return false; } // ��� ����������������� ��������

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
	Solid();

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������
};

// �����, ������������, solid

class Pipe : public Object { // P
public:
	Pipe();

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	void setCurrentFrame(float); // ������ ������� ��� � ����������� �� ��������� �� ��������� � ������ ����� �������� (������, ����������)
	// float currentFrame �������� �� ���
	
};


// �����, ������������, solid

class Tap : public Object { // T
public:
	Tap();

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	void setCurrentFrame(float); // ������ ������� ��� � ����������� �� ��������� �� ��������� � ������ ����� �������� (������, ����������)
};

class Destructible : public Object { // D
public:

	Destructible(float x, float y);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	bool actionOnCollision(float &dx, float &dy, float &x, float &y, bool& p_dir); // - ���� ������� �����, �� ����������

};

class Moving : public Object { // M <-> // m ^
public:
	Moving(sf::Texture& image);

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
	Coin();

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	void update(float &time); // �������� ����������!
	// ������� ���������� ��� �������� ����� �����������

	// void actionOnCollision() - ���� ����������, �� ���������� ��������

	bool actionOnCollision(float &dx, float &dy, float &x, float &y, bool& p_dir); // �������� ��� ������������

	static void increaseCoinsAmount(); // ���������� �������� �����
	
	static int getCoinsAmount(); // ��������� �������� ���������� �����

	void destructing(); // �������� ����� �����������

private: 

	static int coinsAmount;
};

class BoilingWater : public Object { // Observer // B
public:
	BoilingWater();

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	void update(float& time); // ��������� ��������
};

class Jet : public Object, public IObserver { // Observer // J
public:
	//Jet(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	//void update(float& time); // ��������� ��������
};

class Valve : public Object, public Observable { //Observable // V
public:
	//Valve(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

private:
	char rotation;

};

