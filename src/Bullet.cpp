#include "Bullet.h"
#include "Sprite.h"

#define PI 3.141592653589793


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component(associated) {
  this->speed = Vec2(speed*cos(angle * PI/180), speed*sin(angle * PI/180));
	this->damage = damage;
	this->distanceLeft = maxDistance;
	// this->associated.rotation = angle;

	associated.AddComponent(new Sprite(associated, sprite));
  // Inicialize Component. Depois crie e adicione a sprite. Daí, como Bullet
  // tem a velocidade constante, calcule o vetor velocidade, pois este será usado
  // em todo frame durante a vida do objeto. Lembre-se também de setar a
  // distância remanescente de acordo com o parâmetro dado.
}
void Bullet::Update(float dt) {
  if(this->distanceLeft <= 0) {
		this->associated.RequestDelete();
	}
  else {
    this->associated.box.x += this->speed.x*dt;
		this->associated.box.y += this->speed.y*dt;
		this->distanceLeft -= Vec2().GetHypot(Vec2(speed.x*dt, speed.y*dt));
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