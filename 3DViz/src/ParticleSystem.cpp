//
//  ParticleSystem.cpp
//  3dViz
//
//  Created by Matthew Tytel on 7/26/14.
//
//

#include "ParticleSystem.h"

//--------------------------------------------------------------
void ParticleSystem::setup(ofVec3f cent, ofVec3f dimen, std::string artist_name){
  interpolation_ = 1.0;
  textures_.setup(artist_name);

  bass_amplitude_ = 0.0;
  dc_filtered_bass_ = 0.0;

  center = cent;
  dimensions = dimen;
  color_ = ofColor(1, 0, 0, 1);
  
  gravity_strength = 0.0;
  gravity_position = ofVec3f::zero();
  
  gravity_strength2 = 0.0;
  gravity_position2 = ofVec3f::zero();
  particleSize = 0.9f;
  timeStep = 0.005f;
  numParticles = 500000;
  
  // Width and Heigth of the windows
  width = ofGetWindowWidth();
  height = ofGetWindowHeight();
  
  string shadersFolder;
  if(ofGetGLProgrammableRenderer()){
    shadersFolder="shaders_programmable";
  }else{
    shadersFolder="shaders";
  }
  
  // Loading the Shaders
  updatePos.load("",shadersFolder+"/posUpdate.frag");// shader for updating the texture that store the particles position on RG channels
  updateVel.load("",shadersFolder+"/velUpdate.frag");// shader for updating the texture that store the particles velocity on RG channels
  
  // Frag, Vert and Geo shaders for the rendering process of the spark image
  updateRender.setGeometryInputType(GL_POINTS);
  updateRender.setGeometryOutputType(GL_TRIANGLE_STRIP);
  updateRender.setGeometryOutputCount(6);
  updateRender.load(shadersFolder+"/render.vert",shadersFolder+"/render.frag",shadersFolder+"/render.geom");
  
  // Seting the textures where the information ( position and velocity ) will be
  textureRes = (int)sqrt((float)numParticles);
  numParticles = textureRes * textureRes;
  
  // 1. Making arrays of float pixels with position information
  float * resting_pos = new float[numParticles*3];
  float * pos = new float[numParticles*3];
  for (int x = 0; x < textureRes; x++){
    for (int y = 0; y < textureRes; y++){
      int i = textureRes * y + x;
      resting_pos[i*3 + 0] = pos[i*3 + 0] = ofRandom(-dimensions.x, dimensions.x);
      resting_pos[i*3 + 1] = pos[i*3 + 1] = ofRandom(-dimensions.y, dimensions.y);
      resting_pos[i*3 + 2] = pos[i*3 + 2] = ofRandom(-dimensions.z, dimensions.z);
    }
  }
  // Load this information in to the FBOÔøΩs texture
  posPingPong.allocate(textureRes, textureRes,GL_RGB32F);
  posPingPong.src->getTextureReference().loadData(pos, textureRes, textureRes, GL_RGB);
  posPingPong.dst->getTextureReference().loadData(pos, textureRes, textureRes, GL_RGB);
  
  restingPos.allocate(textureRes, textureRes,GL_RGB32F);
  restingPos.src->getTextureReference().loadData(resting_pos, textureRes, textureRes, GL_RGB);
  restingPos.dst->getTextureReference().loadData(resting_pos, textureRes, textureRes, GL_RGB);
  delete [] pos;    // Delete the array
  delete [] resting_pos;    // Delete the array
  
  
  // 2. Making arrays of float pixels with velocity information and the load it to a texture
  float * vel = new float[numParticles*3];
  for (int i = 0; i < numParticles; i++){
    vel[i*3 + 0] = ofRandom(0, 0);
    vel[i*3 + 1] = ofRandom(0, 0);
    vel[i*3 + 2] = ofRandom(-100.0, 100.0);
  }
  // Load this information in to the FBOÔøΩs texture
  velPingPong.allocate(textureRes, textureRes,GL_RGB32F);
  velPingPong.src->getTextureReference().loadData(vel, textureRes, textureRes, GL_RGB);
  velPingPong.dst->getTextureReference().loadData(vel, textureRes, textureRes, GL_RGB);
  delete [] vel; // Delete the array
  
  // Loading and setings of the variables of the textures of the particles
  sparkImg.loadImage("spark.png");
  imgWidth = sparkImg.getWidth();
  imgHeight = sparkImg.getHeight();
  
  // Allocate the final
  renderFBO.allocate(width, height, GL_RGB32F);
  renderFBO.begin();
  ofClear(0, 0, 0, 255);
  renderFBO.end();
  
  
  mesh.setMode(OF_PRIMITIVE_POINTS);
  for(int x = 0; x < textureRes; x++){
    for(int y = 0; y < textureRes; y++){
      mesh.addVertex(ofVec3f(x,y));
      mesh.addTexCoord(ofVec2f(x, y));
    }
  }
}

void ParticleSystem::changeArtist(std::string artist_name) {
  textures_.changeArtist(artist_name);
  interpolation_ = 1.0f;
}

