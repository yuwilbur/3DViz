//
//  AudioPlayer.cpp
//  3dViz
//
//  Created by Matthew Tytel on 7/27/14.
//
//

#include "AudioPlayer.h"


//--------------------------------------------------------------
void AudioPlayer::setup() {
  bass_amplitude_ = 0.0;
	// load in sounds:
	input_music_.loadSound("sounds/Journeyman.mp3");
	input_music_.play();
  input_music_.setLoop(true);
  
  // input_music_.setPosition(0.2);
  
	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
  
	amplitude_limit_ = 500.0f;
	average_amplitude_ = 0.0f;
	prev_average_amplitude_ = 0.0f;
	nBandsToGet = 512;
	BG_R_ = 255;
	BG_G_ = 0;
	BG_B_ = 0;
}


//--------------------------------------------------------------
void AudioPlayer::update(){
	// update the sound playing system:
	ofSoundUpdate();
	// (5) grab the fft, and put in into a "smoothed" array,
	//		by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.96f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
		
	}
  
	updateColor(BG_R_, BG_G_, BG_B_);
	float BG_R = BG_R_;
	float BG_G = BG_G_;
	float BG_B = BG_B_;
	amplifyColor(BG_R, BG_G, BG_B);
  
	ofBackground(BG_R,BG_G,BG_B);
}

void AudioPlayer::updateColor(float& R, float& G, float& B) {
	
	float spectrum_increment = 0.25f;
  
	if (R >= 255 && G < 255 && B <= 0) {
		G += spectrum_increment; // 255,0,0 -> 255,255,0
	} else if (R > 0 && G >= 255 && B <= 0) {
		R -= spectrum_increment; // 255,255,0 -> 0,255,0
	} else if (R >= 0 && G >= 255 && B < 255) {
		B += spectrum_increment; // 0,255,0 -> 0,255,255
	} else if (R >= 0 && G > 0 && B >= 255) {
		G -= spectrum_increment; // 0,255,255 -> 0,0,255
	} else if (R < 255 && G <= 0 && B >= 255) {
		R += spectrum_increment; // 0,0,255 -> 255,0,255
	} else if (R >= 255 && G <= 0 && B > 0) {
		B -= spectrum_increment; // 255,0,255 -> 255,0,0
	}
}

void AudioPlayer::updateColor(ofColor& color) {
	int max_value = 255;
  int spectrum_increment = std::max<int>(1, std::min<int>(64 ,max_hf_amplitude_ / 10));
  float hue_increment = std::max(0.0005f, (max_hf_amplitude_*5 - bass_amplitude_) / 1000);
  std::cout << hue_increment << std::endl;
  int R = (int)color.r;
  int G = (int)color.g;
  int B = (int)color.b;
	if (R >= max_value && G < max_value && B <= 0) {
		G += spectrum_increment; // 255,0,0 -> 255,255,0
	} else if (R > 0 && G >= max_value && B <= 0) {
		R -= spectrum_increment; // 255,255,0 -> 0,255,0
	} else if (R >= 0 && G >= max_value && B < max_value) {
		B += spectrum_increment; // 0,255,0 -> 0,255,255
	} else if (R >= 0 && G > 0 && B >= max_value) {
		G -= spectrum_increment; // 0,255,255 -> 0,0,255
	} else if (R < max_value && G <= 0 && B >= max_value) {
		R += spectrum_increment; // 0,0,255 -> 255,0,255
	} else if (R >= max_value && G <= 0 && B > 0) {
		B -= spectrum_increment; // 255,0,255 -> 255,0,0
	}
  //color.r = std::min<unsigned char>(255,std::max<int>(0,R));
  //color.g = std::min<unsigned char>(255,std::max<int>(0,G));
  //color.b = std::min<unsigned char>(255,std::max<int>(0,B));
  color.setHue(color.getHue() + hue_increment);
  
  std::cout << (int)color.r << " " << (int)color.g << " " << (int)color.b << std::endl;
}

