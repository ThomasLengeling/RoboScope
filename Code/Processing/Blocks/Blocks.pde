import controlP5.*;
import peasy.*;

//cam
PeasyCam cam;
CameraState state;

Grid  tableGrid;

int gridX = 50;
int gridY = 30;

int gridStartX = 250;
int gridStartY = 50;

ControlP5 cp5;

Accordion accordionGrid;
Accordion accordionIds;

int currentIdRoad = 0;

boolean enableDraw = false;

boolean enableMap =  false;
boolean enableColorMap = false;
boolean enableGrouping = false;

//group blocks
int groupCounter = 0;
int groupMax = 4;
GroupBlock groupBlockTmp = new GroupBlock();

boolean activeAnimation = false;
boolean recording = false;

Map map;

void setup() {
  size(1920, 1080, P3D);
  smooth(8);

  cam = new PeasyCam(this, 500);
  state = cam.getState();

  cp5 = new ControlP5(this);
  cp5.setAutoDraw(false);

  // group number 1, contains 2 bangs
  Group g1 = cp5.addGroup("Gird")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(150);

  // group number 1, contains 2 bangs
  Group g2 = cp5.addGroup("ids")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(150);

  // group number 1, contains 2 bangs
  Group g3 = cp5.addGroup("groups")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(150);

  cp5.addSlider2D("gridSize")
    .setPosition(10, 10)
    .setSize(75, 75)
    .setMinMax(1, 1, 80, 45)
    .setValue(50, 30)
    .moveTo(g1)
    ;

  cp5.addSlider2D("gridSpace")
    .setPosition(100, 10)
    .setSize(75, 75)
    .setMinMax(0, 0, 20, 20)
    .setValue(8, 8)
    .moveTo(g1)
    ;

  cp5.addSlider("blockSize")
    .setPosition(10, 120)
    .setSize(90, 15)
    .setValue(28)
    .setRange(10, 100)
    .setGroup(g1)
    ;

  //ids


  cp5.addTextlabel("idGrid")
    .setText("id: ")
    .setPosition(100, 50)
    .setFont(createFont("Georgia", 12))
    .setGroup(g2);

  cp5.addSlider("density")
    .setPosition(90, 10)
    .setSize(90, 15)
    .setGroup(g2)
    ;

  cp5.addToggle("id")
    .setPosition(150, 50)
    .setSize(20, 20)
    .setGroup(g2)
    ;


  cp5.addRadioButton("amenities")
    .setPosition(10, 10)
    .setSize(20, 20)
    .addItem("Office", 0)
    .addItem("Residential", 1)
    .addItem("Parks", 2)
    .addItem("Roads", 3)
    .addItem("Map", 4)
    .setGroup(g2)
    ;

  accordionGrid = cp5.addAccordion("Master")
    .setPosition(10, 20)
    .setWidth(230)
    .addItem(g1)
    .addItem(g3)
    .addItem(g2);

  cp5.addRadioButton("Groups")
    .setPosition(10, 20)
    .setSize(20, 20)
    .addItem("Group_1", 0)
    .addItem("Group_2", 1)
    .addItem("Gorup_3", 2)
    .setGroup(g3)
    ;

  accordionGrid.open(0, 1, 2);
  accordionGrid.setCollapseMode(Accordion.MULTI);

  //real map
  map = new Map();

  {
    float [] gridSize = cp5.getController("gridSize").getArrayValue();
    float [] gridSpace = cp5.getController("gridSpace").getArrayValue();
    int blockSize = int(cp5.getController("blockSize").getValue());

    tableGrid = new Grid((int)gridSize[0], (int)gridSize[1], (int)gridSpace[0], (int)gridSpace[1], blockSize);
  }
}


void draw() {
  background(0); //190



  pushMatrix();
  translate(-850, -550, 0);
  tableGrid.draw();
  tableGrid.drawContour();
  popMatrix();


  if (!enableDraw) {
    float [] gridSize = cp5.getController("gridSize").getArrayValue();
    tableGrid.setGridDim(gridSize);

    float [] gridSpace = cp5.getController("gridSpace").getArrayValue();
    tableGrid.setSetSpace(gridSpace);
  }

  Block bl = tableGrid.getCurrenBlock(mouseX, mouseY);
  if (bl != null) {
    cp5.getController("idGrid").setStringValue("id: "+bl.getId());
  }


  //density
  float scaleX = 50.0;
  float scaleY = 50.0;
  float scaleZ = 10.0;

  float scale = cp5.getController("density").getValue();
  //createCube(scaleX, scaleY + scale, scaleZ );

  int wTable = tableGrid.getEndX();
  int hTable = tableGrid.getEndY();
  //real map

  if (enableMap) {
    // map.draw(gridStartX, gridStartY, wTable, hTable);
  }

  if (!recording) {
    drawGUI();
  }
  //set Colr dimentions

  if (recording) {
    saveFrame("output/frames-######.png");
  }
}

void drawGUI() {

  hint(DISABLE_DEPTH_TEST);



  cam.beginHUD();

  fill(0);
  text(frameRate, 10, 10);

  cp5.draw();
  cam.endHUD();
  hint(ENABLE_DEPTH_TEST);
}

void mousePressed() {
  Block bl = tableGrid.getCurrenBlock(mouseX, mouseY);

  int Office = int(cp5.getController("Office").getValue());
  int Residential = int(cp5.getController("Residential").getValue());
  int Parks = int(cp5.getController("Parks").getValue());
  int Map = int(cp5.getController("Map").getValue());

  if (bl != null) {
    if (Office == 1) {
      bl.setType(1);
    } else if (Residential == 1) {
      bl.setType(2);
    } else if (Parks == 1) {
      bl.setType(3);
    }

    tableGrid.updateBlockType(bl);
  }

  if (Map == 1) {
    tableGrid.setGridColors(map.getImgDensity(), map.getImgColor());
  }

  //grouping, create group

  int groupBuildings = int(cp5.getController("Group_1").getValue());
}

void keyPressed() {

  if (key == '1') { 
    state = cam.getState();
    println("pos");
    printArray(cam.getPosition());
    println("rot");
    printArray(cam.getRotations());
  }
  
  if (key == '2') { 
    cam.setState(state, 18000);
  }
  
  if (key == 'a') {
    enableMap = !enableMap;
  }

  if (key == 'b') {
    enableColorMap = !enableColorMap;
  }

  if (key == 'z') {
    activeAnimation = !activeAnimation;
  }

  if (key == 'r' || key == 'R') {
    recording = !recording;
  }
}

void blockSize(float bsize) {
  tableGrid.setBlockSize(int(bsize));
}

void id() {
  enableDraw = !enableDraw;

  if (!enableDraw) {
    float [] gridSize = cp5.getController("gridSize").getArrayValue();
    tableGrid.setGridDim(gridSize);

    float [] gridSpace = cp5.getController("gridSpace").getArrayValue();
    tableGrid.setSetSpace(gridSpace);
  }
}
