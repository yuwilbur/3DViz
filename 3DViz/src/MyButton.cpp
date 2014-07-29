//
//  Button.cpp
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#include "MyButton.h"

MyButton::MyButton() {}

void MyButton::setup(std::string label, int x, int y, int w, int h) {
  label_ = label;
  x_ = x;
  y_ = y;
  w_ = w;
  h_ = h;
  
  rect_.set(x_, y_, w_, h_);
  
  ofAddListener(ofEvents().mouseReleased, this, &MyButton::mouseReleased);
}

void MyButton::update() {

}

void MyButton::draw() {
  ofPushStyle();
  ofSetColor(0, 0, 0);
  ofFill();
  ofRect(x_, y_, w_, h_);
  ofSetColor(255, 255, 255);
  ofDrawBitmapString(label_, x_ + padding_, y_ + h_/2 + MYBUTTON_FONT_H/2);
  ofPopStyle();
}

void MyButton::mouseReleased(ofMouseEventArgs &m) {
  if (!rect_.inside(m.x, m.y)) {
    return;
  }
  ofNotifyEvent(click, label_, this);
}

void MyButton::exit() {
  ofRemoveListener(ofEvents().mouseReleased, this, &MyButton::mouseReleased);
}