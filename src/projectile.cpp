//
// Created by uddeepk on 4/6/21.
//
//#include "projectile.h"
#include "main.h"
#include "projectile.h"


Projectile::Projectile() :Entity()
{

}

Projectile::Projectile(double x, double y) : Entity(x,y){
    setDirection( olc::vd2d{0,1});
    setSpeed(0);
    //setDecal("fireBall.png");
}

Projectile::Projectile(double x, double y, const olc::vd2d &fPos):Entity(), _endPosition(fPos) {
    setDirection(_endPosition - getPos());
    setSpeed(0.5);
    //setDecal("test2.png");
}

Projectile::Projectile(double x, double y, double fx, double fy):Entity(), _endPosition(fx, fy) {
    setDirection(_endPosition - getPos());
    setSpeed(0.5);
    //setDecal("test2.png");
}

void Projectile::drawSelf(Example& gfx) const
{
    if (!_hasHit)
        //gfx.DrawRotatedDecal(getPos() , getDecal(), getSpriteRot("fireBall"), getDecalCenter() , getDecalScale(10));
        drawDecal(gfx, "fireBall", getPos());
    else
        gfx.DrawStringDecal(getPos(), "BOOM", olc::RED);

}

// Used to add in the decals/sprites for the entity --> NEEDS TO BE OVERWITTEN FOR EVERY MOB WITH DIFFERENT DECALS!
void Projectile::graphicsSetup()
{
    addDecalAndIfData("fireBall");
}

void Projectile::update() {
    if (!_hasHit) {
        auto displacement = getDirection() * getSpeed();
        addToPos(displacement);
    } else {
        // do nothing
    }
}

void Projectile::setEndPosition(const olc::vd2d &newEndPosition) {
    _endPosition = newEndPosition;
}

olc::vd2d Projectile::getEndPosition() const {
    return _endPosition;
}

void Projectile::setHasHit() {
    _hasHit = true;
}

bool Projectile::getHasHit() const {
    return _hasHit;
}

double Projectile::getRadius() const {
    return _radius;
}

std::unique_ptr<Projectile> projectileFactory ( double x, double y, double fx, double fy) // fP only gives directions
{
    return std::make_unique<Projectile>(x, y, fx, fy);
}

HomingProjectile::HomingProjectile(double x, double y, Mob* mob) :
        Projectile(x, y, mob->getPos()) , _entityTarget(mob) {
}

void HomingProjectile::update() {
    // Get Final position from the object
    // adjust direction to object
    // adjust position
    if ( !getHasHit() && getLevel()->has(_entityTarget) ) {
        auto oldDirection = getDirection();
        setEndPosition(_entityTarget->getPos());
        auto directionToObject = (getEndPosition() - getPos()).norm();
        auto newDirection = oldDirection * .96 + directionToObject * .04; // adjust multiplier for responsetimes.
        // Bigger multiplier for oldDirection, slower response time.
        setDirection(newDirection);
        Projectile::update();
    } else {
        // do nothing
    }
}

// Used to add in the decals/sprites for the entity --> NEEDS TO BE OVERWITTEN FOR EVERY MOB WITH DIFFERENT DECALS!
void HomingProjectile::graphicsSetup()
{
    addDecalAndIfData("fireBall");
}

OrbitalProjectile::OrbitalProjectile(double x, double y, double cx, double cy):
        Projectile(x, y)
{
    olc::vd2d sPos {x, y};
    olc::vd2d centre {cx, cy};

    setDirection ((sPos - centre).perp());
    radiusOrbital = (sPos - centre).mag();
    //setDecal("fireBall");
}

void OrbitalProjectile::update() {

    auto direction = getDirection();
    direction += direction.perp() * getSpeed() / radiusOrbital;
    setDirection(direction);

    Projectile::update();
}

// Used to add in the decals/sprites for the entity --> NEEDS TO BE OVERWITTEN FOR EVERY MOB WITH DIFFERENT DECALS!
void OrbitalProjectile::graphicsSetup()
{
    addDecalAndIfData("fireBall");
}
