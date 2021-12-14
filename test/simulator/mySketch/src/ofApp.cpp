#include "ofApp.h"
#include <iostream>
#include <vector>
float xpos,ypos;
vector<double>xpoint;
vector<double>ypoint;

void draw_field(){

    ofTranslate(400,600);
    
    ofSetColor(70,70,70);
    for(int i=0;i<ofGetWidth();i+=50){
        ofLine(i,0,i,-ofGetHeight());
    }
    for(int i=0;i>-ofGetHeight();i-=50){
        ofLine(0,i,ofGetWidth(),i);
    }

    ofSetColor(255,255,255);
    ofLine(50,-50,550,-50);
    ofLine(50,-50,50,-500);
    ofLine(50,-275,80,-275);
    ofLine(80,-275,80,-320);
    ofLine(80,-320,50,-320);
    
    ofSetColor(255,0,0);
    ofLine(50,-175,550,-175);
    
    ofSetColor(0,255,0);
    ofLine(125,-175,125,-500);

    ofSetColor(0,0,255);
    ofLine(275,-50,275,-100);
    ofLine(275,-100,325,-100);
    ofLine(325,-100,325,-50);
    
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    xpos=0.0;
    ypos=0.0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    draw_field();

    if(xpoint.size()!=0&&ypoint.size()!=0){
        ofSetColor(102,255,51);
        for(int i=0;i<xpoint.size();i++){
            ofDrawCircle(xpoint[i],ypoint[i],3);
        }
    }

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    std::cout<<mouseX-400<<endl;;
    xpos=mouseX-400;
    ypos=mouseY-600;

    xpoint.push_back(xpos);
    ypoint.push_back(ypos);


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
