#include "objects.h"

Solid::Solid(sf::Texture& image) {

	this->texture = image;

	sprite.setTexture(texture);

	rect = sf::FloatRect(0, 0, 32, 32);
	
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 1;
}

void Solid::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	
		//!!! ��������
		int tile = 32;
		sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
		rectangle.setFillColor(sf::Color::Green);
		rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
		window.draw(rectangle);
	
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}

sf::Sprite Solid::getSprite() {
	return sprite;
}


Pipe::Pipe(sf::Texture& image) {

	this->texture = image;

	sprite.setTexture(texture);

	rect = sf::FloatRect(160, 0, 32, 32);

	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));

	currentFrame = 0;
	solid = true;
	type = 2;
}

void Pipe::display(sf::RenderWindow& window, size_t i, size_t j, float offsetX, float offsetY, float time) {
	/*
	//!!! ��������
	int tile = 32;
	sf::RectangleShape rectangle(sf::Vector2f(tile, tile));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(rectangle);
	*/
	
	sprite.setPosition(j * tile - offsetX, i * tile - offsetY);
	window.draw(sprite);
}

Tap::Tap(sf::Texture& image) {
	sprite.setTexture(image);
	rect = sf::FloatRect(32, 32, 32, 32);
	currentFrame = 0;
	solid = true;
}