#include "image_struct.hpp"
#include "utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void Image_load(Image *const img, const std::string &fname) {
    if (uint8_t *data_ptr = stbi_load(fname.c_str(), img->get_width_ptr(), img->get_height_ptr(), img->get_channels_ptr(), 0);
        data_ptr != NULL) {
        img->set_data(data_ptr);
        img->set_size(img->get_width() * img->get_height() * img->get_channels());
        img->set_allocation(STB_ALLOCATED);
    } else {
        LOG_ERR(true, "Cannot load the image");
    }
}

void Image_save(Image *const img, const std::string &fname) {
    std::string ext = get_ext(fname);
    if (ext.empty()) {
        LOG_INF("Missing of extension file name");
        return;
    }

    if (ext == ".jpg" || ext == ".JPG" ||
        ext == ".jpeg" || ext == ".JPEG") {
        stbi_write_jpg(fname.c_str(), img->get_width(), img->get_height(), img->get_channels(), img->get_data(), 100);
    } else if (ext == ".png" || ext == ".PNG") {
        stbi_write_png(fname.c_str(), img->get_width(), img->get_height(), img->get_channels(), img->get_data(), img->get_width() * img->get_channels());
    } else {
        LOG_ERR(true, "This extension isn't supported");
    }
}

void Image_free(Image *const img) {
    if (img->get_allocation() != NO_ALLOCATION && img->get_data() != NULL) {
        if (img->get_allocation() == STB_ALLOCATED) {
            stbi_image_free(img->get_data());
        } else {
            free(img->get_data());
        }
        img->set_data(NULL);
        img->set_width(0);
        img->set_height(0);
        img->set_size(0);
        img->set_allocation(NO_ALLOCATION);
    }
}
