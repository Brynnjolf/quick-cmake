
#include <cxxopts.hpp>

#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#include <FileBuilder/FileBuilder.h>

void printHelp()
{
    std::cout << "usage: quick-cmake <path> [-l] [name]\n";
}

cxxopts::ParseResult parseArgs(int argc, char* argv[])
{
   cxxopts::Options options("quick-cmake", "a tool to quickly generate cmake executable and library directories");

    // fmt options : [Qml, Qt, Catch2Test]
    options.add_options()
        ("path", "location for new cmake library", cxxopts::value<std::string>())
        ("l", "library")
        ("h", "help")
        ("fmt", "project format", cxxopts::value<std::string>())
        ("name", "project (or library) name", cxxopts::value<std::string>());

    options.parse_positional({"path", "name"});

    return options.parse(argc, argv);
}

Format resolveFormatString(std::string fmt) {
    std::transform(fmt.begin(), fmt.end(), fmt.begin(),
            [](unsigned char c) { return std::tolower(c); });
    if(fmt == "qt") return Format::Qt;
    if(fmt == "qml") return Format::Qml;
    if(fmt == "catch" || fmt == "catch2") return Format::Catch;
    return Format::Default;
}
    

int main(int argc, char* argv[])
{
    auto args = parseArgs(argc, argv);
    
    if(args["h"].as<bool>() || args.count("path") == 0)
    {
        printHelp();
        return 1;
    }
    if(args.count("fmt") > 1) {
        std::cerr << "\"fmt\" option can only be declared a maximum of once";
        return 1;
    }

    Type type = args["l"].as<bool>() ? Type::Lib : Type::Exe;

    std::filesystem::path dirPath = args["path"].as<std::string>();
    std::string projectName = args.count("name") ? args["name"].as<std::string>() : dirPath.filename().string();

    if(std::filesystem::exists(dirPath / "CMakeLists.txt"))
    {
        std::cout << "Cmake project already exists in this directory\n";
        return 1;
    }


    if(projectName == ".")
    {
        projectName = std::filesystem::current_path().filename();
    }

    const std::string fmt = args.count("fmt") > 0 ?  args["fmt"].as<std::string>() : "";
    Format format = resolveFormatString(fmt);
    
    std::filesystem::create_directories(dirPath);
    FileBuilder fileBuilder(projectName, dirPath, type, format);
    fileBuilder.create(); 
    return 0;
}
