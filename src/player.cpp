//
// Created by aleks on 04/08/21.
//
#include "player.h"
#include "spell.h"
#include <vector>

Player::Player(): Mob(400, 50, 50), _lives(3) {}// Values passed to Mob() are temporary for now.

Player::Player(int health, int x, int y): Mob(health,x,y), _lives(3) {

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

void Player::update() {
	regen();


}

//This is called on every player update,
//note that updates happen 50 times per second.
//Choose/balance this number wisely!
//(Making it relative to maxHP makes it more like a percentage)
void Player::regen() {
	heal(getMaxHp() * 0.001);
}

void Player::die(){
	if(_lives < 0){
		//end the game & display a game over screen
	}
	//display dying animation or sprite
	//respawn in the starting location for the level
	_lives--;
}
