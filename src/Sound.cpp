#include "Sound.h"

Sound::Sound(GameObject& associated) : Component(associated){
  chunk = nullptr;
  channel = -1;
}

Sound::Sound(GameObject& associated, string file) : Sound(associated){
  Open(file);
}

Sound::~Sound(){
 
  if(IsOpen() and not IsPlaying()){
    Stop();
    Mix_FreeChunk(chunk);
    chunk = nullptr;
  }
  
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(channel, chunk, times - (times > 0 ? 1 : 0));
	if(channel == -1) {
		printf("Mix_PlayChannel failed: %s\n", SDL_GetError());
		exit(-1);
	}
}

void Sound::Stop(){
  if(chunk != nullptr)
    Mix_HaltChannel(channel);
  channel = -1;
}

bool Sound::IsPlaying() {
	return (Mix_Playing(channel));
}

void Sound::Open(string file) {
	chunk = Mix_LoadWAV(file.c_str());
	if(!IsOpen()) {
		printf("Mix_LoadWAV failed: %s\n", SDL_GetError());
		exit(-1);
	}
}

bool Sound::IsOpen(){
  if(!chunk)
    return false;
  return true;
}

void Sound::Update(float dt){
}

void Sound::Render(){
}

bool Sound::Is(string type){
  return(type == "Sound");
}

void Sound::Start(){

}