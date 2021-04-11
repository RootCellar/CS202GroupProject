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
//#include "text.cpp"

class Example : public olc::PixelGameEngine
{
public:

	float fTargetFrameTime = 1.0f / 50.0f; // Virtual FPS of 50fps
  float fAccumulatedTime = 0.0f;

	int x = 0;
	int y = 0;

	std::vector<Text> _vText;

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
		DecalMap::get().loadDecals();


		x = ScreenWidth() / 2;
		y = ScreenHeight() / 2;


		//addText(string("Hi! This is my trial text."), "TextTrial", { 0.5f, 0.5f }, { 255, 0, 255 }, -1, _vText, DecalMap::get().getDecal("Text"));

		addText("Do I have this working?", "Testing", olc::vf2d{ 1.0f, 0.5f }, olc::Pixel{255, 255, 255}, 300, _vText, DecalMap::get().getDecal("Text"));
		moveTextPos("Testing", {5,5}, _vText);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		drawText(this, _vText);

		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime)
		{
			fAccumulatedTime -= fTargetFrameTime;
			//fElapsedTime = fTargetFrameTime;
		}
		else
			return true; // Don't do anything this frame

		
		updateTextLifetimes(_vText);

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

double convertToAngle(const olc::vd2d components)
{
	if (components.x > 0)
		return atanf(components.y / components.x);
	else
		return atanf((components.y / components.x) + PI);
}

double convertToMagnitude(const olc::vd2d components)
{
	return sqrt(components.x * components.x + components.y * components.y);
}

int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
