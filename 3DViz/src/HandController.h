#pragma once

#ifndef HANDS_H
#define HANDS_H

#include "ofMain.h"
#include <vector>
#include "Leap.h"

typedef std::vector<std::pair<ofVec3f, float> > pinch_list;

class HandController {
public:
  HandController() : scale_(1.0f) { }
  
  pinch_list getPinches();
  
  void setScale(float scale) { scale_ = scale; }
  void setTranslation(ofVec3f translation) { translation_ = translation; }
  
  void drawHands();
  
private:
  void drawJoint(const Leap::Vector& joint_position);
  void drawBone(const Leap::Bone& bone);
  
  Leap::Controller controller_;
  ofVec3f translation_;
  float scale_;
};

#endif