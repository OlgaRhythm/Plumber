#pragma once
#include "units.h"
#include <iostream>

//// паттерн Наблюдатель (примитивный)
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
			//!!! Пластырь
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

	void actionOnCollision(){ } // действие на соприкосание с Plumber

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
		// float x; // начальная
		// float y; //	позиция
		// sf::FloatRect rect; //left, top, wigth, height
		// sf::Sprite sprite; 
		// float currentFrame;
	

};

// земля, неизменяемая, solid

class Solid : public Object { // S
public:
	Solid(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация
	
	//static void setCommonSprite(sf::Texture); //!!!!

private:
	static sf::Sprite commonSprite;
};

// трубы, неизменяемые, solid

class Pipe : public Object { // P
public:
	Pipe(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	//!!! меняет внешний вид в зависимости от положения по отношению к другим таким объектам (изгибы, соединения)
};


// краны, неизменяемые, solid

class Tap : public Object { // T
public:
	Tap(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

};

class Destructible : public Object { // D
public:

	Destructible(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	void destructAnimation(); // анимация после касания гг снизу

	void setDestructed(); // доступна для Plumper

	// void actionOnCollision() - если пригнул снизу, то разрушение

private:
	bool destructed = false; // когда Plumper в прыжке дотронулся снизу - активируется

};

class Moving : public Object { // M <-> // m ^
public:
	Moving(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	// как сделать взаимодействие с Plumper, не меняя положение в массиве?
	// Решение: хранить в списке живых существ

private:
	bool vertically; // вертикально (m) или горизонтально (M)

	float speed; // скорость

};

class Raft : public Object { // R // Нужен ли?
public:
	Raft(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация
};


class Teleport : public Object { // E - elevator
public:
	Teleport(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	// void actionOnCollision() - если прыгнул сверху, то смена карты
	// подает сигнал о смене карты, если Plumper прыгнет сверху
};

class Coin : public Object { // C
public:
	Coin(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	void update(float &time); // мерцание СИНХРОННОЕ!
	// сделать переменную для хранения кадра статической

	// void actionOnCollision() - если дотронулся, то увеличение счётчика

	static void increaseCoinsAmount();
private: 

	static int coinsAmount;
};

class BoilingWater : public Object { // Observer // B
public:
	BoilingWater(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	void update(float& time); // синхронно мелькает
};

class Jet : public Object, public IObserver { // Observer // J
public:
	//Jet(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	//void update(float& time); // синхронно мелькает
};

class Valve : public Object, public Observable { //Observable // V
public:
	//Valve(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

private:
	char rotation;

};

