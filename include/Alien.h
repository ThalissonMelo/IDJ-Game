#ifndef ALIEN_H_
#define ALIEN_H_

#include<iostream>
#include "GameObject.h"
#include "Component.h"
#include "Timer.h"

using namespace std;

class Alien : public Component {

  public:
    Alien (GameObject& associated, int nMinions);
    ~Alien ();
    
    void Start();
    void Render ();
    bool Is (string type);
    void Update (float dt);
    void AlienDamage(int damage);
    void NotifyCollision(GameObject& other);

    int alienCount;
    float cooldown;
  private:
    int hp;
    Vec2 speed;
    int nMinions;
    enum AlienState { MOVING, RESTING };
    AlienState state;
    Timer restTimer;
    Vec2 destination;
    vector<weak_ptr<GameObject>> minionArray;
};

#endif