#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	 

	// load in sounds:
	input_music_.loadSound("sounds/Journeyman.mp3");
	input_music_.play();

	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}

	amplitude_limit_ = 500.0f;
	nBandsToGet = 128;
	BG_R_ = 255;
	BG_G_ = 0;
	BG_B_ = 0;
}


//--------------------------------------------------------------
void ofApp::update(){
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
	
	float amplitude_ratio = average_amplitude_ / amplitude_limit_ * 4;
	amplitude_ratio = std::min(1.0f, std::max(0.1f, amplitude_ratio));

	float amplitude_offset = max_amplitude_ / amplitude_limit_ * 255;

	float BG_R = std::max(0.0f, std::min(255.0f, BG_R_ * amplitude_ratio + amplitude_offset));
	float BG_G = std::max(0.0f, std::min(255.0f, BG_G_ * amplitude_ratio + amplitude_offset));
	float BG_B = std::max(0.0f, std::min(255.0f, BG_B_ * amplitude_ratio + amplitude_offset));

	ofBackground(BG_R,BG_G,BG_B);
}

void ofApp::updateColor(float& R, float& G, float& B) {
	float spectrum_increment = 0.25f; 
	float spectrum_length = 255.0f / spectrum_increment;
	
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

//--------------------------------------------------------------
void ofApp::draw(){
	float total_width = ofGetWidth();
	// draw the fft resutls:
	ofSetColor(255,255,255,255); // Draw the bands white
	float width = std::min(10.0f, (float)(total_width) / nBandsToGet);
	max_amplitude_ = 0;
	int num_useful_amplitudes = 0;
	average_amplitude_ = 0;
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		float amplitude = fftSmoothed[i] * 100;
		amplitude = std::min(amplitude, amplitude_limit_);
		ofRect(0+i*width,ofGetHeight()/2-amplitude/2,width,amplitude);
		max_amplitude_ = std::max(max_amplitude_, amplitude);
		
		if (amplitude> 10.0f) {
			average_amplitude_ += amplitude;
			num_useful_amplitudes++;
		}
	}
	if (num_useful_amplitudes > 0) {
		average_amplitude_ /= num_useful_amplitudes;
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}
 
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

