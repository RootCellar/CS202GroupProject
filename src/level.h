#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "entity.h"
#include "mob.h"
#include "player.h"
#include "projectile.h"

//The world, bosses everyone else around but also serves them
class Level {
private:

  Player player;

  std::vector<Mob> mobs;
  std::vector<Projectile> projectiles;

public:

  Level(Player p) {
    player = p;
  }

  void update() {


    for(Mob m : mobs) {
      m.update();
    }

    for(Projectile p : projectiles) {
      p.update();
    }

  }

};

#endif
