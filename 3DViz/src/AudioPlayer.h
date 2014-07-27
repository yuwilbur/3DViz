//
//  AudioPlayer.h
//  3dViz
//
//  Created by Matthew Tytel on 7/27/14.
//
//

#pragma once

#include "ofMain.h"

class AudioPlayer {
public:
  void setup();
  void update();
  void draw();
  
  void updateColor(float& R, float& G, float& B);
  void updateColor(ofColor& color);
  void amplifyColor(float& R, float& G, float& B);
  void amplifyColor(ofColor& color);
    
  ofSoundPlayer input_music_;
  
  float* fftSmoothed;
  float	amplitude_limit_;
  float	max_amplitude_;
  float	average_amplitude_;
  float	prev_average_amplitude_;
  float	BG_R_;
  float	BG_G_;
  float	BG_B_;
  
  int nBandsToGet;
};