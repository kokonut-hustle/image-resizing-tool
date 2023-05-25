#include <iostream>
#include <constants.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

int main(int argc, char *argv[]) {
    int width, height, channels;
    unsigned char *img = stbi_load("image/test.jpg", &width, &height, &channels, 0);
    if (img == NULL) {
        std::cout << "Error in loading the image" << std::endl;
        exit(1);
    }
    std::cout << "Loaded image with a width of " << width << " dpx, a height of "
                << height << " dpx and " << channels << " channels" << std::endl;

    return 0;
}
