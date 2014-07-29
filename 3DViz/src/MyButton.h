//
//  Button.h
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#ifndef ___dViz__MyButton__
#define ___dViz__MyButton__

#define MYBUTTON_FONT_H 9

#include <iostream>
#include <string.h>
#include "ofMain.h"

class MyButton {
public:
  MyButton();
  
  void setup(std::string label, int x, int y, int w, int h);
  void update();
  void draw();
  void exit();
  
  ofEvent<std::string> click;
  void mouseReleased(ofMouseEventArgs &m);
  
private:
  std::string label_;
  int x_, y_, w_, h_;
  int padding_ = 5;
  ofRectangle rect_;
};

#endif /* defined(___dViz__MyButton__) */
