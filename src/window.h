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
    sf::RenderWindow window(sf::VideoMode(tile * 20 * 2, tile * 20), "Ordinary Plumber");
    
    Texture t;
    t.loadFromFile("img/spriteListMainCharacterOriginal.png");

    Map MainMap(26, 66);
    MainMap.Map1();

    //float currentFrame = 0;
    Plumber p(t); // создание персонажа

    Clock clock; //фиксируем время с последнего тика

    //sf::RectangleShape rectangle(sf::Vector2f(tile, tile));

    while (window.isOpen())
    {
        //float time = clock.getElapsedTime().asMilliseconds() * 3; // фиксируем время с последнего тика 
        //clock.restart(); //! Надо изменить, а то персонаж двигается рывками
        float time = 1.0f;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                //MainMap.~Map();
            }
        }
        
        p.moveWithKeyboard();

        p.offsetting(550, 250);

        p.update(time, MainMap.backgroundAndObjects);

        MainMap.update(window, p);

        window.draw(p.getSprite());
        
        window.display();

    }

    return;
}