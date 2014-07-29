//
//  ImageInput.cpp
//  3dViz
//
//  Created by Noura Howell on 7/26/14.
//
//

#include "ImageInput.h"

ImageInput::ImageInput() {}

void ImageInput::setup(std::string artist_name) {
    // TODO get an image related to artist_name
  if (artist_name == "Amon Tobin") {
    str_filename_ = "images/artists/Amon Tobin.jpg";
  } else if (artist_name == "Boards of Canada") {
    str_filename_ = "images/artists/Boards of Canada.jpg";
  } else {
    str_filename_ = "images/bleep_or_die.jpg";
  }
  of_img_.loadImage(str_filename_);
  color = of_img_.getTextureReference();
}

void ImageInput::changeArtist(std::string artist_name) {
  setup(artist_name);
}


