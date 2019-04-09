#ifndef SPRITE_H_
#define SPRITE_H_

#pragma once
#include <SDL2/SDL.h>
#include "../include/SDL_include.h"
#include <bits/stdc++.h>
#include "Component.h"

using namespace std;

class Sprite : public Component{
  public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, string file);
    ~Sprite();
    void open(string file);
    void setClip(int x, int y, int w, int h);
    void render(int x, int y); 
    int getWidth(); 
    int getHeight();
    bool isOpen();
    void Update(float dt);
    void Render();
    void Render(int x, int y);
    bool Is(string type);
  private:
    SDL_Texture* texture; 
    int width;
    int height;
    SDL_Rect clipRect;
};

#endif
