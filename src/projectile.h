#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile : public Entity {

public:

  //update the projectile, move it etc.
  void update() {

  }

  virtual void drawSelf(olc::PixelGameEngine* gfx) const override {
      // Drawing code here...
  }

};

#endif
