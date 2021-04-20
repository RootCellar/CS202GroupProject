/*
* main.cpp
* 3/25/2021
*
* This project is written by:
* Darian Marvel
* Uddeep Karki
* Aleks McCormick
* Nathon Damon
*
*/

#define OLC_PGE_APPLICATION
#include "main.h"

Example::Example(): player(), level(player)
{
	sAppName = "Example";

	debug("Constructing the game...");
}


bool Example::OnUserCreate()
{
	// Called once at the start, so create things here
	DecalMap::get().loadDecals();
	Text::loadTextDecal();

	Text::addText("Game Start!", "Begin", { 255, 255, 255 }, 70);
	Text::addToTextPos("Begin", { 50, 50 });

	level.add(&player);

	return true;
}

bool Example::OnUserUpdate(float fElapsedTime)
{
	//Rendering Code

	//Clear the Screen
	for (int x = 0; x < ScreenWidth(); x++)
	for (int y = 0; y < ScreenHeight(); y++)
	Draw(x, y, olc::Pixel(0, 0, 0));

	//Draw reference dots
	for (int x = 0; x < 1000; x+=50)
	for (int y = 0; y < 1000; y+=50)
	drawPixel(x, y, 255, 255, 255);

	for(int x = 0; x < levelWidth; x++) {
		drawPixel(x, 0, 255, 255, 255);
		drawPixel(x, levelHeight, 255, 255, 255);
	}


	for(int y = 0; y < levelHeight; y++) {
		drawPixel(0, y, 255, 255, 255);
		drawPixel(levelWidth, y, 255, 255, 255);
	}

	level.renderEntities(*this);

	Text::drawText(*this);

	//Button Presses

	if(GetKey(olc::K0).bPressed && player.getMana() > 80) { // key pressed 0
		player.setMana(player.getMana() - 80);
		player.setSpeed(player.getSpeed() * 1.75);
		player._speedSpellDuration = 80;
	}

	if(GetKey(olc::K3).bPressed && player.getMana() > 200) {
		player.heal(200);
		player.setMana(player.getMana() - 200);
	}

	if (GetKey(olc::K4).bPressed) { // key pressed 0
		player.toggleBarrier();
	}

	if (GetKey(olc::U).bPressed) {
		player.upgradeStaff();
	}

	//Keep game simulating at the correct rate

	fAccumulatedTime += fElapsedTime;
	if (fAccumulatedTime >= fTargetFrameTime)
	{
		fAccumulatedTime -= fTargetFrameTime;
		//fElapsedTime = fTargetFrameTime;
	}
	else
	return true; // Don't do anything this frame

	if(GetKey(olc::A).bHeld) {
		//			x--;

		player.move("left");
		if (player.getXPos() < 16)
			player.setXPos(16);
	}
	if(GetKey(olc::D).bHeld) {
		//			x++;
		player.move("right");
		if (player.getXPos() > levelWidth)
			player.setXPos(levelWidth);
	}

	if(GetKey(olc::W).bHeld) {
		//			y--;
		player.move("up");
		if (player.getYPos() < 16)
			player.setYPos(16);
	}
	if(GetKey(olc::S).bHeld) {
		//			y++;
		player.move("down");
		if (player.getYPos() > levelHeight)
			player.setYPos(levelHeight);
	}

	//// Shoot fireball
	//if (GetKey(olc::K2).bPressed) { // key pressed 2
	//	player.setMana(player.getMana() - 50);
	//	Projectile a(player.getXPos(), player.getYPos(), GetMouseX(), GetMouseY());
	//	p = a;
	//	level.add(&p);
	//}

	xOffs = player.getXPos();
	yOffs = player.getYPos();

	level.update();
	Text::updateTextLifetimes();

	return true;
}

void Example::drawPixel(int xPos, int yPos, int r, int g, int b) {
	if(xPos < 0 || yPos < 0) return;

	xPos -= xOffs;
	xPos += (ScreenWidth() / 2);

	yPos -= yOffs;
	yPos += (ScreenHeight() / 2);

	Draw(xPos, yPos, olc::Pixel( r, g, b) );
}



int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
	demo.Start();

	return 0;
}
