#pragma once

#include "scaler.hpp"

class BIScaler : public Scaler {
public:
    Image resize(const Image &img, double scaleX, double scaleY);
    Image resize(const Image &img, int width, int height);
};
