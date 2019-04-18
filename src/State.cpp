#include "State.h"
#include "InputManager.h"


 #define PI 3.1415

 State::State(){
  quitRequested = false;
 	objectArray = std::vector<std::shared_ptr<GameObject>>();
	
	srand(time(NULL));
	
 	LoadAssets();
	
  music.play(-1);

	GameObject* map = new GameObject();
	TileSet* tiles = new TileSet(*map, 64, 64, "assets/img/tileset.png");

	Component* tileMap = new TileMap(*map, "assets/map/tileMap.txt", tiles);
	map->AddComponent(tileMap);
	map->box = Rect();
	objectArray.emplace_back(map);
 }

 State::~State(){
   objectArray.clear();
 }

 bool State::QuitRequested(){
   return quitRequested;
 }

 void State::LoadAssets(){
 	GameObject* bg = new GameObject();
   bgScreen = new Sprite(*bg,"assets/img/ocean.jpg");
   bg->AddComponent(bgScreen);
 	objectArray.emplace_back(bg);
 	music.open("assets/audio/stageState.ogg");
 }

 void State::Update(float dt) {
 	
	// SDL_Event event;

	// if(event.type == SDL_QUIT) {
	// 	quitRequested = true;
	// }

	// if( event.type == SDL_KEYDOWN ) {
 	// 	if( event.key.keysym.sym == SDLK_ESCAPE ) {
 	// 		quitRequested = true;
 	// 	}
 	// 	else {
			// Vec2 objPos = (Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()))+Vec2::Rotate(200, std::rand()%360);
			// AddObject(objPos.x, objPos.y);
 	// 	}
	// }

	quitRequested = InputManager::GetInstance().QuitRequested();

	if(InputManager::GetInstance().KeyPress(SPACE_KEY)){
		cout << "Alo Alo" << endl;
		double randomic1 = rand()%360;
		double randomic2 = rand()%360;
		double randomic3 = rand()%360;
		double finalRand = ((randomic1 + randomic2 + randomic3)/3);
		Vec2 objPos = (Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()))+Vec2::Rotate(200, finalRand);
		AddObject(objPos.x, objPos.y);
		cout << finalRand << endl;


	}


 	for(auto& i: objectArray)
 		i->Update(dt);

 	for(int i = objectArray.size()-1; i >= 0; i--)
 		if(objectArray[i] != nullptr){
 			if(objectArray[i]->IsDead())
 				objectArray.erase(objectArray.begin()+i);
 		}
 }
 void State::Render(){
   for (auto& obj : objectArray) 
     obj->Render();
 }
//  void State::Input() {
//  	SDL_Event event;
//  	int mouseX, mouseY;
//  	SDL_GetMouseState(&mouseX, &mouseY);
//  	while (SDL_PollEvent(&event)) {
//  		if(event.type == SDL_QUIT) {
//  			quitRequested = true;
//  		}
	
//  		if(event.type == SDL_MOUSEBUTTONDOWN) {
//  			for(int i = objectArray.size() - 1; i >= 0; --i) {
//  				GameObject* go = (GameObject*) objectArray[i].get();
//  				if(go->box.Contains((float)mouseX, (float)mouseY)) {
//  					Face* face = (Face*)go->GetComponent( "Face" );
//  					if ( nullptr != face ) {
//  						face->Damage(std::rand() % 10 + 10);
//  						break;
//  					}
//  				}
//  			}
//  		}
//  		if( event.type == SDL_KEYDOWN ) {
//  			if( event.key.keysym.sym == SDLK_ESCAPE ) {
//  				quitRequested = true;
//  			}
//  			else {
//  				Vec2 objPos = Vec2::Rotate(200, std::rand()%360) + Vec2(mouseX, mouseY);
//  				AddObject((int)objPos.x, (int)objPos.y);
//  			}
//  		}
//  	}
//  }
 void State::AddObject (int mouseX, int mouseY){
 	GameObject* go = new GameObject();
 	Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
 	go->AddComponent(sprite);
 	go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
 	go->AddComponent(new Face(*go));
 	objectArray.emplace_back(go);
 	go->box = Rect(mouseX, mouseY, sprite->getWidth(), sprite->getHeight());
 }