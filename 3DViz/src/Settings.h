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

class Settings {
public:
  Settings();
  
  void setup();
  void update();
  void draw();
  void exit();
  
  ofEvent<std::string> artistSelection;
  
private:
  int count;
  std::string artist_name_;
  
};

#endif /* defined(___dViz__Settings__) */
