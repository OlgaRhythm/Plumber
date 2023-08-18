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

	int type = 0;
protected:	
	int tile = 32;

	bool solid = false;
	bool destructible = false;
	bool killing = false;

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

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	sf::Sprite getSprite();

private:
	sf::Sprite* spritePtr;

	sf::Texture texture;
	
};

// трубы, неизменяемые, solid

class Pipe : public Object { // P
public:
	Pipe(sf::Texture& image);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	//void setSprite(sf::Texture& image);
};


// краны, неизменяемые, solid

class Tap : public Object { // T
public:
	Tap(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	//void setSprite(sf::Texture& image);
};

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

