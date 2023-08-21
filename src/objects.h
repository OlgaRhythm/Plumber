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

	void actionOnCollision(){ } // �������� �� ������������ � Plumber

	int type = 0;

	static void setCommonTexture(sf::Texture& image) {
		texture = image;
	}

	int getDamageValue() {
		return damage;
	}

	

protected:	
	int tile = 32;

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
	Solid(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������
	
	//static void setCommonSprite(sf::Texture); //!!!!

private:
	static sf::Sprite commonSprite;
};

// �����, ������������, solid

class Pipe : public Object { // P
public:
	Pipe(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	//!!! ������ ������� ��� � ����������� �� ��������� �� ��������� � ������ ����� �������� (������, ����������)
};


// �����, ������������, solid

class Tap : public Object { // T
public:
	Tap(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

};

class Destructible : public Object { // D
public:

	Destructible(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	void destructAnimation(); // �������� ����� ������� �� �����

	void setDestructed(); // �������� ��� Plumper

	// void actionOnCollision() - ���� ������� �����, �� ����������

private:
	bool destructed = false; // ����� Plumper � ������ ���������� ����� - ������������

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
	Coin(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // ��������

	void update(float &time); // �������� ����������!
	// ������� ���������� ��� �������� ����� �����������

	// void actionOnCollision() - ���� ����������, �� ���������� ��������

	static void increaseCoinsAmount();
private: 

	static int coinsAmount;
};

class BoilingWater : public Object { // Observer // B
public:
	BoilingWater(sf::Texture& image);

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

