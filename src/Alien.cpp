#include "Alien.h"
#include "Component.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sprite.h"
#include "PenguinBody.h"

#define EPS 1e-9

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
  this->speed = Vec2(0,0);
  this->hp = 10;
  this->minionArray = vector<std::weak_ptr<GameObject>>();
  this->nMinions = nMinions;

  this->state = RESTING;
  this->cooldown = 1 + (rand()%11)/10;
  
  this->associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
  this->associated.AddComponent(new Collider(associated));

  this->alienCount++;
}

Alien::~Alien(){
  this->minionArray.clear();
  this->minionArray = vector<std::weak_ptr<GameObject>>();

  alienCount--;
}

void Alien::Start(){
  for(int i = 0; i < this->nMinions; i++) {
		GameObject* go = new GameObject();
		go->AddComponent(new Minion(*go, associated, i*(360/this->nMinions)));
		this->minionArray.push_back(Game::getInstance().getState().AddObject(go));
	}
}

bool equals(double a, double b){
  return fabs(a - b) < EPS;
}

void Alien::Update(float dt){

  this->associated.rotation -= 60*dt;

  if(PenguinBody::player) {
    if(this->state == RESTING) {
	  		this->restTimer.Update(dt);
	  		if(this->restTimer.Get() > this->cooldown) {
	  			this->state = MOVING;
	  			this->restTimer.Restart();
	  			this->cooldown = 1 + (rand()%11)/10;
	  			this->destination = PenguinBody::player->GetPlayerCenter();
	  		}
	  	}

    if(this->state == MOVING){
      Vec2 position = this->associated.box.GetCenter();
	  	Vec2 dest = this->destination;

	  	float cos = position.GetCos(dest);
	  	if(cos != cos)
	  		cos = 0;
	  	float sin = position.GetSin(dest);
	  	if(sin != sin)
	  		sin = 0;
	  	speed = Vec2(500*cos, 500*sin);
	  	if((position.x+speed.x*dt > dest.x && dest.x > position.x) || (position.x+speed.x*dt < dest.x && dest.x < position.x))
	  		position.x = dest.x;
	  	else
	  		position.x += speed.x*dt;
	  	if((position.y+speed.y*dt > dest.y && dest.y > position.y) || (position.y+speed.y*dt < dest.y && dest.y < position.y))
	  		position.y = dest.y;
	  	else
	  		position.y += speed.y*dt;

      this->associated.box.SetCenter(position);
  
	  	if(equals(position.x, dest.x) && equals(position.y, dest.y)) {
	  		this->state = RESTING;
	  		this->destination = PenguinBody::player->GetPlayerCenter();
	  		int nearestMinion = 0;
	  		float minionDistance = minionArray[0].lock()->box.GetCenter().GetHypot(this->destination);
	  		for(unsigned i = 1; i < minionArray.size(); i++) {
	  			if(minionArray[i].lock()->box.GetCenter().GetHypot(this->destination) < minionDistance) {
	  				nearestMinion = i;
	  				minionDistance = minionArray[i].lock()->box.GetCenter().GetHypot(this->destination);
	  			}
	  		}
	  		Minion* m = (Minion*) minionArray[nearestMinion].lock()->GetComponent("Minion");
	  		m->Shoot(this->destination);
	  	}
    }
  }
}

bool Alien::Is(string type){
  return(type == "Alien");
}

void Alien::Render(){

}

void Alien::AlienDamage(int damage){
  this->hp -= damage;

  if(this->hp < 1){
    this->associated.RequestDelete();

    GameObject* alienDeath = new GameObject();

		alienDeath->AddComponent(new Sprite(*alienDeath, "assets/img/aliendeath.png", 4, 0.15, false, 1.5));
		
    Sound* sound = new Sound(*alienDeath, "assets/audio/boom.wav");
		sound->Play();
		alienDeath->AddComponent(sound);
		
    alienDeath->box.SetCenter(associated.box.GetCenter());
		alienDeath->rotation = rand()%360;
		
    Game::getInstance().getState().AddObject(alienDeath);
  }
}

void Alien::NotifyCollision(GameObject& other){
  Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
  if(bullet)
    if(!bullet->targetsPlayer)
      this->AlienDamage(bullet->GetDamage());
}