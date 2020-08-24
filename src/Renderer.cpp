/*
 * 
 *based on CirclesRenderer.cpp Created on: 11/07/2012 by Author: arturo
 */

#include "Renderer.h"

Renderer::Renderer() {

}


void Renderer::setup(string name,int i, int movie, int movie2, int markerid, bool recent, float posX, float posY){


    videofiles[0]="movies/faces.mp4";videofiles[1]="movies/facesRec.mp4";
    videofiles[2]= "movies/dance.mp4";videofiles[3]="movies/danceRec.mp4";
    videofiles[4]= "movies/school.mp4";videofiles[5]= "movies/schoolRec.mp4";
    videofiles[6]= "movies/omada.mp4";videofiles[7]= "movies/omadaRec.mp4";
    videofiles[8]= "movies/5.mp4";videofiles[9]= "movies/prezo4.mp4";

    dx=posX;dy=posY;id=i;marker=markerid;
    recVideo=movie2;
    pastVideo=movie;
    rec=recent;
    video.loadMovie(videofiles[pastVideo]);
    video.play();
    videoRec.loadMovie(videofiles[recVideo]);
    videoRec.play();
    

}

void Renderer::update(){
    if(rec)videoRec.update();
    else video.update();

}

void Renderer::draw(){
	frameNum ++;
	ofSetColor(color);
    ofPushMatrix();
    ofTranslate(position.get().x,position.get().y, 0);
    ofScale(rsize,rsize,1);
    ofRotateZ(rotation.get().y);
     if (video.isFrameNew()) {
        fbo.begin();
        video.draw(0, 0, 320/2, 240/2);
        fbo.end();
    }
    fbo.draw(0-fbo.getWidth()*rsize/2,0-fbo.getHeight()*rsize/2,fbo.getWidth(),fbo.getHeight());
    ofPopMatrix();
}


void Renderer::draw0(){

      video.draw(0, 0,320,240);

}


void Renderer::playSoundChanged(bool & playSound){

}


void Renderer::setPosition(float posX, float posY){
    position.set("position",ofVec2f(posX,posY));
}
