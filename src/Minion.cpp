#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "math.h"
#include "Bullet.h"

#define PI 3.141592653589793

Minion::Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg) : Component(associated){
  this->alienCenter = (Game::getInstance().getState().GetObjectPtr(&alienCenter));//.lock();
  this->associated.AddComponent(new Sprite(this->associated, "assets/img/minion.png"));
  // Os argumentos do construtor (além do obrigatório por ser componente)
  this->arc = arcOffsetDeg;
  // são o objeto que devemos orbitar e o ângulo inicial em graus. Adicionamos o
  // componente Sprite (igual fizemos para Alien) e calculamos o primeiro valor da
  // box (explicamos como a seguir).
}
void Minion::Update (float dt){

  if(alienCenter.expired()) {
		associated.RequestDelete();
	}else{
		this->arc += 60*dt;
		// this->associated.rotation = arc-90;
		this->associated.box.x = alienCenter.lock()->box.GetCenter().x+(200*cos(arc * PI/180))-(associated.box.w/2);
		this->associated.box.y = alienCenter.lock()->box.GetCenter().y+(200*sin(arc * PI/180))-(associated.box.h/2);
	}

  // Como Minion anda em círculo, não em linha reta, não usamos uma
  // velocidade com coordenadas x e y. Em vez disso, usamos uma velocidade 
  // angular (radianos/segundo), e incrementamos o arco a cada frame. Defina
  // uma constante para isso, de preferência, uma fração de pi.
  // Calcular a posição do Minion é uma tarefa bem mais fácil do que parece.
  // Começamos assumindo que o Minion ficará na origem do mapa. Crie um vetor
  // que represente a distância da origem que o Minion começará caso seu offset
  // inicial seja zero (por exemplo {x = 200, y = 0}). Depois, o rotacionamos pelo
  // seu arco atual (arc). Por último, somamos com a posição atual do centro de
  // sua rotação, ou seja, o centro do box de alienCenter. Essa é a posição que o
  // centro do Minion deve assumir.
  // Visto que alienCenter é um std::weak_ptr, devemos dar lock() nele
  // para obtermos um shared_ptr que podemos usar para usarmos sua box. Se o
  // que retornou for um shared_ptr for vazio, nosso centro não existe mais, então
  // devemos pedir a deleção e encerrar o Update agora mesmo.
}
void Minion::Render (){
  
}
bool Minion::Is (string type){
  return(type == "Minion");
}
void Minion::Shoot (Vec2 target){
  float distance = this->associated.box.GetCenter().GetHypot(target);

	float angle = this->associated.box.GetCenter().GetAngle(target);
	
  GameObject* go = new GameObject();
	
  go->AddComponent(new Bullet(*go, distance, angle, 600, 5, "assets/img/minionbullet2.png"));
	
  go->box.SetPosition(this->associated.box.GetCenter()-Vec2(go->box.w/2, go->box.h/2));
	
  Game::getInstance().getState().AddObject(go);
  // Shoot recebe uma posição e dispara um projétil naquela direção
}