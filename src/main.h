#ifndef MAIN_H
#define MAIN_H

//Declare our game class first,
//because we include the other files in here that need it
//before we define it
class Example;


//Our Headers
#include "debug.h"

#include "level.h"
#include "entity.h"
#include "mob.h"
#include "projectile.h"
#include "player.h"
#include "spell.h"

//C++ Headers
#include <iostream>

//Using statements
using std::cout;
using std::endl;

#endif
