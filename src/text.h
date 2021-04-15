/*text.h
4/10/2021
This is the header file for the text classes and functions.
*/

#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include "olcPixelGameEngine.h"

class Text;

struct textData
{
    olc::vf2d _pos = { 0.0f, 0.0f };
    olc::vf2d _scale = { 1.0f, 1.0f };
    olc::Pixel _color = { 0, 0, 0 };
    int _Lifetime = -1; // Lifetime in frames, -1 is permenant until otherwise, 0 is delete
    std::vector<Text> _vText;
};

class Text
{
private:
    Text();
    static olc::Decal* _decal;   
    static std::map<std::string, textData> _mText; // Holds the text information
    static olc::vf2d _sourceSize;

public:
    Text(const olc::vf2d sourceOffset, const olc::vf2d position);
    
    static void loadTextDecal(std::string sFilename = "Alphabet.png");

    //std::string _purpose = "none"; // Define the purpose of the decal
    olc::vf2d _sourceOffset = { 0.0f, 0.0f };
    olc::vf2d _posOffSet = { 0.0f, 0.0f };

// Adds in a new line of text
static void addText(std::string str, const std::string& purpose, const olc::vf2d scale, const olc::Pixel color, const int frameDuration);

// Adds text to an already present piece of text data
static void concatenateText(std::string str, const std::string& purpose, const bool addToEnd = true, const olc::vf2d offSet = { 0.0f, 0.0f });

// Edits a text already added
static bool overWriteText(std::string str, const std::string& purpose);
static bool overWriteText(std::string str, const std::string& purpose, const olc::Pixel color);
static bool overWriteText(std::string str, const std::string& purpose, const olc::vf2d scale, const olc::Pixel color, const int frameDuration);

// Removes the specified text
static void removeText(const std::string& purpose);

// Can be transitioned to a more abstract class (probably)

// Updates the lifetimes of all text
static void updateTextLifetimes();

// Sets the text to the specified position
static void setTextPos(const std::string& purpose, olc::vi2d Offset);

// Moves the text by a specified offset from the position
static void addToTextPos(const std::string& purpose, olc::vi2d Offset);

// Draws all the text stored in the _mText map
static void drawText(olc::PixelGameEngine* gfx);
};

// Does the assembling of the characters
void textArranger(std::string str, const std::string& purpose, const olc::vf2d scale, std::map<std::string, textData>& mText, olc::vf2d linePos = { 0.0f, 0.0f });

std::string valueToString(double value);


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

    olc::Decal* getDecal(std::string name)
    {
        return _mapDecals[name]; // State specifies item in vector
    }

    void loadDecals();

private:
    DecalMap();
    ~DecalMap();

    std::map<std::string, olc::Decal*> _mapDecals;
};

#endif // !TEXT_HPP