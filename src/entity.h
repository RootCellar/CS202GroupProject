#ifndef ENTITY_H
#define ENTITY_H

#define PI 3.14159265
#include <string>
using std::string;

#include "olcPixelGameEngine.h"

class Level;
class Example;

class Entity {

private:

  bool _bRedundant = false;
  string _name;

  olc::vd2d _pos;

  // Decal/Sprite
  olc::Decal* _decal;
  int _facingDirection;
  int _graphicState;
  // How many frames until we change the step
  int _graphicStepTimer;

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
  virtual void drawSelf(olc::PixelGameEngine& gfx) const = 0;

  // Position manipulation
  void setXPos(double newX);
  void setYPos(double newY);
  void addToXPos(double addedX);
  void addToYPos(double addedY);

  auto getXPos() const;
  auto getYPos() const;

  void setRedundant();
  bool isRedundant() const;

  int getId() const;
};

bool operator==(const Entity &one, const Entity &two);

#include "level.h"

#endif
