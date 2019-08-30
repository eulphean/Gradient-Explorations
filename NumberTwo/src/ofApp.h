#pragma once

#include "ofMain.h"

class Cell {
  public:
    Cell(glm::vec2 pos, int h) {
      position = pos;
      hue = h;
    }
  
    void drawCell(float xGridSize, float yGridSize) {
      ofPushMatrix();
        ofTranslate(position);
        ofPushStyle();
          ofSetColor(ofColor::fromHsb(hue, 255, 255));
          ofDrawRectangle(0, 0, xGridSize, yGridSize);
        ofPopStyle();
      ofPopMatrix();
    }
  
    void drawCellByValueVertical(float xGridSize, float yGridSize) {
      // Subdivide the this cell into 256 parts and draw it with respect to the value
      float interval = xGridSize/256; // Because there are 256 value intervals in a hue
      ofPushMatrix();
        ofTranslate(position);
        int j = 0;
        for (float i = 0.0; i < xGridSize; i += interval) {
          auto color = ofColor::fromHsb(hue, 255, j);
          ofPushStyle();
            ofSetColor(color);
            ofDrawLine(i, 0, i, yGridSize);
          ofPopStyle();
          j++;
        }
      ofPopMatrix();
    }
  
    void drawCellByValueHorizontal(float xGridSize, float yGridSize) {
      float interval = yGridSize/256; // Because there are 256 value intervals in a hue
      ofPushMatrix();
        ofTranslate(position);
        int j = 0;
        for (float i = 0; i < yGridSize; i += interval) {
          auto color = ofColor::fromHsb(hue, 255, j);
          ofPushStyle();
            ofSetColor(color);
            ofDrawLine(0, i, xGridSize, i);
          ofPopStyle();
          j++;
        }
      ofPopMatrix();
    }
  
    void drawCellBySaturation(float xGridSize, float yGridSize) {
      float interval = xGridSize/256; // Because there are 256 value intervals in a hue
      ofPushMatrix();
        ofTranslate(position);
        int j = 0;
        for (float i = 0; i < xGridSize; i += interval) {
          auto color = ofColor::fromHsb(hue, j, 200);
          ofPushStyle();
            ofSetColor(color);
            ofDrawLine(i, 0, i, yGridSize);
          ofPopStyle();
          j++;
        }
      ofPopMatrix();
    }
  
    void drawCellWithValueFlower(float xGridSize, float yGridSize) {
       ofPushMatrix();
        ofTranslate(position);
        // Draw the cell with original hue.
        ofPushStyle();
          ofSetColor(ofColor::fromHsb(hue, 255, 255));
          ofDrawRectangle(0, 0, xGridSize, yGridSize);
        ofPopStyle();
        // Draw the value flower inside the cell.
        float angleInterval = 360/32;
        float length = yGridSize/2;
        ofTranslate(xGridSize/2, yGridSize/2);
        int j = 0;
        for (float a = 0; a < 360; a+= angleInterval) {
          ofPushMatrix();
            ofRotateDeg(a);
            ofPushStyle();
            ofSetColor(ofColor::fromHsb(hue, 255, j));
            ofDrawLine(0, 0, 0, length);
            ofPopStyle();
          ofPopMatrix();
          j+=8;
        }
      ofPopMatrix();
    }
  
    ofColor color;
    glm::vec2 position;
    int hue;
}; 

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void drawCircle();

		void keyPressed(int key);
  
    int numRows = 16;
    int numColumns = 16;
    float xGridSize;
    float yGridSize; 
  
    std::vector<Cell> grid;
  
    ofFbo drawFbo;
  
    // Number of Rows - 16
    // Number of Columns - 16
};
