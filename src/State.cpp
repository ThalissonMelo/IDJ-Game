 #include <SDL2/SDL.h>
 #include "State.h"
 #include "Face.h"
 #include "Vec2.h"
#include "Sound.h"
#include "Sprite.h"

 #define PI 3.1415

 State::State(){
   quitRequested = false;
 	objectArray = std::vector<std::unique_ptr<GameObject>>();
	
 	LoadAssets();
	
   music.play(-1);
 }

 State::~State(){
   objectArray.clear();
 }

 bool State::QuitRequested(){
   return quitRequested;
 }

 void State::LoadAssets(){
   //Carrega os assets(imagens e músicas) do State
 	GameObject* bg = new GameObject();
   bgScreen = new Sprite(*bg,"assets/img/ocean.jpg");
   bg->AddComponent(bgScreen);
 	objectArray.emplace_back(bg);
 	music.open("assets/audio/stageState.ogg");
 }

 // void State::update(float dt){
 //   // SDL_QuitRequested() ? quitRequested = true : quitRequested;
 //   Input();
 //   for (auto& obj : objectArray) 
 //     obj->Update(dt);

 //   if (SDL_QuitRequested()) {
 //         quitRequested = true;
 //     }

 //   for (auto it = 0; it != objectArray.size()-1; it++)
 //     if(objectArray[it]->IsDead())
 //       objectArray.erase(objectArray.begin() + it);
 // 	// for(int i = objectArray.size()-1; i >= 0; i--)
 // 	// {
 // 	// 	if(objectArray[i]->IsDead()){

 // 	// 		// cout << "Entrou aqui carai " << objectArray[objectArray.begin()+i]->IsDead() << endl;
 // 	// 		objectArray.erase(objectArray.begin()+i);

 // 	// 	}
 // 	// for (int i = objectArray.size() - 1; i >= 0; i--){
 //   //   // cout << objectArray[i]->IsDead() << endl;
 // 	// 	if (objectArray[i]->IsDead()){
 // 	// 		if(objectArray[i] != nullptr)
 // 	// 			cout << "Ta nulo não carai de asa" << endl;
 //   //     objectArray.erase(objectArray[i]);
 // 	// 	}
 // 	// }
 // 	// for(auto it = objectArray.size()-1; it >= 0; it--)
 //   // 		if(objectArray[it]->IsDead())
 //   // 			objectArray.erase(objectArray.begin()+it);
 // }
 void State::Update(float dt) {
 	Input();
 	for(auto& i: objectArray)
 		i->Update(dt);
 	for(int i = objectArray.size()-1; i >= 0; i--)
 		if(objectArray[i] != nullptr){
 			if(objectArray[i]->IsDead())
 				objectArray.erase(objectArray.begin()+i);
 		}
 }
 void State::Render(){
   //renderiza o jogo
   for (auto& obj : objectArray) 
     obj->Render();
 }
 void State::Input() {
 	SDL_Event event;
 	int mouseX, mouseY;
 	// Obtenha as coordenadas do mouse
 	SDL_GetMouseState(&mouseX, &mouseY);
 	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
 	while (SDL_PollEvent(&event)) {
 		// Se o evento for quit, setar a flag para terminação
 		if(event.type == SDL_QUIT) {
 			quitRequested = true;
 		}
	
 		// Se o evento for clique...
 		if(event.type == SDL_MOUSEBUTTONDOWN) {
 			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
 			for(int i = objectArray.size() - 1; i >= 0; --i) {
 				// Obtem o ponteiro e casta pra Face.
 				GameObject* go = (GameObject*) objectArray[i].get();
 				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
 				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
 				// ao usar get(), violamos esse princípio e estamos menos seguros.
 				// Esse código, assim como a classe Face, é provisório. Futuramente, para
 				// chamar funções de GameObjects, use objectArray[i]->função() direto.
 				if(go->box.Contains((float)mouseX, (float)mouseY)) {
 					Face* face = (Face*)go->GetComponent( "Face" );
 					if ( nullptr != face ) {
 						// Aplica dano
 						face->Damage(std::rand() % 10 + 10);
 						// Sai do loop (só queremos acertar um)
 						break;
 					}
 				}
 			}
 		}
 		if( event.type == SDL_KEYDOWN ) {
 				// cout << "wtffffffffffff" << endl;
 			// Se a tecla for ESC, setar a flag de quit
 			if( event.key.keysym.sym == SDLK_ESCAPE ) {
 				quitRequested = true;
 			}
 			// Se não, crie um objeto
 			else {
 				// cout << "vai caraaaaaaio" << endl;
 				// Vec2 objPos = Vec2(200, 0) + Vec2((float)mouseX, (float)mouseY);
 				Vec2 objPos = Vec2::Rotate(200, std::rand()%360) + Vec2(mouseX, mouseY);
 				// cout << (int)objPos.x << " " << (int)objPos.y<< endl;
 				AddObject((int)objPos.x, (int)objPos.y);
 			}
 		}
 	}
 }
 void State::AddObject (int mouseX, int mouseY){
   // GameObject* go = new GameObject();
 	// Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
   /*
     Atribua uma posição (na box do
     GO) para o GameObject com base nos argumentos.
     Lembrando que é bom compensar o tamanho da sprite, caso contrário
     a imagem não ficará centrada nas coordenadas passadas. Você pode usar as
     informações do tamanho da imagem, contida na Sprite e colocadas na
     largura e altura da box de GameObject, para realizar o cálculo.
   */
   // go->box = Rect(mouseX-sprite->GetWidth()/2, mouseY-sprite->GetHeight()/2,
 	// 			   sprite->GetWidth(), sprite->GetHeight());
   // go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
 	// go->AddComponent(sprite);

 	// go->AddComponent(new Face(*go));
 	// objectArray.emplace_back(go);
 	// GameObject* go = new GameObject();
 	// Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
 	// go->AddComponent(sprite);
 	// go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
 	// go->AddComponent(new Face(*go));
 	// objectArray.emplace_back(go);
 	// go->box = Rect(mouseX-sprite->getWidth()/2, mouseY-sprite->getHeight()/2,
 	// 			   sprite->getWidth(), sprite->getHeight());
 	GameObject* go = new GameObject();
 	Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
 	go->AddComponent(sprite);
 	go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
 	go->AddComponent(new Face(*go));
 	objectArray.emplace_back(go);
 	go->box = Rect(mouseX, mouseY, sprite->getWidth(), sprite->getHeight());
 }
 // AddObject é chamada por Input e recebe a posição atual do cursor.
 // Para esse trabalho, ajuste Input para que esse objeto seja instanciado a 200
 // pixels dessa posição, num ângulo aleatório. Para poder gerar números
 // (pseudo-)aleatórios, seede a função rand() no construtor de Game. Use a
 // função srand() (<cstdlib>) com time(NULL) (<ctime>) como argumento.
 // Agora que você implementou State usando unique pointers para
 // manter um registro de GOs, você pode retornar à classe GameObject e
 // modificá-la para, ao invés de usar ponteiros puros, usar
 // unique_ptr<Component>. As funções que você terá que modificar são
 // ~GameObject, AddComponent, RemoveComponent e GetComponent. Além da
 // declaração do vetor components.
