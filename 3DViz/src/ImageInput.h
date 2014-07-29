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
    void changeArtist(std::string artist_name);
  
    ofTexture color;
    
private:

    std::string str_filename_;
    ofImage of_img_;
    
    ofTexture grayscale;
    ofTexture contours;
    
    bool drawn_;

};


#endif
