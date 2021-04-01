#ifndef MOB_H
#define MOB_H

#include "entity.h"

class Mob : public Entity {

public:
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

	void update(int xPosMod, int yPosMod) {
		addToXPos(xPosMod);
		addToYPos(yPosMod);
	}

	~Mob(){
		_mobPop--;
	}
private:
	int _health;
	static int _mobPop;
};

#endif
