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
#include <chrono>
using std::chrono::steady_clock;

//void call()
//{
//	Text::addText("Call test", "CallTest", { 0.6, 0.6 }, { 255, 255, 255 }, 80);
//	Text::setTextPos("CallTest", { 5,5 });
//}

class Example : public olc::PixelGameEngine
{
public:

	steady_clock::time_point _timeStart;
	std::chrono::duration<double> _timeSpan;

	float fTargetFrameTime = 1.0f / 50.0f; // Virtual FPS of 50fps
  float fAccumulatedTime = 0.0f;

	int x = 0;
	int y = 0;

	int counter = 0;

	olc::Decal* m_pDecal_HealthBar;
	int numHealthBarState = 30.0;
	int inputCounter = 0;
	int updateAfterCount = 5;
	double health = 500.0;
	double maxHealth = 500.0;

	double mana = 500.0;
	double maxMana = 500.0;

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
		m_pDecal_HealthBar = new olc::Decal(new olc::Sprite("Health Bar States.png"));

		x = ScreenWidth() / 2;
		y = ScreenHeight() / 2;

		Text::addText("Testing testing 1 2 3...", "Testing", { 0.5f, 0.5f }, {51, 255, 255}, 200);
		Text::addText("HP " + valueToString(health), "HP", { 0.5f, 0.5f }, { 255, 25, 25 }, -1);
		Text::setTextPos("HP", { 50, 220});

		Text::addText("MP " + valueToString(mana), "MP", { 0.5f, 0.5f }, { 255, 25, 25 }, -1);
		Text::setTextPos("MP", { 50, 210 });
		return true;	

	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		_timeStart = steady_clock::now(); // Get time stamp at start

	
		Text::drawText(this);

		//fAccumulatedTime += fElapsedTime;
		//if (fAccumulatedTime >= fTargetFrameTime)
		//{
		//	fAccumulatedTime -= fTargetFrameTime;
		//	//fElapsedTime = fTargetFrameTime;
		//}
		//else
		//	return true; // Don't do anything this frame

		if (IsFocused())
		{
			if (GetKey(olc::V).bPressed)
			{
				Text::flipStuckToScreen("HP");
				Text::flipStuckToScreen("MP");
			}
			if (inputCounter >= updateAfterCount)
			{
				if (GetKey(olc::G).bHeld)
					health -= 22.1;
				if (GetKey(olc::H).bHeld)
					health += 22.1287;
							   
				if (health < 0.0)
					health = 0.0;
				if (health > maxHealth)
					health = maxHealth;

				if (GetKey(olc::B).bHeld)
					mana -= 18.1;
				if (GetKey(olc::N).bHeld)
					mana += 19.1287;

				if (mana < 0.0)
					mana = 0.0;
				if (mana > maxMana)
					mana = maxMana;

				inputCounter = 0;
			}
			else
				inputCounter++;
		}


		DrawPartialDecal({ 10.0f, 220.0f }, m_pDecal_HealthBar, { 0.0f, 120.0f - 4.0f * std::ceil(float(health / maxHealth * 30.0)) }, { 32.0f, 5.0f });
		Text::overWriteText("HP " + valueToString(health), "HP", olc::PixelF(1.0 - health / maxHealth, health / maxHealth, 0));

		DrawPartialDecal({ 10.0f, 210.0f }, m_pDecal_HealthBar, { 33.0f, 120.0f - 4.0f * std::ceil(float(mana / maxMana * 30.0)) }, { 32.0f, 5.0f });
		Text::overWriteText("MP " + valueToString(mana), "MP", olc::PixelF(1.0 - (mana / maxMana) * 0.7 - 0.3, 1.0 - (mana / maxMana) * 0.7 - 0.3, 1.0));

		Text::updateTextLifetimes();

		// called once per frame
		/*
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));
		*/

		Clear(olc::DARK_CYAN/*olc::Pixel{0, 255, 255}*/);
		/*for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(0, 0, 0));*/

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
			Text::updateTextPositions({ -1.0f, 0.0f });
		}
		if(GetKey(olc::D).bHeld) {
			x++;
			Text::updateTextPositions({ 1.0f, 0.0f });
		}

		if(GetKey(olc::W).bHeld) {
			y--;
			Text::updateTextPositions({ 0.0f, -1.0f });
		}
		if(GetKey(olc::S).bHeld) {
			y++;
			Text::updateTextPositions({ 0.0f, 1.0f });
		}

		//level.update();

		// Runs until the fixed frame time has passed
		while (true)
		{
			steady_clock::time_point checkTime = steady_clock::now(); // Get time stamp at end
			if ((std::chrono::duration_cast<std::chrono::duration<double>>(checkTime - _timeStart)).count() > fTargetFrameTime)
				break;
		}

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
