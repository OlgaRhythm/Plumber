#include "units.h"
#include "creatures.h"

class Plumber : public Unit { //keybord control
public:
	Plumber() {
		sf::Texture tempTexture;
	}
private:
	float dx, dy;
	sf::FloatRect rect;
	bool onGround;
	float currentFrame;
	sf::Sprite sprite;
};

class Creature : public Unit { //AI
public:
	void moving() {

	}
};

