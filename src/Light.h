#pragma once
#include "ofMain.h"
#include "ofxDmx.h"
#include "hothouseConstants.h"

class Light {
public:
    void setup(int ID, ofxDmx &dmx);
    void setColor(ofColor color);
    void draw();
    ofColor getColor();

    
private:
    ofColor curColor;
    int ID;
    int xPos;
    int yPos;
    ofxDmx dmx;
};
                  
