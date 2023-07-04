#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "creatures.h"

using namespace sf;

void showWindow(const char* spriteListObjects, const char* spriteListMainCharacter, const char* spriteListMobs) {
    sf::RenderWindow window(sf::VideoMode(500, 200), "Ordinary Plumber");
    
    Texture t;
    //t.loadFromFile(spriteListMainCharacter);
    t.loadFromFile("img/spriteListMainCharacterOriginal.png");

    float currentFrame = 0;

    Sprite s;
    s.setTexture(t);
    s.setTextureRect(IntRect(10, 244, 75, 100));
    s.setPosition(50, 100);

    Clock clock; //фиксируем время с последнего тика

    while (window.isOpen())
    {
        //float time = clock.getElapsedTime().asMilliseconds() * 10; // фиксируем время с последнего тика 
        //clock.restart(); //! Надо изменить, а то персонаж двигается рывками
        float time = 2.0f;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            s.move(-0.1*time, 0);
            currentFrame += 0.005*time;
            if (currentFrame > 3) currentFrame -= 3;
            s.setTextureRect(IntRect(88 * int(currentFrame) + 73 + 88, 244, -73, 100));
        } 
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            s.move(0.1*time, 0);
            currentFrame += 0.005*time;
            if (currentFrame > 3) currentFrame -= 3;
            s.setTextureRect(IntRect(88 * int(currentFrame) + 88, 244, 73, 100));
        } 
        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            s.move(0, -0.1*time);
        }
        else {
            currentFrame = 0.0f;
            s.setTextureRect(IntRect(10, 244, 75, 100));
        }

        window.clear();
        window.draw(s);
        window.display();
    }

    return;
}