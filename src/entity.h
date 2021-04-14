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
  std::string _name;

  olc::vd2d _pos;
  olc::vd2d _vel = { 0.0, 0.0 };

    olc::vd2d _direction;

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

  // Sprite stuff following what I did for projectiles
  std::shared_ptr <olc::Sprite> _spritePtr = nullptr;
  std::shared_ptr <olc::Decal> _decalPtr = nullptr;
  float _spriteOffset = 0;
  // Now we need getters and setters I made down, we may be able to replace with * but I don't want
  // to manage resources
public:
  Entity();

  Entity(double x, double y);

  virtual ~Entity() = default;

  virtual void setLevel(Level* l);

  virtual void update() = 0;

  // This may not need to be a virtual function or pure virtual function
  // Offsets x and y are for position on screen as opposed to on the map.
  virtual void drawSelf(olc::PixelGameEngine * gfx /*, float offsetx, float offsety*/) const = 0;

//  virtual void drawSelf(Example& gfx) const = 0;

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

  void setRedundant();
  void setRedundant(bool b);
  bool isRedundant() const;

  olc::vd2d getPos() const;
  void setPos(const olc::vd2d &newPos) ;
  void addToPos(const olc::vd2d &disp) ;
  olc::vd2d getDirection () const;
  void setDirection(const olc::vd2d &newDirection);



  int getId() const;

  // Sprite stuff
//  void setDecal(std::string); // maybe combine set sprite and decal so that it's faster
  olc::Decal * getDecal () const; // use .get() method in unique_ptr
  olc::vf2d getDecalScale (float pixels) const;
  float getSpriteRot () const;
  void setSpriteOffset () ;
  olc::vd2d getDecalCenter () const;
};

bool operator==(const Entity &one, const Entity &two);

//#include "level.h"

#endif
