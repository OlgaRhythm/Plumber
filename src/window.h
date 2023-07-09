#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "creatures.h"

using namespace sf;

const int H = 20;
const int W = 66;
const int tile = 32; // размер плитки

char TileMap1[H][W] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 0
    "B                                                        B",// 1
    "B   BBB   B     BB   BB  BBB                             B",// 2
    "B   B  B  B    B  B B  B B  B                            B",// 3
    "B   BBB   B    B  B B  B B  B                            B",// 4
    "B   B  B  B    B  B B  B B  B                            B",// 5
    "B   BBB   BBBB  BB   BB  BBB               0             B",// 6
    "B                                                        B",// 7
    "B                0000                          B         B",// 8
    "B                                        B               B",// 9
    "B       BBBB                   BBBB                      B",// 10
    "B            00     BBBBB                                B",// 11
    "B                         0                              B",// 12
    "B     000                0                               B",// 13
    "B                       0       0                        B",// 14
    "B               BBB             0                        B",// 15
    "B       B      B B B     BBB    0                        B",// 16
    "B      B B    B     B   B   B                            B",// 17
    "B     B   B  B       B B     B                           B",// 18
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 19
};


int temp = 0;

void showWindow(const char* spriteListObjects, const char* spriteListMainCharacter, const char* spriteListMobs) {
    sf::RenderWindow window(sf::VideoMode(tile * H * 2, tile * H), "Ordinary Plumber");
    
    Texture t;
    //t.loadFromFile(spriteListMainCharacter);
    t.loadFromFile("img/spriteListMainCharacterOriginal.png");

    float currentFrame = 0;
    
    char** TileMap = new char* [H];
    for (size_t i = 0; i < H; ++i) {
        TileMap[i] = new char[W];
        for (size_t j = 0; j < W; ++j) {
            TileMap[i][j] = TileMap1[i][j];
        }
    }
    

    Plumber p(t, TileMap);

    Clock clock; //фиксируем время с последнего тика

    sf::RectangleShape rectangle(sf::Vector2f(tile, tile));

    while (window.isOpen())
    {
        //float time = clock.getElapsedTime().asMilliseconds() * 3; // фиксируем время с последнего тика 
        //clock.restart(); //! Надо изменить, а то персонаж двигается рывками
        float time = 1.0f;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                for (size_t i = 0; i < H; ++i) {
                    delete[] TileMap[i];
                }
                delete[] TileMap;
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            p.moveToTheLeft(0.1);
        } 
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            p.moveToTheRight(0.1);
        } 
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            p.jump(0.5);
        }

        p.offsetting(550, 250);

        p.update(time, TileMap);

        window.clear(Color::White);

        for (size_t i = 0; i < H; ++i) {
            for (size_t j = 0; j < W; ++j) {
                if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Red);
                if (TileMap[i][j] == '0') { rectangle.setFillColor(Color::Green); TileMap[i][j] = '1'; }
                if (TileMap[i][j] == '1') { rectangle.setFillColor(Color::Yellow); TileMap[i][j] = '0'; }
                if (TileMap[i][j] == ' ') continue;
                rectangle.setPosition(j * tile - p.getOffsetX(), i * tile - p.getOffsetY());
                window.draw(rectangle);
            }
        }

        window.draw(p.getSprite());
        window.display();
    }

    return;
}