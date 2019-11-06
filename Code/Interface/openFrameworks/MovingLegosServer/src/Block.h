#pragma once

/*

*/
#include "ofMain.h"

//block size
#define BLOCK_SIZE 20

//memory
class Block;
typedef std::shared_ptr<Block> BlockRef;

///////////////////
class Block{
public:
  Block(){

  }

  ~Block(){

  }

  //create memory
  static BlockRef create() {
      return std::make_shared<Block>();
  }


  //draw
  void draw();
  void update();

  //set Position
  void setPos(glm::vec2 pos);
  void setSize(glm::vec3 mSize);
  void setColor(ofColor col);

private:
  //position
  glm::vec2  mPos;
  glm::vec2  mCenter;

  //rod
  glm::vec3 mDims;

  //unique id
  int mId

  //
  float mWidth;
  

  //color
  ofColor mColor;

  //animation
};
