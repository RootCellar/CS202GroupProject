#ifndef MOB_H
#define MOB_H

#include "entity.h"

class Mob : public Entity {

public:
	using Entity::Entity;

	Mob();

	~Mob();

	Mob(int health, int x, int y);

	int getHealth() const;

	void setHealth(int x);

	static int getCount();

	void takeDamage(int damage);

	// update function needs to have the same parameters as the update function it inherits/overrides
	void update() override;

	void drawSelf(Example& gfx) const override {
		// Drawing code here...
	}

	void die();

private:
	int _health;

	//Keeps track of the number of current constructed mobs in existence.
	//if you want a counter to keep mob counts within a range in the level,
	//it needs to be done differently.
	static int _mobPop;
};
#endif

/*
 * make a pure virtual function attack()
 * pass update() & drawSelf() onto the derived classes
 * create derived classes: anAcctualTank, gunThrower, spellCaster, tank, summoner, summonedMob
 */
