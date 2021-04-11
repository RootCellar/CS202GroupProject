#ifndef MAIN_H
#define MAIN_H

//Engine
#include "olcPixelGameEngine.h"

//Our Headers
#include "debug.h"

#include "entity.h"
#include "mob.h"
#include "projectile.h"
#include "spell.h"
#include "player.h"
#include "level.h"

//C++ Headers
#include <iostream>

//Using statements
using std::cout;
using std::endl;

double convertToAngle(const olc::vd2d components);
double convertToMagnitude(const olc::vd2d components);

#endif
