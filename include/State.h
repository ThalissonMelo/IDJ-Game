#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include <bits/stdc++.h>

class State{
	public:
		State();
    ~State();
    bool QuitRequested();
    void loadAssets();
    void update(float dt);
    void render();
	private:
    Sprite bg;
    Music music;
    bool quitRequested;

};