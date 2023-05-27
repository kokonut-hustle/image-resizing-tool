#include <iostream>
#include <chrono>
#include <filesystem>
#include "constants.hpp"
#include "image_struct.hpp"
#include "bilinear_interpolation.hpp"
#include "simd_bilinear_interpolation.hpp"

int main(int argc, char *argv[]) {
    Image img;
    // Image_load(&img, "image/test.jpg");

    // std::cout << "Loaded image with a width of " << img.get_width() << " dpx, a height of "
    //             << img.get_height() << " dpx and " << img.get_channels() << " channels" << std::endl;

    Scaler *ss = new SIMDBIScaler();
    Scaler *bs = new BIScaler();
    std::string path = "image/";

    std::vector<std::string> img_paths;
    std::error_code ec;
    for (const auto &entry : std::filesystem::recursive_directory_iterator(path)) {
        if (std::filesystem::is_regular_file(entry, ec)) {
            img_paths.push_back(entry.path());
        }
    }
    std::cout << "There are " << img_paths.size() << " images" << std::endl;

    Image rz_img;

    // Measure running time of original BIScaler
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto &p : img_paths) {
        Image_load(&img, p);
        rz_img = bs->resize(img, img.get_width()/3, img.get_height()/2);
        Image_free(&rz_img);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Original BIScaler took " << duration.count() << " microseconds" << std::endl;

    // Measure running time of SIMD BIScaler
    start = std::chrono::high_resolution_clock::now();
    for (const auto &p : img_paths) {
        Image_load(&img, p);
        rz_img = ss->resize(img, img.get_width()/3, img.get_height()/2);
        Image_free(&rz_img);
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "SIMD BIScaler took " << duration.count() << " microseconds" << std::endl;

    // Image rz_img = s->resize(img, img.get_width()*3, img.get_height()*2);

    // Image_save(&rz_img, "image/resized_img.png");

    Image_free(&img);
    Image_free(&rz_img);

    return 0;
}
