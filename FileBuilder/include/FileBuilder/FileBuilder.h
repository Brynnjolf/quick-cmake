#pragma once

#include "Strategy.h"

enum class Type
{
    Exe,
    Lib
};

enum class Format
{
    Default,
    Qt,
    Qml
};

class FileBuilder
{
public:
    FileBuilder(std::string projectName, std::filesystem::path dirPath, Type type, Format format);

    void create();
    void setStrategy(std::unique_ptr<Strategy>&& strat);

private:
    std::string projectName;
    std::filesystem::path dirPath;
    Type type;
    Format format;

    std::unique_ptr<Strategy> strategy = std::make_unique<ExecutableStrategy>();
};
