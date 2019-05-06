#ifndef STATE_H_
#define STATE_H_

#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include <bits/stdc++.h>
#include <GameObject.h>
#include "Vec2.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include <SDL2/SDL.h>
#include "Camera.h"


class State {

  public:
    GameObject* bg;
	  GameObject* map;
    weak_ptr< GameObject > AddObject(GameObject* go);
    weak_ptr< GameObject > GetObjectPtr(GameObject* go);

    State();
    ~State();

    void Update(float dt);
    bool QuitRequested();
    void LoadAssets();
    void Render();
    void Start();

  private:

    Music music;
    bool started;
    bool quitRequested;
    Component* bgScreen;
    vector<shared_ptr<GameObject>> objectArray;

    void AddObject(int mouseX, int mouseY);
};

#endif
