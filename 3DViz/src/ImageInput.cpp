//
//  ImageInput.cpp
//  3dViz
//
//  Created by Noura Howell on 7/26/14.
//
//

#include "ImageInput.h"

ImageInput::ImageInput() : drawn_(false) {}

void ImageInput::setup(std::string artist_name) {
    // TODO get an image related to artist_name
    str_filename_ = "album_art.jpg";
    of_img_.loadImage(str_filename_);
    color = of_img_.getTextureReference();
}

void ImageInput::changeArtist(std::string artist_name) {
  of_img_.loadImage("boards_of_canada.jpg");
  color = of_img_.getTextureReference();
}


