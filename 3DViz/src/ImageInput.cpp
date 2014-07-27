//
//  ImageInput.cpp
//  3dViz
//
//  Created by Noura Howell on 7/26/14.
//
//

#include "ImageInput.h"

ImageInput::ImageInput() {}

ofTexture& ImageInput::image(std::string filename) {
    filename_ = filename;
    image_.loadImage(filename);
    return image_.getTextureReference();
}

