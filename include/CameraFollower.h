#ifndef CAMERAFOLLOW_H_
#define CAMERAFOLLOW_H_

#include "GameObject.h"
#include "Component.h"
#include<iostream>

using namespace std; 

class CameraFollower : public Component {
  public:
    CameraFollower (GameObject& go);
    void Update (float dt);
    void Render();
    void Start();
    bool Is(string type);
};

#endif