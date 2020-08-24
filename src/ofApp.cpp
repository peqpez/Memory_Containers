/*
* created by peqpez, 2014
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    renderer[0].setup("container#1",0,0,1,12,false,1.76,1.76);
	renderer[1].setup("container#2",1,2,3,446,false,1.607,1.607);
	renderer[2].setup("container#3",2,4,5,213,false,1.454,1.454);
	renderer[3].setup("container#4",3,6,7,964,false,1.327,1.327);
    renderer[4].setup("container#5",4,8,9,228,false,1.4,1.4);


	parameters.setName("settings");
	parameters.add(vSync.set("vSync",true));
	parameters.add(markersize.set("marker size",ofVec2f(1,1),ofVec2f(0,0),ofVec2f(5,5)));

	gui.setup(parameters);

	gui.loadFromFile("settings.xml");

	font.loadFont( OF_TTF_SANS,9,true,true);
	ofEnableAlphaBlending();
	displayGui=true;
    img.loadImage("board.png");
    ofSetWindowTitle("controls");

 
    secondWindow.setup(" ", 380, 50, 1024, 768,false);
    grabber.listDevices();
    grabber.setDeviceID(1);
    grabber.initGrabber(1024, 768);
    camera = &grabber;
    string boardName = "boardConfiguration.yml";
    aruco.setup("intrinsics.int", camera->getWidth(), camera->getHeight(), boardName);
	aruco.getBoardImage(board.getPixelsRef());
	board.update();

    ofPixels pixels;
	ofBitmapStringGetTextureRef().readToPixels(pixels);
	ofSaveImage(pixels,"font.bmp");

    cameradraw=true;
    showMarkers=false;
    drawCube=true;

    ofSetVerticalSync(true);

}

//--------------------------------------------------------------
void ofApp::update(){
    for(int r=0;r<BOXNUM;r++)renderer[r].update();

    camera->update();
	if(camera->isFrameNew()){
		aruco.detectBoards(camera->getPixelsRef());
	}
}

void ofApp::vSyncChanged(bool & vSync){
	ofSetVerticalSync(vSync);
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackgroundGradient(ofColor::white, ofColor::gray);
	if(displayGui)gui.draw();
	font.drawString("frame: " + ofToString(renderer[0].frameNum),ofGetWidth()-150,20);
	font.drawString("fps: " + ofToString((int)ofGetFrameRate()),ofGetWidth()-150,40);

    // draw the second window
    secondWindow.begin();
        ofBackground(0);


        if(cameradraw)camera->draw(0,0);

            if(showMarkers){
            for(int i=0;i<aruco.getNumMarkers();i++){
                aruco.begin(i);
                //marker.draw(0,0,50,50);
                //renderer[i].update();
                aruco::Marker curMarker=aruco.getMarkers()[i];
                double modelview_matrix[16];
                curMarker.glGetModelViewMatrix(modelview_matrix);
                cout<<curMarker.idMarker<<"   x: "<<modelview_matrix[12]<<"   y: "<<modelview_matrix[13]<<"   z: "<<modelview_matrix[14]<<"\n";
                mid=-1;
                for(int m=0;m<BOXNUM;m++){
                    if(renderer[m].marker==curMarker.idMarker) {
                            mid=m;
                            if(modelview_matrix[12]<0)renderer[m].rec=true; else renderer[m].rec=false;
                    }
                }
                if(mid!=-1)drawMarker(0.15,mid,ofColor::white,i);
                aruco.end();

            }
        }

    secondWindow.end();

}



//--------------------------------------------------------------
void ofApp::drawMarker(float size, int mark, const ofColor & color, int id){
    if(drawCube){
        ofDrawAxis(size);
        ofTranslate(0,0,0);
		ofFill();
		ofSetColor(color,50);
		ofBox(size,0,size);
		ofNoFill();
		ofSetColor(color);
		ofBox(size,0,size);
		ofPopMatrix();
    }
    else{
        ofEnableDepthTest();
        ofEnableNormalizedTexCoords();
        if(renderer[mark].rec)
           renderer[mark].videoRec.getTextureReference().bind();
        else
            renderer[mark].video.getTextureReference().bind();

        ofFill();
		ofSetColor(255);
        ofBox(size*renderer[mark].dx,0,size*renderer[mark].dy);
        if(renderer[mark].rec)
           renderer[mark].videoRec.getTextureReference().unbind();
        else
            renderer[mark].video.getTextureReference().unbind();
        ofDisableDepthTest();
        ofDisableNormalizedTexCoords();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
		displayGui = !displayGui;
	}
	if(key=='s'){
		settings.serialize(parameters);
		settings.save("settings.xml");
	}
	if(key=='l'){
		settings.load("settings.xml");
		settings.deserialize(parameters);
	}
	if(key=='o'){
		cout << renderer[0].parameters;
		cout << renderer[1].parameters;
	}
	if(key=='r'){
		renderer[0].color = ofColor(127);
		renderer[1].color = ofColor(127);
	}
	if(key=='c'){
	    cameradraw=!cameradraw;
	}
	if(key=='m') showMarkers = !showMarkers;
	if(key=='d') drawCube = !drawCube;
	if(key=='p') renderer[0].setPosition(100,100);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
