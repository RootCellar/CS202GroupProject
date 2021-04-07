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

// update function needs to have the same parameters as the update function it inherits/overrides
void Mob::update(/*int xPosMod, int yPosMod*/) override {
	//addToXPos(xPosMod);
	//addToYPos(yPosMod);
	healthRegen();
	manaRegen(); // Maybe not this one for everything
}

// Any sort of health regeneration that needs to be called
void Mob::healthRegen()
{
	if (_isAlive) // Regenerate health
	{
		if (_health < _maxHealth)
			_health += _hpPerFrame;
		if (_health > _maxHealth)
			_health = _maxHealth;
	}
	// Additional code for abilities that regen health
}

// Any sort of mana regeneration that needs to be called
void Mob::manaRegen()
{
	if (_isAlive) // Regenerate mana
	{
		if (_mana < _maxMana)
			_mana += _mpPerFrame;
		if (_mana > _maxMana)
			_mana = _maxMana;
	}
	// Additional code for abilities that regen mana
}

void Mob::movement() // Has levelRef and members to determine speed and direction or if to stop
{
	if (_vel.x > 0)
		_spriteRot = atanf(_vel.y / _vel.x);
	else
		_spriteRot = atanf((_vel.y / _vel.x) + PI);
}

bool Mob::inRange(const Mob& target) // Has levelRef and members to determine location
{
	
}


void Mob::drawSelf(Example& gfx) const override {
	// Drawing code here...
}

Mob::~Mob() {
	_mobPop--;
}