void AudioPlayer::amplifyColor(float& R, float& G, float& B) {
	float amplitude_ratio = average_amplitude_ / amplitude_limit_ * 4;
	amplitude_ratio = std::min(1.0f, std::max(0.1f, amplitude_ratio));
  
	float amplitude_offset = max_amplitude_ / amplitude_limit_ * 255;
  
	R = std::max(0.0f, std::min(255.0f, R * amplitude_ratio + amplitude_offset));
	G = std::max(0.0f, std::min(255.0f, G * amplitude_ratio + amplitude_offset));
	B = std::max(0.0f, std::min(255.0f, B * amplitude_ratio + amplitude_offset));
}

void AudioPlayer::amplifyColor(ofColor& color) {
  float max_value = 255.0f;
	float amplitude_ratio = average_amplitude_ / amplitude_limit_ * 4;
	amplitude_ratio = std::min(1.0f, std::max(0.1f, amplitude_ratio));
  
	float amplitude_offset = max_amplitude_ / amplitude_limit_ * max_value/8;
  
  float R = color.r;
  float G = color.g;
  float B = color.b;
	R = std::max(0.0f, std::min(max_value, R * amplitude_ratio + amplitude_offset));
	G = std::max(0.0f, std::min(max_value, G * amplitude_ratio + amplitude_offset));
	B = std::max(0.0f, std::min(max_value, B * amplitude_ratio + amplitude_offset));
  color.r = (unsigned char)R;
  color.g = (unsigned char)G;
  color.b = (unsigned char)B;
}

//--------------------------------------------------------------
void AudioPlayer::draw(){
  static const int bass_bands = 10;
  bass_amplitude_ = 0.0;
  
	float total_width = ofGetWidth();
	float width = std::min(10.0f, (float)(total_width) / nBandsToGet);
	max_amplitude_ = 0;
	int num_useful_amplitudes = 0;
  int num_hf_amplitudes = 0;
	prev_average_amplitude_ = average_amplitude_;
	average_amplitude_ = 0;
  hf_amplitude_ = 0;
  max_hf_amplitude_ = 0;
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		float amplitude = fftSmoothed[i] * 200;
    if (i < bass_bands)
      bass_amplitude_ += amplitude / 5120.0;
    else
      max_hf_amplitude_ = std::max(amplitude, max_hf_amplitude_);
		amplitude = std::min(amplitude, amplitude_limit_);
    float visual_amplitude = amplitude * 1.5;
    int outline_color = std::min<int>(128,fftSmoothed[i] * 60 + bass_amplitude_ * 250);
    ofSetColor(outline_color);
    float ratio = 1.5;
    float outline_height = visual_amplitude*ratio;
		ofRect(ofGetWidth()/2+i*width,ofGetHeight()/2-outline_height/2,width,outline_height);
    ofRect(ofGetWidth()/2-i*width,ofGetHeight()/2-outline_height/2,-width,outline_height);
    ofSetColor(0,0,0,255);
		ofRect(ofGetWidth()/2+i*width,ofGetHeight()/2-visual_amplitude/2,width,visual_amplitude);
    ofRect(ofGetWidth()/2-i*width,ofGetHeight()/2-visual_amplitude/2,-width,visual_amplitude);
		max_amplitude_ = std::max(max_amplitude_, amplitude);
		
		if (amplitude> 10.0f) {
      if (i >= bass_bands) {
        hf_amplitude_ += amplitude;
        num_hf_amplitudes++;
      }
			average_amplitude_ += amplitude;
			num_useful_amplitudes++;
		}
	}
	if (num_useful_amplitudes > 0) {
		average_amplitude_ /= num_useful_amplitudes;
	}
  if (num_hf_amplitudes > 0) {
    hf_amplitude_ /= num_hf_amplitudes;
  }
  bass_amplitude_ *= bass_amplitude_;
}
