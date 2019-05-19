#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "Sprite.h"
#include "MathHelper.h"
#include "Collider.h"

#define PI 3.141592653589793

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr< GameObject > penguinBody) : Component(associated){
  this->pbody = penguinBody;    
  this->angle = 0;
  this->cooldown = Timer();

  this->associated.AddComponent(new Sprite(this->associated, "assets/img/cubngun.png"));
  this->associated.AddComponent(new Collider(associated));
}
void PenguinCannon::Update(float dt){
  if(this->pbody.expired())
    this->associated.RequestDelete();
  else
  {
    cooldown.Update(dt);
    Vec2 bodyCenter = this->pbody.lock()->box.GetCenter();
    this->associated.box.SetCenter(Vec2(this->pbody.lock()->box.GetCenter().x, this->pbody.lock()->box.GetCenter().y));
    this->angle = this->associated.box.GetCenter().GetAngle(InputManager::GetInstance().GetMousePosition());
    this->associated.rotation = this->angle;
  }

  
  // Antes, vamos verificar se o PenguinBody ainda existe. Porque, se ele foi
  // deletado, devemos deixar de existir também (assim como os minions em
  // relação ao Alien). Em seguinte, vamos fazer com que o centro da box dele
  // seja igual ao centro da box do corpo. Depois, temos que ajustar o canhão. O
  // canhão deve seguir a posição atual do mouse. Para saber o ângulo, use o
  // centro da box, que, como veremos em seguida, coincidirá com o eixo do
  // canhão, e forme uma reta. O canhão deve ter o mesmo ângulo dessa reta.
  // Não se esqueça de considerar a posição da câmera.
  // Finalmente, se o botão esquerdo do mouse for pressionado, devemos
  // atirar.

}
void PenguinCannon::Render(){

}
bool PenguinCannon::Is(string type){
  return(type == "PenguinCannon");
}

void PenguinCannon::Shoot(){
	if(this->cooldown.Get() > 0.5) {
    GameObject* go = new GameObject();

    Sprite* sprite = new Sprite(*go, "assets/img/penguinbullet.png", 4, 10, false);
    sprite->SetScaleX(1, 1);
    
    go->AddComponent(new Bullet(*go, this->angle, 500, 2, 1000, "assets/img/penguinbullet.png", false, 4, false));
    go->box.SetCenter(associated.box.GetCenter()+Vec2(MathHelper::Cos(angle)*associated.box.w/2, MathHelper::Sin(angle)*associated.box.w/2));
    
    Game::getInstance().getState().AddObject(go);
    this->cooldown.Restart();
  }
}

void PenguinCannon::NotifyCollision(GameObject& other){
  
}