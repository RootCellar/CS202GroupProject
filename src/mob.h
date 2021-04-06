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
	void update(/*int xPosMod, int yPosMod*/) override {
		//addToXPos(xPosMod);
		//addToYPos(yPosMod);
	}

	void drawSelf(Example& gfx) const override {
		// Drawing code here...
	}

private:
	int _health;
	static int _mobPop;

	void die();
};
#endif
