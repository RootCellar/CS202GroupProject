//
// Created by aleks on 04/08/21.
//
#include <vector>

#include "player.h"
#include "spell.h"
#include "main.h"

using std::string;

Player::Player(): Mob(400, 200, 200), _lives(3) {
	setSpeed(1);
	setMaxMana(500);
	playerTextSetup(getHealth(), getMana());
	set_decal("Barrier");
	setGraphicState(0, 18);
	setGraphicFrameTimer(5);
}

Player::Player(int health, int x, int y): Mob(health,x,y), _lives(3) {
	setSpeed(1);
	setMaxMana(500);
	playerTextSetup(getHealth(), getMana());
	set_decal("Barrier");
	setGraphicState(0, 18);
	setGraphicFrameTimer(5);
}

Player::Player(const string &text) : Mob( 100, 100, 100) {
	// test player if you use text as parameter
	// notice that constructor also sets decal
	setMaxMana(500);
	playerTextSetup(getHealth(), getMana());
	//setDecal("Orb_Wizard_and_Staff.png");
	set_decal("Barrier");
	setGraphicState(0, 18);
	setGraphicFrameTimer(5);
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
	setMaxHp((mod *= getHealth()));
}

void Player::update() {
	if (!isRedundant())
	{
		regen();
		manaRegen();
		if (getMana() > getMaxMana()) {
			setMana(getMaxMana());
		}

		//damage(4.0);

		// Speed spell
		if (getSpeed() > 1.0)
		{
			if (_speedSpellDuration > 0)
				_speedSpellDuration--;
			else
				setSpeed(1.0);
		}

		if (_barrier)
		{
			regen();
			regen();
			setMana(getMana() - 0.6);
			if (getMana() <= 0.0)
				_barrier = false;
		}


		// Graphics related changes
		// Orb Wizard
		_bounceMotion += 0.12f;

		// Staff
		staffUpdate();

		// Barrier for now
		spriteStateManager(isAlive());
	}
}

//This is called on every player update,
//note that updates happen 50 times per second.
//Choose/balance this number wisely!
//(Making it relative to maxHP makes it more like a percentage)
void Player::regen() {
	heal(getMaxHp() * 0.001);
}

void Player::manaRegen() {
	addToMana(getMaxMana() * 0.001);
}

void Player::drawSelf(Example& gfx) const {

	// HOT Bar
	gfx.DrawPartialDecal({ 0.0f, 214.0f }, DecalMap::get().getDecal("HOT"), { 0.0f, 0.0f }, { 165.0f, 26.0f });

	// Player center screen
	float screenCenterX = gfx.ScreenWidth() / 2.0f - getSpriteSourceSize().x / 2;
	float screenCenterY = gfx.ScreenHeight() / 2.0f - getSpriteSourceSize().y / 2;

	// Barrier
	if(_barrier)
		gfx.DrawPartialDecal({ screenCenterX - 8.0f, screenCenterY - 8.0f }, DecalMap::get().getDecal("Barrier"), { (float)getSpriteSheetOffset().x, 16.0f }, { 16.0f, 16.0f });

	// Orb Wizard
	float changeX = 0.1f * cosf(_bounceMotion);
	float changeY = 0.05f * sinf(_bounceMotion - float(PI) / 2.0f);
	gfx.DrawPartialRotatedDecal({ screenCenterX - 4.0f * changeY, screenCenterY + 6.0f * changeX }, DecalMap::get().getDecal("Wizard"), 0.0f, { 8.0f, 8.0f }, { 0.0f, 0.0f }, { 16.0f, 14.0f }, { 0.90f + changeX, 0.95f + changeY });

	if (_barrier)
		gfx.DrawPartialDecal({ screenCenterX - 8.0f, screenCenterY - 8.0f }, DecalMap::get().getDecal("Barrier"), { (float)getSpriteSheetOffset().x, 0.0f }, { 16.0f, 16.0f });

	// Staff
	gfx.DrawPartialRotatedDecal(olc::vf2d{ screenCenterX, screenCenterY } +_staffPosFromPLayer + _staffPosOffset, DecalMap::get().getDecal("Staffs"), _staffAngle - PI / 7.0f, { 17.0f, 18.0f }, { 34.0f * _staffStage, 0 }, { 34.0f, 36.0f });

	// Health bar
	gfx.DrawPartialDecal({ 5.0f, 205.0f }, DecalMap::get().getDecal("Hp&Mp"), { 0.0f, 120.0f - 4.0f * std::ceil(float(getHealth() / getMaxHp() * 30.0)) }, { 32.0f, 5.0f });
	Text::overWriteText("HP " + valueToString( (int)getHealth() ), "HP", olc::PixelF(1.0 - getHealth() / getMaxHealth(), getHealth() / getMaxHealth(), 0));

	// Mana bar
	gfx.DrawPartialDecal({ 5.0f, 195.0f }, DecalMap::get().getDecal("Hp&Mp"), { 33.0f, 120.0f - 4.0f * std::ceil(float(getMana() / getMaxMana() * 30.0)) }, { 32.0f, 5.0f });
	Text::overWriteText("MP " + valueToString( (int)getMana() ), "MP", olc::PixelF(1.0 - (getMana() / getMaxMana()) * 0.7 - 0.3, 1.0 - getMana() / getMaxMana() * 0.7 - 0.3, 1.0));

}

