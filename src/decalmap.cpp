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

    // Mob
    load("Spider", "Spider.png");
}