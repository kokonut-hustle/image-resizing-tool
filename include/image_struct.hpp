#pragma once
#include <string>
#include <vector>

enum allocation_type {
    NO_ALLOCATION,
    SELF_ALLOCATED,
    STB_ALLOCATED
};

class Image {
public:
    Image(){}

    Image(int width_, int height_, int channels_)
     : width(width_), height(height_), channels(channels_) {
        size = width * height * channels;
        data = (uint8_t *) malloc(size);
        allocation_ = SELF_ALLOCATED;
    }

    ~Image() {
        free(data);
    }

    int get_width() const {
        return this->width;
    }

    int *get_width_ptr() {
        return &(this->width);
    }

    int get_height() const {
        return this->height;
    }

    int *get_height_ptr() {
        return &(this->height);
    }

    int get_channels() const {
        return this->channels;
    }

    int *get_channels_ptr() {
        return &(this->channels);
    }

    int get_size() const {
        return this->size;
    }

    uint8_t *get_data() const {
        return this->data;
    }

    enum allocation_type get_allocation() {
        return this->allocation_;
    }

    void set_width(const int width_) {
        this->width = width_;
    }

    void set_height(const int height_) {
        this->height = height_;
    }

    void set_channels(const int channels_) {
        this->channels = channels_;
    }

    void set_size(const size_t size_) {
        this->size = size_;
    }

    void set_data(uint8_t *const data_) {
        this->data = data_;
    }

    void set_allocation(const enum allocation_type allocation_) {
        this->allocation_ = allocation_;
    }

private:
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;
    enum allocation_type allocation_;

};

void Image_load(Image *const img, const std::string &fname);
void Image_save(Image *const img, const std::string &fname);
void Image_free(Image *const img);
