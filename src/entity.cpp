#include "entity.h"

int Entity::idPoint = 0;

Entity::Entity() {
  id = idPoint++;

//  debug("Entity constructed");
}

Entity::Entity(const olc::vd2d &sPos): _position(sPos) {
    id = idPoint++;

//    debug("Entity constructed using vd2d");
}
void Entity::setLevel(Level* l) {
  level = l;
}

/*
// Should contain something like the following IF we are using sprites/decals

olc::Decal* m_pDecal = new olc::Decal(new olc::Sprite(sFilename));
gfx->DrawPartialDecal( // Sprite
      { (_posx - offsetx) * unitSize, (_posy - offsety) * untiSize }, // x and y with unitSize = size of the map's unit increment (unit or tile)
      m_pDecal, { nSheetOffsetX, nSheetOffsetY }, { 16, 16 }, // The sprite as a decal, offsets into the sprite sheet, and the pixel size of the sprite
      { scaleX, scaleY }); // scaling in x and y
*/

// Position manipulation
void Entity::setXPos(int newX) { xPos = newX; }
void Entity::setYPos(int newY) { yPos = newY; };
void Entity::addToXPos(int addedX) { xPos += addedX; }
void Entity::addToYPos(int addedY) { yPos += addedY; }

auto Entity::getXPos() const { return xPos; }
auto Entity::getYPos() const { return yPos; }

void Entity::setRedundant() { _bRedundant = true; }
bool Entity::isRedundant() const { return _bRedundant; }

int Entity::getId() const { return id; }

bool operator==(const Entity &one, const Entity &two) {
  return one.getId() == two.getId();
}
