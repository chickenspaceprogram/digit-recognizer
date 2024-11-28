cmake_minimum_required(VERSION 3.15)
project(network CXX)

set(NETWORK_SRCS 
    activation-funcs.hpp
    activation-funcs.cpp
    cost-funcs.hpp
    cost-funcs.cpp
    layer.hpp
    layer.cpp
    network.hpp
    network.cpp
)
add_library(network ${NETWORK_SRCS})

target_link_libraries(network libs)