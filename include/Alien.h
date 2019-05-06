#ifndef ALIEN_H_
#define ALIEN_H_

#include<iostream>
#include "GameObject.h"
#include "Component.h"

using namespace std;

class Alien : public Component {

  public:
    Alien (GameObject& associated, int nMinions);
    ~Alien ();
    void Start();
    void Update (float dt);
    void Render ();
    bool Is (string type);

  private:
    class Action {
      public:
        enum ActionType {MOVE, SHOOT};
        ActionType type;
        Vec2 pos;
        
        Action(ActionType type, float x, float y);
    };

    Vec2 speed;
    int hp;
    int nMinions;

    queue<Action> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;
};

#endif