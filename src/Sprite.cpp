#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated){
  texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Sprite(associated){
  // texture = nullptr;
  open(file);
}

Sprite::~Sprite(){
  if(texture)
    SDL_DestroyTexture(texture);
}

void Sprite::open(string file){

  Game& gameInstance = Game::getInstance();

  if(texture != nullptr)
    SDL_DestroyTexture(texture);

  texture = IMG_LoadTexture(gameInstance.getRenderer(), file.c_str());

  if(texture == nullptr){
    cout << "Texture was loaded: " << SDL_GetError() << endl;
  }
  else
  {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  }

  setClip(0, 0, width, height);
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

  SDL_Rect dst = {x, y, getWidth(), getHeight()};

  SDL_RenderCopy(gameInstance.getRenderer(),
                 texture,
                 &clipRect,
                 &dst);
}

void Sprite::Render() {

  Game& gameInstance = Game::getInstance();

  Render(associated.box.x, associated.box.y);
}

bool Sprite::Is(std::string type) {
	return (type == "Sprite");
}