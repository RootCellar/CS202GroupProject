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
  olc::vd2d _vel = { 0.0, 0.0 };


  // Decal/Sprite variables
  olc::Decal* _decal = nullptr;
  olc::vf2d _spriteDimensions;
  olc::vi2d _spriteSheetOffset;
  olc::vi2d _spriteSourceSize = { 16, 16 };
  olc::vf2d _spriteScaling = { 1.0f, 1.0f };

  bool _singleSprite = false; // If it's single image that we rotate set to true
  bool _useRotaions; // If we want the sprite to be rotated
  double _spriteRot = 0.0; // Rotation of sprite
  double _spriteRotOffset = 0.0;
  int _graphicState; // The specfic state of motion in the given faced direction
  int _graphicStateCount = 2; // Number of states per direction faced
  // How many frames until we change the state
  int _graphicStateTimer = 25;
  int _frameCount = 0;

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
  virtual void drawSelf(Example& gfx) const = 0;
  // Graphics related functions
  //virtual void drawSelf(olc::PixelGameEngine& gfx, olc::vd2d offset);

  //void setDecal(string sFilename);
  //void setGraphicStateTimer(int t); // Sets _graphicStateTimer -> (How many frames until we change the state)
  //void setSpriteRot(double angle); // Sets the angle the sprite is rotated to

  //bool getIfSpriteRot();  // Maybe not need

  //void spriteStateManager(bool isAlive); // Manages the Decal/Sprite variables as needed

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
