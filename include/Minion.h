#ifndef MINION_H_
#define MINION_H_
#include "GameObject.h"
#include "Component.h"

using namespace std;

class Minion : public Component{
  public:
    Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg = 0);
    
    void Render ();
    bool Is (string type);
    void Update (float dt);
    void Shoot (Vec2 target);
    void NotifyCollision(GameObject& other);
  
  private:
    weak_ptr<GameObject> alienCenter;
    float arc;
};

#endif