#pragma once
#include <SDL2/SDL.h>
#include "../include/SDL_include.h"
#include <bits/stdc++.h>

using namespace std;

class Sprite{
  public:
    Sprite();
    Sprite(string file);
    ~Sprite();
    void open(string file);
    void setClip(int x, int y, int w, int h);
    void render(int x, int y); 
    int getWidth(); 
    int getHeight();
    bool isOpen();
  private:
    SDL_Texture* texture; 
    int width;
    int height;
    SDL_Rect clipRect;
};