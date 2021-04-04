#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iterator>

#include "debug.h"
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

  #ifdef DEBUG
  //debug-only default constructor to allow us to use the level without having a player yet
  Level() {
    debug("Debug constructing a default level! No player given!");
  }
  #endif

  Level(Player p): player(p) {
  }

  void add(Mob m) {
    if(!has(m)) pendingMobSpawns.push_back(m);
  }

  void add(Projectile p) {
    if(!has(p)) pendingProjectileSpawns.push_back(p);
  }

  void remove(Mob m) {
    if(has(m)) pendingMobRemovals.push_back(m);
  }

  void remove(Projectile p) {
    if(has(p)) pendingProjectileRemovals.push_back(p);
  }

  bool has(Mob m) const {
    for(Mob j : mobs) {
      if( m == j ) return true;
    }
    return false;
  }

  bool has(Projectile p) const {
    for(Projectile j : projectiles) {
      if( p == j ) return true;
    }
    return false;
  }

  //Loop through the list of mobs and return an iterator to the one you're looking for
  std::vector<Mob>::iterator getIteratorToMob(Mob m) {
    for(size_t i=0; i<mobs.size(); i++) {
      Mob j = mobs.at(i);
      if(m == j) return mobs.begin() + i;
    }
    return mobs.end();
  }

  //Loop through the list of projectiles and return an iterator to the one you're looking for
  std::vector<Projectile>::iterator getIteratorToProjectile(Projectile p) {
    for(size_t i=0; i<projectiles.size(); i++) {
      Projectile j = projectiles.at(i);
      if(p == j) return projectiles.begin() + i;
    }
    return projectiles.end();
  }

  //Call update for everybody, handle spawns and despawns
  void update() {

    for(Mob m : mobs) {
      m.update();
    }

    for(Projectile p : projectiles) {
      p.update();
    }

    //Spawn mobs and projectiles from our lists

    while(pendingMobSpawns.size() > 0) {
      Mob m = pendingMobSpawns.at(0);
      pendingMobSpawns.erase( pendingMobSpawns.begin() );
      if(!has(m)) mobs.push_back(m);
    }

    while(pendingProjectileSpawns.size() > 0) {
      Projectile p = pendingProjectileSpawns.at(0);
      pendingProjectileSpawns.erase( pendingProjectileSpawns.begin() );
      if(!has(p)) projectiles.push_back(p);
    }

    //De-spawn mobs from lists
    while(pendingMobRemovals.size() > 0) {
      Mob m = pendingMobRemovals.at(0);
      pendingMobRemovals.erase( pendingMobRemovals.begin() );
      if(!has(m)) {
        continue;
      }

      mobs.erase( getIteratorToMob(m) );
    }

    //Despawn projectile from lists

    while(pendingProjectileRemovals.size() > 0) {
      Projectile p = pendingProjectileRemovals.at(0);
      pendingProjectileRemovals.erase( pendingProjectileRemovals.begin() );
      if(!has(p)) {
        continue;
      }

      projectiles.erase( getIteratorToProjectile(p) );
    }

  }

  void renderEntities(Example &gfx) const {
    for(Projectile p : projectiles) {
      p.drawSelf(gfx);
    }

    for(Mob m : mobs) {
      m.drawSelf(gfx);
    }
  }

};

#endif
