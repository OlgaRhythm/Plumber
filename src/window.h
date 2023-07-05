#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "creatures.h"

using namespace sf;

const int H = 20;
const int W = 37;
const int tile = 32; // размер плитки

char TileMap1[H][W] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 0
    "B                                  B",// 1
    "B   BBB   B     BB   BB  BBB       B",// 2
    "B   B  B  B    B  B B  B B  B      B",// 3
    "B   BBB   B    B  B B  B B  B      B",// 4
    "B   B  B  B    B  B B  B B  B      B",// 5
    "B   BBB   BBBB  BB   BB  BBB       B",// 6
    "B                                  B",// 7
    "B                                  B",// 8
    "B                                  B",// 9
    "B       BBBB                       B",// 10
    "B                   BBBBB          B",// 11
    "B                                  B",// 12
    "B     000                          B",// 13
    "B                                  B",// 14
    "B               BBB                B",// 15
    "B       B      B   B     BBB       B",// 16
    "B      B B    B     B   B   B      B",// 17
    "B     B   B  B       B B     B     B",// 18
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",// 19
};


int temp = 0;

void showWindow(const char* spriteListObjects, const char* spriteListMainCharacter, const char* spriteListMobs) {
    sf::RenderWindow window(sf::VideoMode(tile * W, tile * H), "Ordinary Plumber");
    
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
        float time = clock.getElapsedTime().asMilliseconds() * 3; // фиксируем время с последнего тика 
        clock.restart(); //! Надо изменить, а то персонаж двигается рывками
        //float time = 4.0f;

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
            p.dx = -0.1;
           
        } 
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            p.dx = 0.1;
        } 
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (p.onGround) {
                p.dy = -0.4;
                p.onGround = false;
            }
        }

        p.update(time, TileMap);

        window.clear(Color::White);

        for (size_t i = 0; i < H; ++i) {
            for (size_t j = 0; j < W; ++j) {
                if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Red);
                if (TileMap[i][j] == '0') { rectangle.setFillColor(Color::Green); TileMap[i][j] = '1'; }
                if (TileMap[i][j] == '1') { rectangle.setFillColor(Color::Yellow); TileMap[i][j] = '0'; }
                if (TileMap[i][j] == ' ') continue;
                rectangle.setPosition(j * tile, i * tile);
                window.draw(rectangle);
            }
        }

        window.draw(p.sprite);
        window.display();
    }

    return;
}