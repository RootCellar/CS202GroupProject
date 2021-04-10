//
// Created by uddeepk on 4/6/21.
//
#include "projectile.h"

Projectile::Projectile(olc::vd2d sPos, olc::vd2d ePos) : Entity(sPos.x, sPos.y), _endPosition(ePos)
{
    auto displacement = _endPosition - getPos();
    _distance = displacement.mag();
    _direction = displacement / _distance; // (v2d / mag(v2d))
//    /*olc::Decal*  */ m_pDecal = new olc::Decal(new olc::Sprite("fireBall.png"));
//    fireBall2 = std::make_shared<olc::Sprite>("test2.png");
//    test2 = std::make_shared<olc::Decal> (fireBall2.get());
    setDecal("test2.png");
}

void Projectile::drawSelf(olc::PixelGameEngine * gfx) const //, double offsetx, double offsety) {
{
    float myAngle = PI/2 + atan(_direction.y / _direction.x);
    if ( _direction.x < 0 ) {
        myAngle += PI;
    }
//    gfx->DrawRotatedDecal(_position - olc::vd2d{offsetx, offsety}, test2.get(), myAngle);
//    gfx->DrawRotatedDecal(_position , test2.get(), myAngle);
//    auto scale = 10.f / fireBall2->width; //10.f represents the size in pixels we want
    gfx->DrawRotatedDecal(getPos() , getDecal(), myAngle, {0, 0}, getDecalScale(10));

}

void Projectile::update() {
    // Updating position of projectile
//    auto position = getPos();
//    setPos(position + _direction * _speed) ; //need offset if map moves around.
    auto displacement = _direction * _speed;
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
//    m_pDecal = new olc::Decal(new olc::Sprite("fireBall.png"));
//    fireBall2 = std::make_shared<olc::Sprite>("fireBall.png");
//    test2 = std::make_shared<olc::Decal> (fireBall2.get());
    setDecal("fireBall.png");
}

void HomingProjectile::update() {
    // Get Final position from the object
    // adjust direction to object
    // adjust position

    auto changeToPos = _direction * _speed * .69;
//    _position += _direction * _speed * .5 ;
    addToPos(changeToPos);

    _endPosition = notPointerToEntity->getPos();
    auto displacement = _endPosition - getPos();
    _distance = displacement.mag();
    _direction = displacement / _distance ;//*.5;
    //_direction = _direction / _direction.mag();
    changeToPos =  _direction * _speed * .2;

    addToPos(changeToPos);

}

void OrbitalProjectile::update() {
    _direction += _direction.perp() * _speed / radiusOrbital ;
    _direction = _direction.norm();
    Projectile::update();
//    _position =
}