//--------------------------------------------------------------
void ParticleSystem::update(){
  interpolation_ *= 0.99; //cos(inter_count_ * .01) * 0.5 + 0.5;
  // In each cycle itÔøΩs going to update the velocity first and the the position
  // Each one one with a different shader and FBO.
  // Because on GPU you canÔøΩt write over the texture that you are reading we are
  // using to pair of ofFbo attached together on what we call pingPongBuffer
  // Learn more about Ping-Pong at:
  //
  // http://www.comp.nus.edu/~ashwinna/docs/PingPong_FBO.pdf
  // http://www.seas.upenn.edu/~cis565/fbo.htm#setupgl4
  
  // Velocities PingPong
  //
  // It calculates the next frame and see if itÔøΩs there any collition
  // then updates the velocity with that information
  //
  velPingPong.dst->begin();
  ofClear(0);
  updateVel.begin();
  updateVel.setUniformTexture("backbuffer", velPingPong.src->getTextureReference(), 0);   // passing the previus velocity information
  updateVel.setUniformTexture("posData", posPingPong.src->getTextureReference(), 1);  // passing the position information
  updateVel.setUniformTexture("restingPosData", restingPos.src->getTextureReference(), 2);
  updateVel.setUniform1i("resolution", (int)textureRes);
  updateVel.setUniform2f("screen", (float)width, (float)height);
  updateVel.setUniform1f("timestep", (float)timeStep);
  updateVel.setUniform3f("gravity_position", gravity_position.x,
                                             gravity_position.y,
                                             gravity_position.z);
  updateVel.setUniform1f("gravity_strength", gravity_strength);
  updateVel.setUniform3f("gravity_position2", gravity_position2.x,
                                              gravity_position2.y,
                                              gravity_position2.z);
  updateVel.setUniform1f("gravity_strength2", gravity_strength2);
  
  // draw the source velocity texture to be updated
  velPingPong.src->draw(0, 0);
  
  updateVel.end();
  velPingPong.dst->end();
  
  velPingPong.swap();
  
  // Positions PingPong
  //
  // With the velocity calculated updates the position
  //
  posPingPong.dst->begin();
  ofClear(0);
  updatePos.begin();
  updatePos.setUniformTexture("prevPosData", posPingPong.src->getTextureReference(), 0); // Previus position
  updatePos.setUniformTexture("velData", velPingPong.src->getTextureReference(), 1);  // Velocity
  updatePos.setUniform1f("timestep",(float) timeStep );
  updatePos.setUniform1f("pulse", dc_filtered_bass_ + 0.05);
  
  // draw the source position texture to be updated
  posPingPong.src->draw(0, 0);
  
  updatePos.end();
  posPingPong.dst->end();
  
  posPingPong.swap();
  
  // Rendering
  //
  // 1.   Sending this vertex to the Vertex Shader.
  //      Each one itÔøΩs draw exactly on the position that match where itÔøΩs stored on both vel and pos textures
  //      So on the Vertex Shader (thatÔøΩs is first at the pipeline) can search for it information and move it
  //      to it right position.
  // 2.   Once itÔøΩs in the right place the Geometry Shader make 6 more vertex in order to make a billboard
  // 3.   that then on the Fragment Shader itÔøΩs going to be filled with the pixels of sparkImg texture
  //
  renderFBO.begin();
  ofClear(0,0,0,0);
  updateRender.begin();
  updateRender.setUniformTexture("posTex", posPingPong.dst->getTextureReference(), 0);
  updateRender.setUniformTexture("sparkTex", sparkImg.getTextureReference() , 1);
  updateRender.setUniform1i("resolution", (float)textureRes);
  updateRender.setUniform2f("screen", (float)width, (float)height);
  updateRender.setUniform1f("size", (float)particleSize);
  updateRender.setUniform1f("imgWidth", (float)sparkImg.getWidth());
  updateRender.setUniform1f("imgHeight", (float)sparkImg.getHeight());
  
  ofPushStyle();
  ofEnableBlendMode( OF_BLENDMODE_ADD );
  ofSetColor(255);
  
  mesh.draw();
  
  ofDisableBlendMode();
  glEnd();
  
  updateRender.end();
  renderFBO.end();
  ofPopStyle();
}

void ParticleSystem::setGravity(ofVec3f position, float strength) {
  gravity_position = position;
  gravity_strength = strength;
}

void ParticleSystem::setGravity2(ofVec3f position, float strength) {
  gravity_position2 = position;
  gravity_strength2 = strength;
}


//--------------------------------------------------------------
void ParticleSystem::draw(){
  // ofBackground(0);
  static const float min_color = 10.0f;
  
  updateRender.begin();
  updateRender.setUniformTexture("posTex", posPingPong.dst->getTextureReference(), 0);
  updateRender.setUniformTexture("sparkTex", sparkImg.getTextureReference() , 1);
  updateRender.setUniformTexture("albumArt", textures_.color, 2);

  float r = std::max<float>(color_.r, min_color);
  float g = std::max<float>(color_.g, min_color);
  float b = std::max<float>(color_.b, min_color);
  updateRender.setUniform4f("color", r, g, b, 255.0f);
  updateRender.setUniform1i("resolution", (float)textureRes);
  updateRender.setUniform2f("screen", (float)width, (float)height);
  updateRender.setUniform1f("size", (float)particleSize);
  updateRender.setUniform1f("imgWidth", (float)sparkImg.getWidth());
  updateRender.setUniform1f("imgHeight", (float)sparkImg.getHeight());
  updateRender.setUniform1f("interpolation", (float)interpolation_ + bass_amplitude_ * 0.7);
  
  ofPushStyle();
  ofEnableBlendMode( OF_BLENDMODE_ADD );
  ofSetColor(255);
  
  mesh.draw();
  
  ofDisableBlendMode();
  glEnd();
  
  updateRender.end();
  ofPopStyle();
}
