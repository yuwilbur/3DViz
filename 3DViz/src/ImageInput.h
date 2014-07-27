//
//  ImageInput.h
//  3dViz
//
//  Created by Noura Howell on 7/26/14.
//
//

#ifndef IMAGE_INPUT_H
#define IMAGE_INPUT_H

#include <iostream>
#include <string.h>
#include "ofMain.h"

class ImageInput {
public:
    ImageInput();
    
    void setup(std::string artist_name);
    void update_draw_hack();
    
    ofTexture color;
    
private:

    std::string str_filename_;
    ofImage of_img_;
    ofxCvColorImage cv_color_img_;
    ofxCvGrayscaleImage cv_grayscale_img_;
    ofxCvContourFinder cv_contour_finder_;
    
    ofTexture grayscale;
    ofTexture contours;
    
    bool drawn_;

};


#endif
