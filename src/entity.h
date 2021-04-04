#ifndef ENTITY_H
#define ENTITY_H

#define PI 3.14159265
#include <string>
using std::string;
#include "olcPixelGameEngine.h"

struct vec2D
{
    double _x;
    double _y;
};

class Entity {
private:
    bool _bRedundant = false;
    string _name;

  int xPos;
  int yPos;

  static int idPoint;
  int id;

public:
  Entity() {
    id = idPoint++;
  }

  virtual ~Entity() = default;

  virtual void update() = 0;

  // This may not need to be a virtual function or pure virtual function
  // Offsets x and y are for position on screen as opposed to on the map.
  virtual void drawSelf(olc::PixelGameEngine* gfx /*, float offsetx, float offsety*/) const = 0;
  /*
  // Should contain something like the following IF we are using sprites/decals

  olc::Decal* m_pDecal = new olc::Decal(new olc::Sprite(sFilename));
  gfx->DrawPartialDecal( // Sprite
        { (_posx - offsetx) * unitSize, (_posy - offsety) * untiSize }, // x and y with unitSize = size of the map's unit increment (unit or tile)
        m_pDecal, { nSheetOffsetX, nSheetOffsetY }, { 16, 16 }, // The sprite as a decal, offsets into the sprite sheet, and the pixel size of the sprite
        { scaleX, scaleY }); // scaling in x and y
  */

  // Position manipulation
  template<typename T>
  void setXPos(T newX) { xPos = newX; }
  template<typename T>
  void setYPos(T newY) { yPos = newY; };
  template<typename T>
  void addToXPos(T addedX) { xPos += addedX; }
  template<typename T>
  void addToYPos(T addedY) { yPos += addedY; }

  auto getXPos() { return xPos; };
  auto getYPos() { return yPos; }

  void setRedundant() { _bRedundant = true; }
  bool isRedundant() { return _bRedundant; }

  int getId() const { return id; }
};

bool operator==(const Entity &one, const Entity &two) {
  return one.getId() == two.getId();
}

int Entity::idPoint = 0;

#endif
