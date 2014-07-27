#include "testApp.h"
#include "Leap.h"

void testApp::setup(){

  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_VERBOSE);

  l1.setPosition(200, 300, 50);
  l2.setPosition(-200, -200, 50);

  cam.setOrientation(ofPoint(-20, 0, 0));

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}


//--------------------------------------------------------------
void testApp::update(){
}

void testApp::drawBone(Leap::Bone bone) {
  
}

//--------------------------------------------------------------
void testApp::draw(){
  ofDisableLighting();
  ofBackgroundGradient(ofColor(90, 90, 90), ofColor(30, 30, 30),  OF_GRADIENT_BAR);

  ofSetColor(200);

  cam.begin();	

  ofPushMatrix();
  ofRotate(90, 0, 0, 1);
  ofSetColor(20);
  ofDrawGridPlane(800, 20, false);
  ofPopMatrix();

  ofEnableLighting();
  l1.enable();
  l2.enable();

  m1.begin(); 
  m1.setShininess(0.6);

  l2.disable();

  m1.end();
  cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void testApp::exit(){
  
}
