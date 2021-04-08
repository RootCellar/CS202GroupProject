#ifndef MOB_H
#define MOB_H

#include "entity.h"

class Mob : public Entity {

public:
	using Entity::Entity;

	Mob();

	~Mob();

	Mob(double maxHealth, double x, double y);

	double getHealth() const;

	void setHealth(double x);

	static int getCount();

	void damage(double damage);

	void heal(double amt);

	void checkHp();

	// update function needs to have the same parameters as the update function it inherits/overrides
	void update() override;

	void drawSelf(olc::PixelGameEngine* gfx) const override {
		// Drawing code here...
	}

	void die();

private:
	double _health;
	double _maxHealth;

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
