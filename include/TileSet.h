#ifndef TILESET_H_
#define TILESET_H_

#include <bits/stdc++.h>
#include "Sprite.h"
#include "GameObject.h"

using namespace std;

 class TileSet{
  public:
    TileSet(GameObject& associated, int tileWidth, int tileHeight, string file);
    ~TileSet();
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth(); 
    int GetTileHeight(); 
  private:
    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
 };

 #endif