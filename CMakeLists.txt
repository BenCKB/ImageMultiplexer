cmake_minimum_required(VERSION 3.5)

project(imgmltplx)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_executable(imgmltplx ImageMultiplexer.cpp stb_image.h stb_image_write.h)