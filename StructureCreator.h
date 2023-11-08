#pragma once

#include <filesystem>
#include <memory>
#include <fstream>

enum class Type
{
    Executable,
    Library
};

enum class Format
{
    Default,
    QtWidgets,
    Qml
};

class Strategy 
{
public:
  virtual ~Strategy() = default;
  virtual void create(std::string projectName, std::filesystem::path dirPath) const = 0;
};

class DefaultStrategy : public Strategy
{
public:
    void create(std::string projectName, std::filesystem::path dirPath) const override
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
};

class StructureCreator
{
public:
    StructureCreator(std::string projectName, std::filesystem::path dirPath, Type type, Format format) : projectName(projectName), dirPath(dirPath), type(type), format(format)
    {

    }

    void create()
    {
        strategy->create(projectName, dirPath);
    }

    void setStrategy(std::unique_ptr<Strategy> strat) 
    {
        strategy = std::move(strat);
    }

private:
    std::string projectName;
    std::filesystem::path dirPath;
    Type type;
    Format format;

    std::unique_ptr<Strategy> strategy = std::make_unique<DefaultStrategy>();
};
