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

  //Lists of mobs and projectiles in the level

  std::vector<Mob> mobs;
  std::vector<Projectile> projectiles;

  //Lists of creatures to spawn and despawn
  //Avoids certain bugs, and means mobs/projectiles can make actions on spawn/despawn

  std::vector<Mob> pendingMobSpawns;
  std::vector<Mob> pendingMobRemovals;

  std::vector<Projectile> pendingProjectileSpawns;
  std::vector<Projectile> pendingProjectileRemovals;

public:

  //Temporary default constructor to allow us to use the level without having a player yet
  Level() {

  }

  Level(Player p) {
    player = p;
  }

  void add(Mob m) {
    if(!has(m)) pendingMobSpawns.push_back(m);
  }

  void add(Projectile p) {
    if(!has(p)) pendingProjectileSpawns.push_back(p);
  }

  bool has(Mob m) {
    for(Mob j : mobs) {
      if( m == j ) return true;
    }
    return false;
  }

  bool has(Projectile p) {
    for(Projectile j : projectiles) {
      if( p == j ) return true;
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

    while(pendingMobSpawns.size() > 0) {
      Mob m = pendingMobSpawns.at(0);
      pendingMobSpawns.erase( pendingMobSpawns.begin() );
      if(!has(m)) mobs.push_back(m);
    }

  }

  void renderEntities(Example &gfx) {
    for(Projectile p : projectiles) {
      p.drawSelf(gfx);
    }

    for(Mob m : mobs) {
      m.drawSelf(gfx);
    }
  }

};

#endif
