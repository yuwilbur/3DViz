#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:

		void setup();
		void update();
		void draw();

		void updateColor(float& R, float& G, float& B);

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofSoundPlayer 		input_music_;

		float 				* fftSmoothed;
		float				amplitude_limit_;
		float				max_amplitude_;
		float				average_amplitude_;
		float				BG_R_;
		float				BG_G_;
		float				BG_B_;

		int nBandsToGet;
};

