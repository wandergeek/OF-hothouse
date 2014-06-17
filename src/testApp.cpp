#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    //MOSQUITTO
//    mosquitto.setup("127.0.0.1", 1883);
    mosquitto.setup("10.0.1.129", 1883);
    mosquitto.connect();
    ofAddListener(mosquitto.onConnect, this, &testApp::onMosquittoConnect);
    
    //LIGHTS
    for(int i = 0; i<NUMLIGHTS; i++) {
        Light light;
        light.setup(i,dmx);
        lights.push_back(light);
    }
    hue.setup("10.0.1.111", "newdeveloper");
    
    //GUI
    int panelX = 20;
    int panelY = 20;
    int panelW = 240;
    int panelH = 200;
    guiRect.x = panelX - 10;
    guiRect.y = panelY - 10;
    guiRect.width = panelW;
    guiRect.height = 300;
    gui.setup("HotHouse Debug");
    gui.add(lightsOn.setup("Lights On"));
    lightsOn.addListener(this, &testApp::lightsOnPressed);
    gui.add(lightsOff.setup("Lights Off"));
    lightsOff.addListener(this, &testApp::lightsOffPressed);
    mqttStatusPos.x = ofGetWidth() * 0.85;
    mqttStatusPos.y = ofGetHeight() * 0.07;
    lastMessage="";
    nina.loadImage("nina.png");
    bool bDebug = true;
    

}

//--------------------------------------------------------------
void testApp::update()
{
    
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(255, 200, 10);
    for(int i = 0; i<lights.size(); i++) {
        lights[i].draw();
    }
    
    if(bDebug == true) {
        ofSetColor(ofFloatColor(0.0, 0.8));
        ofRect(guiRect);
        ofSetColor(ofFloatColor(1.0, 0.8));
        ofNoFill();
        ofRect(guiRect);
        ofFill();
        ofSetColor(255);
        gui.draw();
        ofSetColor(0);
        ofDrawBitmapString(messageStr, ofGetWidth()*0.2,ofGetHeight()*0.8);
    }
    
    nina.draw(ofGetWidth()*0.9, ofGetHeight()*0.05);
    
    
}

//--------------------------------------------------------------
void testApp::exit()
{
    mosquitto.disconnect();
}

//--------------------------------------------------------------
void testApp::onMosquittoConnect(int &rc)
{
    
    if (MOSQ_ERR_SUCCESS == rc)
    {
        mosquitto.subscribe(NULL, GESTURE_TOPIC);
        ofAddListener(mosquitto.onMessage, this, &testApp::onMosquittoMessageReceived);
    }
}

//--------------------------------------------------------------
void testApp::onMosquittoMessageReceived(ofxMosquittoMessage &msg)
{
    if (msg.payloadlen)
    {
        messageStr = msg.payloadAsString();
        cout << "received: " << messageStr << endl;
        
        bool parseSuccess = json.parse(messageStr);
        ofColor color;
        if(parseSuccess) {
            float hue = ofToFloat(json["hue"].toStyledString());
            float mapHue = ofMap(hue, 0, 65535, 0, 255);
            cout << "hue = " << hue << ", mapHue = "  << mapHue << endl;
            color.setHsb(mapHue, 255, 200);

            cout << "parsed: " << color << " color hue =" << color.getHue() << ", parsed hue = " << hue << "\n\n\n" << endl;
            setLights(color,true);
        } else {
            ofLog(OF_LOG_ERROR, "Parse failed: %s", messageStr.c_str());
            return;
        }

        
    }
}
//--------------------------------------------------------------

void testApp::setLights(ofColor _col, bool isOn) {
    
    cout << "setLights " << _col << endl;
    
    if(DMX_ENABLED) {
        for(int i = 0; i<lights.size(); i++) {
            lights[i].setColor(_col);
        }
    }
    
    if(HUES_ENABLED) {
        float colBrightness = ofMap(_col.getBrightness(), 0, 255, 0, 1);  //library (for some reason) requires value between 0 and 1 for all params
        float colHue = ofMap(_col.getHue(), 0, 255, 0, 1);
        float colSaturation = ofMap(_col.getSaturation(),0,255,0,1);
        
        cout << colHue <<","<< colSaturation <<"," << colBrightness << endl;
        
        for(int i = 1; i <= NUM_HUES; i++){
            hue.setLightState(
                              i,		//light bulb ID #
                              isOn,			//on-off
                              colBrightness,	//brightness
                              colSaturation,			//sat
                              colHue,		//hue
                              300				//transition duration in ms
                              );
        }
    }
}

//--------------------------------------------------------------
void testApp::setLight(ofColor _col, bool _isOn, int lightID) {
    lights[lightID].setColor(_col);
    
}

//--------------------------------------------------------------
void testApp::lightsOnPressed() {
    setLights(ofColor::white, true);
    
}
//--------------------------------------------------------------

void testApp::lightsOffPressed() {
    setLights(ofColor::black,false);
}
//--------------------------------------------------------------
