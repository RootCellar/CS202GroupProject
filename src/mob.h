#ifndef MOB_H
#define MOB_H

#include "entity.h"

class Mob : public Entity {

public:

	int getHealth() {
		return _health;
	}

	void setHealth() {

	}

	void update(int xPos, int yPos){

	}

	~Mob()= default;
private:
	int _health;

};

#endif
