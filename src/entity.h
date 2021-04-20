#ifndef ENTITY_H
#define ENTITY_H

#define PI 3.14159265
#include <string>

#include "olcPixelGameEngine.h"

class Level;
class Example;

class Entity {

private:

  bool _bRedundant = false;
  std::string _name;

  olc::vd2d _pos;
  //olc::vd2d _vel = { 0.0, 0.0 };

    olc::vd2d _direction;// = {.6, .8};
    double _speed;
  // Decal/Sprite variables
  olc::Decal* _decal = nullptr;
  olc::vi2d _spriteSheetOffset = { 0, 0 };
  olc::vi2d _spriteSourceSize = { 16, 16 };
  olc::vf2d _spriteScaling = { 1.0f, 1.0f };

  olc::vf2d _spriteDeadOffset = { 1.0f, 1.0f };
  olc::vf2d _spriteAttackOffset = { 1.0f, 0.0f };

  bool _useRotations = true; // Sprites will rotate based on velocity direction
  bool _singleSprite = false; // If it's single image that we rotate set to true
  bool _attackAnimation = false; // Display upon launching an attack

  double _spriteRot = 0.0; // Rotation of sprite
  double _spriteRotOffset = 0.0 + PI / 2.0;

  int _graphicState; // The specfic state of motion in the given faced direction
  int _graphicStateCount = 2; // Number of states per direction faced

  bool _graphicFlicker = false;
  int _flickerStart = 0;
  int _flickerEnd = 0;
  // How many frames until we change the state
  int _graphicStateTimer = 25;
  int _graphicframeCount = 0;

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
  Level * getLevel() const;
  virtual void update() = 0;

 // Graphics related functions
  virtual void drawSelf(Example& gfx) const = 0;
  void decalOut(Example& gfx, const olc::Pixel& tint = { 255, 255, 255 }) const;

  void set_decal(std::string sName);
  olc::Decal* get_decal() const;

  void set_spriteSourceSize(olc::vi2d sourceSize);

  void setSpriteScaling(olc::vf2d scale);

  void setDeadSpriteSource(olc::vf2d source);

  void setAttackSpriteSource(olc::vf2d source);

  void setGraphicState(int startState, int stateCount); // Sets the starting state and the number of states

  void setGraphicFrameTimer(int numFrames); // Sets _graphicStateTimer -> (How many frames until we change the state)

  void setGraphicFlicker(bool flicker, int flickerStateStart = 0, int flickerStateEnd = 1); // Set flicker bool and start/end states

  void setSpriteRotOffset(double angle); // Sets the angle the sprite is rotated to

  void setGraphicParameters(const int movementStates, const olc::vi2d sourceSize, const olc::vf2d scale, const std::string decal); // Takes input for parameters related to graphics
  

  auto getGraphicState() const;

  int getGraphicFrameTimer() const;

  olc::vi2d getSpriteSheetOffset() const;

  olc::vf2d getSpriteScaling() const;

  olc::vf2d getDeadSpriteSource() const;

  olc::vf2d getAttackSpriteSource() const;

  auto getSpriteRotOffset() const;
  

  void spriteStateManager(bool isAlive); // Manages the Decal/Sprite variables as needed

  virtual void graphicsSetup();

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

  olc::vd2d getPos() const;
  void setPos(const olc::vd2d &newPos) ;
  void addToPos(const olc::vd2d &disp) ;
  olc::vd2d getDirection () const;
  void setDirection(const olc::vd2d &newDirection);

    void setSpeed(double s);
    double getSpeed () const;


  int getId() const;

  // Sprite stuff
  void setDecal(std::string); // maybe combine set sprite and decal so that it's faster
  olc::Decal * getDecal () const; // use .get() method in unique_ptr
  olc::vf2d getDecalScale (float pixels) const;
  float getSpriteRot () const;
  void setSpriteOffset () ;
  olc::vd2d getDecalCenter () const;
  void setSpriteSourceSize (const olc::vi2d&);
  olc::vi2d getSpriteSourceSize() const;

//  double getRadius () const;
//  void setRadius (double);
};

bool operator==(const Entity &one, const Entity &two);

//#include "level.h"

#endif
