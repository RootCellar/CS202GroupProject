#ifndef MOB_H
#define MOB_H

#include "entity.h"
#include "team.h"

class Mob : public Entity {

public:
	using Entity::Entity;

	Mob();

	virtual ~Mob();

	Mob(double maxHealth, double x, double y);

	double getHealth() const;

	void setHealth(double x);

	double getMaxHp() const;

	static int getCount();

	void damage(double damage);

	void heal(double amt);

	void checkHp();

	// update function needs to have the same parameters as the update function it inherits/overrides
	void update() override;

	virtual void drawSelf(olc::PixelGameEngine* gfx) const override {
		// Drawing code here...
//		gfx->DrawDecal(getPos(), getDecal(), getDecalScale(20));
		gfx->DrawRotatedDecal(getPos(), getDecal(), 0, getDecalCenter(), getDecalScale(20));
	}

	virtual void die();
	virtual void revive();

	//each type of mob will have a different attack type & it is up to them to implement this
	virtual void attack(Mob* target);

	Team& getTeam();

	double getSpeed() const;
	void setSpeed(double);

private:
	double _health;
	double _maxHealth;

	double _speed;

	Team _team;

	//Keeps track of the number of current constructed mobs in existence.
	//if you want a counter to keep mob counts within a range in the level,
	//it needs to be done differently.
	static int _mobPop;
};

#endif

/*
 * make a pure virtual function attack()
 * pass update() & drawSelf() onto the derived classes
 * create derived classes: anActualTank, gunThrower, spellCaster, tank, summoner, summonedMob
 */
