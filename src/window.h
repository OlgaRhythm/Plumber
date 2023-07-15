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

void showWindow(const char* spriteListObjects, const char* spriteListMainCharacter, const char* spriteListMobs) {
    sf::RenderWindow window(sf::VideoMode(tile * 20 * 2, tile * 20), "Ordinary Plumber");
    
    Texture t;
    t.loadFromFile("img/spriteListMainCharacterOriginal.png");
    
    /*
    char** TileMap = new char* [H];
    for (size_t i = 0; i < H; ++i) {
        TileMap[i] = new char[W];
        for (size_t j = 0; j < W; ++j) {
            TileMap[i][j] = TileMap1[i][j];
        }
    }
    */


    Map MainMap(26, 66, 0);//
    MainMap.Map1();//

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
                /*
                for (size_t i = 0; i < H; ++i) {
                    delete[] TileMap[i];
                }
                delete[] TileMap;
                */
                //MainMap.~Map();
                window.close();
            }
        }
        
        p.moveWithKeyboard();

        p.offsetting(550, 250);

        p.update(time, MainMap.solidObjects);//

        // создается char 5 массивов, которые не меняются другими функциями, только заполняются
        // каждый массив соответствует своему уровню
        // в Map передается свой указатель для вывода этого массива

        /// Map (будет 5 разных карт со своими массивами и настройками фона)
        // смена карты происходит, когда встанем на трубу (in_teleport)
        // case, вызывается один из методов Map, который и выводит карту на экран

        MainMap.update(window, p);

        window.draw(p.getSprite());
        
        window.display();

    }

    return;
}