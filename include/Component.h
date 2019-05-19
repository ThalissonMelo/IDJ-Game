#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <bits/stdc++.h>

#include "GameObject.h"

using namespace std;

class Component{
  public:
    Component(GameObject& associated);
    virtual ~Component();
    virtual void Start();
    virtual void Render() = 0;
    virtual bool Is(string type) = 0;
    virtual void Update(float dt) = 0;
    virtual void NotifyCollision(GameObject& other);

  protected:
    GameObject& associated;

};

#endif