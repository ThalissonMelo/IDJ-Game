#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
  this->isDead = false;
  this->started = false;
  this->box = Rect();
}

GameObject::~GameObject(){
  this->components.clear();
}

void GameObject::Update(float dt){
  // for(auto& component: this->components)
	// 	component->Update(dt);
  for(unsigned i = 0; i < this->components.size(); i++)
    components[i]->Update(dt);
}

void GameObject::Render(){
  // for(auto& component: this->components)
	// 	component->Render();
  for(unsigned i = 0; i < this->components.size(); i++)
    components[i]->Render();
}

void GameObject::Start(){
	// for(auto& component : this->components)
	// 	component->Start();
  for(unsigned i = 0; i < this->components.size(); i++)
    components[i]->Start();

	this->started = true;
}

bool GameObject::IsDead(){
  return this->isDead;
}

void GameObject::RequestDelete(){
  this->isDead = true;
}

void GameObject::AddComponent(Component* cpt){
  this->components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt){
  for(auto it = this->components.size()-1; it > 1; it--)
  		if(this->components[it].get() == cpt)
  			this->components.erase(this->components.begin()+it);
}

Component* GameObject::GetComponent(string type){
  
  for (unsigned it = 0; it < this->components.size(); it++)
    if (this->components[it]->Is(type))
      return this->components[it].get();
  
  return nullptr;
}

void GameObject::NotifyCollision(GameObject& other){
  for(int i = 0; i < other.components.size(); i++)
    this->components[i]->NotifyCollision(other);
}