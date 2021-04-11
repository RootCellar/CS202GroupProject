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

class Example : public olc::PixelGameEngine
{
public:

	float fTargetFrameTime = 1.0f / 50.0f; // Virtual FPS of 50fps
  float fAccumulatedTime = 0.0f;

	int x = 0;
	int y = 0;

	std::unique_ptr<Player> player = nullptr;

	std::unique_ptr<Level> level = nullptr;

//    Player player;
//
//    Level level;
    std::unique_ptr<Projectile> testProjectile, test2, test3, followPlayer;
public:

	Example()//: level(&player)
	{
		sAppName = "Example";

		debug("Constructing the game...");
	}


	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		x = ScreenWidth() / 2;
		y = ScreenHeight() / 2;

		//////////////////////
		// According to the olc wiki, says whatever we need to create here !!!
		// So initializeing the pointers here
		player = std::make_unique<Player> ("test");

		level = std::make_unique<Level>(player.get());
		testProjectile = std::make_unique<Projectile> ( olc::vd2d {75, 75}, olc::vd2d{ 80, 80});

		test2  =  std::make_unique<OrbitalProjectile>( olc::vd2d {50, 50}, olc::vd2d{ 126, 110});

		test3 =  std::make_unique<HomingProjectile>( olc::vd2d{100, 100}, test2.get());

		followPlayer = std::make_unique<HomingProjectile>( olc::vd2d{200, 200}, player.get());

		level->add(testProjectile.get());
		level->add(test2.get());
		level->add(test3.get());
		level->add(followPlayer.get());
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        level->renderEntities(this);

        fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime)
		{
			fAccumulatedTime -= fTargetFrameTime;
			//fElapsedTime = fTargetFrameTime;
		}
		else
			return true; // Don't do anything this frame

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

//		level->renderEntities(this);

		//if( x > ScreenWidth() ) x=0;

		if(GetKey(olc::A).bHeld) {
//			x--;
            player->move("left");
		}
		if(GetKey(olc::D).bHeld) {
//			x++;
            player->move("right");
		}

		if(GetKey(olc::W).bHeld) {
//			y--;
            player->move("up");
		}
		if(GetKey(olc::S).bHeld) {
//			y++;
            player->move("down");
		}

		level->update();

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
