#include "State.h"
#include "InputManager.h"
#include "CameraFollower.h"

 #define PI 3.1415

 State::State(){
  quitRequested = false;
 	objectArray = std::vector<std::shared_ptr<GameObject>>();
  srand(time(NULL));

 	LoadAssets();
	
  music.play(-1);

	this->map = new GameObject();
	TileSet* tiles = new TileSet(*map, 64, 64, "assets/img/tileset.png");

	Component* tileMap = new TileMap(*map, "assets/map/tileMap.txt", tiles);

	this->map->AddComponent(tileMap);
	this->map->box = Rect();

	objectArray.emplace_back(map);
 }

 State::~State(){
   objectArray.clear();
 }

 bool State::QuitRequested(){
   return quitRequested;
 }

 void State::LoadAssets(){
		this->bg = new GameObject();
  	bgScreen = new Sprite(*this->bg,"assets/img/ocean.jpg");
  	this->bg->AddComponent(bgScreen);
		this->bg->AddComponent(new CameraFollower(*this->bg));
 		objectArray.emplace_back(bg);
 		music.open("assets/audio/stageState.ogg");
 }

 void State::Update(float dt) {

	Camera::Update(dt);
	this->map->Update(dt);
	
	quitRequested = InputManager::GetInstance().QuitRequested();

	if(InputManager::GetInstance().KeyPress(SPACE_KEY)){
		Vec2 objPos = (Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()))+Vec2::Rotate(200, rand()%360);
		AddObject(objPos.x, objPos.y);
	}

 	for(auto& i: objectArray){
 		i->Update(dt);
	}

 	for(int i = objectArray.size()-1; i >= 0; i--)
 		if(objectArray[i] != nullptr){
 			if(objectArray[i]->IsDead())
 				objectArray.erase(objectArray.begin()+i);
 		}
 }

 void State::Render(){
	
	bg->Render();

	for(auto& i: objectArray)
		i->Render();
 }

 void State::AddObject (int mouseX, int mouseY){
 	GameObject* go = new GameObject();
 	Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
 	go->AddComponent(sprite);
 	go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
 	go->AddComponent(new Face(*go));
 	objectArray.emplace_back(go);
 
 	go->box = Rect(mouseX-sprite->getWidth()/2, mouseY-sprite->getHeight()/2,
				   sprite->getWidth(), sprite->getHeight());
 }