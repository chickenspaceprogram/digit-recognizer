cmake_minimum_required(VERSION 3.15)
project(libs CXX)

set(LIBS_SRCS blas-wrapper.cpp blas-wrapper.hpp load-img.cpp load-img.hpp rand.cpp rand.hpp)
add_library(libs ${LIBS_SRCS})