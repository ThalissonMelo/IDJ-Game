#include "Alien.h"
#include "Component.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"

#define EPS 1e-9

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
  this->speed = Vec2(0,0);
  this->hp = 10;
  this->taskQueue = queue<Action>();
  this->minionArray = vector<std::weak_ptr<GameObject>>();
  this->nMinions = nMinions;
  
  associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
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
		this->minionArray.push_back(Game::getInstance().getState().AddObject(go));
	}
}

bool equals(double a, double b){
  return fabs(a - b) < EPS;
}

void Alien::Update(float dt){

  this->associated.rotation -=60*dt;

  if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
    float xAxis = (float)InputManager::GetInstance().GetMouseX();
    float yAxis = (float)InputManager::GetInstance().GetMouseY();
    this->taskQueue.push(Action(Action::SHOOT, xAxis, yAxis));
  }
  if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)){
    float xAxis = (float)InputManager::GetInstance().GetMouseX() - associated.box.w/2;
    float yAxis = (float)InputManager::GetInstance().GetMouseY() - associated.box.h/2;
    
    this->taskQueue.push(Action(Action::MOVE, xAxis, yAxis));
  }

  if(this->taskQueue.size() > 0){
    Vec2 targetClick = taskQueue.front().pos;
    if(this->taskQueue.front().type == Action::MOVE){
      
      Vec2 alienPosition = Vec2(associated.box.x, associated.box.y);

      float cos = alienPosition.GetCos(targetClick);
      float sin = alienPosition.GetSin(targetClick);
      
      this->speed = Vec2(500*cos, 500*sin);

      if((associated.box.x+speed.x*dt > targetClick.x && targetClick.x > associated.box.x)
      || (associated.box.x+speed.x*dt < targetClick.x && targetClick.x < associated.box.x))
				associated.box.x = targetClick.x;
			else
				associated.box.x += speed.x*dt;
			
      if((associated.box.y+speed.y*dt > targetClick.y && targetClick.y > associated.box.y)
      || (associated.box.y+speed.y*dt < targetClick.y && targetClick.y < associated.box.y))
				associated.box.y = targetClick.y;
			else
				associated.box.y += speed.y*dt;
      if(associated.box.x == targetClick.x && associated.box.y == targetClick.y)
        this->taskQueue.pop();
    }
    else if(this->taskQueue.front().type == Action::SHOOT){
      int nearestMinion = 0;
			float minionDistance = this->minionArray[0].lock()->box.GetCenter().GetHypot(targetClick);
			for(unsigned i = 0; i < this->minionArray.size(); i++) {
				if(this->minionArray[i].lock()->box.GetCenter().GetHypot(targetClick) < minionDistance) {
					nearestMinion = i;
					minionDistance = this->minionArray[i].lock()->box.GetCenter().GetHypot(targetClick);
				}
			}
			Minion* minion = (Minion*) this->minionArray[nearestMinion].lock()->GetComponent("Minion");
			minion->Shoot(targetClick);
      taskQueue.pop();
    }

    if(this->hp < 1)
      this->associated.RequestDelete();
  }
}

bool Alien::Is(string type){
  return(type == "Alien");
}

void Alien::Render(){

}