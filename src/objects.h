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

class Raft : public Object {

};

class Pipe : public Object {

};

class Tap : public Object {

};

class Teleport : public Object {

};

class Coin : public Object {

};

class Background : public Object {

};

class BoilingWater : public Object, public IObserver { // Observer

};

class Jet : public Object, public IObserver { // Observer

};

class Valve : public Object, public Observable { //Observable

};

//// паттерн Наблюдатель (примитивный)
class IObserver {
public:
	virtual void act() = 0;
};

class Observable {
public:
	Observable() : list(nullptr), size(0) {}

	Observable(IObserver *obs) : list(new IObserver* [1]), size(1) {
		list[0] = obs;
	}

	virtual ~Observable() {
		delete[] list;
		list = nullptr;
	}
	void addObserver(IObserver *obs) {
		++size;
	}

	void removeObserver(IObserver *obs) {
		--size;
	}

	void notifyObservers() {
		for (size_t i = 0; i < size; ++i) list[i]->act();
	}

private:
	IObserver** list;
	int size;
};



