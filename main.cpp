
#include <cxxopts.hpp>

#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <FileBuilder/FileBuilder.h>

void printHelp()
{
    std::cout << "usage: quick-cmake <path> [-l] [name]\n";
}
    

int main(int argc, char* argv[])
{
    cxxopts::Options options("quick-cmake", "a tool to quickly generate cmake executable and library directories");

    options.add_options()
            ("path", "location for new cmake library", cxxopts::value<std::string>())
            ("l", "library")
            ("h", "help")
            ("Qml", "generate qml project format")
            ("Qt", "generate Qt project format")
            ("name", "project (or library) name", cxxopts::value<std::string>());
    
    options.parse_positional({"path", "name"});

    auto args = options.parse(argc, argv);
    
    if(args["h"].as<bool>() || args.count("path") == 0)
    {
        printHelp();
        return 1;
    }

    bool qt = args["Qt"].as<bool>();
    bool qml = args["Qml"].as<bool>();

    if(qt && qml)
    {
        std::cerr << "Qt and Qml options are mutually exclusive.";
        return 1;
    }

    std::filesystem::path dirPath = args["path"].as<std::string>();
    if(std::filesystem::exists(dirPath / "CMakeLists.txt"))
    {
        std::cout << "Cmake project already exists in this directory\n";
        return 1;
    }

    std::string projectName = args.count("name") > 0 ? args["name"].as<std::string>() : dirPath.filename().string();

    if(projectName == ".")
    {
        projectName = std::filesystem::current_path().filename();
    }
    
    Type type = args["l"].as<bool>() ? Type::Lib : Type::Exe;
    Format format;
    if(qt || qml)
    {
        format = qt ? Format::Qt : Format::Qml;
    }
    else
    {
        format = Format::Default;
    }

    std::filesystem::create_directories(dirPath);
    FileBuilder fileBuilder(projectName, dirPath, type, format);
    fileBuilder.create(); 
    return 0;
}
