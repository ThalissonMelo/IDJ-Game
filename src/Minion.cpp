#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "math.h"
#include "Bullet.h"
#include "MathHelper.h"
#include "Collider.h"

#define PI 3.141592653589793

Minion::Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg) : Component(associated){
  this->alienCenter = (Game::getInstance().getState().GetObjectPtr(&alienCenter));
  this->arc = arcOffsetDeg;
  
  Sprite *minion = new Sprite(this->associated, "assets/img/minion.png");
	float scale = 1 + (float)(rand()%501)/1000;
	minion->SetScaleX(scale, scale);

  this->associated.AddComponent(minion);
  this->associated.AddComponent(new Collider(associated));
}
void Minion::Update (float dt){

  if(this->alienCenter.expired()) {
		associated.RequestDelete();
	} 
  else {
		this->arc += 60*dt;
		this->associated.rotation = this->arc-90;
    
    Rect alienRect = this->alienCenter.lock()->box;
    
    float cosA= MathHelper::Cos(this->arc);

    float rotateCos = (200*cosA);

    float widthBox = (this->associated.box.w/2);

    float finalRotatePositionX = rotateCos - widthBox;
		
    this->associated.box.x =  alienRect.GetCenter().x+(finalRotatePositionX);

    float sinA = MathHelper::Sin(this->arc);
		
    float rotateSin = (200.0*sinA);

    float heigthBox = (this->associated.box.h/2.0);

    float finalRotatePositionY = rotateSin - heigthBox;

    this->associated.box.y = alienRect.GetCenter().y+finalRotatePositionY;
	}
}
void Minion::Render (){
  
}
bool Minion::Is (string type){
  return(type == "Minion");
}
void Minion::Shoot (Vec2 target){
  float maxDistance = this->associated.box.GetCenter().GetHypot(target);

	float angle = this->associated.box.GetCenter().GetAngle(target);

  GameObject* go = new GameObject();

  go->AddComponent(new Bullet(*go, angle, 500, 5, maxDistance, "assets/img/minionbullet2.png", true, 3, true));

  go->box.SetPosition(this->associated.box.GetCenter()-Vec2(go->box.w/2, go->box.h/2));

  Game::getInstance().getState().AddObject(go);
}

void Minion::NotifyCollision(GameObject& other){

}