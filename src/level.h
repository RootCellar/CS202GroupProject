#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iterator>
#include "olcPixelGameEngine.h"
#include "debug.h"
#include "main.h"
#include "team.h"

class Player;
class Mob;
class Projectile;
class Example;
//class DecalMap;
//The world, bosses everyone else around but also serves them
class Level {
private:

  Player * player;

  //Lists of mobs and projectiles in the level

  std::vector<Mob*> mobs;
  std::vector<Projectile*> projectiles;

  //Lists of creatures to spawn and despawn
  //Avoids certain bugs, and means mobs/projectiles can make actions on spawn/despawn

  std::vector<Mob*> pendingMobSpawns;
  std::vector<Mob*> pendingMobRemovals;

  std::vector<Projectile*> pendingProjectileSpawns;
  std::vector<Projectile*> pendingProjectileRemovals;

  //Test projectiles below
  Projectile testProjectile { olc::vd2d {75, 75}, olc::vd2d{ 80, 80}};

  OrbitalProjectile test2 { olc::vd2d {50, 50}, olc::vd2d{ 126, 110}};

  HomingProjectile test3 { olc::vd2d{100, 100}, &test2};

  HomingProjectile followPlayer { olc::vd2d{200, 200}, player};
  // testing decalmap

public:

  Level(Player * p);

  void add(Mob *m);

  void add(Projectile *p);

  void remove(Mob *m);

  void remove(Projectile *p);

  bool has(Mob *m) const;

  bool has(Projectile *p) const;

  //Loop through the list of mobs and return an iterator to the one you're looking for
  std::vector<Mob*>::iterator getIteratorToMob(Mob *m);

  //Loop through the list of projectiles and return an iterator to the one you're looking for
  std::vector<Projectile*>::iterator getIteratorToProjectile(Projectile *p);

  //Call update for everybody, handle spawns and despawns
  void update();

  void renderEntities(olc::PixelGameEngine * gfx) const;
  //Get mobs within range from some point
  std::vector<Mob*> getMobsInRange(double xPos, double yPos, double radius);

  //Get mobs within range from some point and not on the given team
  //(So the returned list is only enemies)
  std::vector<Mob*> getMobsInRange(double xPos, double yPos, double radius, Team t);

  double getDistanceBetween(double xP1, double yP1, double xP2, double yP2);

};

#endif
