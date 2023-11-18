cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_CXX_STANDARD 20)
project(quick-cmake VERSION 0.1.0 LANGUAGES C CXX)

add_executable(quick-cmake main.cpp)

find_package(Catch2 QUIET)

include(FetchContent)
FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v3.1.1
)
FetchContent_MakeAvailable(cxxopts)
if(NOT Catch2_FOUND)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()    

add_subdirectory(FileBuilder)

include(CTest)
add_subdirectory(tests)

target_link_libraries(quick-cmake 
    cxxopts
    FileBuilder
)
target_include_directories(quick-cmake PUBLIC .)

