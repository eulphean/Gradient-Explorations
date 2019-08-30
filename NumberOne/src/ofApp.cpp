#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  // Allocate background image. 
  bgImg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
  fgImg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
  shapeFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  saveFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  
  w = ofGetWidth(); h = ofGetHeight();
  
  shapeHeight = 20; shapeWidth = 40;
  
  ofEnableAntiAliasing();
  
  drawBackground();
  drawForeground();
  drawShape();
}

//--------------------------------------------------------------
void ofApp::update(){
  fgImg.getTexture().setAlphaMask(shapeFbo.getTexture());
  saveFbo.begin();
    ofClear(0);
    ofSetColor(255);
    bgImg.draw(0, 0);
    ofSetColor(255, 40);
    bgImg.draw(0, 0);
    ofSetColor(255);
    fgImg.draw(0, 0);
  saveFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
  saveFbo.draw(0, 0);
}

void ofApp::drawForeground() {
  for (int x = w/2-shapeWidth/2; x < w/2+shapeWidth/2; x++) {
    for (int y = h/2-shapeHeight/2; y < h/2+shapeHeight; y++) {
      auto hue = ofMap(y, h/2-shapeHeight/2, h/2+shapeHeight, 185, 195, true);
      auto c = ofColor::fromHsb(hue, 200, 200);
      fgImg.setColor(x, y, c);
    }
  }
  fgImg.update();
}

void ofApp::drawBackground() {
  auto a = ofColor::fromHsb(0, 255, 255);
  auto b = ofColor::fromHsb(255, 255, 255);
  
  ofColor c;
  for (int y=0; y<h; y++) {
    for (int x=0; x<w; x++) {
      float hue = (x <= w/2) ? ofMap(x, 0, w/2, 170, 185, true):ofMap(x, w/2, w, 185, 170, true);
      c = ofColor::fromHsb(hue,125,125);
      bgImg.setColor(x,y,c);
    }
  }
  bgImg.update();
}

void ofApp::drawShape() {
  shapeFbo.begin();
    ofClear(0, 0, 0, 0);
    ofSetColor(255);
    // Draw a triangle
    auto topVert = glm::vec2(ofGetWidth()/2, ofGetHeight()/2-shapeHeight/2);
    auto leftVert = glm::vec2(ofGetWidth()/2-shapeWidth/2, ofGetHeight()/2+shapeHeight/2);
    auto rightVert = glm::vec2(ofGetWidth()/2+shapeWidth/2, ofGetHeight()/2+shapeHeight/2);
    ofDrawTriangle(topVert, leftVert, rightVert);
  shapeFbo.end();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == ' ') {
    ofPixels pix;
    saveFbo.readToPixels(pix);
    auto fileName = "Save.png";
    ofSaveImage(pix, fileName, OF_IMAGE_QUALITY_BEST);
  }
}
