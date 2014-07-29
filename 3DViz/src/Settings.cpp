//
//  Setup.cpp
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#include "Settings.h"

Settings::Settings() {
  artist_name_ = "";
  selected_ = NULL;
  ofAddListener(ofEvents().mouseReleased, this, &Settings::onClick);
}

void Settings::setup() {
  selected_ = NULL;
  stage stages[] = {
    {"Lands End", dx_ + 65, dy_ + 343},
    {"Sutro", dx_ + 196, dy_ + 112},
    {"Twin Peaks", dx_ + 995, dy_ + 90},
    {"Panhandle", dx_ + 845, dy_ + 98},
    {"House", dx_ + 626, dy_ + 234},
    {"Barbary", dx_ + 562, dy_ + 63} };

  stages_.push_back(stages[0]);
  stages_.push_back(stages[1]);
  stages_.push_back(stages[2]);
  stages_.push_back(stages[3]);
  stages_.push_back(stages[4]);
  stages_.push_back(stages[5]);
  
  map_.loadImage("images/map.png");
}

void Settings::update() {

}

void Settings::draw() {
  ofShowCursor();

  ofPushStyle();
  ofDisableLighting();
  ofSetColor(255, 255, 255, 255);
  ofFill();
  ofRect(0, 0, ofGetWidth(), ofGetHeight());
  ofSetColor(255, 255, 255, 255);
  map_.draw(dx_, dy_, 1099, 516);
  if (selected_) {
    ofSetColor(50, 255, 255, 125);
    ofCircle(selected_->x, selected_->y, 50);
  }
  ofEnableLighting();
  ofPopStyle();
}

void Settings::onClick(ofMouseEventArgs &m) {
  std::cout << "CLICK" << std::endl;
  for (vector<stage>::iterator it = stages_.begin(); it != stages_.end(); it++) {
    if (ofDist(m.x, m.y, it->x, it->y) < r_) {
      if (selected_ != NULL && selected_->name == it->name) {
        findArtist();
        selected_ = NULL;
      } else {
        selected_ = &(*it);
      }
    }
  }
}

void Settings::findArtist() {
  //ofNotifyEvent(artistSelection, selected_->name, this);
  // TODO actually find the artist for that stage at that time
  artist_name_ = "Amon Tobin";
  ofNotifyEvent(artistSelection, artist_name_, this);
}

void Settings::exit() {
  ofAddListener(ofEvents().mouseReleased, this, &Settings::onClick);
}
