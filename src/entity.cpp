#include "entity.h"
#include "debug.h"
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

//void Entity::setDecal(string sFilename) { olc::Decal* m_pDecal = new olc::Decal(new olc::Sprite(sFilename)); }
//void Entity::setGraphicStateTimer(int t) { _graphicStepTimer = t; }
//void Entity::setSpriteRot(double angle) { _spriteRot = angle; }

//bool Entity::getIfSpriteRot() { return _useRotaions; } // Maybe not need

//void Entity::spriteStateManager(bool isAlive)
//{
//    if (isAlive)
//    {
//        if (_useRotaions) // Rotating the sprites
//        {
//            _spriteRot = convertToAngle(_vel);
//        }
//
//        if (_frameCount >= _graphicStateTimer)
//        {
//            _frameCount = 0;
//            _graphicState++;
//            if (_graphicState >= _graphicStateCount)
//                _graphicState = 0;
//        }
//
//        _spriteSheetOffset.y = _graphicState * _spriteSourceSize.y;
//        _spriteSheetOffset.x = _facingDirection * _spriteSourceSize.x;
//        _frameCount++;
//    }
//    else
//    { // Dead sprite supposedly
//        _spriteSheetOffset.x = 4 * _spriteSourceSize.y;
//        _spriteSheetOffset.y = 1 * _spriteSourceSize.x;
//    }
//}


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

/////////////////////


void Entity::setRedundant() { _bRedundant = true; }
void Entity::setRedundant(bool b) { _bRedundant = b; }
bool Entity::isRedundant() const { return _bRedundant; }

int Entity::getId() const { return id; }

//////////////////
// For sprite and decals
void Entity::setDecal(std::string fileName) {
    if (fileName == "test2.png")
        _spriteOffset = PI/2;
    _spritePtr = std::make_shared<olc::Sprite> (fileName);
    _decalPtr = std::make_shared<olc::Decal> (_spritePtr.get());
}

olc::Decal *Entity::getDecal() const {
    return _decalPtr.get();
}

olc::vf2d Entity::getDecalScale(float pixels) const{
    float scale = pixels / _spritePtr->height;
    return {scale, scale};
}

float Entity::getSpriteRot() const {
    return _spriteOffset + atan(_direction.y / _direction.x) + ( _direction.x < 0 ? PI : 0);
}

//Returns the center of the decal using the size. ie, half the width, and half the height of the sprite size
olc::vd2d Entity::getDecalCenter() const{
    return olc::vd2d(_spritePtr->width/2.0, _spritePtr->height/2.0);
}
//////////////
bool operator==(const Entity &one, const Entity &two) {
  return one.getId() == two.getId();
}
