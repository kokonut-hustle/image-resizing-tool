#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "image_struct.hpp"

#define LOG_ERR(cond, message) \
do { \
    if (cond) { \
        std::cerr << "Error in function: " << __func__ << " at line " << __LINE__ << std::endl; \
        std::cerr << message << std::endl; \
    } \
} while(0)

#define LOG_INF(message) \
std::clog << message << std::endl

static inline std::string get_ext(const std::string &fname) {
    std::size_t pos = fname.find_last_of('.');
    if (pos == std::string::npos)
        return "";

    return fname.substr(pos);
}

static inline void get_nearest_pxls(std::vector<std::pair<int, int>> &vp,
                                double &originalX, double &originalY,
                                int &width, int &height) {
    std::pair<int, int> P1 = {std::max(0.0, floor(originalX)), std::max(0.0, floor(originalY))};
    std::pair<int, int> P2 = {std::min(ceil(originalX), width-1.0), std::max(0.0, floor(originalY))};
    std::pair<int, int> P3 = {std::max(0.0, floor(originalX)), std::min(ceil(originalY), height-1.0)};
    std::pair<int, int> P4 = {std::min(ceil(originalX), width-1.0), std::min(ceil(originalY), height-1.0)};

    vp.push_back(P1);
    vp.push_back(P2);
    vp.push_back(P3);
    vp.push_back(P4);
}

static inline uint8_t get_nearest_value(const Image &img, const std::vector<std::pair<int, int>> &vp,
                                        double &u, double &v, int channel) {
    int index;

    if (u <= 0.5) {
        if (v <= 0.5)
            index = 0;
        else
            index = 2;
    } else {
        if (v <= 0.5)
            index = 1;
        else
            index = 3;
    }

    return img.get_data()[img.get_channels() * (vp[index].second * img.get_width() + vp[index].first) + channel];
}
