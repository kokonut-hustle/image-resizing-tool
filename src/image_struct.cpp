#include "image_struct.hpp"
#include "utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void Image_load(Image *img, const std::string &fname) {
    if ((img->data = stbi_load(fname.c_str(), &img->width, &img->height, &img->channels, 0)) != NULL) {
        img->size = img->width * img->height * img->channels;
        img->allocation_ = STB_ALLOCATED;
    }
}

void Image_save(const Image *img, const std::string &fname) {
    std::string ext = get_ext(fname);
    if (ext.empty()) {
        LOG_INF("Missing of extension file name");
        return;
    }

    if (ext == ".jpg" || ext == ".JPG" ||
        ext == ".jpeg" || ext == ".JPEG") {
        stbi_write_jpg(fname.c_str(), img->width, img->height, img->channels, img->data, 100);
    } else if (ext == ".png" || ext == ".PNG") {
        stbi_write_png(fname.c_str(), img->width, img->height, img->channels, img->data, img->width * img->channels);
    } else {
        LOG_ERR(true, "This extension isn't supported");
    }
}

void Image_free(Image *img) {
    if (img->allocation_ != NO_ALLOCATION && img->data != NULL) {
        if (img->allocation_ == STB_ALLOCATED) {
            stbi_image_free(img->data);
        } else {
            free(img->data);
        }
        img->data = NULL;
        img->width = 0;
        img->height = 0;
        img->size = 0;
        img->allocation_ = NO_ALLOCATION;
    }
}
