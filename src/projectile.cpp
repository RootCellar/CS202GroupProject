//
// Created by uddeepk on 4/6/21.
//
//#include "projectile.h"
#include "main.h"
#include "projectile.h"


Projectile::Projectile() :Entity()
{
    // Probably don't need it but just keeping here
}

Projectile::Projectile(double x, double y) : Entity(x,y){
    setDirection( olc::vd2d{0,1});
    setSpeed(0);
    setDecal("fireBall.png");
}

Projectile::Projectile(double x, double y, const olc::vd2d &fPos):Entity(), _endPosition(fPos) {
    setDirection(_endPosition - getPos());
    setSpeed(0.5);
    setDecal("test2.png");
}

Projectile::Projectile(double x, double y, double fx, double fy):Entity(), _endPosition(fx, fy) {
    setDirection(_endPosition - getPos());
    setSpeed(0.5);
    setDecal("test2.png");
}

void Projectile::drawSelf(Example& gfx) const //, double offsetx, double offsety) {
{
    if ( !_hasHit)
        gfx.DrawRotatedDecal(getPos() , getDecal(), getSpriteRot(), getDecalCenter() , getDecalScale(10));
    else
        gfx.DrawStringDecal(getPos(), "BOOM", olc::RED);

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

//double Projectile::getSpeed() const {
//    return _speed;
//}

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

std::vector<std::unique_ptr<Projectile>> getMyBalls(double x, double y, int numberOfBalls) {
    int &n = numberOfBalls;
    std::vector <std::unique_ptr<Projectile>> myBalls ;
    // Generate balls in a circle ?
    //
    double angleRad = 0 ;
    for ( int i = 0 ; i < n ; ++i ) {
        angleRad = 2.0 * PI * (static_cast<double> (i) /n) ;
        auto direction = olc::vd2d{cos (angleRad), sin (angleRad)};
        myBalls.push_back(projectileFactory(  x, y, direction.x, direction.y ));
    }
    return myBalls;
}

HomingProjectile::HomingProjectile(double x, double y, Entity *ent) :
        Projectile(x, y, ent->getPos()) , notPointerToEntity(ent) {
}

void HomingProjectile::update() {
    // Get Final position from the object
    // adjust direction to object
    // adjust position
    if ( !getHasHit()) {
        auto oldDirection = getDirection();
        setEndPosition(notPointerToEntity->getPos());
        auto directionToObject = (getEndPosition() - getPos()).norm();
        auto newDirection = oldDirection * .96 + directionToObject * .04; // adjust multiplier for responsetimes.
        // Bigger multiplier for oldDirection, slower response time.
        setDirection(newDirection);
        Projectile::update();
    } else {
        // do nothing
    }
}

OrbitalProjectile::OrbitalProjectile(double x, double y, double cx, double cy):
        Projectile(x, y)
{
    olc::vd2d sPos {x, y};
    olc::vd2d centre {cx, cy};

    setDirection ((sPos - centre).perp());
    radiusOrbital = (sPos - centre).mag();
    setDecal("fireBall.png");
}

void OrbitalProjectile::update() {

    auto direction = getDirection();
    direction += direction.perp() * getSpeed() / radiusOrbital;
    setDirection(direction);

    Projectile::update();
}

