include(Catch)

add_executable(test_FileBuilder test_FileBuilder.cpp)

target_link_libraries(test_FileBuilder
    Catch2::Catch2WithMain
    FileBuilder
)

catch_discover_tests(test_FileBuilder)
