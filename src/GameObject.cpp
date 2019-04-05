#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
  isDead = false;
}

GameObject::~GameObject(){
  for(auto t=ceil((double)components.size()/2); t!=0; t--)
  {
    if(components.size() % 2 != 0 && t == 1){
      components.erase(components.begin());
      break;
    }
    components.erase((components.begin() + t), (components.end() - t));
  }
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
  for(auto it = components.size()-1; it >= 0; it--)
  		if(components[it] == cpt)
  			components.erase(components.begin()+it);
}

Component* GameObject::GetComponent(string type){
  
  for (auto it = 0; it < components.size(); it++)
    if (components[it]->Is(type))
      return components[it];
  
  return nullptr;
}