//
//  OptionsButtons.h
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#ifndef ___dViz__OptionsButtons__
#define ___dViz__OptionsButtons__

#include <iostream>
#include <string.h>
#include "ofMain.h"
#include "MyButton.h"

class OptionsButtons {
public:
  OptionsButtons();
  
  void setup(std::vector<string> options, std::string label, int x, int y, int w, int h);
  void update();
  void draw();
  void exit();
  
  void onClick(std::string &clicked_button_label);
  
  ofEvent<std::string> choice;
  
private:
  std::string label_;
  int x_, y_, w_, h_;
  int padding_ = 5;
  int font_h_ = 9;
  ofRectangle rect_;
  std::vector<MyButton*> buttons_;
};


#endif /* defined(___dViz__OptionsButtons__) */
