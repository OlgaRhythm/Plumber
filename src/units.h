#include <SFML/Graphics.hpp>

class Unit {
public:
	Unit() {};
	virtual ~Unit() = 0;
protected:
	sf::Texture texture;
	int x;
	int y;
};
