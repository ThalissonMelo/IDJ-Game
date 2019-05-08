#include "Bullet.h"
#include "Sprite.h"

#define PI 3.141592653589793


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component(associated) {
  this->speed = Vec2(speed*cos(angle * (PI/180.0)), speed*sin(angle * (PI/180.0)));
	this->damage = damage;
	this->distanceLeft = maxDistance;
	this->associated.rotation = angle;

	this->associated.AddComponent(new Sprite(associated, sprite));
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