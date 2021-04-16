#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <memory>
//#include "olcPixelGameEngine.h"
#include "entity.h"

class Projectile : public Entity {
private:

    olc::vd2d _endPosition;

    double _radius = 10;

    bool _hasHit = false;
//    virtual void setlevel (Level * l ) override ; //idk how to use it
public:
    Projectile(); // Random ??
    Projectile(olc::vd2d sPos, olc::vd2d ePos);

    ~Projectile() = default; // only worked after I did this
    virtual void drawSelf(Example& gfx) const override;//, double offsetx, double offsety);
    //update the projectile, move it etc.
    virtual void update() override;

    void setEndPosition(const olc::vd2d &newEndPosition);

    olc::vd2d getEndPosition() const;

    double getRadius() const;

    bool getHasHit() const;

    void setHasHit();
};

std::unique_ptr<Projectile> projectileFactory(olc::vd2d sPos, olc::vd2d fPos);

std::vector<std::unique_ptr<Projectile>> getMyBalls(olc::vd2d sPos, int numberOfBalls);

// HomingProjectile keeps reference to an entity
// need a btter way to mitigate failure incase entity is removed from level. Maybe check with nullptr ?
class HomingProjectile : public Projectile {
public:
    Entity *notPointerToEntity;// = nullptr;
    HomingProjectile(olc::vd2d sPos, Entity *ent);

    virtual void update() override;

};

class OrbitalProjectile : public Projectile {
public:
    OrbitalProjectile(const olc::vd2d &sPos, const olc::vd2d &centre);

    double radiusOrbital;
    float fAngle = 0;

    virtual void update() override;
};

#endif
