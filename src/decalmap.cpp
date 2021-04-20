/*decalmap.cpp
4/16/2021
This is the cpp file for the decalmap class.
*/

#include "decalmap.h"

DecalMap::DecalMap() {}
DecalMap::~DecalMap() {}

spriteInfo::spriteInfo(olc::vi2d sourceSize, int stateCount, olc::vf2d scaling, olc::vf2d deadOffset, olc::vf2d attackOffset, int stateTimer, bool singleSprite = false) :
    _spriteSourceSize(sourceSize), _graphicStateCount(stateCount), _spriteScaling(scaling), _spriteDeadOffset(deadOffset), _spriteAttackOffset(attackOffset), _graphicFrameTimer(stateTimer), _singleSprite(singleSprite)
{}

void spriteInfo::setFlicker(int setStart, int setEnd, bool flicker = true)
{
    _flickerStart = setStart;
    _flickerEnd = setEnd;
    _graphicFlicker = flicker;
}

void spriteInfo::setRotations(double spriteRotOffset = PI / 2.0, bool useRot = true)
{
    _useRotations = useRot;
    _spriteRotOffset = spriteRotOffset;
}

void spriteInfo::spriteStateManager(bool isAlive, olc::vd2d direction, double spriteRot) {
    if (!_singleSprite)
    {
        if (isAlive) {
            if (direction != olc::vd2d{ 0.0, 0.0 } || !_useDirection) // Sprite when moving or if not affected direction
            {
                if (_useRotations)
                    _spriteRot = spriteRot + _spriteRotOffset;

                if (_graphicframeCount >= _graphicFrameTimer) // Runs through all movement states and starts again
                {
                    _graphicframeCount = 0;
                    _graphicState++;

                    if (_graphicFlicker) // Flicker the decal between specified sprite animations
                    {
                        if (_graphicState > _flickerEnd)
                            _graphicState = _flickerStart;
                    }
                    if (_graphicState >= _graphicStateCount)
                        _graphicState = 0;
                }
            }
            else // Sprite when stationary
                _graphicState = 0;

            _spriteSheetOffset.x = _graphicState * _spriteSourceSize.x;
            _spriteSheetOffset.y = 0;

            // Sprite when lauching an attack
            if (_attackAnimation)
                _spriteSheetOffset = _spriteAttackOffset * _spriteSourceSize;

            _graphicframeCount++;
        }
        else
        { // Dead sprite, supposedly
            _spriteSheetOffset = _spriteDeadOffset * _spriteSourceSize;
        }
    }
}

//void spriteInfo::drawDecal(Example& gfx, olc::vd2d pos, olc::vi2d additionalSheetOffset)
//{
//    
//}


void DecalMap::loadD(std::string sName, std::string sFilename, olc::vi2d sourceSize, int stateCount, bool useDirection, olc::vf2d scaling, bool singleSprite, double spriteRotOffset, bool useRot, olc::vf2d spriteCenter,
    olc::vf2d deadOffset, olc::vf2d attackOffset, int stateTimer, int setStart, int setEnd, bool flicker)
{
    olc::Decal* d = new olc::Decal(new olc::Sprite(sFilename));
    _mapDecals[sName] = d;

    spriteInfo s(sourceSize, stateCount, scaling, deadOffset, attackOffset, stateTimer, singleSprite);
    s.setFlicker(setStart, setEnd, flicker);
    s.setRotations(spriteRotOffset, useRot);
    s.setSpriteCenter(spriteCenter);
    s.setIfUseDirection(useDirection);
    _mapDecalsData[sName] = s;
};

void DecalMap::loadDecals()
{
    auto load = [&](std::string sName, std::string sFilename)
    {
        olc::Decal* d = new olc::Decal(new olc::Sprite(sFilename));
        _mapDecals[sName] = d;
    };

    //auto load = [&](std::string sName, std::string sFilename, olc::vi2d sourceSize, int stateCount, olc::vf2d scaling, olc::vf2d deadOffset, olc::vf2d attackOffset, 
    //    int stateTimer, bool singleSprite, int setStart, int setEnd, bool flicker, double spriteRotOffset, bool useRot)
    //{
    //    olc::Decal* d = new olc::Decal(new olc::Sprite(sFilename));
    //    _mapDecals[sName] = d;
    //    spriteInfo s(sourceSize, stateCount, scaling, deadOffset, attackOffset, stateTimer, singleSprite);
    //    s.setFlicker(setStart, setEnd, flicker);
    //    s.setRotations(spriteRotOffset, useRot);
    //    _mapDecalsData[sName] = s;
    //};

    // Text
    load("Text", "Alphabet.png");

    // Player drawn sprites
    load("Hp&Mp", "Health Bar States.png");
    loadD("Wizard", "Orb Wizard.png", { 16, 14 }, 1, false, { 1.0f, 1.0f }, true, 0.0f, false, {8.0f, 7.0f});
    loadD("Staffs", "Staffs.png", { 34.0f, 36.0f }, 3, false, { 1.0f, 1.0f }, false, -PI / 7.0f, true, { 17.0f, 18.0f });

    // Barrier
    loadD("Barrier", "Barrier.png", { 16, 16 }, 18, false, { 1.0f, 1.0f }, false, PI / 2.0, false, { 8.0f, 8.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 5);
    
    // Hot bar
    load("HOT","HOT Bar.png");

    // Mob
    loadD("Spider", "Spider.png", { 16, 16 }, 2, true);
    loadD("Slime", "Slime.png", { 16, 16 }, 6, true);

    // Projectiles
    loadD("Black Hole", "Black Hole Reformatted.png", { 16, 16 }, 10, false, { 1.0f, 1.0f }, false, PI / 2.0, false, { 8.0f, 8.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f }, 15, 5, 6, true);
    loadD("Web", "Web Projectile.png", { 7, 11 }, 2, true);
    loadD("Bullet", "Bullet.png", { 16, 5 }, 3, true, { 0.5f, 0.5f }, false, PI / 2.0, true, {10.5f, 2.5f});
    loadD("fireBall", "fireBall.png", { 16, 32 }, 1, true, { 1.0f, 1.0f }, true, PI / 2.0, true, { 8.5f, 9.5f });

    // Test sprites
    //load("test2.png", "test2.png");

    // Miscellaneous
    loadD("Dollar", "Dollar.png", { 27, 13 }, 1, true, { 0.2f, 0.2f }, true, PI / 2.0, true, { 13.5f, 6.5f });
}