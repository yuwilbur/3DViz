#pragma once

#include "ofMain.h"
#include "Leap.h"
#include "HandController.h"
#include "ParticleSystem.h"

class testApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();
  void drawBone(Leap::Bone bone);
  
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
  ofEasyCam cam;
  ofLight l1;
  ofLight l2;
  ofMaterial m1;
  ofCylinderPrimitive cylinder_;
  
  HandController hand_controller_;
  ParticleSystem particle_system_;
};
