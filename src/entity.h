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

public:

  virtual ~Entity() = default;

  virtual void update() = 0;
};



vec2D move(const double speed, const double angle)
{
    vec2D v;
    v._x = (cos(angle) * speed);
    v._y = (sin(angle) * speed);
    return v;
}

#endif
