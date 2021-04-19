//
// Created by aleks on 04/06/21.
//
#include "mob.h"
#include "main.h"

//start this at zero, otherwise it becomes whatever value was already at that location
//Don't forget to initialize your data!
int Mob::_mobPop = 0;

Mob::Mob(): _speed(1), _team(true) {
	_mobPop++;
	graphicsSetup();
}

Mob::Mob(double maxHealth, double x, double y): Entity(x, y), _health(maxHealth), _maxHealth(maxHealth), _speed(1), _team(true) {
	_mobPop++;
	graphicsSetup();
}

Mob::~Mob() {
	_mobPop--;
}

double Mob::getHealth() const {
		return _health;
}

double Mob::getMaxHp() const {
	return _maxHealth;
}

void Mob::setHealth(double x) {
		_health = x;
}

int Mob::getCount() {
	return _mobPop;
}

void Mob::die() {
	//_mobPop--; //Do not decrement this counter here, when the mob is deconstructed it will decrement again...

}

void Mob::revive() {
	setRedundant(false);
}

void Mob::attack(Mob* target) {

}

void Mob::damage(double damage) {
	if(damage < 0) damage *= -1;
	_health -= damage;
	checkHp();
}

void Mob::heal(double amt) {
	if(amt < 0) amt *= -1;
	_health += amt;
	checkHp();
}

void Mob::checkHp() {
	if(_health > _maxHealth) _health = _maxHealth;
	if(_health <= 0) die();
}

void Mob::healthRegen()
{
	if (_isAlive) // Regenerate health
	{
		if (_health < _maxHealth)
			_health += _hpPerFrame;
		if (_health > _maxHealth)
			_health = _maxHealth;
	}
	// Additional code for abilities that regen health
}

	// Any sort of mana regeneration that needs to be called
void Mob::manaRegen()
{
	if (_isAlive) // Regenerate mana
	{
		if (_mana < _maxMana)
			_mana += _mpPerFrame;
		if (_mana > _maxMana)
			_mana = _maxMana;
	}
	// Additional code for abilities that regen mana
}


void Mob::update() {
	addToXPos(0.5);
	_vel = { 0.5, 0.0 };
	spriteStateManager(getIsAlive());
}

void Mob::drawSelf(Example& gfx) const {
	// Drawing code here...
	decalOut(gfx);
}

// Calls the set up for this mob (Needs to be overwritten if data needs to be different)
void Mob::graphicsSetup()
{
	// This is just some default/temporary stuff to test the sprite code
	setGraphicParameters(1, { 16, 16 }, { 0.5f, 0.5f }, "Spider");
	setDeadSpriteSource({ 16, 16 });
	setAttackSpriteSource({ 0, 16 });

	setGraphicFrameTimer(20);
}

bool Mob::getIsAlive() { return _isAlive; };

// Increase Hp by hpPlus
void Mob::addToHealth(double hpPlus) {	_health += hpPlus;}
// Set Maximum health
void Mob::setMaxHealth(double hpMax){
	_maxHealth = hpMax;
}
// Set the Hp regenerated each frame
void Mob::setHpPerFrame(double hpRegen){
	_hpPerFrame = hpRegen;
}
// Increase the amount of health regenerated each frame
void Mob::addToHpPerFrame(double hpRegenPlus) {
	_hpPerFrame += hpRegenPlus;
}

double Mob::getMaxHealth() const {
	return _maxHealth;
}
double Mob::getHpPerFrame()  const {
	return _hpPerFrame;
}

// Mana
void Mob::setMana(double mp){
	_mana = mp;
}
// Increase Mp by mpPlus
void Mob::addToMana(double mpPlus){
	_mana += mpPlus;
}
// Set Maximum mana
void Mob::setMaxMana(double mpMax){
	_maxMana = mpMax;
}
// Set the Mp regenerated each frame
void Mob::setMpPerFrame(double mpRegen){
	_mpPerFrame = mpRegen;
}
// Increase the amount of mana regenerated each frame
void Mob::addToMpPerFrame(double mpRegenPlus){
	_mpPerFrame += mpRegenPlus;
}


double Mob::getMana() const {
	return _mana;
}
double Mob::getMaxMana() const {
	return _maxMana;
}
double Mob::getMpPerFrame()  const {
	return _mpPerFrame;
}


// Offense
// Set the amount of damage dealt by this mob
void Mob::setAttackDmg(double attackDmg){
	_attackDmg = attackDmg;
}
// Get the critical damage modifier for this mob
void Mob::setCritModifier(double critModifier){
	_critModifier = critModifier;
}
// Get the critical chance for this mob's attacks
void Mob::setCritChance(double critChance){
	_critChance = critChance;
}
// Get the range of attack for this mob
void Mob::setAttackRange(double attackRange){
	_attackRange = attackRange;
}

// Get the amount of damage dealt by this mob
double Mob::getAttackDmg() const {
	return _attackDmg;
}
// Get the critical damage modifier for this mob
double Mob::getCritModifier() const {
	return _critModifier;
}
// Get the critical chance for this mob's attacks
double Mob::getCritChance() const {
	return _critChance;
}
// Get the range of attack for this mob
double Mob::getAttackRange() const {
	return _attackRange;
}
// Get the distance between this mob and its target  - > // Prabably more of a level function
double Mob::getDistFromTarget() const {
	return _distFromTarget;
}





Team& Mob::getTeam() { return _team; }

double Mob::getSpeed() const { return _speed; }
void Mob::setSpeed(double i) { _speed = i; }
