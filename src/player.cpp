//
// Created by aleks on 04/08/21.
//
#include "player.h"
#include "spell.h"
#include <vector>

int Player::_lives = 3;
Player::Player(): Mob(400, 50, 50) {}// Values passed to Mob() are temporary for now.

Player::Player(int health, int x, int y): Mob(health,x,y) {

}
Player::Player(const string &text) : Mob( 100, 100, 100) {
    // test player if you use text as parameter
    // notice that constructor also sets decal
    setDecal("Orb_Wizard_and_Staff.png");
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

void Player::attack(Mob &target) {
	//code to have the player select a spell or melee

	//target takes damage if the attack hits
	//target.damage(/*amount of damage dealt*/);
}

void Player::die(){
	if(_lives < 0){
		//end the game & display a game over screen
	}
	//display dying animation or sprite
	//respawn in the starting location for the level
	_lives--;
}
// Uses the PGE's way to take input implemented at main.cpp
// gets the string and moves player position corresponding direction
void Player::move(const string &direction) {
    olc::vd2d north = {0, -1}, east = {1, 0}, changeToPos;
    if ( direction == "up")
        changeToPos = north;
    else if (direction == "down")
        changeToPos = north * (-1);
    else if (direction == "right")
        changeToPos = east;
    else if (direction == "left")
        changeToPos = east * (-1);
    // note may use a multiplier to influence the amount of change
    addToPos(changeToPos);
}



