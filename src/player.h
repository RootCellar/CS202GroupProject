#ifndef PLAYER_H
#define PLAYER_H

#include "mob.h"
#include "spell.h"
#include <vector>
using std::vector;

class Player : public Mob {
public:
	using Mob::Mob;
	Player() {}
	Player(int health, int x, int y): Mob(health,x,y) {

	}

	const vector<Spell> * getSpellList() {
		return _AvailableSpells;
	}

	void setSpellSlot(int slotNum /*Spell type*/) {

	}

	void increaseMaxHealth(int mod) {
		setHealth((mod *= getHealth()));
	}

private:
	vector<Spell> _AvailableSpells[10];
};

#endif
