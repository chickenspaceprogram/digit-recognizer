cmake_minimum_required(VERSION 3.15)
project(digit-recognizer C)

set(CMAKE_C_STANDARD 11)
if (${APPLE})

# using Apple's version of BLAS
set (CMAKE_C_FLAGS "-DACCELERATE_NEW_LAPACK")
set (BLAS_FOUND true)
set (BLAS "-lcblas")

elseif (${WIN32})

# using a hand-coded, bad version of BLAS since getting the actual thing to work on windows was a pain
# this will slow down the windows version massively but i'm not developing this on windows so i don't really care
set (BLAS_FOUND true)

else ()

find_package(BLAS REQUIRED)
include_directories(/usr/include/openblas/) # may have to change since this is gonna be distro specific

endif ()




add_subdirectory(../src/libs ./libs)

add_executable(digit-recognizer
    ../src/main.c
    ../src/activation-funcs.c
    ../src/activation-funcs.h
    ../src/layer.c
    ../src/layer.h
)

if (BLAS_FOUND)
    message("BLAS found! Compilation can proceed.")
    target_link_libraries(digit-recognizer ${BLAS_LIBRARIES} libs -lm ${BLAS})
endif(BLAS_FOUND)