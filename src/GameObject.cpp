#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
  this->isDead = false;
  this->started = false;
}

GameObject::~GameObject(){
  this->components.clear();
}

void GameObject::Update(float dt){
  for(auto& component: this->components)
		component->Update(dt);
}

void GameObject::Render(){
  for(auto& component: this->components)
		component->Render();
}

void GameObject::Start(){
	for(auto& component : this->components)
		component->Start();

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