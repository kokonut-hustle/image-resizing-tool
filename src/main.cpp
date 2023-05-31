#include <iostream>
#include <chrono>
#include <filesystem>
#include "constants.hpp"
#include "image_struct.hpp"
#include "nearest_neighbor.hpp"
#include "bilinear_interpolation.hpp"
#include "simd_bilinear_interpolation.hpp"

int main(int argc, char *argv[]) {
    Image img;

    Scaler *ns = new NNScaler();
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

    // Measure running time of NNIScaler
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto &p : img_paths) {
        Image_load(&img, p);
        rz_img = ns->resize(img, img.get_width()/3, img.get_height()/2);
        Image_free(&rz_img);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "NNScaler took " << duration.count() << " microseconds" << std::endl;

    Image_free(&img);
    Image_free(&rz_img);

    return 0;
}
