#ifndef PLAYER_H
#define PLAYER_H

#include "mob.h"
#include "spell.h"
#include <vector>
//using std::vector; //removed the using statement because it is propper practice not to have using statements in the header files

class Player : public Mob {
public:
	using Mob::Mob;
	Player();
	Player(int health, int x, int y);

	const std::vector<Spell> * getSpellList();

	void setSpellSlot(int slotNum /*Spell type*/);

	void increaseMaxHealth(double mod);

	void attack(Mob& target) override;

	void die() override;
private:
	std::vector<Spell> _AvailableSpells[10];
	static int _lives;
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