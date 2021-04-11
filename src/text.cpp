/*text.cpp
4/10/2021
This is the cpp file for the text classes and functions.
*/

#include "text.h"

//olc::Decal* Text::_decal = new olc::Decal(new olc::Sprite("Alphabet.png"));

//void Text::loadTextDecal(std::string sFilename)
//{
//    _decal = new olc::Decal(new olc::Sprite(sFilename));
//}

Text::Text() {}
Text::Text(const std::string purpose, olc::Decal* decal, const olc::vf2d sourceOffset, const olc::vf2d position, const int Lifetime)
    : _purpose{ purpose }, _decal{ decal }, _sourceOffset{ sourceOffset }, _pos{ position }, _Lifetime{ Lifetime } {}

void addText(std::string str, const std::string& purpose, const olc::vf2d scale, const olc::Pixel color, const int frameDuration, std::vector<Text>& vDec, olc::Decal* decalptr)
{
    char temp;

    float charW = 9.0f + 3.0f; // Character width
    float charH = 12.0f + 3.0f; // and hieght
    float offsetRow = 0.0f;
    float offsetCol = 0.0f;

    float charSpacing = 1.0f;
    float charString = 0.0f; // Add to 

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
        case '!': // Period
            offsetCol = 11.0f;
            offsetRow = 2.0f;
            break;
        case '.': // Period
            offsetCol = 12.0f;
            offsetRow = 2.0f;
            break;
        case '?': // Period
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
            offsetRow = 0.0f + float(int(temp) - 48);
            offsetCol = 2.0f;
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

        Text t(purpose, decalptr, { offsetCol * charW, offsetRow * charH }, { charString, 0.0f }, frameDuration);
        t._scale = scale;
        t._color = color;
        vDec.push_back(t);
        charString += (charW - 2.0f) * scale.x;
    }
}

void updateTextLifetimes(std::vector<Text>& vDec)
{
    for (auto& i : vDec)
    {
        if (i._Lifetime == -1)
            continue;
        else
            i._Lifetime--;
    }

    vDec.erase(remove_if(vDec.begin(), vDec.end(),
        [](const Text a) {return a._Lifetime == 0; }), vDec.end());
}

void moveTextPos(const std::string& purpose, olc::vi2d Offset, std::vector<Text>& vDec)
{
    bool ret = false;
    for (auto& i : vDec)
    {
        if (i._purpose == purpose)
        {
            i._pos += Offset;
            ret = true;
        }
    }
    if (ret)
        return;
    else
        cout << purpose << " move FAILURE!" << endl;
}

void drawText(olc::PixelGameEngine* gfx, const std::vector<Text>& vDec)
{
    for (auto& i : vDec)
        gfx->DrawPartialDecal(i._pos, i._decal, i._sourceOffset, i._sourceSize, i._scale, i._color);
}
