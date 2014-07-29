#pragma once

#include "ofMain.h"
#include "Player.h"
#include "Settings.h"
#include <string>

class testApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();
  
  void onArtistSelection(std::string &artist_name);
  
  void keyPressed  (int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  void exit();
  
private:
  Player player_;
  Settings settings_;
  bool show_player_;

};
