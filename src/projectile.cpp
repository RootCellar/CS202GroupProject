//
// Created by uddeepk on 4/6/21.
//
#include "projectile.h"

Projectile::Projectile(olc::vd2d sPos, olc::vd2d ePos) : Entity(sPos.x, sPos.y), _endPosition(ePos)
{
    setDirection(_endPosition - getPos());
    setDecal("test2.png");
}

void Projectile::drawSelf(olc::PixelGameEngine * gfx) const //, double offsetx, double offsety) {
{
    gfx->DrawRotatedDecal(getPos() , getDecal(), getSpriteRot(), getDecalCenter() , getDecalScale(10));

}

void Projectile::update() {
    auto displacement = getDirection() * _speed;
    addToPos(displacement);
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

OrbitalProjectile::OrbitalProjectile(const olc::vd2d &sPos, const olc::vd2d &centre):
Projectile(sPos, sPos + (sPos-centre).perp()), radiusOrbital((sPos-centre).mag())
{
    setDecal("fireBall.png");
}

void HomingProjectile::update() {
    // Get Final position from the object
    // adjust direction to object
    // adjust position

    auto oldDirection = getDirection();
    _endPosition = notPointerToEntity->getPos();
    auto directionToObject = (_endPosition - getPos()).norm();
    auto newDirection = oldDirection * .96 + directionToObject * .04 ; // adjust multiplier for responsetimes.
    // Bigger multiplier for oldDirection, slower response time.
    setDirection(newDirection);
    Projectile::update();
}

void OrbitalProjectile::update() {

    auto direction = getDirection();
    direction += direction.perp() * _speed / radiusOrbital;
    setDirection(direction);

    Projectile::update();
}

