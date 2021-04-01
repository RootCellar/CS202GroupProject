#ifndef PLAYER_H
#define PLAYER_H

#include "mob.h"
#include "spell.h"
#include <vector>
using std::vector;

class Player : public Mob {
public:
	Player(int health, int x, int y): Mob(health,x,y){

	}
private:

};

#endif
