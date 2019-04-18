#include "Sound.h"
#include "InputManager.h"
#include "Face.h"

Face::Face(GameObject& associated) : Component(associated){
  this->hitpoints = 30;
}
Face::~Face(){

}
void Face::Damage(int damage){
  this->hitpoints -= damage;

	if(this->hitpoints <= 0){
		this->associated.RequestDelete();

    Sound *sound = (Sound *) this->associated.GetComponent("Sound");
    if(sound != nullptr)
      sound->Play(1);
  }
}
void Face::Update(float dt){
  if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
    if(associated.box.Contains(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())){
      Face* face = (Face*) associated.GetComponent("Face");
      if(face) {
        if(face->hitpoints > 0){
          face->Damage(10+std::rand()%10);
        }
      }
    }
 	}
}
void Face::Render(){

}
bool Face::Is(string type){
  return (type == "Face");
}