//
//  OptionsButtons.cpp
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#include "OptionsButtons.h"

OptionsButtons::OptionsButtons() {}

void OptionsButtons::setup(std::vector<string> options, std::string label, int x, int y, int w, int h) {
  label_ = label;
  x_ = x;
  y_ = y;
  w_ = w;
  h_ = h;
  
  rect_.set(x_, y_, w_, h_);
  
  int y_margin = 10;
  int bh = MYBUTTON_FONT_H*2 + 10;
  int by = y_ + MYBUTTON_FONT_H + y_margin; // save room for the label up top
  
  for(std::vector<string>::iterator it = options.begin(); it != options.end(); ++it) {
    std::string s = (*it);
    MyButton *b = new MyButton();
    b->setup(s, x_, by, w_, bh);
    buttons_.push_back(b);
    ofAddListener(b->click, this, &OptionsButtons::onClick);
    by += bh + y_margin;
  }
  
}

void OptionsButtons::update() {
  
}

void OptionsButtons::draw() {
  ofPushStyle();
  ofSetColor(0, 0, 0);
  ofDrawBitmapString(label_, x_, y_);
  for(std::vector<MyButton*>::iterator it = buttons_.begin(); it != buttons_.end(); ++it) {
    (*it)->draw();
  }
  ofPopStyle();
}

void OptionsButtons::onClick(std::string& clicked_button_label) {
  ofNotifyEvent(choice, label_, this);
}

void OptionsButtons::exit() {
  for(std::vector<MyButton*>::iterator it = buttons_.begin(); it != buttons_.end(); ++it) {
    MyButton* b = (*it);
    ofRemoveListener(b->click, this, &OptionsButtons::onClick);
    delete b;
  }
}
