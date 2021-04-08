//
// Created by aleks on 04/08/21.
//
#include "player.h"
#include "spell.h"
#include <vector>

Player::Player(): Mob(400, 50, 50) {}// Values passed to Mob() are temporary for now.

Player::Player(int health, int x, int y): Mob(health,x,y) {

}

const std::vector<Spell> *Player::getSpellList() {
	return _AvailableSpells;
}

// used for adding a spell when the player completes a level or levels up
//sould have a random selecion of spells to choose from depending on the level
void Player::setSpellSlot(int slotNum) {

}

//used to increase the max health of the player when they level up or completes a level
void Player::increaseMaxHealth(double mod) {
	setHealth((mod *= getHealth()));
}
