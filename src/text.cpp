/*text.cpp
4/10/2021
This is the cpp file for the text classes and functions.
*/

#include "text.h"

olc::Decal* Text::_decal = nullptr;
std::map<std::string, textData> Text::_mText = {}; // Holds the text information
olc::vf2d Text::_sourceSize = { 9.0f, 12.0f }; // Size of character on the sprite sheet

void Text::loadTextDecal(std::string sFilename)
{
    _decal = new olc::Decal(new olc::Sprite(sFilename));
}

Text::Text() {}
Text::Text(const olc::vf2d sourceOffset, const olc::vf2d position)
    : _sourceOffset{ sourceOffset }, _posOffSet{ position }{}

void Text::addText(std::string str, const std::string& purpose, const olc::Pixel color, const int frameDuration, const olc::vf2d scale)
{
    if (doesTextExist(purpose))
    {
        std::cout << "Tried to use the already used text key: " << purpose << std::endl;
        return;
    }
    _mText[purpose]._color = color;
    _mText[purpose]._Lifetime = frameDuration;
    _mText[purpose]._scale = scale;

    textArranger(str, purpose, scale, _mText);
}

// Adds text to an already present piece of text data
void Text::concatenateText(std::string str, const std::string& purpose, const bool addToEnd, olc::vf2d offSet)
{
    if (!doesTextExist(purpose))
    {
        std::cout << "Tried to concatenate text with an invalid text key: " << purpose << std::endl;
        return;
    }
    else
    {
        if (addToEnd)
            offSet = _mText[purpose]._vText.back()._posOffSet + olc::vf2d{ _sourceSize.x, 0.0f };

        textArranger(str, purpose, _mText[purpose]._scale, _mText, offSet);
    }
}

// Edits a text already added
bool Text::overWriteText(std::string str, const std::string& purpose)
{
    if (doesTextExist(purpose))
    {
        _mText[purpose]._vText.clear(); // Empty the vector of letters
        textArranger(str, purpose, _mText[purpose]._scale, _mText); // Write new letters
        return true;
    }
    else
    {
        std::cout << "Tried to overwrite an invalid text key: " << purpose << std::endl;
        return false;

    }
}

// Edits a text already added
bool Text::overWriteText(std::string str, const std::string& purpose, const olc::Pixel color)
{   
    if (overWriteText(str, purpose))
        _mText[purpose]._color = color;
    else
        return false;
    return true;

}

// Edits a text already added
bool Text::overWriteText(std::string str, const std::string& purpose, const olc::Pixel color, const int frameDuration, const olc::vf2d scale)
{
    if (overWriteText(str, purpose, color))
        _mText[purpose]._Lifetime = frameDuration;
    else
        return false;
    return true;
};

// Updates the lifetimes of all text
void Text::updateTextLifetimes()
{
    std::vector<std::string> deletionQue; // Store keys of the data to be deleted

    for (auto& [key, data] : _mText)
    {
        if (data._Lifetime == -1)
            continue;
        else
            data._Lifetime--;

        if (data._Lifetime == 0)
            deletionQue.push_back(key);
    }

    // Remove key data pair if lifetime reaches zero
    for (auto& i : deletionQue)
        removeText(i);
}

// Sets the text to the specified position
void Text::setTextPos(const std::string& purpose, olc::vf2d newPos)
{
    if (doesTextExist(purpose)) // Check if the key, purpose, is in _mText
        _mText[purpose]._pos = newPos;
    else
        std::cout << "Tried to set position of invalid text key: " << purpose << std::endl;
}

// Changes an existing text's color with the same given purpose
void Text::editTextColor(const std::string& purpose, const olc::Pixel color)
{
    if (doesTextExist(purpose))
        _mText[purpose]._color = color;
}

// Returns true if a text with the given purpose exists
bool Text::doesTextExist(const std::string& purpose)
{
    return _mText.count(purpose); // Check if the key, purpose, is in _mText
}

// Removes the specified text
void Text::removeText(const std::string& purpose)
{
    // Remove key data pair
    if (doesTextExist(purpose)) // Check if the key, purpose, is in _mText
        _mText.erase(purpose);
    else
        std::cout << "Tried to erase invalid text key: " << purpose << std::endl;
}

// Flips the _stuckOnScreen bool
void  Text::flipStuckToScreen(const std::string& purpose) {
    if (doesTextExist(purpose))
    {
        if (_mText[purpose]._stuckOnScreen)
            _mText[purpose]._stuckOnScreen = false;
        else
            _mText[purpose]._stuckOnScreen = true;
    }
    else
        std::cout << "Tried to overwrite an invalid text key: " << purpose << std::endl;
}

// Updates the positions of all text that move with the game world
void Text::updateTextPositions(const olc::vf2d& playerPosDelta)
{
    for (auto& [key, data] : _mText)
    {
        if (data._stuckOnScreen)
            continue;
        else
        {
            //addToTextPos(key, -playerPosDelta/5.0f);
            setTextPos(key, (data._pos - playerPosDelta));
        };
    }
}

// Moves the text by a specified offset from the position
void Text::addToTextPos(const std::string& purpose, olc::vf2d Offset)
{
    if (doesTextExist(purpose)) // Check if the key, purpose, is in _mText
        _mText[purpose]._pos += Offset;
    else
        std::cout << "Tried to change position of invalid text key: " << purpose << std::endl;

}

// Draws all the text stored in the _mText map
void Text::drawText(olc::PixelGameEngine* gfx)
{
    for (const auto& [key, data] : _mText)
        for (auto& letter : data._vText)
            gfx->DrawPartialDecal(data._pos + letter._posOffSet, _decal, letter._sourceOffset, letter._sourceSize, data._scale, data._color);
}

// Does the assembling of the characters
void textArranger(std::string str, const std::string& purpose, const olc::vf2d scale, std::map<std::string, textData>& mText, olc::vf2d linePos)
{
    char temp;

    float charW = 9.0f + 3.0f; // Character width
    float charH = 12.0f + 3.0f; // and hieght
    float offsetRow = 0.0f;
    float offsetCol = 0.0f;

    float charString = 0.0f; // Add to 

    charString = linePos.x;

    for (int i = 0; i < str.size(); i++)
    {
        offsetRow = 0.0f;
        offsetCol = 0.0f;

        temp = str[i];

        switch (temp)
        {
        case ' ': // Space
            charString += (charW - 2.0f) * scale.x;
            continue;
        case '!': // Exclamation mark
            offsetCol = 11.0f;
            offsetRow = 2.0f;
            break;
        case '.': // Period
            offsetCol = 12.0f;
            offsetRow = 2.0f;
            break;
        case '?': // Question mark
            offsetCol = 10.0f;
            offsetRow = 2.0f;
            break;
        case '0': // "0" - "9" = numbers
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            offsetCol = 0.0f + float(int(temp) - 48);
            offsetRow = 2.0f;
            break;
        default:
            break;
        }

        if (temp >= 'A' && temp <= 'z')
        {
            if (temp > 'Z')
                temp -= 32;
            temp -= 'A';
            offsetCol = float(temp % 13);
            offsetRow = float(temp / 13);
        }

        Text t({ offsetCol * charW, offsetRow * charH }, { charString, linePos.y });
        mText[purpose]._vText.push_back(t); // Add the new letter to the given key's (purpose's) vector
        charString += (charW - 2.0f) * scale.x;
    }
}

std::string valueToString(double value)
{
    std::stringstream s;
    s << value;
    return s.str();
}


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
}