cmake_minimum_required(VERSION 3.24)
project(tc)

set(CMAKE_CXX_STANDARD 23)

include_directories (include)


# add_library(tc library.cpp)
add_executable (test_lazyReadFile library.cpp)
add_executable (test_pairItems pair_items.cpp)