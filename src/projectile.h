#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <memory>

class Projectile : public Entity {
private:
    olc::vd2d _position ;
    olc::vd2d _endPosition;
    olc::vd2d _direction ;
    //olc::vd2d _displacement; // to make it easier. //
    double _distance;
    // Since, comparison of doulbes difficult, will be using the max distance to travel for life
    // time of projectile

    double _speed = .9;//.0009; // 0 for testing
    double _radius = 5;
    std::unique_ptr <olc::Sprite> fireBall = std::make_unique<olc::Sprite> ("fireBall.png");
    olc::Sprite* myBalls = fireBall->Duplicate(_position, olc::vi2d{50, 50});
public:
    Projectile() ; // Random ??
    Projectile(olc::vd2d sPos, olc::vd2d ePos): _position(sPos), _endPosition(ePos)
    {
        auto displacement = _endPosition - _position;
        _distance = displacement.mag();
        _direction = displacement / _distance; // (v2d / mag(v2d))
    }
    ~Projectile()
    {
        delete myBalls;
    }
    void drawSelf(olc::PixelGameEngine* pge, double offsetx, double offsety)
    {
//        float sx = .5f, sy = .5f;
//        std::vector<std::vector<float>> { { sx, 0, 0} , {0, sy, 0}, {0, 0, 1}};
        pge->FillCircle(_position - olc::vd2d{offsetx, offsety}, _radius, olc::MAGENTA);
//        pge->DrawSprite(_position - olc::vd2d{offsetx, offsety}, fireBall.get());
//        pge->DrawSprite(_position - olc::vd2d{offsetx, offsety}, myBalls);


//        for (int x = 0 ; x < fireBall->width ; ++x) {
//            for (int y = 0 ; y < fireBall->height ; ++y) {
//                olc::Pixel p = fireBall->GetPixel(x, y);
//
//                float nx, ny;
//                nx = x;
//                ny = y;
//
////                this->draw
//            }
//        }
    }
  //update the projectile, move it etc.
  virtual void update() override
  {
        // Updating position of projectile
        _position += _direction * _speed; //need offset if map moves around.

  }
    void xxx(const std::vector<std::vector<float>> &v, float x, float y, float &nx, float &ny)
    {

    }
};

#endif
