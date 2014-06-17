//
//  Light.cpp
//  ofxDmxExample
//
//  Created by nick on 11/06/2014.
//
//


#include "Light.h"
#define WIDTH 50
#define HEIGHT 25
#define XOFFSET 20

void Light::setup(int _ID, ofxDmx &_dmx) {
    ID = _ID;
    xPos = (ID * WIDTH) + (XOFFSET*ID) + XOFFSET*4;
    yPos = ofGetHeight()/2;
    curColor = ofColor::black;
    dmx = _dmx;
}

void Light::setColor(ofColor color) {
    curColor = color;
//    int dmxOffset = (ID * 6) + 4;
//    for(int i=0; i<3; i++) {
//        dmx.setLevel(dmxOffset+i, color[i]);
//    }
//    dmx.update();
}

ofColor Light::getColor() {
    return curColor;
}

void Light::draw() {
    ofSetColor(curColor);
    ofFill();
    ofRect(xPos,yPos,WIDTH,HEIGHT);
}
