#include <SDL2/SDL.h>
#include "State.h"

State::State(){
  quitRequested = false;
  quitRequested = false;
  loadAssets();
  // sleep(10);
  music.play(-1);
  // Instacia o Spirte
}

State::~State(){

}

bool State::QuitRequested(){
  return quitRequested;
}

void State::loadAssets(){
  //Carrega os assets(imagens e músicas) do State
  bg.open("assets/img/ocean.jpg");
  music.open("assets/audio/stageState.ogg");
}

void State::update(float dt){
  // SDL_QuitRequested() ? quitRequested = true : quitRequested;
  if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::render(){
  //renderiza o jogo
  this->bg.render(0,0);
}