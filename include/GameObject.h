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
    void Start();
    void Render(); 
    bool IsDead(); 
    void Update(float dt);
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);
    
    Rect box;
    bool started;
    float rotation;
  
  private:
    vector<shared_ptr<Component>> components;
    bool isDead;
};

#endif