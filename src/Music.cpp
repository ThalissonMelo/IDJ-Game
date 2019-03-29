#include "Music.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>


Music::Music(){
  music = nullptr;
}

Music::Music(string file){
  open(file);
}

Music::~Music() {
  stop(1500);
  Mix_FreeMusic(music);
}

void Music::play(int times){
  times = -1;
  if(Mix_PlayMusic(this->music, times) == -1){
    cout << "Music Error: " << Mix_GetError() << endl;
  }
}

void Music::stop(int msToStop){
  msToStop = 1500;
  Mix_FadeOutMusic(msToStop);
}

void Music::open(string file){
  music = Mix_LoadMUS(file.c_str());
  if(!music){
    cout << "Error to initialize music. Error: " << SDL_GetError() << endl;
  }
}

bool Music::isOpen(){
  if(music != nullptr)
    return true;

  return false;
}