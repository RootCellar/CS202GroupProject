//
// Created by uddeepk on 4/6/21.
//
#include "projectile.h"

Projectile::Projectile() :Entity()
{
    // Probably don't need it but just keeping here
}

Projectile::Projectile(olc::vd2d sPos, olc::vd2d ePos) : Entity(sPos.x, sPos.y), _endPosition(ePos)
{
    setDirection(_endPosition - getPos());
    setDecal("test2.png");
}

void Projectile::drawSelf(olc::PixelGameEngine * gfx) const //, double offsetx, double offsety) {
{
    if ( !_hasHit)
        gfx->DrawRotatedDecal(getPos() , getDecal(), getSpriteRot(), getDecalCenter() , getDecalScale(10));
    else
        gfx->DrawStringDecal(getPos(), "BOOM", olc::RED);

}

void Projectile::update() {
    if (!_hasHit) {
        auto displacement = getDirection() * _speed;
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

double Projectile::getSpeed() const {
    return _speed;
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


std::unique_ptr<Projectile> projectileFactory ( olc::vd2d sPos , olc::vd2d fPos) // fP only gives directions
{
    return std::make_unique<Projectile>(sPos, fPos);
}

std::vector<std::unique_ptr<Projectile>> getMyBalls(olc::vd2d sPos, int numberOfBalls) {
    int &n = numberOfBalls;
    std::vector <std::unique_ptr<Projectile>> myBalls ;
    // Generate balls in a circle ?
    //
    double angleRad = 0 ;
    for ( int i = 0 ; i < n ; ++i ) {
        angleRad = 2.0 * PI * (static_cast<double> (i) /n) ;
        auto direction = olc::vd2d{cos (angleRad), sin (angleRad)};
        myBalls.push_back(projectileFactory( sPos, sPos + direction ));
    }
    return myBalls;
}

HomingProjectile::HomingProjectile(olc::vd2d sPos, Entity *ent) :
        Projectile(sPos, ent->getPos()) , notPointerToEntity(ent) {
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

OrbitalProjectile::OrbitalProjectile(const olc::vd2d &sPos, const olc::vd2d &centre):
        Projectile(sPos, sPos + (sPos-centre).perp()), radiusOrbital((sPos-centre).mag())
{
    setDecal("fireBall.png");
}

void OrbitalProjectile::update() {

    auto direction = getDirection();
    direction += direction.perp() * getSpeed() / radiusOrbital;
    setDirection(direction);

    Projectile::update();
}

