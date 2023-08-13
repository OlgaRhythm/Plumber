#pragma once
#include "units.h"

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
	static void setCommonTexture(sf::Texture &image) {
		commonTexture = image;
	}

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
	}

	virtual void getObjectFromPointer(Object* ptr) {};

protected:
	bool collision = false;
	static sf::Texture commonTexture;
	int tile = 32;

private:
	//Units
		// float x; // начальная
		// float y; //	позиция
		// sf::FloatRect rect; //left, top, wigth, height
		// sf::Sprite sprite;
		// float currentFrame;
	bool solid;
	bool destructible;
	bool killing;

};

// земля, неизменяемая, solid

class Solid : public Object { // S
public:
	Solid();
	Solid(sf::Texture& image);

	void getObjectFromPointer(Object* ptr);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

};

Solid::Solid() {
	sprite.setTexture(commonTexture);
	rect = sf::FloatRect(0, 0, 32, 32);
	currentFrame = 0;
	collision = true;
}

Solid::Solid(sf::Texture& image) {
	sprite.setTexture(image);
	rect = sf::FloatRect(0, 0, 32, 32);
	currentFrame = 0;
	collision = true;
}

void Solid::getObjectFromPointer(Object* ptr) {
		// sf::FloatRect rect; //left, top, wigth, height
		// sf::Sprite sprite;
		// float currentFrame;
	bool solid;
	bool destructible;
	bool killing;
}

/*
void Solid::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
/*
	//!!! Пластырь
	int tile = 32;
	sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(rectangle);

	
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}
*/
// трубы, неизменяемые, solid

class Pipe : public Object { // P
public:
	Pipe();

	Pipe(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

};
/*
void Pipe::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	/*
	//!!! Пластырь
	int tile = 32;
	sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(rectangle);
	
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}
*/

Pipe::Pipe() {
	sprite.setTexture(commonTexture);
	rect = sf::FloatRect(160, 0, 32, 32);
	currentFrame = 0;
	collision = true;
}

Pipe::Pipe(sf::Texture& image) {
	sprite.setTexture(image);
	rect = sf::FloatRect(160, 0, 32, 32);
	currentFrame = 0;
	collision = true;
}

// краны, неизменяемые, solid

class Tap : public Object { // T
public:
	Tap();

	Tap(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

};

Tap::Tap() {
	sprite.setTexture(commonTexture);
	rect = sf::FloatRect(32, 32, 32, 32);
	currentFrame = 0;
	collision = true;
}

Tap::Tap(sf::Texture& image) {
	sprite.setTexture(image);
	rect = sf::FloatRect(32, 32, 32, 32);
	currentFrame = 0;
	collision = true;
}
/*
void Tap::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	//!!! Пластырь
	int tile = 32;
	sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(rectangle);
}
*/
// 
class Destructible : public Object {

};

class Moving : public Object {

};

class Raft : public Object {

};


class Teleport : public Object {

};

class Coin : public Object {

};

class Background : public Object {

};

class BoilingWater : public Object, public IObserver { // Observer

};

class Jet : public Object, public IObserver { // Observer

};

class Valve : public Object, public Observable { //Observable

};

