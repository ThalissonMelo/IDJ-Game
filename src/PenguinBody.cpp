#include "PenguinBody.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "MathHelper.h"
#include "Collider.h"
#include "Bullet.h"

#define PI 3.141592653589793

PenguinBody *PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated){
  this->pcannon = weak_ptr< GameObject >();
  this->speed = Vec2(1,1);
  this->linearSpeed = 0;
  this->angle = 0;
  this->hp = 20;
  if(this->player)
    this->player->associated.RequestDelete();
  this->player = this;

  associated.AddComponent(new Sprite(associated, "assets/img/penguin.png"));
  this->associated.AddComponent(new Collider(associated));
}

PenguinBody::~PenguinBody(){
  this->player = nullptr;
}

void PenguinBody::Start(){
  GameObject *go = new GameObject();
  go->AddComponent(new PenguinCannon(*go, Game::getInstance().getState().GetObjectPtr(&this->associated)));
  this->pcannon = Game::getInstance().getState().AddObject(go);
}
void PenguinBody::Update (float dt){

  if(InputManager::GetInstance().IsKeyDown(W_KEY)){
    if(this->linearSpeed < 400)
      this->linearSpeed +=100;
  }

  if(InputManager::GetInstance().IsKeyDown(S_KEY))
    if(this->linearSpeed > -200)
      this->linearSpeed -=100;

  if(InputManager::GetInstance().IsKeyDown(A_KEY))
    this->angle -= 180*dt;
  
  if(InputManager::GetInstance().IsKeyDown(D_KEY))
    this->angle += 180*dt;

  this->speed.x = MathHelper::Cos(this->angle)*this->linearSpeed;
	this->speed.y = MathHelper::Sin(this->angle)*this->linearSpeed;
	this->associated.rotation = angle;
	this->associated.box.SetPosition(this->associated.box.GetPosition()+this->speed*dt);

  if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		PenguinCannon* cannon = (PenguinCannon*) this->pcannon.lock()->GetComponent("PenguinCannon");
		cannon->Shoot();
	}

  if(this->hp <= 0){
    this->player->associated.RequestDelete();
    
    // Verificar se funciona
    GameObject *penguinCannon = new GameObject;
    penguinCannon->GetComponent("PenguinCannon");
    penguinCannon->RequestDelete();
  }


  // Quando apertamos W ou S, os Penguins não se movem diretamente.
  // Em vez disso, aplicamos uma aceleração constante, que por sua vez implicará
  // num aumento ou diminuição da velocidade. Deve haver limites positivos e
  // negativos impostos para essa velocidade.
  // A direção para a qual o pinguim de baixo está apontado é alterada pelo
  // pressionamento das teclas A ou D, que aplicam uma velocidade angular
  // constante nos pinguins (a rotação não é acelerada). Sabendo essa direção, a
  // velocidade linear, e o dt, você pode calcular a posição.
  // Por último, solicite a deleção de si mesmo e do pinguim do canhão se
  // hp for menor ou igual a zero.
  // Obs.: É bem possível, usando rotação de vetores, não usar a variável
  // linearSpeed. Ela só serve para simplificar e muito o trabalho, especialmente
  // considerando que os pinguins podem andar de ré. Principalmente se quiser
  // implementar mecânicas como atrito.

}
void PenguinBody::Render (){

}
bool PenguinBody::Is (string type){
  return(type == "PenguinBody");
}

void PenguinBody::PenguinBodyDamage(int damage){
  this->hp -= damage;
	if(this->hp < 1) {
    Camera::Unfollow();
		associated.RequestDelete();
    
		GameObject* PenguinDeath = new GameObject();
		PenguinDeath->AddComponent(new Sprite(*PenguinDeath, "assets/img/penguindeath.png", 5, 0.15, false, 1.5));
		
    Sound* sound = new Sound(*PenguinDeath, "assets/audio/boom.wav");
    sound->Play();
		
    PenguinDeath->AddComponent(sound);
		
    PenguinDeath->box.SetCenter(associated.box.GetCenter());
		PenguinDeath->rotation = rand()%360;
		
    Game::getInstance().getState().AddObject(PenguinDeath);
	}
}

void PenguinBody::NotifyCollision(GameObject& other){
  Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
	
  if(bullet)
		if(bullet->targetsPlayer)
		  PenguinBodyDamage(bullet->GetDamage());
}

Vec2 PenguinBody::GetPlayerCenter() {
	return associated.box.GetCenter();
}