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
    /* testing that images get changed -- only for debugging
    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    ofFill();
    ofDisableLighting();
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    player_.particle_system_.textures_.color.draw(0, 0);
    ofEnableLighting();
    ofPopStyle();
     */
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
  if (show_player_) {
    show_player_ = false;
  } else {
    if (key == 120) { // 'x'
      show_player_ = true;
    }
  }
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
