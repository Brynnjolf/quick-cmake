
#include <cxxopts.hpp>

#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <FileBuilder/FileBuilder.h>

void create_executable(std::filesystem::path dirPath, std::string projectName)
{

    std::ofstream cmakeF(dirPath / "CMakeLists.txt");
    std::ofstream mainF(dirPath / "main.cpp");

    cmakeF  << "cmake_minimum_required(VERSION 3.0.0)\n"
        << "project(" << projectName << ")\n\n"
        << "add_executable(" << projectName << " main.cpp)";

    mainF << "#include <iostream>\n\n"
        << "int main()\n"
        << "{\n"
        << "\tstd::cout << \"hello from " << projectName << "\\n\";\n"
        << "\treturn 0;\n"
        << "}\n";
}

void create_library(std::filesystem::path dirPath, std::string projectName)
{
    std::filesystem::path srcPath = dirPath / "src";
    std::filesystem::path includePath = dirPath / "include" / projectName;
    std::filesystem::create_directories(includePath);  
    std::filesystem::create_directories(srcPath);  

    std::ofstream hFile(includePath / (projectName + ".h"));
    std::ofstream srcFile(srcPath / (projectName + ".cpp"));
    srcFile << "#include <" << projectName << "/" << projectName << ".h>\n";
    hFile << "#pragma once\n";

    std::ofstream cmakeFile(dirPath / "CMakeLists.txt");
    cmakeFile << "add_library(" << projectName << " src/" << projectName << ".cpp)"
        << "\ntarget_include_directories(" << projectName << " PUBLIC ./include)\n";
}

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
