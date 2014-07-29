//
//  Setup.cpp
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#include "Settings.h"

Settings::Settings() {
  count = 0;
  artist_name_ = "";
}

void Settings::setup() {}

void Settings::update() {
  if (count >= 100) {
    artist_name_ = "Boards of Canada";
    ofNotifyEvent(artistSelection, artist_name_, this);
  } else {
    count += 1;
  }
}

void Settings::draw() {
  ofSetColor(0, 0, 0);
  for(int i = 0; i < count; i++) {
    ofDrawBitmapString(".", i * 2, 50);
  }
}

void Settings::exit() {}
