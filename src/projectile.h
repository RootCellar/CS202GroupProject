#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <memory>
//#include "olcPixelGameEngine.h"
#include "entity.h"

class Projectile : public Entity {
private:
public:
//    olc::vd2d _position ;
    olc::vd2d _endPosition;
    olc::vd2d _direction ;
    //olc::vd2d _displacement; // to make it easier. //
    double _distance;
    // Since, comparison of doulbes difficult, will be using the max distance to travel for life
    // time of projectile

    double _speed = .5;//.0009; // 0 for testing
    double _radius = 5;
//    std::unique_ptr <olc::Sprite> fireBall = std::make_unique<olc::Sprite> ("fireBall.png");
//    olc::Sprite* myBalls = fireBall->Duplicate(_position, olc::vi2d{50, 50});
//    std::unique_ptr <olc::Decal> ballPtr = std::make_unique<olc::Decal> (fireBall.get());
    olc::Decal * m_pDecal = nullptr;
//    /*olc::Decal*  */ m_pDecal = new olc::Decal(new olc::Sprite("fireBall.png"));

    std::shared_ptr <olc::Sprite> fireBall2 = nullptr;
    std::shared_ptr <olc::Decal> test2 = nullptr;
    float kurtAngle = 0;

//    virtual void setlevel (Level * l ) override ;
public:
    Projectile():Entity()
    {

    } ; // Random ??
    Projectile(olc::vd2d sPos, olc::vd2d ePos);
    ~Projectile()
    {
//        delete myBalls;
        delete m_pDecal;
    }
    virtual void drawSelf(Example &gfx) const override;//, double offsetx, double offsety);
  //update the projectile, move it etc.
  virtual void update() override;

};
std::unique_ptr<Projectile> projectileFactory ( olc::vd2d sPos , olc::vd2d fPos);



std::vector <std::unique_ptr<Projectile>> getMyBalls (olc::vd2d sPos, int numberOfBalls);

class HomingProjectile : public Projectile {
public:
    Entity * notPointerToEntity;// = nullptr;
    HomingProjectile( olc::vd2d sPos, Entity * ent ):
    Projectile(sPos, ent->_pos) , notPointerToEntity(ent) {
//        notPointerToEntity = ent;
    }

    virtual void update() override;

};

class OrbitalProjectile: public Projectile {
public:
    OrbitalProjectile(const olc::vd2d &sPos, const olc::vd2d &centre );
    double radiusOrbital ;
    float fAngle = 0;
    virtual void update() override;
};
#endif
