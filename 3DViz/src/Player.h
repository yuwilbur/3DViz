//
//  Player.h
//  3dViz
//
//  Created by Noura Howell on 7/28/14.
//
//

#ifndef ___dViz__Player__
#define ___dViz__Player__

#include <iostream>

#pragma once

#include "ofMain.h"
#include "Leap.h"
#include "HandController.h"
#include "ParticleSystem.h"
#include "AudioPlayer.h"

class Player {
    
public:
  void setup(std::string artist_name);
  void update();
  void draw();
  void drawBone(Leap::Bone bone);
  void changeArtist(std::string artist_name);
  
  void exit();
  
private:
  ofEasyCam cam;
  ofLight l1;
  ofLight l2;
  ofMaterial m1;
  ofCylinderPrimitive cylinder_;
  
  HandController hand_controller_;
  ParticleSystem particle_system_;
  AudioPlayer audio_player_;
  
  ofColor current_color_;
  ofColor amped_color_;
};


#endif /* defined(___dViz__Player__) */
