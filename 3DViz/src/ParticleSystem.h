//
//  ParticleSystem.h
//  3dViz
//
//  Created by Matthew Tytel on 7/26/14.
//
//

#pragma once

#include "ofMain.h"
#include "ImageInput.h"

// Struct for doing PingPong quickly and easy
//
// Because on GPU you can´t write over the texture that you are reading we are
// using to pair of ofFbo attached together on what we call pingPongBuffer
// Learn more about Ping-Pong at:
//
// http://www.comp.nus.edu/~ashwinna/docs/PingPong_FBO.pdf
// http://www.seas.upenn.edu/~cis565/fbo.htm#setupgl4
//
struct pingPongBuffer {
public:
  void allocate( int _width, int _height, int _internalformat = GL_RGBA, float _dissipation = 1.0f){
    // Allocate
    for(int i = 0; i < 2; i++){
      FBOs[i].allocate(_width,_height, _internalformat );
      FBOs[i].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    }
    
    // Clean
    clear();
    
    // Set everything to 0
    flag = 0;
    swap();
    flag = 0;
  }
  
  void swap(){
    src = &(FBOs[(flag)%2]);
    dst = &(FBOs[++(flag)%2]);
  }
  
  void clear(){
    for(int i = 0; i < 2; i++){
      FBOs[i].begin();
      ofClear(0,255);
      FBOs[i].end();
    }
  }
  
  ofFbo& operator[]( int n ){ return FBOs[n];}
  
  ofFbo   *src;       // Source       ->  Ping
  ofFbo   *dst;       // Destination  ->  Pong
private:
  ofFbo   FBOs[2];    // Real addresses of ping/pong FBO´s
  int     flag;       // Integer for making a quick swap
};


class ParticleSystem {
public:
  void setup(ofVec3f center, ofVec3f dimensions);
  void update();
  void draw();
  
  void setGravity(ofVec3f position, float strength);
  void setGravity2(ofVec3f position, float strength);
  void setColor(ofColor color) { color_ = color; }
  void setBassAmplitude(float amp) {
    static const float radius = 0.6f;
    static const float scale = (1 + radius) / 2.0f;
    dc_filtered_bass_ = scale * (amp - bass_amplitude_) + radius * dc_filtered_bass_;
    bass_amplitude_ = amp;
  }

  void gotMessage(ofMessage msg);
  
  ofShader    updatePos;
  ofShader    updateVel;
  ofShader    updateRender;
  
  pingPongBuffer posPingPong;
  pingPongBuffer velPingPong;
  pingPongBuffer restingPos;

  ofFbo   renderFBO;
  
  ofImage sparkImg;
  
  float   timeStep;
  float   particleSize;
  
  int     width, height;
  int     imgWidth, imgHeight;
  int     numParticles;
  int     textureRes;
  
  ofVec3f gravity_position;
  float gravity_strength;
  
  ofVec3f gravity_position2;
  float gravity_strength2;
  
  ofVec3f center;
  ofVec3f dimensions;
  
  ofVboMesh mesh;
  ofColor color_;
  
  ImageInput textures_;
  
  float interpolation_;
  
  float bass_amplitude_;
  float dc_filtered_bass_;
};