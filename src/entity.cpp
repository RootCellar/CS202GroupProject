#include "entity.h"
#include "debug.h"
#include "main.h"

int Entity::idPoint = 0;

//Default construct an entity to be far outside the level bounds
Entity::Entity() : _pos(400, 400) {
  id = idPoint++;

  debug("Entity constructed");
}

Entity::Entity(double x, double y) : _pos(x, y) {
  id = idPoint++;

}

void Entity::setLevel(Level *l) {
  level = l;
}

Level* Entity::getLevel() const{
  return level;
}


void Entity::set_decal(std::string sName) { _decal = DecalMap::get().getDecal(sName); }

olc::Decal* Entity::get_decal() const{
  return _decal;
}

void Entity::set_spriteSourceSize(olc::vi2d sourceSize) { _spriteSourceSize = sourceSize; }

void Entity::setSpriteScaling(olc::vf2d scale) { _spriteScaling = scale; }

void Entity::setDeadSpriteSource(olc::vf2d sourceOffsetFactor) { _spriteDeadOffset = sourceOffsetFactor; }

void Entity::setAttackSpriteSource(olc::vf2d sourceOffsetFactor) { _spriteAttackOffset = sourceOffsetFactor; }

void Entity::setGraphicState(int startState, int stateCount) {
  _graphicState = startState;
  _graphicStateCount = stateCount;
}

void Entity::setGraphicFrameTimer(int numFrames) { _graphicStateTimer = numFrames; }

void Entity::setGraphicFlicker(bool flicker, int flickerStateStart, int flickerStateEnd) {
  _graphicFlicker = flicker;
  _flickerStart = flickerStateStart;
  _flickerEnd = flickerStateEnd;
}

void Entity::setSpriteRotOffset(double angle) { _spriteRotOffset = angle; }

void Entity::decalOut(Example& gfx, const olc::Pixel& tint) const
{
    if (_decal == nullptr)
        std::cout << "decal error" << std::endl;
    else
        gfx.DrawPartialRotatedDecal(_pos, _decal, _spriteRot + _spriteRotOffset, _spriteSourceSize / 2, _spriteSheetOffset, _spriteSourceSize, _spriteScaling, tint);
}

// Takes input for parameters related to graphics
void Entity::setGraphicParameters(const int movementStates, const olc::vi2d sourceSize, const olc::vf2d scale, const std::string decal)
{
    setGraphicState(0, 1);
    setSpriteSourceSize(sourceSize);
    setSpriteScaling(scale);
    setDecal(decal);
}



auto Entity::getSpriteRotOffset() const { return _spriteRot; }

auto Entity::getGraphicState() const { return _graphicState; }

int Entity::getGraphicFrameTimer() const { return _graphicStateTimer; }

olc::vi2d Entity::getSpriteSheetOffset() const { return _spriteSheetOffset; }

olc::vf2d Entity::getSpriteScaling() const { return _spriteScaling; }

olc::vf2d Entity::getDeadSpriteSource() const { return _spriteDeadOffset; }

olc::vf2d Entity::getAttackSpriteSource() const { return _spriteAttackOffset; }

void Entity::spriteStateManager(bool isAlive) {
    if (isAlive) {
        if (getDirection() != olc::vd2d{ 0.0, 0.0 }) // Sprite when moving
        {
            if (_useRotations)
                _spriteRot = getSpriteRot();
            if (_graphicframeCount >= _graphicStateTimer) // Runs through all movement states and starts again
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

void Entity::graphicsSetup() {

}



// Position manipulation
void Entity::setXPos(double newX) { _pos.x = newX; }

void Entity::setYPos(double newY) { _pos.y = newY; };

void Entity::addToXPos(double addedX) { _pos.x += addedX; }

void Entity::addToYPos(double addedY) { _pos.y += addedY; }

double Entity::getXPos() const { return _pos.x; }

double Entity::getYPos() const { return _pos.y; }

////////////////////////
// Position getters setters and add using vd2d
void Entity::setPos(const olc::vd2d &newPos) {
  _pos = newPos;
}

void Entity::addToPos(const olc::vd2d &disp) {
  _pos += disp;
}

olc::vd2d Entity::getPos() const {
  return _pos;
}

olc::vd2d Entity::getDirection() const {
  return _direction;
}

void Entity::setDirection(const olc::vd2d &destination) {
  _direction = destination.norm();// .norm changes it into a unit vector.
}

double Entity::getSpeed() const {
  return _speed;
}

void Entity::setSpeed(double s) {
  _speed = s;
}

/////////////////////

// Miscellaneous
void Entity::setRedundant() { _bRedundant = true; }

void Entity::setRedundant(bool b) { _bRedundant = b; }

bool Entity::isRedundant() const { return _bRedundant; }

int Entity::getId() const { return id; }

//////////////////
// For sprite and decals

void Entity::setDecal(std::string fileName) {
    if (fileName == "test2.png")
        _spriteRotOffset = PI/2;
    _spritePtr = std::make_shared<olc::Sprite> (fileName);
    _decalPtr = std::make_shared<olc::Decal> (_spritePtr.get());
}

olc::Decal *Entity::getDecal() const {
    return _decalPtr.get();
}

olc::vf2d Entity::getDecalScale(float pixels) const {
  float scale = pixels / _spritePtr->height;
  return {scale, scale};
}

float Entity::getSpriteRot() const {
  return _spriteRotOffset + atan(_direction.y / _direction.x) + (_direction.x < 0 ? PI : 0);
}

//Returns the center of the decal using the size. ie, half the width, and half the height of the sprite size
olc::vd2d Entity::getDecalCenter() const {
  return olc::vd2d(_spritePtr->width / 2.0, _spritePtr->height / 2.0);
}

void Entity::setSpriteSourceSize(const olc::vi2d &s) {
    _spriteSourceSize = s;
}

olc::vi2d Entity::getSpriteSourceSize() const{
  return _spriteSourceSize;
}

//////////////
bool operator==(const Entity &one, const Entity &two) {
  return one.getId() == two.getId();
}


double convertToAngle(const olc::vd2d components) {
  if (components.x > 0)
  return atan(components.y / components.x);
  else
  return atan((components.y / components.x) + PI);
}

double convertToMagnitude(const olc::vd2d components) {
  return sqrt(components.x * components.x + components.y * components.y);
}
