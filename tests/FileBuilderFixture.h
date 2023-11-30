#include <catch2/catch_test_macros.hpp>
#include <filesystem>

class FileBuilderFixture
{
private:
    const std::filesystem::path test_root_path = "temp";
public:
    FileBuilderFixture()
    {
        std::filesystem::remove_all(test_root_path);
        REQUIRE(std::filesystem::create_directory(test_root_path));
    }
    ~FileBuilderFixture()
    {
        REQUIRE(std::filesystem::remove_all(test_root_path));
    }

    std::filesystem::path rootPath()
    {
        return test_root_path;
    }
};
