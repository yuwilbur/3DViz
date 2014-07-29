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
  }
}

std::string Settings::findArtist() {
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  //ofNotifyEvent(artistSelection, selected_->name, this);
  // TODO actually find the artist for that stage at that time
  artist_name_ = "Amon Tobin";
  
  std::string stage = selected_->name;
  
  // get the time
  int weekday = ofGetWeekday(); // Mon = 1, Tues = 2, etc
  int hours = ofGetHours();
  int minutes = ofGetMinutes();
  
  // force the time to be within the festival
  if (weekday < 5) {
    weekday = 6; // default to Saturday when the best shows are
  }
  
  if (weekday == 5) { // Friday
    if (stage == "Lands End") {
      
    } else if (stage == "Sutro") {
      
    } else if (stage == "Twin Peaks") {
      
    } else if (stage == "Panhandle") {
      
    } else if (stage == "House") {
      
    } else if (stage == "Barbary") {
      
    }
  } else if (weekday == 6) { // Saturday
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

  cout << "****************************************************************************************************" << endl;

}

void Settings::exit() {
  ofAddListener(ofEvents().mouseReleased, this, &Settings::onClick);
}
