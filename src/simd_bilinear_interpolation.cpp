#include <cmath>
#include <cstring>
#include <x86intrin.h>
#include "simd_bilinear_interpolation.hpp"
#include <iostream>

Image SIMDBIScaler::resize(const Image &img, double scaleX, double scaleY) {
    int width = (img.get_width() - 1) / scaleX + 1;
    int height = (img.get_height() - 1) / scaleY + 1;

    Image rz_img(width, height, img.get_channels());

    for (int row = 0; row < rz_img.get_height(); ++row)
        // for (int channel = 0; channel < rz_img.get_channels(); ++channel)
        for (int col = 0; col < rz_img.get_width(); ++col) {
            double originalX = scaleX * col;
            double originalY = scaleY * row;

            std::pair<int, int> P1 = {floor(originalX), floor(originalY)};
            std::pair<int, int> P2 = {ceil(originalX), floor(originalY)};
            std::pair<int, int> P3 = {floor(originalX), ceil(originalY)};
            std::pair<int, int> P4 = {ceil(originalX), ceil(originalY)};

            double u = originalX - floor(originalX);
            double v = originalY - floor(originalY);
            const uint8_t *const img_ptr = img.get_data();

            float arr1[rz_img.get_channels()];
            float arr2[rz_img.get_channels()];
            float arr3[rz_img.get_channels()];
            float arr4[rz_img.get_channels()];

            for (int channel = 0; channel < rz_img.get_channels(); ++channel) {
                arr1[channel] = img_ptr[img.get_channels() * (P1.second * img.get_width() + P1.first) + channel];
                arr2[channel] = img_ptr[img.get_channels() * (P2.second * img.get_width() + P2.first) + channel];
                arr3[channel] = img_ptr[img.get_channels() * (P3.second * img.get_width() + P3.first) + channel];
                arr4[channel] = img_ptr[img.get_channels() * (P4.second * img.get_width() + P4.first) + channel];
            }

            __m128 vec1 = _mm_loadu_ps(arr1);
            __m128 vec2 = _mm_loadu_ps(arr2);
            __m128 vec3 = _mm_loadu_ps(arr3);
            __m128 vec4 = _mm_loadu_ps(arr4);

            __m128 vecI11 = _mm_mul_ps(vec1, _mm_set1_ps(1-u));
            __m128 vecI12 = _mm_mul_ps(vec2, _mm_set1_ps(u));

            __m128 vecI1 = _mm_add_ps(vecI11, vecI12);

            __m128 vecI21 = _mm_mul_ps(vec3, _mm_set1_ps(1-u));
            __m128 vecI22 = _mm_mul_ps(vec4, _mm_set1_ps(u));

            __m128 vecI2 = _mm_add_ps(vecI21, vecI22);

            __m128 vecRes1 = _mm_mul_ps(vecI1, _mm_set1_ps(1-v));
            __m128 vecRes2 = _mm_mul_ps(vecI2, _mm_set1_ps(v));

            __m128 vecRes = _mm_add_ps(vecRes1, vecRes2);

            float buffer[rz_img.get_channels()];
            _mm_storeu_ps(buffer, vecRes);

            size_t index = rz_img.get_channels() * (row * rz_img.get_width() + col);
            for (int channel = 0; channel < rz_img.get_channels(); ++channel) {
                rz_img.get_data()[index+channel] = (uint8_t)buffer[channel];
            }
        }
    return rz_img;
}

Image SIMDBIScaler::resize(const Image &img, int width, int height) {
    double scaleX = (double) (img.get_width()-1) / (width-1);
    double scaleY = (double) (img.get_height()-1) / (height-1);

    return resize(img, scaleX, scaleY);
}
