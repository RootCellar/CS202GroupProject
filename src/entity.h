#ifndef ENTITY_H
#define ENTITY_H

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
