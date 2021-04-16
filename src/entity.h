#ifndef ENTITY_H
#define ENTITY_H

#define PI 3.14159265
#include <string>

#include "olcPixelGameEngine.h"

double convertToAngle(const olc::vd2d components);
double convertToMagnitude(const olc::vd2d components);

class Level;
class Example;

class Entity {

private:

  bool _bRedundant = false;
  std::string _name;

  olc::vd2d _pos;
  olc::vd2d _vel = { 0.0, 0.0 };


  // Decal/Sprite variables
  olc::Decal* _decal = nullptr;
  olc::vf2d _spriteDimensions;
  olc::vi2d _spriteSheetOffset;
  olc::vi2d _spriteSourceSize = { 16, 16 };
  olc::vf2d _spriteScaling = { 1.0f, 1.0f };

  olc::vf2d _spriteDeadOffset = { 0.0f, 0.0f };
  olc::vf2d _spriteAttackOffset = { 0.0f, 0.0f };

  bool _useRotations = true; // Sprites will rotate based on velocity direction
  bool _singleSprite = false; // If it's single image that we rotate set to true
  bool _attackAnimation = false; // Display upon launching an attack

  double _spriteRot = 0.0; // Rotation of sprite
  double _spriteRotOffset = 0.0;

  int _graphicState; // The specfic state of motion in the given faced direction
  int _graphicStateCount = 2; // Number of states per direction faced

  bool _graphicFlicker = false;
  int _flickerStart = 0;
  int _flickerEnd = 0;
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

  // Graphics related functions
  virtual void drawSelf(Example& gfx) const = 0;

  void setDecal(std::string sFilename);

  void setDeadSpriteSource(olc::vf2d source);
  void setAttackSpriteSource(olc::vf2d source);

  void setGraphicState(int startState, int stateCount); // Sets the starting state and the number of states
  auto getGraphicState();

  void setGraphicStateTimer(int t); // Sets _graphicStateTimer -> (How many frames until we change the state)
  void setGraphicFlicker(bool flicker, int flickerStateStart = 0, int flickerStateEnd = 1); // Set flicker bool and start/end states

  void setSpriteRotOffset(double angle); // Sets the angle the sprite is rotated to
  auto getSpriteRotOffset();
  void spriteStateManager(bool isAlive); // Manages the Decal/Sprite variables as needed

  // Position manipulation
  void setXPos(double newX);
  void setYPos(double newY);
  void addToXPos(double addedX);
  void addToYPos(double addedY);

  double getXPos() const;
  double getYPos() const;

  void setRedundant(bool b);
  void setRedundant();
  bool isRedundant() const;

  int getId() const;
};

bool operator==(const Entity &one, const Entity &two);

#include "level.h"

#endif
