#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iterator>

#include "debug.h"

class Player;
class Mob;
class Projectile;
class Example;

//The world, bosses everyone else around but also serves them
class Level {
private:

  Player &player;

  //Lists of mobs and projectiles in the level

  std::vector<Mob*> mobs;
  std::vector<Projectile*> projectiles;

  //Lists of creatures to spawn and despawn
  //Avoids certain bugs, and means mobs/projectiles can make actions on spawn/despawn

  std::vector<Mob*> pendingMobSpawns;
  std::vector<Mob*> pendingMobRemovals;

  std::vector<Projectile*> pendingProjectileSpawns;
  std::vector<Projectile*> pendingProjectileRemovals;

public:

  Level(Player &p);

  void add(Mob *m);

  void add(Projectile *p);

  void remove(Mob *m);

  void remove(Projectile *p);

  bool has(Mob *m) const;

  bool has(Projectile *p) const;

  //Loop through the list of mobs and return an iterator to the one you're looking for
  std::vector<Mob>::iterator getIteratorToMob(Mob *m);

  //Loop through the list of projectiles and return an iterator to the one you're looking for
  std::vector<Projectile>::iterator getIteratorToProjectile(Projectile *p);

  //Call update for everybody, handle spawns and despawns
  void update();

  void renderEntities(Example &gfx) const;

};

#include "mob.h"
#include "projectile.h"

#endif
