#pragma once
#include <iostream>
#include <string>

#define LOG_ERR(cond, message) \
do { \
    if (cond) { \
        std::cerr << "Error in function: " << __func__ << " at line " << __LINE__ << std::endl; \
        std::cerr << message << std::endl; \
    } \
} while(0)

#define LOG_INF(message) \
std::clog << message << std::endl

static inline std::string get_ext(const std::string &fname) {
    std::size_t pos = fname.find_last_of('.');
    if (pos == std::string::npos)
        return "";

    return fname.substr(pos);
}
