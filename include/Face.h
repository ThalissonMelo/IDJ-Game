#ifndef FACE_H_
#define FACE_H_

#include <bits/stdc++.h>
#include "Component.h"

using namespace std;

class Face : public Component{
  public:
    Face(GameObject& associated);
    ~Face();
    void Damage(int damage); 
    void Update(float dt); 
    void Render();
    bool Is(string type); 
  private:
    int hitpoints;
};

#endif