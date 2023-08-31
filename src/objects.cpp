#include "objects.h"

sf::Texture Object::texture;

// CLASS SOLID

Solid::Solid() {

	sprite.setTexture(texture);

	rect = sf::FloatRect(0, 0, tile, tile);
	
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 1;
}


/*void Solid::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	
		//!!! Пластырь
		int tile = 32;
		sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
		rectangle.setFillColor(sf::Color::Green);
		rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
		window.draw(rectangle);
	
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}*/

// CLASS PIPE

Pipe::Pipe() {

	sprite.setTexture(texture);

	rect = sf::FloatRect(0, tile, tile, tile);

	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 2;

	currentFrame = 0.0f;
}


void Pipe::setCurrentFrame(float frame) {
	currentFrame = frame;
	int tempFrame = (int) frame;

	rect = sf::FloatRect(tile * tempFrame, tile, tile, tile);

	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));
	return;
}

// CLASS TAP

Tap::Tap() {
	sprite.setTexture(texture);
	rect = sf::FloatRect(0, tile*2, tile, tile);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 3;

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

	this->x = tempX * tile;
	this->y = tempY * tile;
	
}

void Destructible::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}

bool Destructible::actionOnCollision(float &dx, float &dy, float &p_x, float &p_y, bool &p_dir) {
	/* когда разрушается, сам объект уничтожается, но перед этим
	 * создаёт 4 новых объекта в динамическом массиве aliveObjects,
	 * которые разлетаются в пространстве, как в оригинальном Марио
	 */
	if (dy < 0 && ((this->x - p_x > 0 && p_dir) || (this->x - p_x < 0 && !p_dir))) {
		if ((int)rect.left == 0) rect = sf::FloatRect(tile, tile * 3, tile, tile);
		else { rect = sf::FloatRect(tile * 2, tile * 3, tile, tile); solid = false; }

		sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));		
	}
	
	return false;
}

void Moving::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	
}

void Raft::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {

}

void Teleport::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {

}

int Coin::coinsAmount = 0;

Coin::Coin() {
	
	sprite.setTexture(texture);
	rect = sf::FloatRect(tile * 8, 0, tile, tile);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = false;
	destructible = true;
}

void Coin::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	update(time);
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}

void Coin::update(float &time) {
	//мерцание, меняет currentFrame
}

void Coin::increaseCoinsAmount() {
	++coinsAmount;
}

int Coin::getCoinsAmount() {
	return coinsAmount;
}

bool Coin::actionOnCollision(float &dx, float &dy, float &x, float &y, bool& p_dir) {
	increaseCoinsAmount();
	destructing();
	return true;
}

void Coin::destructing() {

}

BoilingWater::BoilingWater() {
	sprite.setTexture(texture);
	rect = sf::FloatRect(tile * 3, 0, tile, tile);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	destructible = false;
	killing = true;
	damage = 3;
}

void BoilingWater::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}

void BoilingWater::update(float& time) {
	//мерцание, меняет currentFrame
}
