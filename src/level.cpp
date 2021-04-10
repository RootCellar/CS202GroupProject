#include "level.h"
#include "chuck.h"

Level::Level(Player * p): player(p) {
  debug("Constructing the level...");
}

void Level::add(Mob *m) {
  if(!has(m)) pendingMobSpawns.push_back(m);
}

void Level::add(Projectile *p) {
  if(!has(p)) pendingProjectileSpawns.push_back(p);
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
    // My balls
    testProjectile.update();
    test2.update();
    test3.update();
  for(Mob *m : mobs) {
    (*m).update();
  }

  for(Projectile *p : projectiles) {
    (*p).update();
  }

  //Spawn mobs and projectiles from our lists

  while(pendingMobSpawns.size() > 0) {
    Mob *m = pendingMobSpawns.at(0);
    pendingMobSpawns.erase( pendingMobSpawns.begin() );
    if(!has(m)) mobs.push_back(m);
  }

  while(pendingProjectileSpawns.size() > 0) {
    Projectile *p = pendingProjectileSpawns.at(0);
    pendingProjectileSpawns.erase( pendingProjectileSpawns.begin() );
    if(!has(p)) projectiles.push_back(p);
  }

  //De-spawn mobs from lists
  while(pendingMobRemovals.size() > 0) {
    Mob *m = pendingMobRemovals.at(0);
    pendingMobRemovals.erase( pendingMobRemovals.begin() );
    if(!has(m)) {
      continue;
    }

    mobs.erase( getIteratorToMob(m) );
  }

  //Despawn projectile from lists

  while(pendingProjectileRemovals.size() > 0) {
    Projectile *p = pendingProjectileRemovals.at(0);
    pendingProjectileRemovals.erase( pendingProjectileRemovals.begin() );
    if(!has(p)) {
      continue;
    }

    projectiles.erase( getIteratorToProjectile(p) );
  }

}

void Level::renderEntities(olc::PixelGameEngine *gfx) const {
    //Render these balls
    testProjectile.drawSelf(gfx);
    test2.drawSelf(gfx);
    test3.drawSelf(gfx);
    player->drawSelf(gfx);
    // test text
    gfx->DrawStringDecal(olc::vi2d{100,100}, "This text using olc", olc::WHITE);
  for(Projectile *p : projectiles) {
    (*p).drawSelf(gfx);
  }

  for(Mob *m : mobs) {
    (*m).drawSelf(gfx);
  }
}
