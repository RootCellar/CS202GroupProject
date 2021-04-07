#ifndef PLAYER_H
#define PLAYER_H

#include "mob.h"
#include "spell.h"
#include <vector>
using std::vector;

class Player : public Mob {
public:
	using Mob::Mob;
	Player() ;
//	Player(int health, int x, int y): Mob(health,x,y) {
//
//	}

    Player(int health, const olc::vd2d &sPos);
	const vector<Spell> * getSpellList();

	void setSpellSlot(int slotNum /*Spell type*/);

	void increaseMaxHealth(int mod);

private:
	vector<Spell> _AvailableSpells[10];
};


#endif
/*
 * add levelUp() based on # of waves completed
 * levelUp should increaseMaxHealth & add a spellSlot
 * increaseMaxHealth should be set to private
 * Player should implement the drawSelf function handed down from entity
 * add attack() function that attacks using the spell in the indicated spellSlot & melees by default
 * add mana variable & accessor functions
 * add regen function for health & mana
 * decide if mana should be a const value or if it should increase as the player levels up
 * player should have a set number of lives & that num should go down when they die - if number of lives reaches zero send trigger to end the game
 */