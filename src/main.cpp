#include <iostream>
#include <constants.hpp>
#include "image_struct.hpp"

int main(int argc, char *argv[]) {
    Image img;
    Image_load(&img, "image/test.jpg");

    std::cout << "Loaded image with a width of " << img.width << " dpx, a height of "
                << img.height << " dpx and " << img.channels << " channels" << std::endl;
    Image_free(&img);

    return 0;
}
