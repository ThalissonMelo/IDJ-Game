#include "Sprite.h"
#include "Game.h"
#include "Resources.h"


Sprite::Sprite(GameObject& associated) : Component(associated){
  texture = nullptr;
  this->width = 0;
	this->height = 0;
}

Sprite::Sprite(GameObject& associated, std::string file) : Sprite(associated){
  open(file);
}

Sprite::~Sprite(){
  texture = nullptr;
}

void Sprite::open(string file){

  this->texture = Resources::GetImage(file);
	
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	
  this->setClip(0, 0, width, height);
  this->associated.box.w = width;
	this->associated.box.h = height;
}

void Sprite::setClip(int x, int y, int w, int h){
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

int Sprite::getWidth(){
  return width;
}

int Sprite::getHeight(){
  return height;
}

bool Sprite::isOpen(){
  if(texture)
    return true;

  return false;
}

void Sprite::Update(float dt) {

}


void Sprite::Render(int x, int y){

  Game& gameInstance = Game::getInstance();

  SDL_Rect dst = {x, y, clipRect.w, clipRect.h};

  SDL_RenderCopy(Game::getInstance().getRenderer(),
                texture,
                &clipRect,
                &dst);
}

void Sprite::Render() {
  Render(associated.box.x, associated.box.y);
}

bool Sprite::Is(std::string type) {
	return (type == "Sprite");
}