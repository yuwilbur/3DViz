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
    
    ofTexture& image(std::string filename);
    
private:

    std::string filename_;
    ofImage image_;
};


#endif
