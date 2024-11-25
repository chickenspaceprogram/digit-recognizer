cmake_minimum_required(VERSION 3.15)
project(libs C)

set(LIBS_SRCS blas-wrapper.c blas-wrapper.h load-img.c load-img.h rand.c rand.h)
add_library(libs ${LIBS_SRCS})