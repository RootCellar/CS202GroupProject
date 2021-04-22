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
    void setShooter(Mob*);
};

std::unique_ptr<Projectile> projectileFactory(double, double, double, double);
Projectile* gimmeProjectile(int projectileType, double, double, const olc::vd2d &fPos);
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
    OrbitalProjectile(double, double, const olc::vd2d &center);


    double radiusOrbital;
    float fAngle = 0;

    virtual void update() override;
};

class BlackHoleProjectile : public Projectile {
public:
    BlackHoleProjectile(double, double, double, double);
    BlackHoleProjectile(double x, double y, const olc::vd2d &fPos);
    virtual void update() override;
    virtual void drawSelf(Example& gfx) const override;

private:
    double bHCount = 0;
    int stage = 0;
};

// Adding Homing Projectile to work without reference to target.
class NewHomingProjectile : public Projectile {
public:
    NewHomingProjectile(double x, double y, const olc::vd2d &fPos);

};
#endif
