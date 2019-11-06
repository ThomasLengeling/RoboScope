#include "Grid.h"

//---------------------------------------------
void Grid::draw(){
  for(auto & block : mGrid){
    block->draw();
  }
}


//---------------------------------------------
void Grid::update(){

}
