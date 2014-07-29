#include "testApp.h"
#include "Leap.h"

using namespace Leap;

void testApp::setup(){
  player_.setup("Amon Tobin");
  show_player_ = true;
  settings_.setup();
  ofAddListener(settings_.artistSelection, this, &testApp::onArtistSelection);
}

void testApp::update(){
  player_.update();
  settings_.update();
}

void testApp::draw(){
  if (show_player_) {
    player_.draw();
  } else {
    settings_.draw();
  }
}

void testApp::onArtistSelection(std::string &artist_name) {
  player_.changeArtist(artist_name);
  show_player_ = true;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
  show_player_ = !show_player_;
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
