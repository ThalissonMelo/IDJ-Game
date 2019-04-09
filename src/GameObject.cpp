#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
  isDead = false;
}

GameObject::~GameObject(){
  components.clear();
}

void GameObject::Update(float dt){
  for(auto& component: components)
		component->Update(dt);
}

void GameObject::Render(){
  for(auto& component: components)
		component->Render();
}

bool GameObject::IsDead(){
  return isDead;
}

void GameObject::RequestDelete(){
  isDead = true;
}

void GameObject::AddComponent(Component* cpt){
  components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt){
  for(auto it = components.size()-1; it > 1; it--)
  		if(components[it].get() == cpt)
  			components.erase(components.begin()+it);
}

Component* GameObject::GetComponent(string type){
  
  for (unsigned it = 0; it < components.size(); it++)
    if (components[it]->Is(type))
      return components[it].get();
  
  return nullptr;
}