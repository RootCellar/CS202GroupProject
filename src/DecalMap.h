
#ifndef CS202GROUPPROJECT_DECALMAP_H
#define CS202GROUPPROJECT_DECALMAP_H

#include <map>
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

    olc::Decal * getDecal(string name)
    {
        return _mapDecals[name]; // State specifies item in vector
    }

    void loadDecals();

private:
    DecalMap();
    ~DecalMap();

    std::map<string, olc::Decal * > _mapDecals;
};

//DecalMap::DecalMap(){}
//DecalMap::~DecalMap(){}

void DecalMap::loadDecals()
{
    auto load = [&](string sName, string sFilename)
    {
        olc::Decal * d = new olc::Decal(new olc::Sprite(sFilename));
        _mapDecals[sName] = d;
    };

    // Text
    load("Text", "Alphabet.png");
}
#endif //CS202GROUPPROJECT_DECALMAP_H
