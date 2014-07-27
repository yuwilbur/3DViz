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
    //ofPushStyle();
    // TODO get an image related to artist_name
    str_filename_ = "boards_of_canada.jpg";
    of_img_.loadImage(str_filename_);
    color = of_img_.getTextureReference();
    
    /*
    int w = of_img_.getWidth();
    int h = of_img_.getHeight();
    cv_color_img_.allocate(w, h);
    cv_grayscale_img_.allocate(w, h);
    
    cv_color_img_.setFromPixels(of_img_.getPixelsRef());
    cv_grayscale_img_.setFromPixels(of_img_.getPixelsRef());
    cv_grayscale_img_.draw(0, 0);
    
    grayscale = cv_grayscale_img_.getTextureReference();

    //cv_contour_finder_.findContours(cv_grayscale_img_, 20, w+h, 10, true);
    //cv_contour_finder_.draw();

    contours.allocate(w, h, GL_RGB);
     */
}

/*
void ImageInput::update_draw_hack() {
    if (drawn_) {
        return;
    }
    glPushMatrix();
    ofSetColor(255, 255, 0);
    ofFill();
    ofRect(400, 50, 50, 50);
    contours.loadScreenData(400, 50, 100, 100);
    glPopMatrix();
    drawn_ = true;
}*/

