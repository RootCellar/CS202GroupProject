#ifndef MOB_H
#define MOB_H

#include "entity.h"

class Mob : public Entity {

public:
	using Entity::Entity;

	Mob() {
		_mobPop++;
	}

	Mob(int health, int x, int y): _health(health){
		setXPos(x);
		setYPos(y);
		_mobPop++;
	}

	int getHealth() const{
		return _health;
	}

	void setHealth(int x) {
		_health = x;
	}

	int getCount() const{
		return _mobPop;
	}

	// update function needs to have the same parameters as the update function it inherits/overrides
	void update(/*int xPosMod, int yPosMod*/) override {
		//addToXPos(xPosMod);
		//addToYPos(yPosMod);
	}

//	virtual void drawSelf(olc::PixelGameEngine& gfx) const override {
		// Drawing code here...
//	}

	~Mob(){
		_mobPop--;
	}
private:
	int _health;
	static int _mobPop;
};

//start this at zero, otherwise it becomes whatever value was already at that location
//Don't forget to initialize your data!
int Mob::_mobPop = 0;

#endif
