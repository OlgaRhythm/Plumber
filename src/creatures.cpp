#include "units.h"
#include "creatures.h"
#include <iostream>


/*class Creature : public Unit { // живые существа
public:
	// столкновение с блоками (class Object)

	// анимация движения

	// анимация смерти

	// здоровье

};

*/
//class Plumber : public Creature { // keybord control
//public:
	Plumber::Plumber(sf::Texture &image, char** TileMap) {
		sprite.setTexture(image);
		rect = sf::FloatRect(100, 244, 73, 80);
		dx = dy = 0;
		currentFrame = 0;
	}

	void Plumber::Collision(bool dir, char** TileMap) {
		for (size_t i = (rect.top )/32; i < (rect.top+rect.height)/32; ++i) {
			for (size_t j = rect.left/32; j < (rect.left+rect.width)/32; ++j) {
				if (TileMap[i][j] == 'B') {
					if (dx > 0 && !dir) rect.left = j * 32 - rect.width; // right
					if (dx < 0 && !dir) rect.left = j * 32 + 32; // left
					if (dy > 0 && dir) { // down
						rect.top = i * 32 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && dir) { // up
						rect.top = i * 32 + 32;
						dy = 0; 
					}
				}
				if (TileMap[i][j] == '0') {
					std::cout << TileMap << " " << TileMap[i][j] << std::endl;
					TileMap[i][j] = ' ';
					std::cout << "yes" << std::endl;
				}
			}
		}
	}

	void Plumber::update(float time, char** TileMap) {
		rect.left += dx * time;
		Collision(false, TileMap);
		if (!onGround) dy += 0.0005 * time;
		rect.top += dy * time;
		onGround = false;
		Collision(true, TileMap);

		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		
		if (dx < 0) sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 73 + 88, 244, -rect.width, rect.height));
		if (dx > 0) sprite.setTextureRect(sf::IntRect(88 * int(currentFrame) + 88, 244, rect.width, rect.height));
		if (dx == 0) { currentFrame = 0; sprite.setTextureRect(sf::IntRect(10, 244, rect.width, rect.height)); }
	
		if (rect.top > 32 * 35) { rect.top = ground; dy = 0; onGround = true; }

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}


//private:
	//float dx, dy;
	//sf::FloatRect rect;
	//bool onGround;
	//float currentFrame;
	//sf::Sprite sprite;
//};
/*
class Mob : public Creature {
	// поведение в режиме ожидания

	// движение по заданой траетории
};

*/