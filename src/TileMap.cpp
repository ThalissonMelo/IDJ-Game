#include "TileMap.h"
#include "Camera.h"
#include <fstream>

TileMap::TileMap (GameObject& associated, string file, TileSet* tileSet) : Component(associated){
  tileMatrix = vector<int>();
  this->SetTileSet(tileSet);
  this->Load(file);
}
TileMap::~TileMap() {
	tileSet = nullptr;
	tileMatrix.clear();
}
void TileMap::Load(string file){
  ifstream tileMapFile;
  tileMapFile.open(file);
  
  if (!tileMapFile) {
    cerr << "Unable to open file tileMap.txt";
    exit(1);
  }

  int tiles;
  char comma;
  tileMapFile >> this->mapWidth >> comma >> this->mapHeight >> comma >> this->mapDepth >> comma;
  
  for(int i = 0; i < mapDepth; i++) {
		for(int j = 0; j < mapHeight; j++) {
			for(int k = 0; k < mapWidth; k++) {
				tileMapFile >> tiles >> comma;
				tileMatrix.emplace_back(tiles-1);
			}
		}
  }
  
  tileMapFile.close();
}

void TileMap::Update(float dt) {
	
}

void TileMap::SetTileSet (TileSet* tileSet){
  this->tileSet = tileSet;
}

int TileMap::At (int x, int y, int z){
  int elementPosition = x+y*(this->mapWidth)+z*(this->mapWidth*this->mapHeight);
  return this->tileMatrix[elementPosition];
}

void TileMap::Render() {
	for(int layer = 0; layer < mapDepth; layer++)
		RenderLayer(layer, Camera::pos.x*(1+layer*0.5), Camera::pos.y*(1+layer*0.5));
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	for(int j = 0; j < mapHeight; j++) {
		for(int i = 0; i < mapWidth; i++) {
			int x = i*tileSet->GetTileWidth()-cameraX;
			int y = j*tileSet->GetTileHeight()-cameraY;
			tileSet->RenderTile(At(i, j, layer), x, y);
		}
	}
}

int TileMap::GetWidth(){
  return mapWidth;
}
int TileMap::GetHeight(){
  return mapHeight;
}
int TileMap::GetDepth(){
  return mapDepth;
}

bool TileMap::Is(string type){
  return(type == "TyleMap");
}