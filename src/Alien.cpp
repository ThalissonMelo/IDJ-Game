#include "Alien.h"
#include "Component.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"

#define EPS 1e-9

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
  speed = Vec2(0,0);
  hp = 0;
  associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
  this->nMinions = nMinions;
  
  // Mover a adição dos componentes de dependência (e de
  // GameObjects também, como veremos abaixo) para o construtor reduz o
  // tamanho e simplifica o construtor do state mas possui, na nossa engine, uma
  // desvantagem. Consegue descobrir qual é?
}

Alien::~Alien(){
  this->minionArray.clear();
}

Alien::Action::Action(ActionType type, float x, float y) {
	this->type = type;
	this->pos = Vec2(x, y);
}

void Alien::Start(){
  for(int i = 0; i < this->nMinions; i++) {
		GameObject* go = new GameObject();
		go->AddComponent(new Minion(*go, associated, i*(360/this->nMinions)));
		minionArray.push_back(Game::getInstance().getState().AddObject(go));
	}
  // Popule o vetor de Minions do Alien em Alien::Start (chame
  // State::AddObject com o go criado e o retorno dessa função coloque em
  // minionArray) e observe o movimento. Tente mover pelo cenário e veja se eles
  // acompanham o Alien corretamente.
  // Devemos popular o array de Minions com alguns destes objetos,
  // espaçados igualmente. Enquanto não tiver certeza que o Alien funciona como
  // desejado, não faça nada aqui.
}

bool equals(double a, double b){
  return fabs(a - b) < EPS;
}

void Alien::Update(float dt){

  if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
    float xAxis = (float)InputManager::GetInstance().GetMouseX();
    float yAxis = (float)InputManager::GetInstance().GetMouseY();
    this->taskQueue.push(Action(Action::SHOOT, xAxis, yAxis));
  }
  if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)){
    //Movimentação
    float xAxis = (float)InputManager::GetInstance().GetMouseX() - associated.box.w/2;
    float yAxis = (float)InputManager::GetInstance().GetMouseY() - associated.box.h/2;
    
    this->taskQueue.push(Action(Action::MOVE, xAxis, yAxis));
  }

  if(this->taskQueue.size()){
    // this->taskQueue.front().type == Action::ActionType
    Vec2 newPosition = taskQueue.front().pos;
    if(taskQueue.front().type == Action::MOVE){
      
      Vec2 mousePosVec = Vec2(associated.box.x, associated.box.y);

      float cos = mousePosVec.GetCos(newPosition);
      float sin = mousePosVec.GetSin(newPosition);
      
      this->speed = Vec2(500*cos, 500*sin);

      // Revisar essa parte

      if((associated.box.x+speed.x*dt > newPosition.x && newPosition.x > associated.box.x)
      || (associated.box.x+speed.x*dt < newPosition.x && newPosition.x < associated.box.x))
				associated.box.x = newPosition.x;
			else
				associated.box.x += speed.x*dt;
			
      if((associated.box.y+speed.y*dt > newPosition.y && newPosition.y > associated.box.y)
      || (associated.box.y+speed.y*dt < newPosition.y && newPosition.y < associated.box.y))
				associated.box.y = newPosition.y;
			else
				associated.box.y += speed.y*dt;

      // Até aqui

      if(equals(associated.box.x, newPosition.x)
      && equals(associated.box.y, newPosition.y))
        this->taskQueue.pop();
    }
    else if(this->taskQueue.front().type == Action::SHOOT){
      int nearestMinion = 0;
			float minionDS = this->minionArray[0].lock()->box.GetCenter().GetHypot(newPosition);
			for(unsigned i = 1; i < this->minionArray.size(); i++) {
				if(this->minionArray[i].lock()->box.GetCenter().GetHypot(newPosition) < minionDS) {
					nearestMinion = i;
					minionDS = this->minionArray[i].lock()->box.GetCenter().GetHypot(newPosition);
				}
			}
			Minion* minion = (Minion*) this->minionArray[nearestMinion].lock()->GetComponent("Minion");
			minion->Shoot(newPosition);
			taskQueue.pop();
    }
  }
}

bool Alien::Is(string type){
  return(type == "Alien");
}

void Alien::Render(){

}