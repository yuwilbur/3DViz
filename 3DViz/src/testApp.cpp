#include "testApp.h"
#include "Leap.h"

using namespace Leap;

void testApp::setup(){
  got_artist_ = false;
  settings_.setup();
  
  ofAddListener(settings_.artistSelection, this, &testApp::onArtistSelection);
}

void testApp::update(){
  if (got_artist_) {
    player_.update();
  } else {
    settings_.update();
  }
}

void testApp::draw(){
  if (got_artist_) {
    player_.draw();
  } else {
    settings_.draw();
  }
}

void testApp::onArtistSelection(std::string &artist_name) {
  artist_name_ = artist_name;
  player_.setup(artist_name_);
  got_artist_ = true;
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
  ofRemoveListener(settings_.artistSelection, this, &testApp::onArtistSelection);
  player_.exit();
  settings_.exit();
}
