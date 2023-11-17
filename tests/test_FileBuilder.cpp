#include <catch2/catch_test_macros.hpp>
#include <FileBuilder/FileBuilder.h>

TEST_CASE("basic-case")
{
    FileBuilder builder("testProject", ".", Type::Exe, Format::Default);
    builder.create();
}
