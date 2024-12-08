cmake_minimum_required(VERSION 3.15)
project(libs-test CXX)


add_executable(TEST-blas-wrapper
    TEST-blas-wrapper.cpp
)

target_link_libraries(TEST-blas-wrapper libs ${BLAS})

add_test(
    NAME blas-wrapper
    COMMAND $<TARGET_FILE:TEST-blas-wrapper>
)