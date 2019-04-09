#ifndef STATE_H_
#define STATE_H_

#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include <bits/stdc++.h>
#include <GameObject.h>

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
        void Input();
        void AddObject(int mouseX, int mouseY);
        std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif
