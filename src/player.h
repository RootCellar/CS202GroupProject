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
    Player ( const std::string &text);

	const std::vector<Spell> * getSpellList();

	void setSpellSlot(int slotNum /*Spell type*/);

	void increaseMaxHealth(double mod);

	void update() override;

	void regen();
	void increaseMaxHealth(int mod);
	void attack(Mob& target);

	void move (const std::string &direction);

	void drawSelf(Example& gfx) const override;

	virtual void die() override;

	void upgradeStaff(); // Upgrades the staff sprite (should also probably upgrade the player's damage too)
	void staffUpdate(); // Updates the staff

private:

	float _bounceMotion = 0.0f; // Determines the shrink and stretch of the sprite for bouncy motion
	// Staffs drawing and updating parameters
	int _staffStage = 0;
	bool _staffUpgraded = false;
	float _staffOffsetAngle = 0.0f;
	float _staffAngle = 0.0f;
	bool _staffRotShiftLeft = false;
	olc::vf2d _staffPosFromPLayer = { 7.0f,0.0f };
	olc::vf2d _staffPosOffset = { 2.0f, 2.0f };

	olc::Pixel _staffUpTextColor = { 255, 0, 0, 0 };
	int _colorChangeHolder = 0;
	int _shakeTimer = 3;
	int _shakeCounter = 0;

	std::vector<Spell> _AvailableSpells[10];
	int _lives;
};

void playerTextSetup(const double health, const double mana);

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
