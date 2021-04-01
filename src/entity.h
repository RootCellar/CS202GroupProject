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

<<<<<<< HEAD
=======
<<<<<<< HEAD


vec2D move(const double speed, const double angle)
{
    vec2D v;
    v._x = (cos(angle) * speed);
    v._y = (sin(angle) * speed);
    return v;
}

=======
>>>>>>> 7a30ba4
bool operator==(const Entity &one, const Entity &two) {
  return one.getId() == two.getId();
}

int Entity::idPoint = 0;

<<<<<<< HEAD
=======
>>>>>>> 32c35c0... work on level, team and entity fixes
>>>>>>> 7a30ba4
#endif
