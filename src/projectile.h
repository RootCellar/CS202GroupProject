#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <memory>
//#include "olcPixelGameEngine.h"
#include "entity.h"

class Projectile : public Entity {
private:

    olc::vd2d _endPosition;

    double _radius = 10;

    Mob* _shooter;

public:
    Projectile();
    Projectile(double, double);
    Projectile(double, double, const olc::vd2d &fPos);
    Projectile(double x, double y, double fx, double dy);

    ~Projectile() = default; // only worked after I did this

    virtual void drawSelf(Example& gfx) const override;

    virtual void graphicsSetup() override;

    //update the projectile, move it etc.
    virtual void update() override;

    void setEndPosition(const olc::vd2d &newEndPosition);

    olc::vd2d getEndPosition() const;

    double getRadius() const;

    Mob* getShooter();
    Mob* setShooter(Mob*);
};

std::unique_ptr<Projectile> projectileFactory(double, double, double, double);

// HomingProjectile keeps reference to an entity
// need a btter way to mitigate failure incase entity is removed from level. Maybe check with nullptr ?
class HomingProjectile : public Projectile {
public:
    Mob* _entityTarget;
    HomingProjectile(double, double, Mob* mob);

    virtual void update() override;

};

class OrbitalProjectile : public Projectile {
public:
    OrbitalProjectile(double, double, double, double);

    double radiusOrbital;
    float fAngle = 0;

    virtual void update() override;
};

#endif
