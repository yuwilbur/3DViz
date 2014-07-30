//
//  Setup.cpp
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#include "Settings.h"

Settings::Settings() :
  r_(50), dx_(100), dy_(50) {
  artist_name_ = "";
  selected_ = NULL;
  ofAddListener(ofEvents().keyReleased, this, &Settings::keyReleased);
}

void Settings::setup() {
  selected_ = NULL;
  stage stages[] = {
    {"Lands End", dx_ - 25, dy_ + 175}, // 0
    {"Sutro", dx_ + 180, dy_ + 475},    // 1
    {"Barbary", dx_ + 525, dy_ + 515},  // 2
    {"Panhandle", dx_ + 845, dy_ + 475},// 3
    {"Twin Peaks", dx_ + 995, dy_ + 475},// 4
    {"House", dx_ + 626, dy_ + 215} };  // 5

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
  
  ofSetColor(0, 0, 0, 255);
  ofDrawBitmapString("1", stages_[0].x, stages_[0].y);
    ofDrawBitmapString("2", stages_[1].x, stages_[1].y);
    ofDrawBitmapString("3", stages_[2].x, stages_[2].y);
    ofDrawBitmapString("4", stages_[3].x, stages_[3].y);
    ofDrawBitmapString("5", stages_[4].x, stages_[4].y);
    ofDrawBitmapString("6", stages_[5].x, stages_[5].y);
  
  ofDrawBitmapString("1 " + stages_[0].name, 50, 800);
  ofDrawBitmapString("2 " + stages_[1].name, 50, 775);
  ofDrawBitmapString("3 " + stages_[2].name, 50, 750);
  ofDrawBitmapString("4 " + stages_[3].name, 50, 725);
  ofDrawBitmapString("5 " + stages_[4].name, 50, 700);
  ofDrawBitmapString("6 " + stages_[5].name, 50, 675);
  ofDrawBitmapString("x Cancel", 50, 650);
  
  ofEnableLighting();
  ofPopStyle();
}

void Settings::keyReleased(ofKeyEventArgs &e) {
  int n = e.key - 48;
  if (n >= 1 && n <= 6) {
    selected_ = &stages_[n];
    artist_name_ = findArtist();
    cout << "**************************************************************************************" << endl;
    cout << "ARTIST " << artist_name_ << endl;
    ofNotifyEvent(artistSelection, artist_name_, this);
  }
  /*
  std::cout << "CLICK" << std::endl;
  for (vector<stage>::iterator it = stages_.begin(); it != stages_.end(); it++) {
    if (ofDist(m.x, m.y, it->x, it->y) < r_) {
      if (selected_ != NULL && selected_->name == it->name) {
        artist_name_ = findArtist();
        cout << "ARTIST " << artist_name_ << endl;
        selected_ = NULL;
        ofNotifyEvent(artistSelection, artist_name_, this);
      } else {
        selected_ = &(*it);
      }
    }
  }*/
}

std::string Settings::findArtist() {
  // TODO actually find the artist for that stage at that time
  artist_name_ = "Amon Tobin";
  
  std::string stage = selected_->name;
  
  // get the time
  int weekday = ofGetWeekday(); // Mon = 1, Tues = 2, etc
  int hours = ofGetHours();
  int minutes = ofGetMinutes();
  
  // force the time to be within the festival
  if (weekday < 5) {
    weekday = 5; // default to Friday
  }
  
  if (weekday == 6) { // Saturday
    if (stage == "Lands End") {
      
    } else if (stage == "Sutro") {
      
    } else if (stage == "Twin Peaks") {
      
    } else if (stage == "Panhandle") {
      
    } else if (stage == "House") {
      
    } else if (stage == "Barbary") {
      
    }
  } else if (weekday == 5) { // Friday
    if (stage == "Lands End") {
      if (hours < 14) {
        return "The Soul Rebels";
      } else if (hours < 15 && minutes < 20) {
        return "Run the Jewels";
      } else if (hours < 5) {
        return "Holy Ghost";
      } else if (hours < 18 && minutes < 20) {
        return "Chromeo";
      } else if (hours < 20) {
        return "Disclosure";
      } else {
        return "Kanye West";
      }
    } else if (stage == "Sutro") {
      if (hours < 13) {
        return "Rayland Baxter";
      } else if (hours < 15 && minutes < 20) {
        return "Greensky Bluegrass";
      } else if (hours < 16) {
        return "Phosphorescent";
      } else if (hours < 17 && minutes < 20) {
        return "Nicki Bluhm and the Gramblers";
      } else if (hours < 19) {
        return "Kacey Musgraves";
      } else {
        return "Tedeschi Trucks Band";
      }
    } else if (stage == "Twin Peaks") {
      if (hours < 14) {
        return "AER";
      } else if (hours < 15) {
        return "Bleachers";
      } else if (hours < 17) {
        return "WarPaint";
      } else if (hours < 19 && minutes < 30) {
        return "Grouplove";
      } else if (hours < 20) {
        return "Tegan & Sara";
      } else {
        return "Arctic Monkeys";
      }
    } else if (stage == "Panhandle") {
      if (hours < 13) {
        return "Night Terrors of 1927";
      } else if (hours < 15 && minutes < 30) {
        return "USPS Janis Joplin Tribute Featuring Special Guests";
      } else if (hours < 16) {
        return "Nahko and Medicine for the People";
      } else if (hours < 18) {
        return "Mikal Cronin";
      } else if (hours < 19) {
        return "Bear Hands";
      } else {
        return "Typhoon";
      }
    } else if (stage == "House") {
      if (hours < 14 && minutes < 30) {
        return "Shouts!";
      } else if (hours < 15) {
        return "DJ Dials";
      } else if (hours < 17 && minutes < 30) {
        return "Motion Potion";
      } else if (hours < 18) {
        return "Paul Johnson";
      } else {
        return "DJ Icey";
      }
    } else if (stage == "Barbary") {
      if (hours < 14) {
        return "Garfunkel & Oates and Aparna Nancherla";
      } else if (hours < 16) {
        return "Aisha Tyler, Ali Mafi and Matt McArthy";
      } else if (hours < 18) {
        return "Lewis Black, Rory Albanese and Aparna Nancherla";
      } else {
        return "Garfunkel & Oates and Aparna Nancherla";
      }
    }
  } else { // Sunday
    if (stage == "Lands End") {
      
    } else if (stage == "Sutro") {
      
    } else if (stage == "Twin Peaks") {
      
    } else if (stage == "Panhandle") {
      
    } else if (stage == "House") {
      
    } else if (stage == "Barbary") {
      
    }
    
  }

}

void Settings::exit() {
    ofRemoveListener(ofEvents().keyReleased, this, &Settings::keyReleased);
}
