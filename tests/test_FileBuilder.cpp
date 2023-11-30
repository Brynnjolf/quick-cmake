#include <catch2/catch_test_macros.hpp>
#include <FileBuilder/FileBuilder.h>
#include "FileBuilderFixture.h"

bool isTextInFile(std::string&& text, std::string&& filePath) {
    std::ifstream file(filePath);
    std::string line;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            if(line.find(text) != std::string::npos) {
                return true;
            }
        }
    } else {
        std::cout << "error opening file " << filePath << std::endl;
        return false;
    }
    return false;
}


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

TEST_CASE_METHOD(FileBuilderFixture, "Qml Executable creation")
{

    FileBuilder builder("testProject", rootPath(), Type::Exe, Format::Qml);
    builder.create();

    REQUIRE(std::filesystem::exists(rootPath() / "CMakeLists.txt"));
    REQUIRE(std::filesystem::exists(rootPath() / "main.cpp"));
    REQUIRE(std::filesystem::exists(rootPath() / "Main.qml"));
}

TEST_CASE_METHOD(FileBuilderFixture, "Qt Library creation")
{

    FileBuilder builder("testProject", rootPath(), Type::Lib, Format::Qt);
    builder.create();

    REQUIRE(std::filesystem::exists(rootPath() / "CMakeLists.txt"));
    REQUIRE(std::filesystem::exists(rootPath() / "testProject.cpp"));
    REQUIRE(std::filesystem::exists(rootPath() / "testProject.h"));
}

TEST_CASE_METHOD(FileBuilderFixture, "Catch Test creation")
{

    FileBuilder builder("testProject", rootPath(), Type::Exe, Format::Catch);
    builder.create();

    REQUIRE(std::filesystem::exists(rootPath() / "CMakeLists.txt"));
    REQUIRE(std::filesystem::exists(rootPath() / "main.cpp"));

    REQUIRE(isTextInFile("find_package(Catch2 REQUIRED)", rootPath() / "CMakeLists.txt"));
    REQUIRE(isTextInFile("TEST_CASE", rootPath() / "main.cpp"));
}


