#ifndef MAIN_H
#define MAIN_H

//Engine
#include "olcPixelGameEngine.h"

//Our Headers
#include "debug.h"
#include "decalmap.h"

#include "entity.h"
#include "mob.h"
#include "projectile.h"
#include "spell.h"
#include "player.h"
#include "level.h"
#include "text.h"
#include <chrono>

//Mobs
//#include "Soldier.h" //Currently does not compile

//Class Example
class Example : public olc::PixelGameEngine
{
public:

	std::chrono::steady_clock::time_point _timeStart;
	std::chrono::duration<double> _timeSpan;

	float fTargetFrameTime = 1.0f / 50.0f; // Virtual FPS of 50fps
	float fAccumulatedTime = 0.0f;

	int x = 0;
	int y = 0;

	int counter = 0;

	int xOffs = 0;
	int yOffs = 0;

	Player player;

	Level level;

	Example();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	void drawPixel(int xPos, int yPos, int r, int g, int b);

};

//C++ Headers
#include <iostream>

//Using statements
using std::cout;
using std::endl;
#endif
