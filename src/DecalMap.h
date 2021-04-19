/*decalmap.h
4/16/2021
This is the header file for the decalmap class.
*/

#include "olcPixelGameEngine.h"

#ifndef DECALMAP_HPP
#define DECALMAP_HPP

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

#endif // !DECALMAP_HPP
