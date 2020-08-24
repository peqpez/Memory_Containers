/*
 * Based on CirclesRenderer.h  created by arturo on 11/07/2012
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofMain.h"
#include "ofxGui.h"
class Renderer;

template<typename ParameterType>
class ofRendererParam: public ofReadOnlyParameter<ParameterType,Renderer>{
    friend class Renderer;
};

class Renderer {
public:
	Renderer();

	void setup(string name, int id,int movie, int audio, int markerid, bool rec, float posX, float posY);
	void update();
	void draw();
	void playSoundChanged(bool & playSound);
	void setPosition(float posX, float posY);
	void draw0();

	ofParameterGroup parameters;
	ofParameter<float> rsize;
	ofParameter<int> number;
	ofParameter<ofVec2f> position;
	ofParameter<ofVec2f> rotation;
	ofParameter<ofColor> color;
	ofRendererParam<int> frameNum;
	ofParameter<bool> playSound;
    ofParameter<int> videolist;
    ofParameter<int> audiolist;
	ofVideoPlayer video,videoRec;
    ofFbo fbo;
    ofSoundPlayer sound;
    ofxPanel controls;

    ofMesh mesh;
    ofImage image;
    ofPixels fboPixels;
    string videofiles[10];
    string audiofiles[5];
    int pastVideo,curAudio,recVideo;
    bool hasAudio,hasVideo,rec;
    float dx,dy;
    int marker,id;

private:
    int videoWidth = 320;
    int videoHeight = 240;
    int W = 64; //Grid size
    int H = 36;
    int meshSize = 10;



};

#endif /* RENDERER_H_ */
