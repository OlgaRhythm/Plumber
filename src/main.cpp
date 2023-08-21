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
	return 0;
}

/* TASKS:
* |\/| 1) Карта (хранение) [в 2-х текстовых файлах]
* | _| 2) Класс Object и наследники
* | _| 3) класс Creature (Collision, взаимодействие с разными блоками)
* | _| 4) класс Plumber, Mob - взаимодействие между собой
* | _| 5) смена карт, класс Trigger
* 
* 
* Игра вылетает при изменении окна (@_@)
* 
* Странная анимация, если напрыгивать на объект сверху
*/
