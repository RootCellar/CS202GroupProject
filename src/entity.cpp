#include "entity.h"

int Entity::idPoint = 0;

//Default construct an entity to be far outside the level bounds
Entity::Entity(): _pos(-10000, -10000) {
  id = idPoint++;

  debug("Entity constructed");
}

Entity::Entity(double x, double y): _pos(x, y) {
  id = idPoint++;

}

void Entity::setLevel(Level* l) {
  level = l;
}

void Entity::setDecal(string sFilename) { _decal = new olc::Decal(new olc::Sprite(sFilename)); }

void Entity::setDeadSpriteSource(olc::vf2d sourceOffset) { _spriteDeadOffset = sourceOffset; }
void Entity::setAttackSpriteSource(olc::vf2d sourceOffset) { _spriteAttackOffset = sourceOffset; }

void Entity::setGraphicState(int startState, int stateCount) { _graphicState = startState; _graphicStateCount = stateCount; }
auto Entity::getGraphicState() { return _graphicState; }

void Entity::setGraphicStateTimer(int t) { _graphicStateTimer = t; }
void Entity::setGraphicFlicker(bool flicker, int flickerStateStart, int flickerStateEnd)
{
    _graphicFlicker = flicker;
    _flickerStart = flickerStateStart;
    _flickerEnd = flickerStateEnd;
}

void Entity::setSpriteRotOffset(double angle) { _spriteRotOffset = angle; }
auto Entity::getSpriteRotOffset() { return _spriteRot; }



void Entity::spriteStateManager(bool isAlive)
{
    if (isAlive)
    {
        if (_vel != olc::vd2d{ 0.0, 0.0 }) // Sprite when moving
        {
            if (_useRotations)
                _spriteRot = convertToAngle(_vel);
            if (_frameCount >= _graphicStateTimer) // Runs through all movement states and starts again
            {
                _frameCount = 0;
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

        _spriteSheetOffset = _graphicState * _spriteSourceSize;

        // Sprite when lauching an attack
        if (_attackAnimation)
            _spriteSheetOffset = _spriteAttackOffset;

        _frameCount++;
    }
    else
    { // Dead sprite, supposedly
        _spriteSheetOffset = _spriteDeadOffset;
    }
}


// Position manipulation
void Entity::setXPos(double newX) { _pos.x = newX; }
void Entity::setYPos(double newY) { _pos.y = newY; };
void Entity::addToXPos(double addedX) { _pos.x += addedX; }
void Entity::addToYPos(double addedY) { _pos.y += addedY; }

double Entity::getXPos() const { return _pos.x; }
double Entity::getYPos() const { return _pos.y; }

// Miscellaneous
void Entity::setRedundant() { _bRedundant = true; }
void Entity::setRedundant(bool b) { _bRedundant = b; }
bool Entity::isRedundant() const { return _bRedundant; }

int Entity::getId() const { return id; }

bool operator==(const Entity &one, const Entity &two) {
  return one.getId() == two.getId();
}


double convertToAngle(const olc::vd2d components)
{
    if (components.x > 0)
        return atan(components.y / components.x);
    else
        return atan((components.y / components.x) + PI);
}

double convertToMagnitude(const olc::vd2d components)
{
    return sqrt(components.x * components.x + components.y * components.y);
}