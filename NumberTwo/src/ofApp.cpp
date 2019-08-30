#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofBackground(ofColor::fromHsb(224, 255, 175));
  ofEnableAntiAliasing();
  ofEnableSmoothing();
  
  // Allocate FBO for drawing.
  drawFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  
  cout << ofGetWidth() << ", " << ofGetHeight() << endl;
  xGridSize = ofGetWidth()/16; yGridSize = (ofGetHeight()/16) + 1; 
  cout << xGridSize << ", " << yGridSize << endl;
  // Create grid.
  for (int x=0; x < numRows; x++) {
    for (int y=0; y < numColumns; y++) {
      // Get the right hue color for each row and column
      auto hue = x + y * numColumns;
      glm::vec2 pos = glm::vec2(x*xGridSize, y*yGridSize);
      auto cell = Cell(pos, hue);
      grid.push_back(cell); 
    }
  }
}

//--------------------------------------------------------------
void ofApp::update(){
  drawFbo.begin();
    ofClear(0);
    ofEnableAntiAliasing();
//    ofEnableSmoothing();
     // Draw the grid
    for (auto c : grid) {
      c.drawCellWithValueFlower(xGridSize, yGridSize);
    }
  drawFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
  drawFbo.draw(0, 0);
}

// Nice experimental looking good shape.
void ofApp::drawCircle() {
  // Use this background for this
  // ofBackground(ofColor::fromHsb(224, 255, 175));
  int angleInc = 360/256;
  int length = 1200;
  ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    int j = 0;
    for (int a = 0; a < 360; a+= angleInc) {
      ofPushMatrix();
        ofRotateDeg(a);
        ofSetColor(ofColor::fromHsb(240, 210, j));
        ofDrawLine(0, 0, 0, length);
      ofPopMatrix();
      j++;
    }
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == ' ') {
    ofPixels p;
    drawFbo.readToPixels(p);
    auto fileName = ofToString(ofGetMinutes()) + ".png";
    ofSaveImage(p, fileName, OF_IMAGE_QUALITY_BEST); 
  }
}

