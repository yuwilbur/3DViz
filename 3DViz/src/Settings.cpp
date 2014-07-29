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

void Settings::setup() {
  stage_names_.push_back("Stage 1");
  stage_names_.push_back("Stage 2");
  stage_names_.push_back("Main Stage");
  options_.setup(stage_names_, "Stages", 20, 20, 500, 1000);
  ofAddListener(options_.choice, this, &Settings::onOptionsChoice);
}

void Settings::update() {
  options_.update();
}

void Settings::draw() {
  options_.draw();
}

void Settings::onOptionsChoice(std::string &choice) {
  // TODO get the artist name instead of just using the stage name
  ofNotifyEvent(artistSelection, choice, this);
}

void Settings::exit() {}
