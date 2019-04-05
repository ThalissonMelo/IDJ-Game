#include "Sound.h"

Sound::Sound(GameObject& associated) : Component(associated){
  chunk = nullptr;
  channel = -1;
}

Sound::Sound(GameObject& associated, string file) : Sound(associated){
  Open(file);
}

Sound::~Sound(){
  Stop();
  
  if(IsOpen() and not IsPlaying()){
    Mix_FreeChunk(chunk);
  //  Mix_HaltChannel(channel);
  }
  
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(channel, chunk, times-1);
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

void Sound::Open(std::string file) {
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
