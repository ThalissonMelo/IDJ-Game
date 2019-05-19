#include "Sprite.h"
#include "Game.h"
#include "Resources.h"


Sprite::Sprite(GameObject& associated) : Component(associated){
  texture = nullptr;
  this->width = 0;
	this->height = 0;
  this->scale = Vec2(1, 1);
}

Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime, bool repeat, float secondsToSelfDestruct) : Sprite(associated){
  this->timeElapsed = 0;
  this->frameCount = frameCount;
  this->frameTime = frameTime;
  this->currentFrame = 0;
  this->repeats = repeat;
  this->secondsToSelfDestruct = secondsToSelfDestruct;

  this->selfDestructCount = Timer();

  open(file);
}

Sprite::~Sprite(){
  texture = nullptr;
}

void Sprite::open(string file){

  this->texture = Resources::GetImage(file);
	
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  this->setClip(0, 0, round(width/this->frameCount), height);
  this->associated.box.w = this->getWidth();
	this->associated.box.h = this->getHeight();
}

void Sprite::setClip(int x, int y, int w, int h){
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.w = w;
  this->clipRect.h = h;
}

int Sprite::getWidth(){
  return round((this->width/this->frameCount)*this->scale.x);
}

int Sprite::getHeight(){
  return round(this->height*this->scale.y);
}

bool Sprite::isOpen(){
  if(texture)
    return true;

  return false;
}

void Sprite::Update(float dt) {
  this->timeElapsed += dt;

  if(this->secondsToSelfDestruct > 0) {
		this->selfDestructCount.Update(dt);
		if(this->selfDestructCount.Get() > this->secondsToSelfDestruct)
			this->associated.RequestDelete();
	}

  if(this->timeElapsed > this->frameTime){
    this->timeElapsed -= this->frameTime;
    if(this->currentFrame < this->frameCount-1){
      this->currentFrame++;
    }
    else if(this->repeats)
      this->currentFrame = 0;

    this->setClip(this->currentFrame*(this->width/this->frameCount), 0, (this->width/this->frameCount), this->height);
  }
}

void Sprite::Render(int x, int y){

  Game& gameInstance = Game::getInstance();

  SDL_Rect dst = {x, y, clipRect.w*this->scale.x, clipRect.h*this->scale.y};

  SDL_RenderCopyEx(Game::getInstance().getRenderer(),
                texture,
                &clipRect,
                &dst,
                (int) this->associated.rotation,
                nullptr,
                SDL_FLIP_NONE
                );
}

void Sprite::Render() {
  Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

bool Sprite::Is(string type) {
	return (type == "Sprite");
}

void Sprite::Start(){

}

void Sprite::SetScaleX(float scaleX, float scaleY) {
	this->scale = Vec2(scaleX, scaleY);
	this->associated.box.w = getWidth()*this->scale.x;
	this->associated.box.h = getHeight()*this->scale.y;
}

Vec2 Sprite::GetScale() {
	return this->scale;
}

void Sprite::SetFrame(int frame){

  this->currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCount){
//   recomendamos resetar o frame inicial para 0
// e recalcular a box do GameObject associated, visto que a largura será alterada
// (não se esqueça de considerar a escala).
  this->frameCount = frameCount;
  this->currentFrame = 0;
  this->setClip(this->currentFrame*(this->width/this->frameCount), 0, (this->width/this->frameCount), this->height);
}
void Sprite::SetFrameTime(float frameTime){
  this->frameTime = frameTime;
}