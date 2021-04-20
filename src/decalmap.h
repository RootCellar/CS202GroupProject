/*decalmap.h
4/16/2021
This is the header file for the decalmap class.
*/

#include "olcPixelGameEngine.h"

#ifndef PI 3.14159265
#define PI 3.14159265
#endif

#ifndef DECALMAP_HPP
#define DECALMAP_HPP

class Example;

class spriteInfo {
public:
    spriteInfo(olc::vi2d sourceSize, int stateCount, olc::vf2d scaling = { 1.0f, 1.0f }, olc::vf2d deadOffset = { 1.0f, 1.0f }, olc::vf2d attackOffset = { 0.0f, 1.0f }, int stateTimer = 25, bool singleSprite = false);

    void setFlicker(int setStart, int setEnd, bool flicker = true);
    void setRotations(double spriteRotOffset = PI / 2.0, bool useRot = true);

    void spriteStateManager(bool isAlive, olc::vd2d direction, double spriteRot); // Manages the Decal/Sprite variables as needed
    //void drawDecal(Example& gfx, olc::vd2d pos, olc::vi2d additionalSheetOffset);

    // Getters
    olc::vi2d getSpriteSheetOffset() const { return _spriteSheetOffset; }
    int getGraphicFrameCount() const { return _graphicframeCount; }

    olc::vi2d getSpriteSourceSize() const { return _spriteSourceSize; }
    int getGraphicStateCount() const { return _graphicStateCount; }

    olc::vf2d getSpriteScaling() const { return _spriteScaling; }
    olc::vf2d getDeadSpriteSource() const { return _spriteDeadOffset; }
    olc::vf2d getAttackSpriteSource() const { return _spriteAttackOffset; }

    bool getIfFlicker() const { return _graphicFlicker; }
    int getFlickerStart() const { return _flickerStart; }
    int getFlickerEnd() const { return _flickerEnd; }

    int getGraphicState() const { return _graphicState; }
    int getGraphicFrameTimer() const { return _graphicFrameTimer; }

    bool getUseRotations() const { return _useRotations; }
    bool getIfSingleSprite() const { return _singleSprite; }
    bool getIfAttackAnimation() const{ return _attackAnimation; }

    bool getIfUseDirection() { return _useDirection; }
    olc::vf2d getSpriteCenter() const { return _spriteCenter; }
    double getSpriteRot() const { return _spriteRot; }
    double getSpriteRotOffset() const { return _spriteRotOffset; }


    // Setters
    void setSpriteSheetOffset(olc::vi2d sheetOffset) { _spriteSheetOffset = sheetOffset; }
    void setGraphicFrameCount(int frameCount) { _graphicframeCount = frameCount; }

    void setSpriteSourceSize(olc::vi2d sourceSize) { _spriteSourceSize = sourceSize; }
    void setGraphicStateCount(int numOfStates) { _graphicStateCount = numOfStates; }

    void setSpriteScaling(olc::vf2d scale) { _spriteScaling = scale; }
    void setDeadSpriteSource(olc::vf2d deadSourceUnitOffset) { _spriteDeadOffset = deadSourceUnitOffset; }
    void setAttackSpriteSource(olc::vf2d attackSourceUnitOffset) { _spriteAttackOffset = attackSourceUnitOffset; }

    void setIfFlicker(bool shouldFlick) { _graphicFlicker = shouldFlick; }
    void setFlickerStart(int start) { _flickerStart = start; }
    void setFlickerEnd(int end) { _flickerEnd = end; }

    void setGraphicState(int graphicState) { _graphicState = graphicState; }
    void setGraphicFrameTimer(int frameTimer) { _graphicFrameTimer = frameTimer; }

    void setUseRotations(bool useRot) { _useRotations = useRot; }
    void setIfSingleSprite(bool ifSingleSprite) { _singleSprite = ifSingleSprite; }
    void setIfAttackAnimation(bool ifSAttackAnimation) { _attackAnimation = ifSAttackAnimation; }
    
    void setIfUseDirection(bool shouldUseDirection) { _useDirection = shouldUseDirection; }
    void setSpriteCenter(olc::vf2d spriteCenter) { _spriteCenter = spriteCenter; }
    void setSpriteRot(double rotation) { _spriteRot = rotation; }
    void setSpriteRotOffset(double rotationOffset) { _spriteRotOffset = rotationOffset; }

private:
    // Decal/Sprite variables
    olc::vi2d _spriteSheetOffset = { 0, 0 };
    int _graphicframeCount = 0;

    olc::vi2d _spriteSourceSize = { 16, 16 };
    int _graphicStateCount = 2; // Number of states per direction faced

    olc::vf2d _spriteScaling = { 1.0f, 1.0f };
    olc::vf2d _spriteDeadOffset = { 1.0f, 1.0f };
    olc::vf2d _spriteAttackOffset = { 1.0f, 0.0f };

    bool _graphicFlicker = false;
    int _flickerStart = 0;
    int _flickerEnd = 0;

    // How many frames until we change the state
    int _graphicState = 0; // The specfic state of motion in the given faced direction       
    int _graphicFrameTimer = 25;

    bool _useRotations = false; // Sprites will rotate based on velocity direction
    bool _singleSprite = false; // If it's single image that we rotate set to true
    bool _attackAnimation = false; // Display upon launching an attack

    bool _useDirection = false;
    olc::vf2d _spriteCenter = { 8.0f, 8.0f };
    double _spriteRot = 0.0; // Rotation of sprite
    double _spriteRotOffset = 0.0;
};


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

    spriteInfo getDecalData(std::string name)
    {
        return _mapDecalsData[name]; // Name specifies item in vector
    }

    void loadDecals();

    bool hasData(std::string sName)
    {
        return _mapDecalsData.count(sName);
    }

private:
    void loadD(std::string sName, std::string sFilename, olc::vi2d sourceSize, int stateCount, bool useDirection, 
        olc::vf2d scaling = { 1.0f, 1.0f }, bool singleSprite = false,
        double spriteRotOffset = PI / 2.0, bool useRot = true, olc::vf2d spriteCenter = {8.0f, 8.0f},
        olc::vf2d deadOffset = { 1.0f, 1.0f }, olc::vf2d attackOffset = { 0.0f, 1.0f }, 
        int stateTimer = 25, int setStart = 0, int setEnd = 0, bool flicker = false);

private:
    DecalMap();
    ~DecalMap();

    std::map<std::string, olc::Decal*> _mapDecals;
    std::map<std::string, spriteInfo> _mapDecalsData;
};

#endif // !DECALMAP_HPP
