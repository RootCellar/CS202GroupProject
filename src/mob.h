#ifndef MOB_H
#define MOB_H

#include "entity.h"

class Mob : public Entity {

public:
	Mob(int health, int x, int y): _health(health){
		setXPos(x);
		setYPos(y);
	}

	int getHealth() const {
		return _health;
	}

	void setHealth(int x) {
		_health = x;
	}

	void update() {
		//pass through current positions to entity using member functions
	}

	~Mob()= default;
private:
	int _health;
};

#endif
