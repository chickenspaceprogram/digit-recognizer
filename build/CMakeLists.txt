cmake_minimum_required(VERSION 3.15)
project(digit-recognizer CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

if (${WIN32})   ##### remove this line to use the fallback version of BLAS #####

set (FALLBACK_BLAS true)

endif ()        ##### remove this line to use the fallback version of BLAS #####

if (FALLBACK_BLAS)

set (BLAS_FOUND true)

elseif (${APPLE})

# using Apple's version of BLAS
set (CMAKE_CXX_FLAGS "-DACCELERATE_NEW_LAPACK")
set (BLAS_FOUND true)
set (BLAS "-lcblas")

else ()

find_package(BLAS REQUIRED)
include_directories(/usr/include/openblas/) # may have to change since this is gonna be distro specific

endif ()



enable_testing()
add_subdirectory(../src/libs ./libs)
add_subdirectory(../src/network ./network)

add_executable(digit-recognizer
    ../src/main.cpp
    ../src/train.cpp
    ../src/train.hpp
)

if (BLAS_FOUND)
    message("BLAS found! Compilation can proceed.")
    target_link_libraries(digit-recognizer ${BLAS_LIBRARIES} libs network -lm ${BLAS})
endif(BLAS_FOUND)