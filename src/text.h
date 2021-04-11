/*text.h
4/10/2021
This is the header file for the text classes and functions.
*/

#ifndef TEXT_HPP
#define TEXT_HPP


#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using std::stringstream;
#include <map>
using std::map;
#include <iostream>
using std::cout;
using std::endl;
#include "olcPixelGameEngine.h"

class Text
{
public:
    Text();
    Text(const std::string purpose, olc::Decal* decal, const olc::vf2d sourceOffset, const olc::vf2d position, const int Lifetime);
    
    //static void loadTextDecal(std::string sFilename = "Alphabet.png");


    string _purpose = "none"; // Define the purpose of the decal
     /*static*/ olc::Decal* _decal;   
    olc::vf2d _sourceOffset = { 0.0f, 0.0f };
    olc::vf2d _sourceSize = { 9.0f, 12.0f };
    olc::vf2d _pos = { 0.0f, 0.0f };
    olc::vf2d _scale = { 1.0f, 1.0f };
    int _Lifetime = -1; // Lifetime in frames, -1 is permenant until otherwise, 0 is delete
    olc::Pixel _color = { 0, 0, 0 };
};

void addText(std::string str, const std::string& purpose, const olc::vf2d scale, const olc::Pixel color, const int frameDuration, std::vector<Text>& vDec, olc::Decal* decalptr);
void updateTextLifetimes(std::vector<Text>& vDec);
void moveTextPos(const std::string& purpose, olc::vi2d Offset, std::vector<Text>& vDec);
void drawText(olc::PixelGameEngine* gfx, const std::vector<Text>& vDec);

class DecalMap
{
public:
    static DecalMap& get()
    {
        static DecalMap me;
        return me;
    }

    DecalMap(DecalMap const&) = delete;
    void operator=(DecalMap const&) = delete;

    olc::Decal* getDecal(string name)
    {
        return _mapDecals[name]; // State specifies item in vector
    }

    void loadDecals();

private:
    DecalMap();
    ~DecalMap();

    map<string, olc::Decal*> _mapDecals;
};

DecalMap::DecalMap() {}
DecalMap::~DecalMap() {}

void DecalMap::loadDecals()
{
    auto load = [&](string sName, string sFilename)
    {
        olc::Decal* d = new olc::Decal(new olc::Sprite(sFilename));
        _mapDecals[sName] = d;
    };

    // Text
    load("Text", "Alphabet.png");
}

#endif // !TEXT_HPP