#include "HandController.h"
#include <ofGLRenderer.h>

#define HAND_SPHERE_RADIUS 7.0f
#define HAND_SPHERE_DETAIL 32
#define HAND_CYLINDER_RADIUS 4.0f

namespace {
  
  ofMatrix4x4 GetBoneMatrix(const Leap::Bone& bone) {
    float matrix_values[16];
    bone.basis().toArray4x4(matrix_values);
    return ofMatrix4x4(matrix_values);
  }
  
  ofVec3f ToVec3f(const Leap::Vector& vector) {
    return ofVec3f(vector.x, vector.y, vector.z);
  }
}

pinch_list HandController::getPinches() {
  Leap::Frame frame = controller_.frame();
  pinch_list pinches;
  
  for (int i = 0; i < frame.hands().count(); ++i) {
    float pinch_strength = frame.hands()[i].pinchStrength();
    
    Leap::Vector tip = frame.hands()[i].fingers()[1].tipPosition();
    ofVec3f transformed_tip = scale_ * ToVec3f(tip) + translation_;
    
    pinches.push_back(std::pair<ofVec3f, float>(transformed_tip, pinch_strength));
  }
  
  return pinches;
}

void HandController::drawJoint(const Leap::Vector& joint_position) {
  static const ofColor joint_color(0, 0, 255);
  
  glPushMatrix();
  glTranslatef(joint_position.x, joint_position.y, joint_position.z);
  
  ofDrawSphere(ofVec3f::zero(), HAND_SPHERE_RADIUS);
  glPopMatrix();
}

void HandController::drawBone(const Leap::Bone& bone) {
  /*
  static const ColorA bone_color(CM_HSV, 0.5f, 0.0f, 1.0f, 0.5f);
  
  Leap::Vector midpoint = (bone.prevJoint() + bone.prevJoint()) / 2.0;
  
  glPushMatrix();
  glTranslatef(midpoint.x, midpoint.y, midpoint.z);
  glMultMatrixf(GetBoneMatrix(bone));
  glRotatef(90, -1, 0, 0);
  
  glMaterialfv(GL_FRONT, GL_DIFFUSE, bone_color);
  gl::drawCylinder(HAND_CYLINDER_RADIUS, HAND_CYLINDER_RADIUS, bone.length(), 12, 1);
  glPopMatrix();
   */
}

void HandController::drawHands() {
  glPushMatrix();
  glTranslatef(translation_.x, translation_.y, translation_.z);
  glScalef(scale_, scale_, scale_);
  
  Leap::Frame frame = controller_.frame();
  for (int h = 0; h < frame.hands().count(); ++h) {
    Leap::Hand hand = frame.hands()[h];
    
    for (int f = 0; f < hand.fingers().count(); ++f) {
      Leap::Finger finger = hand.fingers()[f];
      
      // Draw first joint inside hand.
      Leap::Bone mcp = finger.bone(Leap::Bone::TYPE_METACARPAL);
      drawJoint(mcp.prevJoint());
      
      for (int b = 0; b < 4; ++b) {
        Leap::Bone bone = finger.bone(static_cast<Leap::Bone::Type>(b));
        drawJoint(bone.nextJoint());
        drawBone(bone);
      }
    }
  }
  
  glPopMatrix();
}