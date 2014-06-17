#pragma once


#include "ofxGui.h"
#include "ofMain.h"
#include "ofxMosquitto.h"
#include "ofxDmx.h"
#include "Light.h"
#include "ofxJSONElement.h"
#include "ofxPhilipsHue.h"
#include "hothouseConstants.h"

class testApp : public ofBaseApp
{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    



//MOSQUITTO
    void onMosquittoConnect(int &rc);
    void onMosquittoMessageReceived(ofxMosquittoMessage &msg);
    ofxMosquitto mosquitto;
    
//LIGHTS
    ofxDmx dmx;
    ofxPhilipsHue hue;
    vector<Light> lights;
    void setLights(ofColor _col,bool _isOn);
    void setLight(ofColor _col,bool _isOn, int lightID);
    

//GUI
    ofxButton lightsOn;
    ofxPanel gui;
    ofxButton lightsOff;
    ofRectangle guiRect;
    string lastMessage;
    ofPoint mqttStatusPos;
    string messageStr;
    void lightsOnPressed();
    void lightsOffPressed();
    ofImage nina;
    bool bDebug = true;
    
    
//PARSE
    ofxJSONElement json;


    
};