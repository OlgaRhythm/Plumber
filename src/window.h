#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

/*void showWindow() {
	RenderWindow window( VideoMode(200, 200), "Test!");
	CircleShape MyC(100.f);
	MyC.setFillColor(Color::Green);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(MyC);
		window.display();
	}
}*/