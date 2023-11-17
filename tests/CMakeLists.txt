find_package(Catch2 REQUIRED)
include(CTest)
enable_testing()

add_executable(test_FileBuilder test_FileBuilder.cpp)

target_link_libraries(test_FileBuilder
    Catch2::Catch2WithMain
    FileBuilder
)

