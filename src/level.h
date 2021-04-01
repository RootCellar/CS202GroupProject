#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "entity.h"
#include "mob.h"
#include "player.h"
#include "projectile.h"
#include "team.h"

//The world, bosses everyone else around but also serves them
class Level {
private:

  Player player;

  std::vector<Mob> mobs;
  std::vector<Projectile> projectiles;

  std::vector<Mob> pendingMobSpawns;
  std::vector<Mob> pendingMobRemovals;

  std::vector<Projectile> pendingProjectileSpawns;
  std::vector<Projectile> pendingProjectileRemovals;

public:

  Level(Player p) {
    player = p;
  }

  void add(Mob m) {

  }

  void add(Projectile p) {

  }

  bool has(Mob m) {
    for(Mob j : mobs) {
      if( m == j ) return true;
    }
    return false;
  }

  void update() {

    for(Mob m : mobs) {
      m.update();
    }

    for(Projectile p : projectiles) {
      p.update();
    }

    /*
    while(pendingMobSpawns.size() > 0) {
      //Mob m = pendingMobSpawns.get(0);

      if(!has(m)) mobs.push_back(m);
    }
    */

  }

};

#endif
