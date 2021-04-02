#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile : public Entity {
private:
    olc::vd2d _position ;
    olc::vd2d _endPosition;
    olc::vd2d _direction ;
    //olc::vd2d _displacement; // to make it easier. //
    double _distance;
    // Since, comparison of doulbes difficult, will be using the max distance to travel for life
    // time of projectile

    double _speed = 0; // 0 for testing
    double _radius;
public:
    Projectile() ; // Random ??
    Projectile(olc::vd2d sPos, olc::vd2d ePos): _position(sPos), _endPosition(ePos)
    {
        auto displacement = _endPosition - _position;
        _distance = displacement.mag();
        _direction = displacement / _distance; // (v2d / mag(v2d))
    }

    void drawSelf(olc::PixelGameEngine* pge)
    {
        pge->FillCircle(_position, 3);
    }
  //update the projectile, move it etc.
  void update(olc::PixelGameEngine* pge)
  {
        // Updating position of projectile
        _position += _direction * _speed;

        drawSelf(pge);

  }

};

#endif
