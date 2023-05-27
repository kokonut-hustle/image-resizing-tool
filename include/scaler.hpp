#pragma once

#include "image_struct.hpp"

class Scaler {
public:
    virtual Image resize(const Image &img, double scaleX, double scaleY) = 0;
    virtual Image resize(const Image &img, int width, int height) = 0;
};