void Player::die(){
	_lives--;

	if (_lives == 0)
	{
		if (!Text::doesTextExist("last life"))
		{
			Text::addText("You are on your last life!", "last life", { 200, 0, 0 }, 80, {0.5f, 0.5f});
			Text::addToTextPos("last life", { 60.0f, 80.0f });
		}
	}
	else if (_lives == 2)
	{
		if (!Text::doesTextExist("Died"))
		{
			Text::addText("You died", "Died", { 200, 0, 0 }, 80, { 0.5f, 0.5f });
			Text::addToTextPos("Died", { 100.0f, 80.0f });
		}
	}
	else if (_lives == 1)
	{
		if (!Text::doesTextExist("Died again"))
		{
			Text::addText("You died. Again...", "Died again", { 200, 0, 0 }, 80, { 0.5f, 0.5f });
			Text::addToTextPos("Died again", { 85.0f, 80.0f });
		}
	};

	if (_lives < 0) {
		//the player has died....
		setRedundant();

		Text::addText("You have died for the last time!", "last death", { 200, 0, 0 }, 200, { 0.7f, 0.7f });
		Text::addText("Game over!", "Game over", { 200, 0, 0 }, 300, { 1.5f, 2.0f });
		Text::addToTextPos("Game over", { 40.0f, 40.0f });

		return;
	}

	//display dying animation or sprite
	//respawn in the starting location for the level

	Text::overWriteText("Spare Lives " + valueToString(_lives), "Spare Lives", { 255, uint8_t(255 / 3 * _lives), uint8_t(255 / 3 * _lives) });



	heal(getMaxHp());
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

	//Multiply changeToPos by speed to apply proper position change
	addToPos(changeToPos * getSpeed());
}


void Player::upgradeStaff()
{
	if (_staffStage < 2)
	{
		_staffStage++;

		if (Text::doesTextExist("StaffUP"))
			Text::removeText("StaffUP");
		Text::addText("staff upgraded!", "StaffUP", { 255, 0, 0, 0 }, 255, { 0.25f * float(_staffStage + 1), 0.25f * float(_staffStage + 1) });
		Text::setTextPos("StaffUP", olc::vf2d{ (float)getXPos(), (float)getYPos() } -olc::vf2d{ 30.0f, 20.0f + 7.5f * float(_staffStage) });
	}
}

