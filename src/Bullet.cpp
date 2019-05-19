#include "Bullet.h"
#include "Sprite.h"
#include "MathHelper.h"
#include "Collider.h"

#define PI 3.141592653589793


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, bool repeat, int frameCount, bool targetsPlayer) : Component(associated) {
  this->speed = Vec2(speed*MathHelper::Cos(angle), speed*MathHelper::Sin(angle));
	this->damage = damage;
	this->distanceLeft = maxDistance;
	this->associated.rotation = angle;
	this->targetsPlayer = targetsPlayer;

	this->associated.AddComponent(new Sprite(associated, sprite, frameCount, 0.15, repeat));
  this->associated.AddComponent(new Collider(associated));
}
void Bullet::Update(float dt) {
  if(this->distanceLeft > 0) {
    this->associated.box.x += this->speed.x*dt;
		this->associated.box.y += this->speed.y*dt;
		this->distanceLeft -= Vec2().GetHypot(Vec2(speed.x*dt, speed.y*dt));
	}
  else {
		this->associated.RequestDelete();
	}
}
void Bullet::Render(){

}
bool Bullet::Is(string type){
  return(type == "Bullet");
}
int Bullet::GetDamage(){
  return this->damage;
}

void Bullet::NotifyCollision(GameObject& other){
  if (this->targetsPlayer) {
    if (other.GetComponent("PenguinCannon") != nullptr || other.GetComponent("PenguinBody") != nullptr) {
      this->associated.RequestDelete();
    }
  }
	else {
    if (other.GetComponent("Alien") != nullptr) {
      this->associated.RequestDelete();
    }
  }
}