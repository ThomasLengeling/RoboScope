#pragma once

/*

*/

#include "ofMain.h"
#include "Block.h"

//Grid texture
class Grid;
typedef std::shared_ptr<Grid> GridRef;

class Grid{
public:

  //create a grid with w and h dimentions
  Grid(int w, int h){
    mDims = glm::vec2(w, h);
    for(int i = 0; i < w * h; i++){
      BlockRef block = Block::create();
      mGrid.push_back(block);
    }

  }

  //create memory
  static GridRef create(int w, int h) {
      return std::make_shared<Grid>(w, h);
  }

  void draw();
  void update();

  ~Grid(){}

private:
  std::vector<BlockRef> mGrid;
  glm::vec2 mDims;
};
