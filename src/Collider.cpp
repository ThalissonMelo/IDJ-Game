#include "Collider.h"
#include "Camera.h"
#include "Game.h"


Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated){
  this->scale = scale;
  this->offset = offset;
}

void Collider::Render(){
  // Vec2 center(box.GetCenter());
	// SDL_Point points[5];

	// Vec2 point;
	// point = (Vec2(box.x, box.y)-center).Rotate(associated.rotation)+center-Camera::pos;
	// points[0] = {(int)point.x, (int)point.y};
	// points[4] = {(int)point.x, (int)point.y};
	
	// point = (Vec2(box.x+box.w, box.y)-center).Rotate(associated.rotation)+center-Camera::pos;
	// points[1] = {(int)point.x, (int)point.y};
	
	// point = (Vec2(box.x+box.w, box.y+box.h)-center).Rotate(associated.rotation)+center-Camera::pos;
	// points[2] = {(int)point.x, (int)point.y};
	
	// point = (Vec2(box.x, box.y+box.h)-center).Rotate(associated.rotation)+center-Camera::pos;
	// points[3] = {(int)point.x, (int)point.y};

	// SDL_SetRenderDrawColor(Game::getInstance().getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	// SDL_RenderDrawLines(Game::getInstance().getRenderer(), points, 5);
}

bool Collider::Is(string type){
  return(type == "Collider");
}

void Collider::Update(float dt){

  this->box = this->associated.box;
  this->box.SetWidHeig((this->associated.box.GetWidHeig() * this->scale));
  this->box.SetCenter((this->associated.box.GetCenter() + this->offset));
  this->box.GetCenter().Rotate(this->associated.rotation);
}

void Collider::SetScale(Vec2 scale){
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset){
  this->offset = offset;
}
