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
#include "text.h"
#include "decalmap.h"

//Mobs
//#include "Soldier.h" //Currently does not compile

//Class Example
class Example : public olc::PixelGameEngine
{
public:

	float fTargetFrameTime = 1.0f / 50.0f; // Virtual FPS of 50fps
  float fAccumulatedTime = 0.0f;

	int xOffs = 0;
	int yOffs = 0;

	int levelWidth = 1000;
	int levelHeight = 1000;

	Player player;

	Level level;

	Team enemyTeam;

	Example();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	void drawPixel(int xPos, int yPos, int r, int g, int b);

	olc::vd2d getOffsetVector();

};

//C++ Headers
#include <iostream>
#include <chrono>

#endif