void Player::staffUpdate()
{
	if (Text::doesTextExist("StaffUP"))
	{
		int colorChangeRate = 4;
		if (_staffUpTextColor.r == 255 && _staffUpTextColor.g < 255 && _staffUpTextColor.b == 0) // Red to yellow
		{
			_colorChangeHolder += 5 * colorChangeRate;
			if (_colorChangeHolder > 255)
				_colorChangeHolder = 255;

			_staffUpTextColor.g = _colorChangeHolder;
		};

		if (_staffUpTextColor.r > 0 && _staffUpTextColor.g == 255 && _staffUpTextColor.b == 0) // Yellow to green
		{
			_colorChangeHolder -= 5 * colorChangeRate;
			if (_colorChangeHolder < 0)
				_colorChangeHolder = 0;

			_staffUpTextColor.r = _colorChangeHolder;
		};

		if (_staffUpTextColor.r == 0 && _staffUpTextColor.g == 255 && _staffUpTextColor.b < 255) // Green to aqua
		{
			_colorChangeHolder += 5 * colorChangeRate;
			if (_colorChangeHolder > 255)
				_colorChangeHolder = 255;

			_staffUpTextColor.b = _colorChangeHolder;
		};

		if (_staffUpTextColor.r == 0 && _staffUpTextColor.g > 0 && _staffUpTextColor.b == 255) // Aqua to blue
		{
			_colorChangeHolder -= 5 * colorChangeRate;
			if (_colorChangeHolder < 0)
				_colorChangeHolder = 0;

			_staffUpTextColor.g = _colorChangeHolder;
		};

		if (_staffUpTextColor.r < 255 && _staffUpTextColor.g == 0 && _staffUpTextColor.b == 255) // Blue to purple
		{
			_colorChangeHolder += 5 * colorChangeRate;
			if (_colorChangeHolder > 255)
				_colorChangeHolder = 255;

			_staffUpTextColor.r = _colorChangeHolder;
		};

		if (_staffUpTextColor.r == 255 && _staffUpTextColor.g == 0 && _staffUpTextColor.b > 0) // Purple to red
		{
			_colorChangeHolder -= 5 * colorChangeRate;
			if (_colorChangeHolder < 0)
				_colorChangeHolder = 0;

			_staffUpTextColor.b = _colorChangeHolder;
		};

		_staffUpTextColor.a -= 1;

		Text::editTextColor("StaffUP", _staffUpTextColor);

		_shakeCounter++;

		if (_shakeCounter == _shakeTimer)
		{
			Text::addToTextPos("StaffUP", { float(rand() % 2) - 0.5f, float(rand() % 2) - 0.5f });
			_shakeCounter = 0;
		}
	}

	if (_staffRotShiftLeft)
	{
		_staffAngle += 0.008;
		if (_staffAngle > PI / 7.0f) // Maybe 8.0f is better than 7.0f
			_staffRotShiftLeft = false;
	}
	else
	{
		_staffAngle -= 0.008;
		if (_staffAngle < 0.0f)
			_staffRotShiftLeft = true;
	}

	_staffOffsetAngle += 0.064f;
	_staffPosOffset = { 2.0f, 2.0f };

	if (_staffOffsetAngle > PI * 4.0f)
		_staffOffsetAngle -= PI * 4.0f;

	if (_staffOffsetAngle >= 0 && _staffOffsetAngle < PI * 2.0f)
	{
		_staffPosOffset.x *= cosf(_staffOffsetAngle);
		_staffPosOffset.y *= sinf(_staffOffsetAngle);
	}
	else if (_staffOffsetAngle >= PI * 2.0f && _staffOffsetAngle < PI * 4.0f)
	{
		_staffPosOffset.x *= cosf(_staffOffsetAngle) / 2.0f + 0.5f;
		_staffPosOffset.y *= sinf(_staffOffsetAngle) / 2.0f;
	}
}

// Activates the player's barrier spell
void Player::toggleBarrier()
{
	if (_barrier)
		_barrier = false;
	else
	{
		if (getMana() - 50 >= 0.0)
		{
			_barrier = true;
			setMana(getMana() - 50);
		}
	}
}

// Sets up the text output for the player
void playerTextSetup(const double health, const double mana)
{
	Text::addText("HP " + valueToString(health), "HP", { 255, 25, 25 }, -1, { 0.5f, 0.5f });
	Text::setTextPos("HP", { 40, 205 });

	Text::addText("MP " + valueToString(mana), "MP", { 255, 25, 25 }, -1, { 0.5f, 0.5f });
	Text::setTextPos("MP", { 40, 195 });

	Text::addText("Spare Lives " + valueToString(3), "Spare Lives", { 255, 255, 255 }, -1, { 0.5f, 0.5f });
	Text::setTextPos("Spare Lives", { 85, 205 });
}
