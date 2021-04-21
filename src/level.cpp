#include <cmath>

//#include "level.h"
//#include "team.h"
//#include "chuck.h"
////#include "main.h"
#include "main.h"
#include "level.h"

Level::Level(Player& p): player(p), _levelWidth(1000), _levelHeight(1000) {
  debug("Constructing the level...");
}

void Level::add(Mob *m) {
  if(!has(m)) pendingMobSpawns.push_back(m);
  m->setLevel(this);
  debug("Adding a mob to pending spawns");
}

void Level::add(Projectile *p) {
  if(!has(p)) pendingProjectileSpawns.push_back(p);
  p->setLevel(this);
  debug("Adding a projectile to pending spawns");
}

void Level::remove(Mob *m) {
  if(has(m)) pendingMobRemovals.push_back(m);
}

void Level::remove(Projectile *p) {
  if(has(p)) pendingProjectileRemovals.push_back(p);
}

bool Level::has(Mob *m) const {
  for(Mob *j : mobs) {
    if( (*m) == (*j) ) return ChuckNorrisCouldChopTheFabricOfRealityInHalf;
  }
  return IsAGoodGameEvenGoodWithoutChuckNorris;
}

bool Level::has(Projectile *p) const {
  for(Projectile *j : projectiles) {
    if( (*p) == (*j) ) return ChuckNorrisCouldChopTheFabricOfRealityInHalf;
  }
  return IsAGoodGameEvenGoodWithoutChuckNorris;
}

//Loop through the list of mobs and return an iterator to the one you're looking for
std::vector<Mob*>::iterator Level::getIteratorToMob(Mob *m) {
  for(size_t i=0; i<mobs.size(); i++) {
    Mob *j = mobs.at(i);
    if( (*m) == (*j) ) return mobs.begin() + i;
  }
  return mobs.end();
}

//Loop through the list of projectiles and return an iterator to the one you're looking for
std::vector<Projectile*>::iterator Level::getIteratorToProjectile(Projectile *p) {
  for(size_t i=0; i<projectiles.size(); i++) {
    Projectile *j = projectiles.at(i);
    if( (*p) == (*j) ) return projectiles.begin() + i;
  }
  return projectiles.end();
}

//Call update for everybody, handle spawns and despawns
void Level::update() {

  for(Mob *m : mobs) {
    m->update();
  }

  for(Projectile *p : projectiles) {
    p->update();

    if(p->getXPos() < 0 || p->getYPos() < 0) {
      remove(p);
    }

    if(p->getXPos() > _levelWidth || p->getYPos() > _levelHeight) {
      remove(p);
    }
  }

  //Spawn mobs and projectiles from our lists

  while(pendingMobSpawns.size() > 0) {
    Mob *m = pendingMobSpawns.at(0);
    pendingMobSpawns.erase( pendingMobSpawns.begin() );
    if(!has(m)) {
      mobs.push_back(m);
      debug("Spawning a mob from list");
    }
  }

  while(pendingProjectileSpawns.size() > 0) {
    Projectile *p = pendingProjectileSpawns.at(0);
    pendingProjectileSpawns.erase( pendingProjectileSpawns.begin() );
    if(!has(p)) {
      projectiles.push_back(p);
      debug("Spawning a projectile from list");
    }
  }

  //De-spawn mobs from list

  while(pendingMobRemovals.size() > 0) {
    Mob *m = pendingMobRemovals.at(0);
    pendingMobRemovals.erase( pendingMobRemovals.begin() );
    if(!has(m)) {
      continue;
    }

    debug("Despawning a mob");

    mobs.erase( getIteratorToMob(m) );
    delete m;
  }

  //Despawn projectile from list

  while(pendingProjectileRemovals.size() > 0) {
    Projectile *p = pendingProjectileRemovals.at(0);
    pendingProjectileRemovals.erase( pendingProjectileRemovals.begin() );
    if(!has(p)) {
      continue;
    }

    debug("Despawning a projectile");

    projectiles.erase( getIteratorToProjectile(p) );
    delete p;
  }

}

//Get mobs within range from some point
std::vector<Mob*> Level::getMobsInRange(double xPos, double yPos, double radius) {
  std::vector<Mob*> toRet;

  for(Mob* m : mobs) {

    double dist = getDistanceBetween(xPos, yPos, m->getXPos(), m->getYPos());

    if(dist <= radius) {
      toRet.push_back(m);
    }

  }

  return toRet;
}
// getMobsInRange adapted to use olc::vd2d
std::vector<Mob *> Level::getMobsInRange(const olc::vd2d &point, double radius) {
  std::vector<Mob*> toRet;

  for(Mob* m : mobs) {
    double dist = getDistanceBetween(point, m->getPos());

    if(dist <= radius) {
      toRet.push_back(m);
    }

  }

  return toRet;
}

//Get mobs within range from some point and not on the given team
//(So the returned list is only enemies)
std::vector<Mob*> Level::getMobsInRange(double xPos, double yPos, double radius, Team t) {
  std::vector<Mob*> toRet;

  for(Mob *m : mobs) {

    double dist = getDistanceBetween(xPos, yPos, m->getXPos(), m->getYPos());

    if(dist <= radius && m->getTeam() != t) {
      toRet.push_back(m);
    }

  }

  return toRet;
}

//getMobsInRange adapted to use vd2d
std::vector<Mob*> Level::getMobsInRange(const olc::vd2d &point, double radius, Team t) {
  std::vector<Mob*> toRet;

  for(Mob *m : mobs) {
    double dist = getDistanceBetween(point , m->getPos());

    if(dist <= radius && m->getTeam() != t) {
      toRet.push_back(m);
    }

  }

  return toRet;
}

double Level::getDistanceBetween(double xP1, double yP1, double xP2, double yP2) {
  return sqrt( pow(xP2 - xP1, 2) + pow(yP2 - yP1, 2) );
}

//getDistanceBetween adapted to use olc::vd2d .mag()
double Level::getDistanceBetween(const olc::vd2d &point1, const olc::vd2d &point2) {
  return (point1 - point2).mag();
}
void Level::renderEntities(Example& gfx) const {
  for(Projectile *p : projectiles) {
    (*p).drawSelf(gfx);
  }

  for(Mob *m : mobs) {
    (*m).drawSelf(gfx);
  }
}

olc::vd2d Level::getPlayerPosition() const{
  return player.getPos();
}

Player& Level::getPlayer() { return player; }

void Level::setWidth(int i) {
  _levelWidth = i;
}

void Level::setHeight(int i) {
  _levelHeight = i;
}

int Level::getWidth() {
  return _levelWidth;
}

int Level::getHeight() {
  return _levelHeight;
}
