#ifndef STATE_H_
#define STATE_H_

#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include <bits/stdc++.h>
#include <GameObject.h>
#include "Face.h"
#include "Vec2.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include <SDL2/SDL.h>


class State{
  public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
  private:
    Component* bgScreen;
    Music music;
    bool quitRequested;
    void AddObject(int mouseX, int mouseY);
    std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif
