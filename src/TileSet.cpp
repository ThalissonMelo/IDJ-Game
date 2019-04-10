#include "TileSet.h"

    TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, string file) : tileSet(associated, file) {
      this->tileHeight = tileHeight;
      this->tileWidth = tileWidth;

      //verificar abertura do tileset
      
      this->columns = tileSet.getWidth()/tileWidth;
      this->rows = tileSet.getHeight()/tileHeight;
    }

    void TileSet::RenderTile(unsigned index, float x, float y){
    
      if(index < this->rows*this->columns){
        int x_axis = this->tileWidth*(index%this->columns);
        int y_axis = this->tileHeight*(index/this->columns);
        tileSet.setClip(x_axis, y_axis, this->tileWidth, this->tileHeight);
        tileSet.Render(x, y);
      }
    
    }

    int TileSet::GetTileWidth(){
      return this->tileWidth;
    } 
    int TileSet::GetTileHeight(){
      return this->tileHeight;
    }
