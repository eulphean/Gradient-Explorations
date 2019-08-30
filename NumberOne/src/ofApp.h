#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    void drawBackground();
    void drawForeground();
    void drawShape(); 
  
    ofImage bgImg;
    ofImage fgImg;
    ofFbo shapeFbo;
    ofFbo saveFbo; 
  
    float w, h;
    int shapeHeight, shapeWidth; 
};
