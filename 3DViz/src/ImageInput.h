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
  
    ofImage of_img_;
    ofTexture color;
  
    std::string str_filename_;

};


#endif
