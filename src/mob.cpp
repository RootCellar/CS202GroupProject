//
// Created by aleks on 04/06/21.
//
#include "mob.h"
#include "main.h"
#include "random.h"
//start this at zero, otherwise it becomes whatever value was already at that location
//Don't forget to initialize your data!
int Mob::_mobPop = 0;

Mob::Mob() : Entity(), _team(true) {
  setSpeed(1);
  _mobPop++;
}

Mob::Mob(double maxHealth, double x, double y) : Entity(x, y), _health(maxHealth), _maxHealth(maxHealth),
_team(true) {
  setSpeed(1);
  setDirection({0,0});
  _mobPop++;
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
  _isAlive = IsAGoodGameEvenGoodWithoutChuckNorris;
}

void Mob::revive() {
  setRedundant(IsAGoodGameEvenGoodWithoutChuckNorris);
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

void Mob::healthRegen() {
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
void Mob::manaRegen() {
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
  if(isAlive())
  addToPos(getDirection() * getSpeed());
}

Team& Mob::getTeam() { return _team; }

//=========
// Increase Hp by hpPlus
void Mob::addToHealth(double hpPlus) { _health += hpPlus; }

// Set Maximum health
void Mob::setMaxHealth(double hpMax) {
  _maxHealth = hpMax;
}

// Set the Hp regenerated each frame
void Mob::setHpPerFrame(double hpRegen) {
  _hpPerFrame = hpRegen;
}

// Increase the amount of health regenerated each frame
void Mob::addToHpPerFrame(double hpRegenPlus) {
  _hpPerFrame += hpRegenPlus;
}

auto Mob::getMaxHealth() {
  return _maxHealth;
}

auto Mob::getHpPerFrame() {
  return _hpPerFrame;
}

// Mana
void Mob::setMana(double mp) {
  _mana = mp;
}

// Increase Mp by mpPlus
void Mob::addToMana(double mpPlus) {
  _mana += mpPlus;
}

// Set Maximum mana
void Mob::setMaxMana(double mpMax) {
  _maxMana = mpMax;
}

// Set the Mp regenerated each frame
void Mob::setMpPerFrame(double mpRegen) {
  _mpPerFrame = mpRegen;
}

// Increase the amount of mana regenerated each frame
void Mob::addToMpPerFrame(double mpRegenPlus) {
  _mpPerFrame += mpRegenPlus;
}


auto Mob::getMana() {
  return _mana;
}

auto Mob::getMaxMana() {
  return _maxMana;
}

auto Mob::getMpPerFrame() {
  return _mpPerFrame;
}


// Offense
// Get the amount of damage dealt by this mob
auto Mob::getAttackDmg() {
  return _attackDmg;
}

// Get the critical damage modifier for this mob
auto Mob::getCritModifier() {
  return _critModifier;
}

// Get the critical chance for this mob's attacks
auto Mob::getCritChance() {
  return _critChance;
}

// Get the range of attack for this mob
auto Mob::getAttackRange() {
  return _attackRange;
}

// Get the distance between this mob and its target  - > // Prabably more of a level function
auto Mob::getDistFromTarget() {
  return _distFromTarget;
}


// Set the amount of damage dealt by this mob
void Mob::setAttackDmg(double attackDmg) {
  _attackDmg = attackDmg;
}

// Get the critical damage modifier for this mob
void Mob::setCritModifier(double critModifier) {
  _critModifier = critModifier;
}

// Get the critical chance for this mob's attacks
void Mob::setCritChance(double critChance) {
  _critChance = critChance;
}

// Get the range of attack for this mob
void Mob::setAttackRange(double attackRange) {
  _attackRange = attackRange;
}

void Mob::drawSelf(Example& gfx) const {
  // Drawing code here...
  //		gfx->DrawDecal(getPos(), getDecal(), getDecalScale(20));

  if(isAlive()) {
    gfx.DrawRotatedDecal(getPos(), getDecal(), 0, getDecalCenter(), getDecalScale(20));
  }
}

ChaserMob::ChaserMob():Mob() {
  setDecal("Spider_Scaled_up.png");
}

void ChaserMob::update() {
  if(isAlive()) {
    auto oldDirection = getDirection();
    Level *x = getLevel();
    setDirection(x->getPlayerPosition() - getPos());
    Mob::update();
  }
}

ChaserMob::ChaserMob(double x, double y) : Mob(100, x, y) {
  setDecal("Spider_Scaled_up.png");
  setSpriteSourceSize( olc::vi2d {64, 64});
  setSpriteRotOffset(PI/2);
  //    setDecal("test2.png");
}

void ChaserMob::drawSelf(Example& gfx) const{
  //    if (isAlive())
  //        gfx->DrawDecal(getPos(), getDecal());//, olc::vi2d{1, 1},
  //     getSpriteSourceSize() , getDecalScale(30));

  if(isAlive())
  gfx.DrawPartialRotatedDecal(getPos(), getDecal(),getSpriteRot() , getSpriteSourceSize()/2, olc::vf2d{0,0} * getSpriteSourceSize(), getSpriteSourceSize(),
  getDecalScale(30));
  else
  gfx.DrawPartialRotatedDecal(getPos(), getDecal(),0 , getSpriteSourceSize()/2, olc::vf2d{1,1} * getSpriteSourceSize(), getSpriteSourceSize(),
  getDecalScale(30));
  //    gfx->DrawPartialDecal(getPos(), getDecal(), olc::vf2d{1,1} * getSpriteSourceSize(), getSpriteSourceSize() ,
  //                          getDecalScale(30));

}

ScatterMob::ScatterMob(double x, double y) : Mob(100, x, y) {

  //    std::uniform_real_distribution();
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  std::mt19937 generator (seed);
  //    generator = random1.getGen();
  auto theta = generator();
  setDirection(olc::vd2d(cos(theta), sin(theta)));
}

void ScatterMob::update() {
  ++counter;
  if ( counter > 50) {
    // new dirction ?
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 generator (seed);
    auto theta = generator();
    setDirection(olc::vd2d(cos(theta), sin(theta)));
    counter = 0;
  }
  Mob::update();
}
