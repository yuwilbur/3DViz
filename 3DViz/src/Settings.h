//
//  Setup.h
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#ifndef ___dViz__Settings__
#define ___dViz__Settings__

#include <iostream>
#include <string.h>
#include "ofMain.h"
#include "OptionsButtons.h"

class Settings {
public:
  Settings();
  
  void setup();
  void update();
  void draw();
  void exit();
  
  void onOptionsChoice(std::string & choice);
  
  ofEvent<std::string> artistSelection;
  
private:
  int count;
  std::string artist_name_;
  std::vector<string> stage_names_;
  OptionsButtons options_;
  
  
};

#endif /* defined(___dViz__Settings__) */
