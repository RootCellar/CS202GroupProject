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
	Text::drawText(*this);

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
	}

	for(int y = 0; y < levelHeight; y++) {
		drawPixel(0, y, 255, 255, 255);
	}

	level.renderEntities(*this);

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
	}
	if(GetKey(olc::D).bHeld) {
		//			x++;
		player.move("right");
	}

	if(GetKey(olc::W).bHeld) {
		//			y--;
		player.move("up");
	}
	if(GetKey(olc::S).bHeld) {
		//			y++;
		player.move("down");
	}

	if (GetKey(olc::U).bPressed) {
		player.upgradeStaff();
	}

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
