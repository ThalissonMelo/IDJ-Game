#ifndef BULLET_H_
#define BULLET_H_
#include "Vec2.h"
#include "GameObject.h"
#include "Component.h"

using namespace std;

class Bullet : public Component{
  public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, bool repeat, int frameCount, bool targetsPlayer);
    void Render();
    int GetDamage();
    bool Is(string type);
    void Update(float dt);
    void NotifyCollision(GameObject& other);

    bool targetsPlayer;
  private:
    int damage;
    Vec2 speed;
    float distanceLeft;
};

#endif