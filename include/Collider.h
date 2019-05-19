#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "Component.h"

class Collider : public Component {
  
  public:
    Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    void Render();
    bool Is(string type);
    void Update(float dt);
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    
    Rect box;

  private:
    Vec2 scale;
    Vec2 offset;
};

#endif