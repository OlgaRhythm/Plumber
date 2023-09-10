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
	} // для взаимодействующих объектов

	void destructing() { } // для разрушаемых объектов (Coin, Destructible)

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
		// float x; // начальная
		// float y; //	позиция
		// sf::FloatRect rect; //left, top, wigth, height
		// sf::Sprite sprite; 
		// float currentFrame;
	

};

// земля, неизменяемая, solid

class Solid : public Object { // S
public:
	Solid(float, float);

	bool actionOnCollision(Plumber* pl, bool& p_dir);
};

// трубы, неизменяемые, solid

class Pipe : public Object { // P
public:
	Pipe(float, float);

	bool actionOnCollision(Plumber* pl, bool& p_dir);

	void setCurrentFrame(float); // меняет внешний вид в зависимости от положения по отношению к другим таким объектам (изгибы, соединения)
	// float currentFrame отвечает за вид
	
};


// краны, неизменяемые, solid

class Tap : public Object { // T
public:
	Tap(float, float);

	bool actionOnCollision(Plumber* pl, bool& p_dir);

	void setCurrentFrame(float); // меняет внешний вид в зависимости от положения по отношению к другим таким объектам (изгибы, соединения)
};

class Destructible : public Object { // D
public:

	Destructible(float x, float y);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	//bool actionOnCollision(float &dx, float &dy, float &x, float &y, bool& p_dir); // - если пригнул снизу, то разрушение

	bool actionOnCollision(Plumber* pl, bool& p_dir);

	//void setVisible(bool);

	//void setSolid(bool);
};




class Moving : public Object { // M <-> // m ^
public:
	Moving(float, float);

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
	Coin(float, float);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	void update(float &time); // мерцание СИНХРОННОЕ!
	// сделать переменную для хранения кадра статической

	bool actionOnCollision(float &dx, float &dy, float &x, float &y, bool& p_dir); // действие при столкновении

	static void increaseCoinsAmount(); // увеличение счётчика монет
	
	static int getCoinsAmount(); // получение значения количества монет

	void destructing(); // действие перед разрушением

private: 

	static int coinsAmount;
};

class BoilingWater : public Object { // Observer // B
public:
	BoilingWater(float, float);

	void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	void update(float& time); // синхронно мелькает

	// void setVisible(bool);
	/*
	* объекты хранятся в неживом массиве
	* триггер -- это Valve нужного порядка, который хранится в списке с подвижными объектами
	* В Valve хранится верхний верхний блок потока воды из трубы
	* При пересечении спрайтов гг и Valve срабатывает метод changeVisible(false) на блоке потока воды.
	* Эта вода начинает цепную реакцию по изменению видимости, причём, по одной строчке за 1 кадр
	* 
	*/
};

class Jet : public Object { // Observer // J
public:
	//Jet(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

	//void update(float& time); // синхронно мелькает
};

class Valve : public Object { //Observable // V
public:
	//Valve(sf::Texture& image);

	//void display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time); // анимация

private:
	char rotation;

};

