#ifndef PENGUINCANNON_H_
#define PENGUINCANNON_H_
#include "Component.h"
#include "GameObject.h"
#include "Timer.h"


class PenguinCannon : public Component{
  public:
    PenguinCannon(GameObject& associated, weak_ptr< GameObject > penguinBody);
    
    void Shoot();
    void Render();
    bool Is(string type);
    void Update(float dt);
    void NotifyCollision(GameObject& other);
  private:
    float angle;
    Timer cooldown;
    weak_ptr< GameObject > pbody;
};

#endif