cmake_minimum_required(VERSION 3.0)

project(image_resizing_tool)

include_directories(include)

file(GLOB SOURCES src/*.cpp)

# Add the executable target
add_executable(im_rez ${SOURCES})

# Set compiler options for im_rez target
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Compiler flags for GNU GCC or Clang
    target_compile_options(im_rez PRIVATE
        -Wall                    # Enable all warnings
        -Wextra                  # Extra warning flags
        -Wpedantic               # Enforce strict standards
        -O2                      # Optimization level 2
    )
elseif(MSVC)
    # Compiler flags for MSVC
    target_compile_options(im_rez PRIVATE
        /W4                      # Enable level 4 warnings
        /WX                      # Treat warnings as errors
        /O2                      # Optimization level 2
    )
endif()
