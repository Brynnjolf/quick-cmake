cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_CXX_STANDARD 20)
project(quick-cmake VERSION 0.1.0 LANGUAGES C CXX)

add_executable(quick-cmake main.cpp)

include(FetchContent)

FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v3.1.1
)

FetchContent_MakeAvailable(cxxopts)

add_subdirectory(FileBuilder)
add_subdirectory(tests)

target_link_libraries(quick-cmake 
    cxxopts
    FileBuilder
)

target_link_libraries(test_FileBuilder FileBuilder)

target_include_directories(quick-cmake PUBLIC .)
