#ifndef MOB_H
#define MOB_H

#include "entity.h"

class Mob : public Entity {

public:
	using Entity::Entity;
	//Mod shouldn't have a default constructor; nothing should ever be just a Mob
/*
	Mob() {
		_mobPop++;
	}
*/
	Mob(int health, int x, int y);

	int getHealth() const;

	void setHealth(int x);

	static int getCount();

	void takeDamage(int damage);

	// update function needs to have the same parameters as the update function it inherits/overrides
	void update(/*int xPosMod, int yPosMod*/) override;

	// Any sort of health regeneration that needs to be called
	void healthRegen();

	// Any sort of mana regeneration that needs to be called
	void manaRegen();

	void movement();

	bool inRange(const Mob& target);

	void drawSelf(Example& gfx) override;

	~Mob();

private:
	// Personal State
	bool _isAlive = true;

	// Health
	int _health;
	int _maxHealth;
	double _hpPerFrame;

	// Mana
	int _mana;
	int _maxMana;
	double _mpPerFrame;

	// Offense
	bool _hasTarget;
	int _dmgDealt;
	double _critModifier;
	int _critChance;
	double _range;
	double _distFromTarget;

	static int _mobPop;

	//Functions
	void die();
};
#endif
