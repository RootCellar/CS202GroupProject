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

	olc::Decal* m_pDecal_OrbWizard;
	float bounceMotion = 0.0f;
	   
	olc::Decal* m_pDecal_Staff;
	int staffStage = 0;
	bool staffUpgraded = false;
	float staffOffsetAngle = 0.0f;
	float staffAngle = 0.0f;
	bool staffRotShiftLeft = false;
	olc::vf2d staffPos = { 150.0f, 150.0f };

	olc::Pixel staffUpTextColor = { 255, 0, 0, 0 };
	int colorChangeHolder = 0;
	int shakeTimer = 3;
	int shakeCounter = 0;

	//Player player;

	//Level level;

public:

	Example()//: level(player)
	{
		sAppName = "Example";

	debug("Constructing the game...");
}


	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		//DecalMap::get().loadDecals();
		Text::loadTextDecal();
		m_pDecal_HealthBar = new olc::Decal(new olc::Sprite("Health Bar States.png"));
		m_pDecal_OrbWizard = new olc::Decal(new olc::Sprite("Orb Wizard.png"));
		m_pDecal_Staff = new olc::Decal(new olc::Sprite("Staffs.png"));

	level.add(&player);

		//Text::addText("Testing testing 1 2 3...", "Testing", { 0.5f, 0.5f }, {51, 255, 255}, 200);
		Text::addText("HP " + valueToString(health), "HP", { 255, 25, 25 }, -1, { 0.5f, 0.5f });
		Text::setTextPos("HP", { 50, 220 });

		Text::addText("MP " + valueToString(mana), "MP", { 255, 25, 25 }, -1, { 0.5f, 0.5f });
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

			if (GetKey(olc::U).bPressed)
			{
				if (staffStage < 3)
					staffStage++;
				Text::addText("staff upgraded!", "StaffUP", { 255, 0, 0, 0 }, 255, { 0.25f * float(staffStage + 1), 0.25f * float(staffStage + 1) });
				Text::setTextPos("StaffUP", staffPos - olc::vf2d{ 30.0f, 20.0f + 7.5f * float(staffStage) });
			}
		}
		if (Text::doesTextExist("StaffUP"))
		{
			int colorChangeRate = 4;
			if (staffUpTextColor.r == 255 && staffUpTextColor.g < 255 && staffUpTextColor.b == 0) // Red to yellow
			{
				colorChangeHolder += 5 * colorChangeRate;
				if (colorChangeHolder > 255)
					colorChangeHolder = 255;

				staffUpTextColor.g = colorChangeHolder;
			};

			if (staffUpTextColor.r > 0 && staffUpTextColor.g == 255 && staffUpTextColor.b == 0) // Yellow to green
			{
				colorChangeHolder -= 5 * colorChangeRate;
				if (colorChangeHolder < 0)
					colorChangeHolder = 0;

				staffUpTextColor.r = colorChangeHolder;
			};

			if (staffUpTextColor.r == 0 && staffUpTextColor.g == 255 && staffUpTextColor.b < 255) // Green to aqua
			{
				colorChangeHolder += 5 * colorChangeRate;
				if (colorChangeHolder > 255)
					colorChangeHolder = 255;

				staffUpTextColor.b = colorChangeHolder;
			};

			if (staffUpTextColor.r == 0 && staffUpTextColor.g > 0 && staffUpTextColor.b == 255) // Aqua to blue
			{
				colorChangeHolder -= 5 * colorChangeRate;
				if (colorChangeHolder < 0)
					colorChangeHolder = 0;

				staffUpTextColor.g = colorChangeHolder;
			};

			if (staffUpTextColor.r < 255 && staffUpTextColor.g == 0 && staffUpTextColor.b == 255) // Blue to purple
			{
				colorChangeHolder += 5 * colorChangeRate;
				if (colorChangeHolder > 255)
					colorChangeHolder = 255;

				staffUpTextColor.r = colorChangeHolder;
			};

			if (staffUpTextColor.r == 255 && staffUpTextColor.g == 0 && staffUpTextColor.b > 0) // Purple to red
			{
				colorChangeHolder -= 5 * colorChangeRate;
				if (colorChangeHolder < 0)
					colorChangeHolder = 0;

				staffUpTextColor.b = colorChangeHolder;
			};

			staffUpTextColor.a -= 1;

			Text::editTextColor("StaffUP", staffUpTextColor);

			shakeCounter++;

			if (shakeCounter == shakeTimer)
			{
				Text::addToTextPos("StaffUP", { float(rand() % 2) - 0.5f, float(rand() % 2) - 0.5f });
				shakeCounter = 0;
			}
		}

		if (staffRotShiftLeft)
		{
			staffAngle += 0.008;
			if (staffAngle > PI / 7.0f) // Maybe 8.0f is better than 7.0f
				staffRotShiftLeft = false;
		}
		else
		{
			staffAngle -= 0.008;
			if (staffAngle < 0.0f)
				staffRotShiftLeft = true;
		}

		staffOffsetAngle += 0.064f;

		olc::vf2d staffPosOffset = {2.0f, 2.0f};

		if (staffOffsetAngle > PI * 4.0f)
			staffOffsetAngle -= PI * 4.0f;

		if (staffOffsetAngle >= 0 && staffOffsetAngle < PI * 2.0f)
		{
			staffPosOffset.x *= cosf(staffOffsetAngle);
			staffPosOffset.y *= sinf(staffOffsetAngle);
		}
		else if (staffOffsetAngle >= PI * 2.0f && staffOffsetAngle < PI * 4.0f)
		{
			staffPosOffset.x *= cosf(staffOffsetAngle) / 2.0f + 0.5f;
			staffPosOffset.y *= sinf(staffOffsetAngle) / 2.0f;
		}

		// Orb Wizard
		bounceMotion += 0.12f;
		float changeX = 0.1f * cosf(bounceMotion);
		float changeY = 0.05f * sinf(bounceMotion - float(PI) / 2.0f);
		DrawPartialRotatedDecal({ 143.0f - 4.0f * changeY, 150.0f + 6.0f * changeX }, m_pDecal_OrbWizard, 0.0f, {8.0f, 8.0f}, { 0.0f, 0.0f }, { 16.0f, 14.0f }, { 0.90f + changeX, 0.95f + changeY });

		// Staff
		DrawPartialRotatedDecal(staffPos + staffPosOffset, m_pDecal_Staff, staffAngle - PI / 7.0f , { 17.0f, 18.0f }, { 34.0f * staffStage, 0 }, { 34.0f, 36.0f });

		// Health bar
		DrawPartialDecal({ 10.0f, 220.0f }, m_pDecal_HealthBar, { 0.0f, 120.0f - 4.0f * std::ceil(float(health / maxHealth * 30.0)) }, { 32.0f, 5.0f });
		Text::overWriteText("HP " + valueToString(health), "HP", olc::PixelF(1.0 - health / maxHealth, health / maxHealth, 0));

		// Mana bar
		DrawPartialDecal({ 10.0f, 210.0f }, m_pDecal_HealthBar, { 33.0f, 120.0f - 4.0f * std::ceil(float(mana / maxMana * 30.0)) }, { 32.0f, 5.0f });
		Text::overWriteText("MP " + valueToString(mana), "MP", olc::PixelF(1.0 - (mana / maxMana) * 0.7 - 0.3, 1.0 - (mana / maxMana) * 0.7 - 0.3, 1.0));

		Text::updateTextLifetimes();

		Clear(olc::DARK_CYAN/*olc::Pixel{0, 255, 255}*/);
		/*for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(0, 0, 0));*/

	for (int x = 0; x < 1000; x+=50)
	for (int y = 0; y < 1000; y+=50)
	drawPixel(x, y, 255, 255, 255);


	level.renderEntities(*this);

		//if( x > ScreenWidth() ) x=0;

	if(GetKey(olc::A).bHeld) {
		player.addToXPos(-1 * player.getSpeed());
	}
	if(GetKey(olc::D).bHeld) {
		player.addToXPos(player.getSpeed());
	}

	if(GetKey(olc::W).bHeld) {
		player.addToYPos(-1 * player.getSpeed());
	}
	if(GetKey(olc::S).bHeld) {
		player.addToYPos(player.getSpeed());
	}

	xOffs = player.getXPos();
	yOffs = player.getYPos();

	level.update();
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
