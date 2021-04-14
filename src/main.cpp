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
#include "text.h"

void call()
{
	Text::addText("Call test", "CallTest", { 0.6, 0.6 }, { 255, 255, 255 }, 80);
	Text::setTextPos("CallTest", { 5,5 });
}

class Example : public olc::PixelGameEngine
{
public:

	float fTargetFrameTime = 1.0f / 50.0f; // Virtual FPS of 50fps
  float fAccumulatedTime = 0.0f;

	int x = 0;
	int y = 0;

	int counter = 0;

	//Player player;

	//Level level;

public:

	Example()//: level(player)
	{
		sAppName = "Example";

		//debug("Constructing the game...");
	}


	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		//DecalMap::get().loadDecals();
		Text::loadTextDecal();

		x = ScreenWidth() / 2;
		y = ScreenHeight() / 2;

		Text::addText("Testing testing 1 2 3...", "Testing", { 0.5f, 0.5f }, {51, 255, 255}, -1);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		Text::drawText(this); // Still flickers when called after the fAccumulatedTime

		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime)
		{
			fAccumulatedTime -= fTargetFrameTime;
			//fElapsedTime = fTargetFrameTime;
		}
		else
			return true; // Don't do anything this frame

		counter++;
		if (counter == 100)
		{
			Text::concatenateText("Many Additions", "Testing", false, { 55.0f, 80.0f });
			call();
		}

		Text::setTextPos("Testing", { 150 - x,150 - y });
		//Text::addToTextPos("Testing", { 1 , 1 });
		Text::updateTextLifetimes();


		// called once per frame
		/*
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));
		*/

		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(0, 0, 0));

		for (int x = 0; x < 1000; x+=50)
			for (int y = 0; y < 1000; y+=50)
				drawPixel(x, y, 255, 255, 255);

		//x++;
		drawPixel(x, y, 255, 0, 0 );
		drawPixel( 75, 75, 0, 255, 0 );

		//level.renderEntities(*this);

		//if( x > ScreenWidth() ) x=0;

		if(GetKey(olc::A).bHeld) {
			x--;
		}
		if(GetKey(olc::D).bHeld) {
			x++;
		}

		if(GetKey(olc::W).bHeld) {
			y--;
		}
		if(GetKey(olc::S).bHeld) {
			y++;
		}

		//level.update();

		return true;
	}

	void drawPixel(int xPos, int yPos, int r, int g, int b) {
		if(xPos < 0 || yPos < 0) return;

		xPos -= x;
		xPos += (ScreenWidth() / 2);

		yPos -= y;
		yPos += (ScreenHeight() / 2);

		Draw(xPos, yPos, olc::Pixel( r, g, b) );
	}

};

int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
