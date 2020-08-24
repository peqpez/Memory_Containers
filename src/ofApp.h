#pragma once

#include "ofMain.h"
#include "ofxSecondWindow.h"
#include "Renderer.h"
#include "ofxAruco.h"
#include "ofBitmapFont.h"

#define BOXNUM 5

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void vSyncChanged(bool & vSync);
    void drawMarker(float size, int id, const ofColor & color,int i);

    ofxSecondWindow secondWindow;

    ofxPanel gui;
    ofParameter<bool> vSync;
    ofParameter<ofVec2f> markersize;
    ofParameterGroup parameters;
    ofXml settings;
    Renderer renderer[BOXNUM];
    ofTrueTypeFont font;
    ofImage img;

    bool displayGui;

    ofxAruco aruco;
    ofVideoGrabber grabber;
    ofBaseVideoDraws * camera;

    ofImage board;
    ofImage marker;
    bool cameradraw,showMarkers,drawCube;

    ofVideoPlayer video;
    float mid=-5;
};
