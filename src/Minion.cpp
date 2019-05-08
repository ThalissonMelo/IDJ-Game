#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "math.h"
#include "Bullet.h"

#define PI 3.141592653589793

Minion::Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg) : Component(associated){
  this->alienCenter = (Game::getInstance().getState().GetObjectPtr(&alienCenter));
  this->arc = arcOffsetDeg;
  
  Sprite *minion = new Sprite(this->associated, "assets/img/minion.png");
	float scale = 1 + (float)(rand()%501)/1000;
	minion->SetScaleX(scale, scale);

  this->associated.AddComponent(minion);
}
void Minion::Update (float dt){

  if(this->alienCenter.expired()) {
		associated.RequestDelete();
	} else {
		this->arc += 60*dt;
		this->associated.rotation = this->arc-90;
		this->associated.box.x = this->alienCenter.lock()->box.GetCenter().x+(200*cos(this->arc * PI/180))-(this->associated.box.w/2);
		this->associated.box.y = this->alienCenter.lock()->box.GetCenter().y+(200*sin(this->arc * PI/180))-(this->associated.box.h/2);
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
	
  go->AddComponent(new Bullet(*go, angle, 600, 5, maxDistance, "assets/img/minionbullet1.png"));
	
  go->box.SetPosition(this->associated.box.GetCenter()-Vec2(go->box.w/2, go->box.h/2));
	
  Game::getInstance().getState().AddObject(go);
}