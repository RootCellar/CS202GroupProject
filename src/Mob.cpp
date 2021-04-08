//
// Created by aleks on 04/06/21.
//
#include "mob.h"

//start this at zero, otherwise it becomes whatever value was already at that location
//Don't forget to initialize your data!
int Mob::_mobPop = 0;
Mob::Mob(int health, double x, double y): Entity(x, y), _health(health) {
    _mobPop++;
}
Mob::Mob() {
	_mobPop++;
}

Mob::Mob(double maxHealth, double x, double y): Entity(x, y), _health(maxHealth), _maxHealth(maxHealth) {
	_mobPop++;
}

Mob::~Mob() {
	_mobPop--;
}

double Mob::getHealth() const {
		return _health;
}

void Mob::setHealth(double x) {
		_health = x;
}

int Mob::getCount() {
	return _mobPop;
}

void Mob::die() {
	//_mobPop--; //Do not decrement this counter here, when the mob is deconstructed it will decrement again...

}

void Mob::damage(double damage) {
	if(damage < 0) damage *= -1;
	_health -= damage;
	checkHp();
}

void Mob::heal(double amt) {
	if(amt < 0) amt *= -1;
	_health += amt;
	checkHp();
}

void Mob::checkHp() {
	if(_health > _maxHealth) _health = _maxHealth;
	if(_health <= 0) die();
}

void Mob::update() {

}
