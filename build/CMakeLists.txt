cmake_minimum_required(VERSION 3.15)
project(digit-recognizer C)

set(CMAKE_C_STANDARD 11)



add_executable(digit-recognizer
    ../src/main.c
    ../src/net.c
    ../src/net.h
)

find_package(BLAS REQUIRED)
if (BLAS_FOUND)
    message("BLAS found! Compilation can proceed.")
    include_directories(/usr/include/openblas) # may have to change since this is gonna be OS specific
    target_link_libraries(digit-recognizer ${BLAS_LIBRARIES})
endif(BLAS_FOUND)