#include <cmath>
#include "bilinear_interpolation.hpp"

Image BIScaler::resize(const Image &img, double scaleX, double scaleY) {
    int width = (img.get_width() - 1) / scaleX + 1;
    int height = (img.get_height() - 1) / scaleY + 1;

    Image rz_img(width, height, img.get_channels());

    for (int row = 0; row < rz_img.get_height(); ++row)
        for (int channel = 0; channel < rz_img.get_channels(); ++channel)
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

                uint8_t P1_value = img_ptr[img.get_channels() * (P1.second * img.get_width() + P1.first) + channel];
                uint8_t P2_value = img_ptr[img.get_channels() * (P2.second * img.get_width() + P2.first) + channel];
                uint8_t P3_value = img_ptr[img.get_channels() * (P3.second * img.get_width() + P3.first) + channel];
                uint8_t P4_value = img_ptr[img.get_channels() * (P4.second * img.get_width() + P4.first) + channel];

                double I1 = (1-u) * P1_value + u * P2_value;
                double I2 = (1-u) * P3_value + u * P4_value;

                rz_img.get_data()[rz_img.get_channels() * (row * rz_img.get_width() + col) + channel] =
                    (1-v) * I1 + v * I2;
            }
    return rz_img;
}

Image BIScaler::resize(const Image &img, int width, int height) {
    double scaleX = (double) (img.get_width()-1) / (width-1);
    double scaleY = (double) (img.get_height()-1) / (height-1);

    return resize(img, scaleX, scaleY);
}
