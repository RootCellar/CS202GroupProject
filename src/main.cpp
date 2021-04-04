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

//Our Headers
#include "debug.h"

//#include "level.h"
#include "entity.h"
#include "mob.h"
#include "projectile.h"
#include "player.h"
#include "spell.h"

//C++ Headers
#include <iostream>

//Using statements
using std::cout;
using std::endl;

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Example";
	}

	float fTargetFrameTime = 1.0f / 50.0f; // Virtual FPS of 50fps
  float fAccumulatedTime = 0.0f;

	int x = 0;
	int y = 0;
//    std::unique_ptr <olc::Sprite> fireBall;
//    olc::Sprite * spritePtr = nullptr;
public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		x = ScreenWidth() / 2;
		y = ScreenHeight() / 2;
//        fireBall = std::make_unique<olc::Sprite>("fireBall.png");
//        spritePtr = new olc::Sprite("fireBall.png");
        m_pDecal = new olc::Decal(new olc::Sprite("test2.png"));
        myBalls = getMyBalls(olc::vd2d{200, 200} , 10);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{



		Clear(olc::BLACK);
		DrawDecal(olc::vi2d{0, 0}, m_pDecal , {1,1});
//        DrawRotatedDecal(olc::vi2d{0, 0}, m_pDecal , {10, 10});
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

		// myBalls
		p.update();
        p.drawSelf(this, x, y);

        this->SetPixelMode(olc::Pixel::ALPHA);

        for ( const auto& ball : myBalls) {
            ball->update();
            ball->drawSelf(this, x, y);
//            ball->update();
//            DrawDecal({200,200}, ball->test2.get());
        }

        this->SetPixelMode(olc::Pixel::NORMAL);
//        DrawSprite(olc::vi2d {x, y}, fireBall.get());


        fAccumulatedTime += fElapsedTime;
        if (fAccumulatedTime >= fTargetFrameTime)
        {
            fAccumulatedTime -= fTargetFrameTime;
            //fElapsedTime = fTargetFrameTime;
        }
        else
            return true; // Don't do anything this frame
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
protected:
    Projectile p { olc::vd2d {100, 100}, olc::vd2d {200,200}};
    std::vector <std::unique_ptr<Projectile>> myBalls ; //= getMyBalls(olc::vd2d{200, 200} , 10);
    olc::Decal* m_pDecal = nullptr;
//    std::unique_ptr<olc::Decal> m_pDecal = nullptr;
    std::unique_ptr<olc::Sprite> myFireballSprite = nullptr;
};


int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
