//
// Created by aleks on 04/06/21.
//
#include "mob.h"
#include "main.h"
#include "random.h"

#include "debug.h"
//start this at zero, otherwise it becomes whatever value was already at that location
//Don't forget to initialize your data!
int Mob::_mobPop = 0;

Mob::Mob() : Entity(), _team(true), _mana(0), _maxMana(100) {
  setSpeed(1);
  _mobPop++;
}

Mob::Mob(double maxHealth, double x, double y) : Entity(x, y), _health(maxHealth), _maxHealth(maxHealth),
_team(true), _mana(0), _maxMana(100) {
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

void Mob::setMaxHp(double d) {
  _maxHealth = d;
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
  spriteStateManager(isAlive());
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
    setDeadSpriteSource({ 1.0f, 1.0f });
    setAttackSpriteSource({ 0.0f, 1.0f });

    setGraphicFrameTimer(20);
}

Team& Mob::getTeam() { return _team; }

void Mob::setTeam(Team t) {
  _team = t;
}

//=========
// Increase Hp by hpPlus
void Mob::addToHealth(double hpPlus) { _health += hpPlus; }

// Set the Hp regenerated each frame
void Mob::setHpPerFrame(double hpRegen) {
  _hpPerFrame = hpRegen;
}

// Increase the amount of health regenerated each frame
void Mob::addToHpPerFrame(double hpRegenPlus) {
  _hpPerFrame += hpRegenPlus;
}

double Mob::getMaxHealth() const {
  return _maxHealth;
}

double Mob::getHpPerFrame() const {
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


double Mob::getMana() const {
  return _mana;
}

double Mob::getMaxMana() const {
  return _maxMana;
}

double Mob::getMpPerFrame() const {
  return _mpPerFrame;
}


// Offense
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

//void Mob::drawSelf(Example& gfx) const {
//  // Drawing code here...
//  //		gfx->DrawDecal(getPos(), getDecal(), getDecalScale(20));
//
// /* if(isAlive())
//  gfx.DrawRotatedDecal(getPos(), getDecal(), 0, getDecalCenter(), getDecalScale(20));*/
//}

ChaserMob::ChaserMob():Mob() {
  setDecal("Spider");

  setSpeed(0.7);
}

void ChaserMob::update() {
  if(isAlive()) {
    //Movement
    auto oldDirection = getDirection();
    Level *level = getLevel();
    setDirection(level->getPlayerPosition() - getPos());

    //Attack
    if( getLevel()->getDistanceBetween(getPos(), getLevel()->getPlayerPosition()) < 20 ) {
      level->getPlayer().damage(2);
    }

    Mob::update();
  }
}

ChaserMob::ChaserMob(double x, double y) : Mob(100, x, y) {
  setDecal("Spider");
  setSpriteSourceSize( olc::vi2d {16, 16});
  setSpriteRotOffset(PI/2);

  setSpeed(0.7);
  //    setDecal("test2.png");
}

void ChaserMob::drawSelf(Example& gfx) const {
    //    if (isAlive())
    //        gfx->DrawDecal(getPos(), getDecal());//, olc::vi2d{1, 1},
    //     getSpriteSourceSize() , getDecalScale(30));


    //olc::vd2d sOffs(gfx.ScreenWidth() / 2, gfx.ScreenHeight() / 2); //New Function!

    if (isAlive())
        gfx.DrawPartialRotatedDecal(getPos() + gfx.getOffsetVector(), getDecal(), getSpriteRot(), getSpriteSourceSize() / 2, olc::vf2d{ 0,0 } *getSpriteSourceSize(), getSpriteSourceSize(),
            getDecalScale(30));
    else
        gfx.DrawPartialRotatedDecal(getPos() + gfx.getOffsetVector(), getDecal(), 0, getSpriteSourceSize() / 2, olc::vf2d{ 1,1 } *getSpriteSourceSize(), getSpriteSourceSize(),
            getDecalScale(30));

    //gfx.drawPixel(getXPos(), getYPos(), 255, 0, 0);

    //    gfx->DrawPartialDecal(getPos(), getDecal(), olc::vf2d{1,1} * getSpriteSourceSize(), getSpriteSourceSize() ,
    //                          getDecalScale(30));

}

RangedChaserMob::RangedChaserMob() {
    setGraphicParameters(5, olc::vi2d{ 16, 16 }, olc::vf2d{ 0.8f, 0.8f }, "Slime");
    setSpriteRotOffset(2.0 * PI);
    setSpeed(0.5);
}

RangedChaserMob::RangedChaserMob(double x, double y) : ChaserMob(x, y) {
    setMaxHp(150);
    setHealth(150);
    setGraphicParameters(5, olc::vi2d{ 16, 16 }, olc::vf2d{ 0.8f, 0.8f }, "Slime");
    setSpriteRotOffset(2.0 * PI);

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto uniDis = std::uniform_int_distribution(0, 5);
    std::mt19937 gen(seed);
    setGraphicState(uniDis(gen), 5); // Set to random state for variance in state among Slimes
    _frameTimeOffset = uniDis(gen); // Set some slimes to be faster and some slower
    setSpeed(0.5);
}

void RangedChaserMob::update() {
    if (isAlive()) {
        //Movement
        auto oldDirection = getDirection();
        Level* level = getLevel();
        if (_attackWaitCount < 80)
            setDirection(level->getPlayerPosition() - getPos());

        //Attack
        if (getLevel()->getDistanceBetween(getPos(), getLevel()->getPlayerPosition()) < 80) {
            setSpeed(0.0);
            setIfAttackAnimation(true);
            if (_attackWaitCount == _attackDelay) // shoot bullet
            {
                _attackWaitCount = 0;

                Projectile* bullet = new Projectile(getXPos(), getYPos());
                bullet->setDirection(getDirection());
                bullet->setShooter(this);
                bullet->setGraphicParameters(2, olc::vi2d{ 16, 5 }, { 1.0f, 1.0f }, "Bullet");
                bullet->setSpriteRotOffset(2.0 * PI);
                bullet->setIfSingleSprite(false);

                getLevel()->add(bullet);
            }

            _attackWaitCount++;
        }
        else
        {
            setIfAttackAnimation(false);

            switch (getGraphicState())
            {
            case 0:
                setGraphicFrameTimer(25 - _frameTimeOffset);
                setSpeed(0.0);
                break;
            case 1:
                setGraphicFrameTimer(22 - _frameTimeOffset);
                setSpeed(0.1);
                break;
            case 2:
                setGraphicFrameTimer(18 - _frameTimeOffset);
                setSpeed(0.3);
                break;
            case 3:
                setGraphicFrameTimer(12 - _frameTimeOffset);
                setSpeed(0.5);
                break;
            case 4:
                setGraphicFrameTimer(18 - _frameTimeOffset);
                setSpeed(0.3);
                break;
            case 5:
                setGraphicFrameTimer(20 - _frameTimeOffset);
                setSpeed(0.1);
                break;
            default:
                break;
            }
        }

        Mob::update();
    }
    else
    {
        setDirection({1.0, 0.0});
        setSpriteSheetOffset(getDeadSpriteSource() * getSpriteSourceSize());
    }
}

void RangedChaserMob::drawSelf(Example& gfx) const {
    gfx.DrawPartialRotatedDecal(getPos() + gfx.getOffsetVector(), getDecal(), getSpriteRot(), getSpriteSourceSize() / 2, getSpriteSheetOffset(), getSpriteSourceSize(),
        getSpriteScaling());
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

  if( getLevel()->getDistanceBetween(getPos(), getLevel()->getPlayerPosition()) > 500 ) {
    setDirection( getLevel()->getPlayerPosition() - getPos() );
  }

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
