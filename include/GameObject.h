#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"

#include <bits/stdc++.h>

#include <vector>
#include <memory>

using namespace std;

class Component;

class GameObject{
  public:
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render(); 
    bool IsDead(); 
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);
    Rect box;
  private:
    // std::vector<std::unique_ptr<Component>> components;
     std::vector<Component *> components;
    bool isDead;   
};

#endif