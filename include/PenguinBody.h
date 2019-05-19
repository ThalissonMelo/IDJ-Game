#ifndef PENGUINBODY_H_
#define PENGUINBODY_H_

#include "Component.h"

class PenguinBody : public Component{
  public:
    PenguinBody (GameObject& associated);
    ~PenguinBody ();
    
    void Start();
    void Render ();
    bool Is (string type);
    void Update (float dt);
    Vec2 GetPlayerCenter();
    static PenguinBody* player;
    void PenguinBodyDamage(int damage);
    void NotifyCollision(GameObject& other);
  private:
    int hp;
    Vec2 speed;
    float angle;
    float linearSpeed;
    weak_ptr< GameObject > pcannon;
};

#endif