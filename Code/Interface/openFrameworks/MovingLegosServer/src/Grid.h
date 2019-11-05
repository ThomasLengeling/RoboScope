#include "ofMain.h"
#include "Block.h"


class Grid;
typedef std::shared_ptr<Grid> GridRef;

class Grid{
public:
  Grid(){

  }

  ~Grid(){

  }

  //create memory
  static GridRef create() {
      return std::make_shared<Grid>();
  }


private:

};
