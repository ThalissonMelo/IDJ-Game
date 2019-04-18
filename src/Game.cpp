#include "Game.h"

#define MIX_DEFAULT_FORMAT AUDIO_S16LSB

#define CHANNELS 32

#define CHUNKSIZE 1024

Game* Game::instance = nullptr;

Game::Game(string title, int width, int heigth){
  if (instance != nullptr) {
      cout << "Error on strat game";
      exit(-1);
  }

  instance = this;

  //Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
    cout << "SDL_Init failed: %s\n" << SDL_GetError();
    exit(-1);
  }

  //Initialize Image
  int imgFlags = (IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);
  if(IMG_Init(imgFlags) != imgFlags)
  {
      cout << "Fail to initialize image! Error: %s\n" << IMG_GetError();
      exit(-1);
  }

  //Initialize Audio
  int audioFlags = MIX_INIT_OGG;
  if(Mix_Init(audioFlags) != audioFlags){
    cout << "Fail to initialize audio! Error: " << Mix_GetError() << endl;
    exit(-1);
  }
  else{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNKSIZE)){
      cout << "Fail to initilaize Mix_OpenAudio: " << SDL_GetError() << endl;
      exit(-1);
    }
    else{
      //Mix allocate channels never fails
      Mix_AllocateChannels(CHANNELS);
    }
  }

  //criando a janela

  window = SDL_CreateWindow(
    title.c_str(),                  // window title
    SDL_WINDOWPOS_CENTERED,         // initial x position
    SDL_WINDOWPOS_CENTERED,         // initial y position
    width,                            // width, in pixels
    heigth,                            // height, in pixels
    0           // flag
  );

  // Check that the window was successfully created
  if (window == nullptr) {
      // In the case that the window could not be made...
      cout << "Fail to create Window: %s\n" << SDL_GetError();
      exit(-1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
      cout << "Fail to create renderer: %s\n" << SDL_GetError();
  }

  this->state = new State();

}

Game::~Game(){
  this->state = nullptr;
  this->instance = nullptr;
  Mix_Quit();
  IMG_Quit();
  Mix_CloseAudio();
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Game::run() {
  while (!(state->QuitRequested())) {
      InputManager::GetInstance().Update();
      state->Update(33);
      state->Render();
      SDL_RenderPresent(Game::getInstance().getRenderer());
  }
}

SDL_Renderer* Game::getRenderer(){
    return renderer;
}

State& Game::getState(){
    return *state;
}

Game& Game::getInstance(){

  string title = "Thalisson B. M. Silva - 15/0046871";

  if(instance == nullptr){
	  return *(new Game(title, 1024, 600));
  }

  return *instance;

}