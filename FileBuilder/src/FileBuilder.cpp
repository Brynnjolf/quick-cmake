#include <FileBuilder/FileBuilder.h>


FileBuilder::FileBuilder(std::string projectName, std::filesystem::path dirPath, Type type, Format format)
    : projectName(projectName), dirPath(dirPath), type(type), format(format)
{
    if(type == Type::Exe)
    {
        switch(format)
        {
            case Format::Qt:
                setStrategy(std::make_unique<QtExecutableStrategy>());
                break;
            case Format::Qml:
                setStrategy(std::make_unique<QmlExecutableStrategy>());
                break;
            case Format::Default:
                setStrategy(std::make_unique<ExecutableStrategy>());
                break;
        }
    }
    else
    {
        switch(format)
        {
            case Format::Qt:
                setStrategy(std::make_unique<QtLibraryStrategy>());
                break;
            case Format::Qml:
                setStrategy(std::make_unique<QmlLibraryStrategy>());
                break;
            case Format::Default:
                setStrategy(std::make_unique<LibraryStrategy>());
                break;
        }
    }
}

