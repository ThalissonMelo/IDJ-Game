#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(){
  texture = nullptr;
}

Sprite::Sprite(string file){
  texture = nullptr;
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

void Sprite::render(int x, int y){
  
  Game& gameInstance = Game::getInstance();

  SDL_Rect dst = {x, y, getWidth(), getHeight()};

  SDL_RenderCopy(gameInstance.getRenderer(),
                 texture,
                 &clipRect,
                 &dst);

}

int Sprite::getWidth(){
  return width;
} 

int Sprite::getHeight(){
  return height;
}

bool Sprite::isOpen(){
  texture ? true : false;
}