/*decalmap.cpp
4/16/2021
This is the cpp file for the decalmap class.
*/

#include "decalmap.h"

DecalMap::DecalMap() {}
DecalMap::~DecalMap() {}

void DecalMap::loadDecals()
{
    auto load = [&](std::string sName, std::string sFilename)
    {
        olc::Decal* d = new olc::Decal(new olc::Sprite(sFilename));
        _mapDecals[sName] = d;
    };

    // Text
    load("Text", "Alphabet.png");

    // Player drawn sprites
    load("Hp&Mp", "Health Bar States.png");
    load("Wizard", "Orb Wizard.png");
    load("Staffs", "Staffs.png");

    // Barrier
    load("Barrier", "Barrier.png");

    // Hot bar
    load("HOT","HOT Bar.png");

    // Mob
    load("Spider", "Spider.png");
    load("Slime", "Slime.png");

    // Projectiles
    load("Black Hole", "Black Hole Reformatted.png");
    load("Web", "Web Projectile.png");
    load("Bullet", "Bullet.png");
    load("fireBall.png", "fireBall.png");

    // Test sprites
    load("test2.png", "test2.png");

    // Miscellaneous
    load("Dollar", "Dollar.png");
}