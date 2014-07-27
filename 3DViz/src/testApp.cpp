#include "testApp.h"
#include "Leap.h"

using namespace Leap;

void testApp::setup(){

  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_VERBOSE);

  l1.setPosition(200, 300, 50);
  l2.setPosition(-200, -200, 50);

  cam.setOrientation(ofPoint(-20, 0, 0));
  
  hand_controller_.setTranslation(ofVec3f(0, -150, -50));
  hand_controller_.setScale(2);
  particle_system_.setup();

  // glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}


//--------------------------------------------------------------
void testApp::update(){
  particle_system_.update();
  pinch_list pinches = hand_controller_.getPinches();
  if (pinches.size() > 0)
    particle_system_.setGravity(pinches[0].first, 100000 * pinches[0].second);
  else
    particle_system_.setGravity(ofVec3f::zero(), 0);

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
  
  ofEnableDepthTest();
  hand_controller_.drawHands();
  ofDisableDepthTest();
  l2.disable();

  m1.end();
  cam.end();
  particle_system_.draw();
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
