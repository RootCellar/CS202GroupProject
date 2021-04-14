#ifndef SOLDIER_H
#define SOLDIER_H

#include "mob.h"
#include "random.h"

class Soldier : public Mob {

private:

  int _reload;

  int _tx;
  int _ty;

public:

  Soldier(): Mob(35, 100, 100), _tx(200), _ty(200) {
    setSpeed(0.5);
  }

  void update() override {

    //Move to target
    if(getXPos() < _tx) {
      addToXPos(getSpeed());
    }
    if(getXPos() > _tx) {
      addToXPos(-1 * getSpeed());
    }
    if(getYPos() < _ty) {
      addToYPos(getSpeed());
    }
    if(getYPos() > _ty) {
      addToYPos(-1 * getSpeed());
    }

    if( (_tx - getXPos()) < getSpeed() ) {

    }

    if( (_ty - getYPos()) < getSpeed() ) {

    }
  }

};

#endif
