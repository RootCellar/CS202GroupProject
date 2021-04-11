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

auto Entity::getXPos() const { return _pos.x; }
auto Entity::getYPos() const { return _pos.y; }


void Entity::setRedundant() { _bRedundant = true; }
bool Entity::isRedundant() const { return _bRedundant; }

int Entity::getId() const { return id; }

bool operator==(const Entity &one, const Entity &two) {
  return one.getId() == two.getId();
}
