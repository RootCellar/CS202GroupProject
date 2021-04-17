//
// Created by aleks on 04/08/21.
//
#include "player.h"
#include "spell.h"
#include "main.h"
#include <vector>

Player::Player(): Mob(400, 50, 50), _lives(3) {
	setSpeed(1);
	playerTextSetup(getHealth(), getMana());
}

Player::Player(int health, int x, int y): Mob(health,x,y), _lives(3) {
	setSpeed(1);
	playerTextSetup(getHealth(), getMana());
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

	// Graphics related changes
	// Orb Wizard
	_bounceMotion += 0.12f;

	// Staff
	staffUpdate();
}

//This is called on every player update,
//note that updates happen 50 times per second.
//Choose/balance this number wisely!
//(Making it relative to maxHP makes it more like a percentage)
void Player::regen() {
	heal(getMaxHp() * 0.001);
}

void Player::drawSelf(Example& gfx) const {
	//gfx.drawPixel( getXPos(), getYPos(), 255, 0, 0);

	// Orb Wizard
	float changeX = 0.1f * cosf(_bounceMotion);
	float changeY = 0.05f * sinf(_bounceMotion - float(PI) / 2.0f);
	gfx.DrawPartialRotatedDecal({ (float)getXPos() - 4.0f * changeY, (float)getYPos() + 6.0f * changeX }, DecalMap::get().getDecal("Wizard"), 0.0f, { 8.0f, 8.0f }, { 0.0f, 0.0f }, { 16.0f, 14.0f }, { 0.90f + changeX, 0.95f + changeY });

	// Staff
	gfx.DrawPartialRotatedDecal(olc::vf2d{ (float)getXPos(), (float)getYPos() } +_staffPosFromPLayer + _staffPosOffset , DecalMap::get().getDecal("Staffs"), _staffAngle - PI / 7.0f, { 17.0f, 18.0f }, { 34.0f * _staffStage, 0 }, { 34.0f, 36.0f });

	// Health bar
	gfx.DrawPartialDecal({ 10.0f, 220.0f }, DecalMap::get().getDecal("Hp&Mp"), { 0.0f, 120.0f - 4.0f * std::ceil(float(getHealth() / getMaxHp() * 30.0)) }, { 32.0f, 5.0f });
	Text::overWriteText("HP " + valueToString(getHealth()), "HP", olc::PixelF(1.0 - getHealth() / getMaxHealth(), getHealth() / getMaxHealth(), 0));

	// Mana bar
	gfx.DrawPartialDecal({ 10.0f, 210.0f }, DecalMap::get().getDecal("Hp&Mp"), { 33.0f, 120.0f - 4.0f * std::ceil(float(getMana() / getMaxMana() * 30.0)) }, { 32.0f, 5.0f });
	Text::overWriteText("MP " + valueToString(getMana()), "MP", olc::PixelF(1.0 - (getMana() / getMaxMana()) * 0.7 - 0.3, 1.0 - getMana() / getMaxMana() * 0.7 - 0.3, 1.0));

}

void Player::die(){
	if(_lives < 0){
		//end the game & display a game over screen
		setRedundant(true);
		return;
	}
	//display dying animation or sprite
	//respawn in the starting location for the level
	_lives--;
}

void Player::upgradeStaff()
{
	if (_staffStage < 2)
	{
		_staffStage++;

		if (Text::doesTextExist("StaffUP"))
			Text::removeText("StaffUP");
		Text::addText("staff upgraded!", "StaffUP", { 255, 0, 0, 0 }, 255, { 0.25f * float(_staffStage + 1), 0.25f * float(_staffStage + 1) });
		Text::setTextPos("StaffUP", olc::vf2d{ (float)getXPos(), (float)getYPos() } - olc::vf2d{ 30.0f, 20.0f + 7.5f * float(_staffStage) });
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

// Sets up the text output for the player
void playerTextSetup(const double health, const double mana)
{
	Text::addText("HP " + valueToString(health), "HP", { 255, 25, 25 }, -1, { 0.5f, 0.5f });
	Text::setTextPos("HP", { 50, 220 });

	Text::addText("MP " + valueToString(mana), "MP", { 255, 25, 25 }, -1, { 0.5f, 0.5f });
	Text::setTextPos("MP", { 50, 210 });
}