#include <cmath>
#include "nearest_neighbor.hpp"
#include "utils.hpp"

Image NNScaler::resize(const Image &img, double scaleX, double scaleY) {
    int width = (img.get_width() - 1) / scaleX + 1;
    int height = (img.get_height() - 1) / scaleY + 1;
    int ori_width = img.get_width();
    int ori_height = img.get_height();

    Image rz_img(width, height, img.get_channels());
    std::vector<std::pair<int, int>> vp;

    for (int row = 0; row < rz_img.get_height(); ++row)
        for (int col = 0; col < rz_img.get_width(); ++col) {
            double originalX = scaleX * col;
            double originalY = scaleY * row;

            get_nearest_pxls(vp, originalX, originalY, ori_width, ori_height);

            double u = originalX - floor(originalX);
            double v = originalY - floor(originalY);

            int index = get_nearest_index(u, v);

            for (int channel = 0; channel < rz_img.get_channels(); ++channel)
                rz_img.get_data()[rz_img.get_channels() * (row * rz_img.get_width() + col) + channel] =
                    img.get_data()[img.get_channels() * (vp[index].second * img.get_width() + vp[index].first) + channel];

            vp.clear();
        }
    return rz_img;
}

Image NNScaler::resize(const Image &img, int width, int height) {
    double scaleX = (double) (img.get_width()-1) / (width-1);
    double scaleY = (double) (img.get_height()-1) / (height-1);

    return resize(img, scaleX, scaleY);
}
