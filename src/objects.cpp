#include "objects.h"

sf::Texture Object::texture;
sf::Sprite Solid::commonSprite;

Solid::Solid(sf::Texture& image) {

	this->texture = image;
	//setCommonSprite(image);
	sprite.setTexture(texture);

	rect = sf::FloatRect(0, 0, 32, 32);
	
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

	rect = sf::FloatRect(160, 0, 32, 32);

	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 2;
}

/*void Pipe::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	/*
	//!!! Пластырь
	int tile = 32;
	sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(rectangle);
	*/
	/*
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}*/

Tap::Tap(sf::Texture& image) {
	//this->texture = image;
	sprite.setTexture(texture);
	rect = sf::FloatRect(32, 32, 32, 32);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 3;

}
/*
void Tap::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	/*
	//!!! Пластырь
	int tile = 32;
	sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(rectangle);
	*/
/*
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}
*/

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

Coin::Coin(sf::Texture& image) {
	//this->texture = image;
	sprite.setTexture(texture);
	rect = sf::FloatRect(256, 0, 32, 32);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
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

BoilingWater::BoilingWater(sf::Texture& image) {
	sprite.setTexture(texture);
	rect = sf::FloatRect(96, 0, 32, 32);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	destructible = false;
	killing = true;
}