#include <iostream>
#include <constants.hpp>
#include "image_struct.hpp"
#include "bilinear_interpolation.hpp"
#include "simd_bilinear_interpolation.hpp"

int main(int argc, char *argv[]) {
    Image img;
    Image_load(&img, "image/test.jpg");

    std::cout << "Loaded image with a width of " << img.get_width() << " dpx, a height of "
                << img.get_height() << " dpx and " << img.get_channels() << " channels" << std::endl;

    Scaler *s = new SIMDBIScaler();
    Image rz_img = s->resize(img, img.get_width()*3, img.get_height()*2);

    Image_save(&rz_img, "image/resized_img.png");

    Image_free(&img);
    Image_free(&rz_img);

    return 0;
}
