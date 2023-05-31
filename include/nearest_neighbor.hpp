#pragma once

#include "scaler.hpp"

class NNScaler : public Scaler {
public:
    Image resize(const Image &img, double scaleX, double scaleY);
    Image resize(const Image &img, int width, int height);
};
