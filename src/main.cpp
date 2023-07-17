#include <iostream>
#include "window.h"
using namespace std;


int main()
{
	const char* spriteListObjects("img/spriteListObjectsOriginal.png");
	const char* spriteListMainCharacter("img/spriteListMainCharacterOriginal.png");
	const char* spriteListMobs("img/spriteListOriginalMobs.png");
	showWindow(spriteListObjects, spriteListMainCharacter, spriteListMobs);
	return 0;
}

/* TASKS:
* 1) Карта (хранение)
* 2) Класс Object и наследники
* 3) класс Creature (Collision, взаимодействие с разными блоками)
* 4) класс Plumber, Mob - взаимодействие между собой
* 
*/