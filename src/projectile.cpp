//
// Created by uddeepk on 4/6/21.
//
#include "projectile.h"

Projectile::Projectile(olc::vd2d sPos, olc::vd2d ePos) : Entity(sPos), _endPosition(ePos)
{
    auto displacement = _endPosition - _position;
    _distance = displacement.mag();
    _direction = displacement / _distance; // (v2d / mag(v2d))
    /*olc::Decal*  */ m_pDecal = new olc::Decal(new olc::Sprite("fireBall.png"));
    fireBall2 = std::make_shared<olc::Sprite>("test2.png");
    test2 = std::make_shared<olc::Decal> (fireBall2.get());

}

void Projectile::drawSelf(olc::PixelGameEngine * gfx) const //, double offsetx, double offsety) {
{
    float myAngle = PI/2 + atan(_direction.y / _direction.x);
    if ( _direction.x < 0 ) {
        myAngle += PI;
    }
//    gfx->DrawRotatedDecal(_position - olc::vd2d{offsetx, offsety}, test2.get(), myAngle);
//    gfx->DrawRotatedDecal(_position , test2.get(), myAngle);
    auto scale = 10.f / fireBall2->width; //10.f represents the size in pixels we want
    gfx->DrawRotatedDecal(_position , test2.get(), myAngle, {0, 0}, {scale, scale});

}

void Projectile::update() {
    // Updating position of projectile
    _position += _direction * _speed; //need offset if map moves around.

}

std::unique_ptr<Projectile> projectileFactory ( olc::vd2d sPos , olc::vd2d fPos) // fP only gives directions
{
//    auto myBall = std::make_unique<Projectile>(sPos, fPos);
//    //std::unique_ptr <Projectile> myProjectile std::make_unique<Projectile> {sPos, fPos};
//    return myBall;
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
    fireBall2 = std::make_shared<olc::Sprite>("fireBall.png");
    test2 = std::make_shared<olc::Decal> (fireBall2.get());
}

void HomingProjectile::update() {
    // Get Final position from the object
    // adjust direction to object
    // adjust position
//        _endPosition = olc::vi2d{notPointerToEntity->getXPos(), notPointerToEntity->getYPos()};
    _endPosition = notPointerToEntity->_position;
//        _endPosition = olc::vd2d{200, 400};
    auto displacement = _endPosition - _position;
    _position += _direction * _speed * .5 ;
    _distance = displacement.mag();
    _direction = displacement / _distance ;//*.5;
    //_direction = _direction / _direction.mag();
    _position +=  _direction * _speed * .5;
}

void OrbitalProjectile::update() {
    _direction += _direction.perp() * _speed / radiusOrbital ;
    _direction = _direction.norm();
    Projectile::update();
//    _position =
}

