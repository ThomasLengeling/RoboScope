#include "ofMain.h"

//block size
#define BLOCK_SIZE 20

//memory
class Block;
typedef std::shared_ptr<Block> BlockRef;


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

  void draw();
  void update();

private:
  //position
  glm::vec2  mPos;
  glm::vec2  mCenter;

  //unique id
  int mId

  //height
  float mHeight;

  //color
  ofColor mColor

  //animation
};
