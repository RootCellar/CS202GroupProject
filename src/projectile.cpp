//
// Created by uddeepk on 4/6/21.
//
//#include "projectile.h"
#include "main.h"
#include "projectile.h"

#include <vector>
using std::vector;


Projectile::Projectile() :Entity()
{

}

Projectile::Projectile(double x, double y) : Entity(x,y){
  setDirection( olc::vd2d{0,1});
  setSpeed(2);
  setDecal("Fireball");
}

Projectile::Projectile(double x, double y, const olc::vd2d &fPos):Entity(x, y), _endPosition(fPos) {
  setDirection(_endPosition - getPos());
  setSpeed(2);
  setDecal("Fireball");
}

Projectile::Projectile(double x, double y, double fx, double fy):Entity(x, y), _endPosition(fx, fy) {
  setDirection(_endPosition - getPos());
  setSpeed(2);
  setDecal("Fireball");
}

//void Projectile::drawSelf(Example& gfx) const
//{
//  gfx.DrawRotatedDecal(getPos() + gfx.getOffsetVector() , getDecal(), getSpriteRot(), getDecalCenter() , getDecalScale(10));
//
//}

// Added this additional drawSelf for sprites with animations
void Projectile::drawSelf(Example& gfx) const
{
    if(getIfSingleSprite())
        gfx.DrawRotatedDecal(getPos() + gfx.getOffsetVector(), getDecal(), getSpriteRot(), getDecalCenter(), getDecalScale(10));
    else
        gfx.DrawPartialRotatedDecal(getPos() + gfx.getOffsetVector(), getDecal(), getSpriteRot(), getSpriteSourceSize() / 2 , getSpriteSheetOffset() , getSpriteSourceSize(), getSpriteScaling());
}

// Calls the set up for this mob (Needs to be overwritten if data needs to be different)
void Projectile::graphicsSetup()
{

}

void Projectile::update() {
  auto displacement = getDirection() * getSpeed();
  addToPos(displacement);

  Level* level = getLevel();
  vector<Mob*> inRange = level->getMobsInRange(getPos(), 20, _shooter->getTeam());
  if(inRange.size() > 0) {
    Mob* toHit = inRange[0];
    toHit->damage(50);
    level->remove(this);
  }
}

void Projectile::setEndPosition(const olc::vd2d &newEndPosition) {
  _endPosition = newEndPosition;
}

olc::vd2d Projectile::getEndPosition() const {
  return _endPosition;
}

double Projectile::getRadius() const {
  return _radius;
}

Mob* Projectile::getShooter() {
  if(_shooter == nullptr) return nullptr;

  return _shooter;
}

void Projectile::setShooter(Mob* m) {
  _shooter = m;
}

std::unique_ptr<Projectile> projectileFactory ( double x, double y, double fx, double fy) // fP only gives directions
{
  return std::make_unique<Projectile>(x, y, fx, fy);
}

HomingProjectile::HomingProjectile(double x, double y, Mob* mob) :
Projectile(x, y, mob->getPos()) , _entityTarget(mob) {
    // maybe shoul use cosest mob's distance instead?
}

void HomingProjectile::update() {
  // Get Final position from the object
  // adjust direction to object
  // adjust position
  if ( getLevel()->has(_entityTarget) ) {
    auto oldDirection = getDirection();
    setEndPosition(_entityTarget->getPos());
    auto directionToObject = (getEndPosition() - getPos()).norm();
    auto newDirection = oldDirection * .96 + directionToObject * .04; // adjust multiplier for responsetimes.
    // Bigger multiplier for oldDirection, slower response time.
    setDirection(newDirection);
    Projectile::update();
  }
}

OrbitalProjectile::OrbitalProjectile(double x, double y, double cx, double cy):
Projectile(x, y)
{
  olc::vd2d sPos {x, y};
  olc::vd2d centre {cx, cy};

  setDirection ((sPos - centre).perp());
  radiusOrbital = (sPos - centre).mag();
  setDecal("Fireball");
}

OrbitalProjectile::OrbitalProjectile(double x, double y, const olc::vd2d &center):Projectile( x, y) {
    olc::vd2d sPos {x, y};
    olc::vd2d centre = center;

    setDirection ((sPos - centre).perp());
    radiusOrbital = (sPos - centre).mag();
    setDecal("Fireball");
}
void OrbitalProjectile::update() {

  auto direction = getDirection();
  direction += direction.perp() * getSpeed() / radiusOrbital;
  setDirection(direction);

  Projectile::update();
}

Projectile * gimmeProjectile( int projectileType, double x, double y, const olc::vd2d &fPos  ) {
    switch (projectileType) {
        case 0:
            // regular
            return new Projectile (x, y, fPos);
            break;
        case 1:
            // blackhole
            return new BlackHoleProjectile (x, y, fPos);
            break;
        case 2:
            //Orbital
            return new OrbitalProjectile(x, y, fPos);
            break;
//            return std::make_unique<Projectile>(x, y, fx, fy);
    }
}

BlackHoleProjectile::BlackHoleProjectile(double x, double y, double fx, double fy) : Projectile(x, y, fx, fy){
    setSpeed(1);
    setDecal("Black Hole");
}

BlackHoleProjectile::BlackHoleProjectile(double x, double y, const olc::vd2d &fPos) : Projectile(x, y, fPos){
    setSpeed(1);
    setDecal("Black Hole");
}

void BlackHoleProjectile::update() {
//    DrawPartialDecal({ 100.0f + xBHHold + xBH * bHCount, 100.0f + yBHHold + yBH * bHCount } , m_pDecal_BH, { 16.0f * (stage % 5), 16.0f * (stage / 5) }, { 16.0f, 16.0f });
    bHCount += 0.2f;
    if (int(bHCount * 50.0f) % 120 == 0)
        stage++;
//    if (stage == 7) && !blackHoleHold)
//    {
//        blackHoleHold = true;
//        xBHHold = xBH * bHCount;
//        yBHHold = yBH * bHCount;
//        xBH = 0.0f;
//        yBH = 0.0f;
//    }
    if (stage > 10)
    {
//        blackHole = false;
//        blackHoleHold = false;
//        xBH = 0.0f;
//        yBH = 0.0f;
//        xBHHold = 0.0f;
//        yBHHold = 0.0f;
        bHCount = 0;
        stage = 0;
        getLevel()->remove(this);
    }
    Projectile::update();
}

void BlackHoleProjectile::drawSelf(Example &gfx) const{
    gfx.DrawPartialDecal(getPos() + gfx.getOffsetVector(),getDecal(), {16.0f * stage, 0}, {16.0f, 16.0f});
//    DrawPartialDecal({ 100.0f + xBHHold + xBH * bHCount, 100.0f + yBHHold + yBH * bHCount } , m_pDecal_BH, { 16.0f * (stage % 5), 16.0f * (stage / 5) }, { 16.0f, 16.0f });

}
