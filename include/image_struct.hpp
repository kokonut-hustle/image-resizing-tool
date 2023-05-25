#pragma once
#include <string>

enum allocation_type {
    NO_ALLOCATION,
    SELF_ALLOCATED,
    STB_ALLOCATED
};

typedef struct {
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;
    enum allocation_type allocation_;
} Image;

void Image_load(Image *img, const std::string &fname);
void Image_save(const Image *img, const std::string &fname);
void Image_free(Image *img);
