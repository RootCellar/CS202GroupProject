//
// Created by aleks on 04/06/21.
//
#include "mob.h"

//start this at zero, otherwise it becomes whatever value was already at that location
//Don't forget to initialize your data!
int Mob::_mobPop = 0;

Mob::Mob(int health, int x, int y): _health(health) {
	setXPos(x);
	setYPos(y);
	_mobPop++;
}

int Mob::getHealth() const {
		return _health;
}

void Mob::setHealth(int x) {
		_health = x;
}

int Mob::getCount() {
	return _mobPop;
}

void Mob::die() {
	_mobPop--;
	// run a dying animation possibly
	//
}

void Mob::takeDamage(int damage) {
	_health -= damage;
	if(_health <= 0)
		die();
}

