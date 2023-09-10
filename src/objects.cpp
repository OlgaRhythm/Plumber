#include "objects.h"

sf::Texture Object::texture;

// CLASS SOLID

Solid::Solid(float x, float y) {

	sprite.setTexture(texture);

	rect = sf::FloatRect(0, 0, tile, tile);
	
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 1;
	this->x = x;
	this->y = y;
}

bool Solid::actionOnCollision(Plumber* pl, bool& p_dir) {
	Object::actionOnCollision(pl, p_dir);
	return false;
}

// CLASS PIPE

Pipe::Pipe(float x, float y) {

	sprite.setTexture(texture);

	rect = sf::FloatRect(0, tile, tile, tile);

	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 2;

	currentFrame = 0.0f;

	this->x = x;
	this->y = y;
}

bool Pipe::actionOnCollision(Plumber* pl, bool& p_dir) {
	Object::actionOnCollision(pl, p_dir);
	return false;
}

void Pipe::setCurrentFrame(float frame) {
	currentFrame = frame;
	int tempFrame = (int) frame;

	rect = sf::FloatRect(tile * tempFrame, tile, tile, tile);

	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));
	return;
}

// CLASS TAP

Tap::Tap(float x, float y) {
	sprite.setTexture(texture);
	rect = sf::FloatRect(0, tile*2, tile, tile);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 3;

	this->x = x;
	this->y = y;
}

bool Tap::actionOnCollision(Plumber* pl, bool& p_dir) {
	Object::actionOnCollision(pl, p_dir);
	return false;
}

void Tap::setCurrentFrame(float frame) {
	currentFrame = frame;
	int tempFrame = (int)frame;

	rect = sf::FloatRect(tile * tempFrame, tile * 2, tile, tile);

	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));
	return;
}

// CLASS DESTRUCTIBLE 

Destructible::Destructible(float tempX, float tempY) {
	sprite.setTexture(texture);
	rect = sf::FloatRect(0, tile * 3, tile, tile);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	destructible = true;

	currentFrame = 0.0f;
	solid = true;

	this->x = tempX; // * tile
	this->y = tempY;
	
}

void Destructible::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}

/*

bool Destructible::actionOnCollision(float &dx, float &dy, float &p_x, float &p_y, bool &p_dir) {
	
/*
	if (dy < 0 && ((this->x - p_x > 0 && p_dir) || (this->x - p_x < 0 && !p_dir))) {
		if ((int)rect.left == 0) rect = sf::FloatRect(tile, tile * 3, tile, tile);
		else { rect = sf::FloatRect(tile * 2, tile * 3, tile, tile); solid = false; }

		sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));		
	}
	
	return false;
}
*/

bool Destructible::actionOnCollision(Plumber* pl, bool& p_dir) {

	/* когда разрушается, сам объект уничтожается, но перед этим
	 * создаёт 4 новых объекта в динамическом массиве aliveObjects,
	 * которые разлетаются в пространстве, как в оригинальном Марио
	 */

	Object::actionOnCollision(pl, p_dir);


	return false;
}

// CLASS COIN 

int Coin::coinsAmount = 0;

Coin::Coin(float x, float y) {

	sprite.setTexture(texture);
	rect = sf::FloatRect(tile * 8, 0, tile, tile);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = false;
	destructible = true;
	this->x = x;
	this->y = y;
}

void Coin::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	update(time);
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}

void Coin::update(float& time) {
	//мерцание, меняет currentFrame
}

void Coin::increaseCoinsAmount() {
	++coinsAmount;
}

int Coin::getCoinsAmount() {
	return coinsAmount;
}

bool Coin::actionOnCollision(float& dx, float& dy, float& x, float& y, bool& p_dir) {
	increaseCoinsAmount();
	destructing();
	return true;
}

void Coin::destructing() {

}

// CLASS BOILINGWATER

BoilingWater::BoilingWater(float x, float y) {
	sprite.setTexture(texture);
	rect = sf::FloatRect(tile * 3, 0, tile, tile);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	destructible = false;
	killing = true;
	damage = 3;
	this->x = x;
	this->y = y;
}

void BoilingWater::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}

void BoilingWater::update(float& time) {
	//мерцание, меняет currentFrame
}





void Moving::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	
}

void Raft::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {

}

void Teleport::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {

}

