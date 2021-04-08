//
// Created by uddeepk on 4/6/21.
//
#include "player.h"
Player::Player():Mob(500, olc::vd2d {0, 0}) {
    // Boom player at
}
Player::Player(int health,const olc::vd2d &sPos):Mob(health, sPos) {
    // Hi
}

const vector<Spell> *Player::getSpellList() {
    return _AvailableSpells;
}

void Player::setSpellSlot(int slotNum) {

}

void Player::increaseMaxHealth(int mod) {
    setHealth((mod *= getHealth()));
}
