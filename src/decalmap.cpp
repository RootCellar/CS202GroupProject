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
        olc::Sprite* s = new olc::Sprite(sFilename);
        olc::Decal* d = new olc::Decal(s);
        _mapSprites[sName] = s;
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
    load("Web", "Web Projectile 7x11.png");
    load("Bullet", "Bullet.png");
    load("Fireball", "fireBall.png");

    // Test sprites
    load("Trailing Fireball", "test2.png");
    load("New Chasing Fireball", "Egg_Yolk_Fireball.png");

    // Miscellaneous
    load("Dollar", "Dollar.png");
}