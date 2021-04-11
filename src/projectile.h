#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <memory>
//#include "olcPixelGameEngine.h"
#include "entity.h"

class Projectile : public Entity {
private:

    olc::vd2d _endPosition;
    olc::vd2d _direction ;
//    double _distance;

    double _speed = .5;//.0009; // 0 for testing
    double _radius = 10;

    bool _hasHit = false;
//    virtual void setlevel (Level * l ) override ;
public:
    Projectile(); ; // Random ??
    Projectile(olc::vd2d sPos, olc::vd2d ePos);
    ~Projectile()=default;
    virtual void drawSelf(olc::PixelGameEngine * gfx) const override;//, double offsetx, double offsety);
  //update the projectile, move it etc.
  virtual void update() override;

  void setEndPosition (const olc::vd2d &newEndPosition);
  olc::vd2d getEndPosition() const;
  double getRadius () const;

  double getSpeed () const;
  bool getHasHit() const;
  void setHasHit() ;
};
std::unique_ptr<Projectile> projectileFactory ( olc::vd2d sPos , olc::vd2d fPos);



std::vector <std::unique_ptr<Projectile>> getMyBalls (olc::vd2d sPos, int numberOfBalls);

class HomingProjectile : public Projectile {
public:
    Entity * notPointerToEntity;// = nullptr;
    HomingProjectile( olc::vd2d sPos, Entity * ent );

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
