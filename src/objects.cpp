#include "objects.h"

sf::Texture Object::texture;


Solid::Solid(sf::Texture& image) {

	//this->texture = image;
	
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



Pipe::Pipe(sf::Texture& image) {

	//this->texture = image;

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


Tap::Tap(sf::Texture& image) {
	//this->texture = image;
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

void Destructible::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	if (destructed) {
		// показывается анимация разрушения destuctAnimation()
	}
	else {
		sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
		window.draw(sprite);
	}
}

void Destructible::destructAnimation() { }

void Destructible::setDestructed() { 
	destructed = true;
}

void Moving::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	
}

void Raft::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {

}

void Teleport::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {

}

int Coin::coinsAmount = 0;

Coin::Coin(sf::Texture& image) {
	//this->texture = image;
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

void Coin::collising() {
	increaseCoinsAmount();
	destructing();
}

void Coin::destructing() {

}

BoilingWater::BoilingWater(sf::Texture& image) {
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
