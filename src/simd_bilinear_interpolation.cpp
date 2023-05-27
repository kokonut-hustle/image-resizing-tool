#include <cmath>
#include <cstring>
#include <x86intrin.h>
#include "simd_bilinear_interpolation.hpp"
#include <iostream>

Image SIMDBIScaler::resize(const Image &img, double scaleX, double scaleY) {
    int width = (img.get_width() - 1) / scaleX + 1;
    int height = (img.get_height() - 1) / scaleY + 1;

    Image rz_img(width, height, img.get_channels());

    float arr1[rz_img.get_channels()];
    float arr2[rz_img.get_channels()];
    float arr3[rz_img.get_channels()];
    float arr4[rz_img.get_channels()];

    float buffer[rz_img.get_channels()];
    float buffer1[rz_img.get_channels()];
    float buffer2[rz_img.get_channels()];

    for (int row = 0; row < rz_img.get_height(); ++row)
        // for (int channel = 0; channel < rz_img.get_channels(); ++channel)
        for (int col = 0; col < rz_img.get_width(); ++col) {
            double originalX = scaleX * col;
            double originalY = scaleY * row;

            std::pair<int, int> P1 = {std::max(0.0, floor(originalX)), std::max(0.0, floor(originalY))};
            std::pair<int, int> P2 = {std::min(ceil(originalX), img.get_width()-1.0), std::max(0.0, floor(originalY))};
            std::pair<int, int> P3 = {std::max(0.0, floor(originalX)), std::min(ceil(originalY), img.get_height()-1.0)};
            std::pair<int, int> P4 = {std::min(ceil(originalX), img.get_width()-1.0), std::min(ceil(originalY), img.get_height()-1.0)};

            double u = originalX - floor(originalX);
            double v = originalY - floor(originalY);
            const uint8_t *const img_ptr = img.get_data();

            for (int channel = 0; channel < rz_img.get_channels(); ++channel) {
                arr1[channel] = (1-u) * img_ptr[img.get_channels() * (P1.second * img.get_width() + P1.first) + channel];
                arr2[channel] = u * img_ptr[img.get_channels() * (P2.second * img.get_width() + P2.first) + channel];
                arr3[channel] = (1-u) * img_ptr[img.get_channels() * (P3.second * img.get_width() + P3.first) + channel];
                arr4[channel] = u * img_ptr[img.get_channels() * (P4.second * img.get_width() + P4.first) + channel];
            }

            __m128 vec1 = _mm_loadu_ps(arr1);
            __m128 vec2 = _mm_loadu_ps(arr2);
            __m128 vec3 = _mm_loadu_ps(arr3);
            __m128 vec4 = _mm_loadu_ps(arr4);

            __m128 vecI1 = _mm_add_ps(vec1, vec2);
            __m128 vecI2 = _mm_add_ps(vec3, vec4);

            _mm_storeu_ps(buffer1, vecI1);
            _mm_storeu_ps(buffer2, vecI2);

            size_t index = rz_img.get_channels() * (row * rz_img.get_width() + col);
            for (int channel = 0; channel < rz_img.get_channels(); ++channel) {
                buffer1[channel] *= (1-v);
                buffer2[channel] *= v;
                rz_img.get_data()[index+channel] = (uint8_t)(buffer1[channel] + buffer2[channel]);
            }
        }
    return rz_img;
}

Image SIMDBIScaler::resize(const Image &img, int width, int height) {
    double scaleX = (double) (img.get_width()-1) / (width-1);
    double scaleY = (double) (img.get_height()-1) / (height-1);

    return resize(img, scaleX, scaleY);
}
