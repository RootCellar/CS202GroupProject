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
	{
		for(int i = 0; i < 4; i++) {

			ChaserMob* m = new ChaserMob(double(i * 100), 100.0);
			level.add(m);

		}

		for (int i = 0; i < 4; i++) {

			RangedChaserMob* m = new RangedChaserMob(double(i * 100), 100.0);
			level.add(m);

		}
	}

	/*
	{
		ScatterMob* m = new ScatterMob(100, 100);
		level.add(m);
	}
	*/

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

	for(int x = 0; x < level.getWidth(); x++) {
		drawPixel(x, 0, 255, 255, 255);
		drawPixel(x, level.getHeight(), 255, 255, 255);
	}


	for(int y = 0; y < level.getHeight(); y++) {
		drawPixel(0, y, 255, 255, 255);
		drawPixel(level.getWidth(), y, 255, 255, 255);
	}

	level.renderEntities(*this);

	Text::drawText(*this);

	//Button Presses

	if(GetKey(olc::K2).bPressed && player.getMana() > 30) {
		player.setMana(player.getMana() - 30);
		olc::vd2d fireballDir( GetMouseX(), GetMouseY() );
		Projectile* fireball = new Projectile(player.getXPos(), player.getYPos(), fireballDir - getOffsetVector());
		fireball->setShooter(&player);
		level.add(fireball);
	}

	if(GetKey(olc::K0).bPressed && player.getMana() > 80) { // key pressed 0
		player.setMana(player.getMana() - 80);
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
		if (player.getXPos() > level.getWidth())
			player.setXPos(level.getWidth());
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
		if (player.getYPos() > level.getHeight())
			player.setYPos(level.getHeight());
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

olc::vd2d Example::getOffsetVector() {
	olc::vd2d offs(ScreenWidth() / 2, ScreenHeight() / 2);
	return offs - player.getPos();
}


int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
	demo.Start();

	return 0;
}
