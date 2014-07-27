#include "testApp.h"
#include "Leap.h"

using namespace Leap;

void testApp::setup(){

  current_color_ = ofColor(255, 0, 0, 1);
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofSetLogLevel(OF_LOG_VERBOSE);

  l1.setPosition(200, 300, 50);
  l2.setPosition(-200, -200, 50);

  cam.setOrientation(ofPoint(-20, 0, 0));
  
  hand_controller_.setTranslation(ofVec3f(0, -300, -100));
  hand_controller_.setScale(2);
  particle_system_.setup(ofVec3f(0, 0, -100), ofVec3f(600, 400, 100));
  audio_player_.setup();

  glEnable(GL_NORMALIZE);
}


//--------------------------------------------------------------
void testApp::update(){
  audio_player_.update();
  audio_player_.updateColor(current_color_);
  amped_color_ = current_color_;
  audio_player_.amplifyColor(amped_color_);
  particle_system_.setBassAmplitude(audio_player_.getBassAmplitude());
  particle_system_.update();
  
  pinch_list pinches = hand_controller_.getPinches();
  if (pinches.size() > 0) {
    particle_system_.setGravity(pinches[0].first, 3000000 * pinches[0].second);
    
    if (pinches.size() > 1) {
      particle_system_.setGravity2(pinches[1].first, 3000000 * pinches[1].second);
    }
    else
      particle_system_.setGravity2(ofVec3f::zero(), 0);

  }
  else {
    particle_system_.setGravity(ofVec3f::zero(), 0);
    particle_system_.setGravity2(ofVec3f::zero(), 0);
  }
  
  particle_system_.setColor(amped_color_);
}

//--------------------------------------------------------------
void testApp::draw(){
  ofDisableLighting();
  ofBackgroundGradient(ofColor(70, 70, 70), ofColor(10, 10, 10),  OF_GRADIENT_BAR);
  audio_player_.draw();

  ofSetColor(10);

  cam.begin();	

  ofPushMatrix();
  ofRotate(90, 0, 0, 1);
  ofSetColor(0);
  ofPopMatrix();

  ofEnableLighting();
  l1.enable();
  l2.enable();

  m1.begin(); 
  m1.setShininess(0.6);
  
  ofEnableDepthTest();
  hand_controller_.drawHands();
  ofDisableDepthTest();
  particle_system_.draw();

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
