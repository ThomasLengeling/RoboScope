#pragma once

/*

*/
#include "ofMain.h"
#include "CanSerial.h"
#include "Grid.h"
#include "Block.h"

//define dimenstions for the grid
#define WIDTH_PINS  12
#define HEIGHT_PINS  8

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//collection of usb ports
		std::vector<CanSerialRef> mSerials;

		//test port
		CanSerialRef mSerialTest;

		//camera movement
		ofEasyCam mCam;

		GridRef mDynamicGrid;
};
