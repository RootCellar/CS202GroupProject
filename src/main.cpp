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

Example::Example() : player(), level(player)
{
	sAppName = "Example";

	debug("Constructing the game...");
}

bool Example::OnUserCreate()
{
	// Called once at the start, so create things here
	DecalMap::get().loadDecals();
	Text::loadTextDecal();

	level.add(&player);

	//Text::addText("Testing testing 1 2 3...", "Testing", { 0.5f, 0.5f }, {51, 255, 255}, 200);
	return true;

}

bool Example::OnUserUpdate(float fElapsedTime)
{
	_timeStart = std::chrono::steady_clock::now(); // Get time stamp at start

	Text::drawText(this);
	Text::updateTextLifetimes();

	Clear(olc::DARK_CYAN/*olc::Pixel{0, 255, 255}*/);

	for (int x = 0; x < 1000; x += 50)
		for (int y = 0; y < 1000; y += 50)
			drawPixel(x, y, 255, 255, 255);


	level.renderEntities(*this);

	if (GetKey(olc::A).bHeld) {
		player.addToXPos(-1 * player.getSpeed());
	}
	if (GetKey(olc::D).bHeld) {
		player.addToXPos(player.getSpeed());
	}

	if (GetKey(olc::W).bHeld) {
		player.addToYPos(-1 * player.getSpeed());
	}
	if (GetKey(olc::S).bHeld) {
		player.addToYPos(player.getSpeed());
	}

	if (GetKey(olc::U).bPressed) {
		player.upgradeStaff();
	}

	xOffs = player.getXPos();
	yOffs = player.getYPos();

	level.update();

	// Runs until the fixed frame time has passed
	while (true)
	{
		std::chrono::steady_clock::time_point checkTime = std::chrono::steady_clock::now(); // Get time stamp at end
		if ((std::chrono::duration_cast<std::chrono::duration<double>>(checkTime - _timeStart)).count() > fTargetFrameTime)
			break;
	}

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
