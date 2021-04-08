#ifndef ENTITY_H
#define ENTITY_H

#define PI 3.14159265
#include <string>
using std::string;

#include "olcPixelGameEngine.h"

class Level;
class Example;

struct vec2D
{
    double _x;
    double _y;
};

class Entity {

private:

  bool _bRedundant = false;
  string _name;

  olc::vd2d _pos;

  static int idPoint;
  int id;

  Level *level;

public:
  Entity();

  Entity(double x, double y);

  virtual ~Entity() = default;

  virtual void setLevel(Level* l);

  virtual void update() = 0;

  // This may not need to be a virtual function or pure virtual function
  // Offsets x and y are for position on screen as opposed to on the map.
  virtual void drawSelf(Example& gfx /*, float offsetx, float offsety*/) const = 0;
  /*
  // Should contain something like the following IF we are using sprites/decals

  olc::Decal* m_pDecal = new olc::Decal(new olc::Sprite(sFilename));
  gfx->DrawPartialDecal( // Sprite
        { (_posx - offsetx) * unitSize, (_posy - offsety) * untiSize }, // x and y with unitSize = size of the map's unit increment (unit or tile)
        m_pDecal, { nSheetOffsetX, nSheetOffsetY }, { 16, 16 }, // The sprite as a decal, offsets into the sprite sheet, and the pixel size of the sprite
        { scaleX, scaleY }); // scaling in x and y
  */

  // Position manipulation
  void setXPos(double newX);
  void setYPos(double newY);
  void addToXPos(double addedX);
  void addToYPos(double addedY);

  auto getXPos() const;
  auto getYPos() const;
  olc::vd2d getPos() const;

  void setRedundant();
  bool isRedundant() const;

  int getId() const;
};

bool operator==(const Entity &one, const Entity &two);

#include "level.h"

#endif
