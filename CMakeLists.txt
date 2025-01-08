cmake_minimum_required(VERSION 3.24)
project(tc)

set(CMAKE_CXX_STANDARD 23)

include_directories (include)


Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/pair_items_test.cpp)
add_executable(chunk_by_tests tests/chunk_by.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(chunk_by_tests PRIVATE Catch2::Catch2WithMain)
