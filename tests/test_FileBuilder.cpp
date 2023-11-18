#include <catch2/catch_test_macros.hpp>
#include <FileBuilder/FileBuilder.h>
#include "FileBuilderFixture.h"


TEST_CASE_METHOD(FileBuilderFixture, "default executable creation")
{

    FileBuilder builder("testProject", rootPath(), Type::Exe, Format::Default);
    builder.create();

    REQUIRE(std::filesystem::exists(rootPath() / "CMakeLists.txt"));
    REQUIRE(std::filesystem::exists(rootPath() / "main.cpp"));
}

TEST_CASE_METHOD(FileBuilderFixture, "default library creation")
{

    FileBuilder builder("testProject", rootPath(), Type::Lib, Format::Default);
    builder.create();

    REQUIRE(std::filesystem::exists(rootPath() / "CMakeLists.txt"));
    REQUIRE(std::filesystem::exists(rootPath() / "include/testProject/testProject.h"));
    REQUIRE(std::filesystem::exists(rootPath() / "src/testProject.cpp"));
}

TEST_CASE_METHOD(FileBuilderFixture, "Qt Executable creation")
{

    FileBuilder builder("testProject", rootPath(), Type::Exe, Format::Qt);
    builder.create();

    REQUIRE(std::filesystem::exists(rootPath() / "CMakeLists.txt"));
    REQUIRE(std::filesystem::exists(rootPath() / "main.cpp"));
    REQUIRE(std::filesystem::exists(rootPath() / "mainwindow.cpp"));
    REQUIRE(std::filesystem::exists(rootPath() / "mainwindow.h"));
}






