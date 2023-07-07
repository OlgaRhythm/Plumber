#pragma once

#include "units.h"

class Object : public Unit {
public:
	void update() { // анимация

	}
private:
	bool solid;
	bool destructible;
	bool killing;

};

class Solid : public Object {

};

class Destructible : public Object {

};

class Moving : public Object {

};

class BoilingWater : public Object { // Observer

};

class Raft : public Object {

};

class Pipe : public Object {

};

class Tap : public Object {

};

class Jet : public Object { // Observer

};

class Valve : public Object { //Observable

};

class Teleport : public Object {

};

class Coin : public Object {

};

class Background : public Object {

};

////
class Listener
{
public:
    void AddEventListener (
		Valve* listener, void (Valve ::* action) (void)
    );
};