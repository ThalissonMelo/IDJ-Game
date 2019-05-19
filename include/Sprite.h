#ifndef SPRITE_H_
#define SPRITE_H_

#pragma once
#include <SDL2/SDL.h>
#include "../include/SDL_include.h"
#include <bits/stdc++.h>
#include "Component.h"
#include "Timer.h"

using namespace std;

class Sprite : public Component{
  public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, string file, int frameCount = 1, float frameTime = 1, bool repeat = true, float secondsToSelfDestruct = 0);
    ~Sprite();
    
    void Start();
    bool isOpen();
    void Render();
    int getWidth(); 
    Vec2 GetScale();
    int getHeight();
    bool Is(string type);
    void Update(float dt);
    void open(string file);
    void render(int x, int y); 
    void Render(int x, int y);
    void SetFrame (int frame);
    void SetFrameCount (int frameCount);
    void SetFrameTime (float frameTime);
    void setClip(int x, int y, int w, int h);
    void SetScaleX(float scaleX, float scaleY);
    
    int frameCount;
    Timer selfDestructCount;
    float secondsToSelfDestruct;

  private:
    int width;
    Vec2 scale;
    int height;
    bool repeats;
    float frameTime;
    int currentFrame;
    SDL_Rect clipRect;
    float timeElapsed;
    SDL_Texture* texture; 
};

#endif
