
#include <cxxopts.hpp>

#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void create_executable(std::filesystem::path dirPath, std::string projectName)
{

    std::ofstream cmakeF(dirPath / "CMakeLists.txt");
    cmakeF  << "cmake_minimum_required(VERSION 3.0.0)\n"
        << "project(" << projectName << ")\n\n"
        << "add_executable(main main.cpp)";

    std::ofstream mainF(dirPath / "main.cpp");
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

    std::ofstream cmakeFile(dirPath / "CMakeLists.txt");
    cmakeFile << "add_library(" << projectName << " src/" << projectName << ".cpp)"
        << "\ntarget_include_directories(" << projectName << "PUBLIC ./include)\n";
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "usage: quick-cmake <path> [name]";
        return 1;
    }

    std::filesystem::path dirPath = argv[1];
    if(std::filesystem::exists(dirPath / "CMakeLists.txt"))
    {
        std::cout << "Cmake project already exists in this directory\n";
        return 1;
    }

    std::string projectName = argc > 3 ? argv[2] : dirPath.filename();
    if(projectName == ".")
    {
        projectName = std::filesystem::current_path().filename();
    }

    std::filesystem::create_directories(dirPath);
    if(argc > 2 && strcmp(argv[2], "-l") == 0)
    {
        create_library(dirPath, projectName);
    }
    else
    {
        create_library(dirPath, projectName);
    }
    return 0;
}
