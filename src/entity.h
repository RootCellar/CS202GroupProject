#ifndef ENTITY_H
#define ENTITY_H

#define PI 3.14159265
struct vec2D
{
    double _x;
    double _y;
};

class Entity {
private:
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

  int getId() const { return id; }
};

bool operator==(const Entity &one, const Entity &two) {
  return one.getId() == two.getId();
}

int Entity::idPoint = 0;

#endif
