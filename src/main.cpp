#include <iostream>
#include "window.h"
using namespace std;
//tile = 32

int main()
{
	const char* spriteListObjects("img/spriteListObjectsOriginal.png");
	const char* spriteListMainCharacter("img/spriteListMainCharacterOriginal.png");
	const char* spriteListMobs("img/spriteListOriginalMobs.png");
	showWindow(spriteListObjects, spriteListMainCharacter, spriteListMobs);


    /*
    Texture textureForMainCharacter;
    textureForMainCharacter.loadFromFile("img/spriteListObjectsOriginal.png");

    Solid p(textureForMainCharacter); // создание персонажа

	sf::RenderWindow window(sf::VideoMode(tile * 6, tile * 6), "test");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
        window.clear(sf::Color::White);
        //window.draw(p);
        p.display(window, 0, 0, 0.0f, 0.0f, 0.0f);
        window.display();
    }*/
	return 0;
}

/* TASKS:
* |\/| 1) Карта (хранение) [в 2-х текстовых файлах]
* | _| 2) Класс Object и наследники
* | _| 3) класс Creature (Collision, взаимодействие с разными блоками)
* | _| 4) класс Plumber, Mob - взаимодействие между собой
* | _| 5) смена карт, класс Trigger
* 
*/