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

struct stage {
  std::string name;
  int x;
  int y;
};

class Settings {
public:
  Settings();
  
  void setup();
  void update();
  void draw();
  void exit();
  
  void onClick(ofMouseEventArgs &m);
  std::string findArtist();
  
  ofEvent<std::string> artistSelection;
  
private:
  int r_, dx_, dy_;
  std::string artist_name_;
  std::vector<stage> stages_;
  stage* selected_;
  ofImage map_;
};

#endif /* defined(___dViz__Settings__) */
