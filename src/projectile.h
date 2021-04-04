#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <memory>

class Projectile : public Entity {
private:
public:
    olc::vd2d _position ;
    olc::vd2d _endPosition;
    olc::vd2d _direction ;
    //olc::vd2d _displacement; // to make it easier. //
    double _distance;
    // Since, comparison of doulbes difficult, will be using the max distance to travel for life
    // time of projectile

    double _speed = .005;//.0009; // 0 for testing
    double _radius = 5;
//    std::unique_ptr <olc::Sprite> fireBall = std::make_unique<olc::Sprite> ("fireBall.png");
//    olc::Sprite* myBalls = fireBall->Duplicate(_position, olc::vi2d{50, 50});
//    std::unique_ptr <olc::Decal> ballPtr = std::make_unique<olc::Decal> (fireBall.get());
    olc::Decal * m_pDecal = nullptr;
//    /*olc::Decal*  */ m_pDecal = new olc::Decal(new olc::Sprite("fireBall.png"));

    std::shared_ptr <olc::Sprite> fireBall2 = nullptr;
    std::shared_ptr <olc::Decal> test2 = nullptr;
    float kurtAngle = 0;
public:
    Projectile():Entity()
    {

    } ; // Random ??
    Projectile(olc::vd2d sPos, olc::vd2d ePos): _position(sPos), _endPosition(ePos)
    {
        auto displacement = _endPosition - _position;
        _distance = displacement.mag();
        _direction = displacement / _distance; // (v2d / mag(v2d))
        /*olc::Decal*  */ m_pDecal = new olc::Decal(new olc::Sprite("fireBall.png"));
        fireBall2 = std::make_shared<olc::Sprite>("test2.png");
        test2 = std::make_shared<olc::Decal> (fireBall2.get());

    }
    ~Projectile()
    {
//        delete myBalls;
        delete m_pDecal;
    }
    void drawSelf(olc::PixelGameEngine* pge, double offsetx, double offsety)
    {

//        pge->FillCircle(_position - olc::vd2d{offsetx, offsety}, _radius, olc::MAGENTA);
//        pge->DrawSprite(_position - olc::vd2d{offsetx, offsety}, fireBall.get());
//        pge->DrawSprite(_position - olc::vd2d{offsetx, offsety}, myBalls);
//        pge->DrawDecal(_position - olc::vd2d{offsetx, offsety}, ballPtr.get());
//        pge.Clear(olc::BLACK);
//        pge.DrawDecal(_position , m_pDecal , {.1, .1});
//        pge.DrawDecal(olc::vi2d{0, 0}, m_pDecal , {.1, .1});
//        pge->DrawDecal(_position - olc::vd2d{offsetx, offsety}, test2.get(), {1.0f, 1.0f});
//        kurtAngle += .01;
        float myAngle = PI/2 + atan(_direction.y / _direction.x);
        if ( _direction.x < 0 ) {
            myAngle += PI;
        }
        pge->DrawRotatedDecal(_position - olc::vd2d{offsetx, offsety}, test2.get(), myAngle);
//        pge->DrawSprite(_position - olc::vd2d{offsetx, offsety}, fireBall2.get());

//        pge.DrawDecal(_position - olc::vd2d{offsetx, offsety}, m_pDecal);
        /////////////////////////////
        // Prototype for Scale function
//        double sx = .05f, sy = .05f;
//        std::vector<std::vector<double>> matrixScale{ { sx, 0, 0} , {0, sy, 0}, {0, 0, 1}};
//
//        for (int x = 0 ; x < fireBall->width ; ++x) {
//            for (int y = 0 ; y < fireBall->height ; ++y) {
//                olc::Pixel p = fireBall->GetPixel(x, y);
//
//                double nx, ny;
//                nx = x * matrixScale[0][0] + y * matrixScale[0][1] + 1 * matrixScale[0][2] ;
//                ny = x * matrixScale[1][0] + y * matrixScale[1][1] + 1 * matrixScale[1][2];
//
//                pge->Draw(nx + _position.x - offsetx  , ny + _position.y - offsety  , p);
//            }
//        }
        // End prototype for scale function
        /////////////////////////////

    }
  //update the projectile, move it etc.
  virtual void update() override {
      // Updating position of projectile
      _position += _direction * _speed; //need offset if map moves around.

  }

//    void scale(float &nx, float &ny, float x, float y,) {
//        // To get scale we need the
//        std::vector<std::vector<float>> matrixScale{{sx, 0,  0},
//                                                    {0,  sy, 0},
//                                                    {0,  0,  1}};
//
//    }
};
std::unique_ptr<Projectile> projectileFactory ( olc::vd2d sPos , olc::vd2d fPos);

std::unique_ptr<Projectile> projectileFactory ( olc::vd2d sPos , olc::vd2d fPos) // fP only gives directions
{
//    auto myBall = std::make_unique<Projectile>(sPos, fPos);
//    //std::unique_ptr <Projectile> myProjectile std::make_unique<Projectile> {sPos, fPos};
//    return myBall;
    return std::make_unique<Projectile>(sPos, fPos);
}

std::vector <std::unique_ptr<Projectile>> getMyBalls (olc::vd2d sPos, int numberOfBalls) {
    int &n = numberOfBalls;
    std::vector <std::unique_ptr<Projectile>> myBalls ;
    // Generate balls in a circle ?
    //
    double angleRad = 0 ;
    for ( int i = 0 ; i < n ; ++i ) {
        angleRad = 2.0 * PI * (static_cast<double> (i) /n) ;
        auto direction = olc::vd2d{cos (angleRad), sin (angleRad)};
        myBalls.push_back(projectileFactory( sPos, sPos + direction ));
    }
    return myBalls;
}


class HomingProjectile : public Projectile {
    Entity &notPointerToEntity ;
    HomingProjectile( olc::vd2d sPos, Entity &ent ):
    Projectile(sPos, olc::vi2d{ent.getXPos(), ent.getYPos()}),
    notPointerToEntity(ent) { }

    virtual void update() override
    {
        // Get Final position from the object
        // adjust direction to object
        // adjust position
        _endPosition = olc::vi2d{notPointerToEntity.getXPos(), notPointerToEntity.getYPos()};
        auto displacement = _endPosition - _position;
        _distance = displacement.mag();
        _direction = displacement / _distance;

        _position =
    }

};
#endif
