#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "creatures.h"
#include "map.h"

using namespace sf;

//const int H = 20;
//const int W = 66;
const int tile = 32; // размер плитки

int temp = 0;
// добавить 5 названий текстовых файлов с картами (на самом деле файлов 15)
void showWindow(const char* spriteListObjects, const char* spriteListMainCharacter, const char* spriteListMobs) {
    sf::RenderWindow window(sf::VideoMode(tile * 20 * 2, tile * 20), "Ordinary Plumber", sf::Style::Fullscreen);
    
    const char fN_backgroundObjects[] = "maps/001_bgO.txt";
    const char fN_inanimateObjects[] = "maps/001_iO.txt";
    const char fN_aliveObjects[] = "maps/001_aO.txt";

    Map MainMap(fN_backgroundObjects, fN_inanimateObjects, fN_aliveObjects); // фиксированная длина имени 16 и 14

    //float currentFrame = 0;
    Texture textureForMainCharacter;
    textureForMainCharacter.loadFromFile("img/spriteListMainCharacterOriginal.png");

    Plumber p(textureForMainCharacter); // создание персонажа

    Clock clock; //фиксируем время с последнего тика

    while (window.isOpen())
    {
        float time = (clock.getElapsedTime().asMilliseconds() + 0.25f) * 3; // фиксируем время с последнего тика 
        clock.restart(); //! Надо изменить, а то персонаж двигается рывками
        //float time = 1.0f;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                //MainMap.~Map();
            }
        }
        
        p.moveWithKeyboard();

        p.offsetting(550, 120); // смещение сцены относительно гг

        MainMap.update(window, p, time);
        
        window.display();

    }

    return;
}