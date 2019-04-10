#include "TileMap.h"

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

void TileMap::Render (){
  for(int layer = mapDepth-1; layer >= 0 ; layer--)
		RenderLayer(layer);
}

void TileMap::RenderLayer (int layer, int cameraX, int cameraY){
	for(int i = 0; i < this->mapHeight; i++)
		for(int j = 0; j < this->mapWidth; j++)
			this->tileSet->RenderTile(this->At(j, i, layer), j*this->tileSet->GetTileHeight(), i*this->tileSet->GetTileWidth());
}

int TileMap::GetWidth (){
  return mapWidth;
}
int TileMap::GetHeight (){
  return mapHeight;
}
int TileMap::GetDepth (){
  return mapDepth;
}

bool TileMap::Is(string type){
  return(type == "TyleMap");
}