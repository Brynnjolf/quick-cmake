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
            case Format::Catch:
                setStrategy(std::make_unique<CatchTestStrategy>());
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
            case Format::Catch:
                std::cout << "Catch tests cannot be a library. Generating catch executable...\n";
                setStrategy(std::make_unique<CatchTestStrategy>());
                break;
            case Format::Default:
                setStrategy(std::make_unique<LibraryStrategy>());
                break;
        }
    }
}

void FileBuilder::create()
{
    strategy->create(projectName, dirPath);
}

void FileBuilder::setStrategy(std::unique_ptr<Strategy>&& strat) 
{
    strategy = std::move(strat);

}

