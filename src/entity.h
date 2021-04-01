#ifndef ENTITY_H
#define ENTITY_H

class Entity {
private:
  int xPos;
  int yPos;

public:

  virtual ~Entity() = default;

  virtual void update() = 0;
};

#endif
