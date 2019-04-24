#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"
#include "Vec2.h"
#include "InputManager.h"

#include<iostream>

using namespace std;

class Camera{
  public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);
    static Vec2 pos;
    static Vec2 speed;
  private:
    static GameObject* focus;
};

#endif