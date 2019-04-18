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
	quitRequested = InputManager::GetInstance().QuitRequested();

	if(InputManager::GetInstance().KeyPress(SPACE_KEY)){
		Vec2 objPos = (Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()))+Vec2::Rotate(200, rand()%360);
		AddObject(objPos.x, objPos.y);
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
 void State::AddObject (int mouseX, int mouseY){
 	GameObject* go = new GameObject();
 	Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
 	go->AddComponent(sprite);
 	go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
 	go->AddComponent(new Face(*go));
 	objectArray.emplace_back(go);
 	go->box = Rect(mouseX, mouseY, sprite->getWidth(), sprite->getHeight());
 }