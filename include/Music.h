#ifndef MUSIC
#define MUSIC

#include "../include/SDL_include.h"
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class Music{
  public:
    Music();
    Music(string file);
    ~Music();
    void play(int times = -1);
    void stop(int msToStop = 1500);
    void open(string file);
    bool isOpen();
  private:
    Mix_Music* music;
};

#endif