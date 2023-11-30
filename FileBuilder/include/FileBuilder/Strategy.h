#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

class Strategy 
{
public:
  virtual ~Strategy() = default;
  virtual void create(std::string projectName, std::filesystem::path dirPath) const = 0;
};

class ExecutableStrategy : public Strategy
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

class LibraryStrategy : public Strategy
{
public:
    void create(std::string projectName, std::filesystem::path dirPath) const override
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
            << "\ntarget_include_directories(" << projectName << " PUBLIC ./include)\n";
    }
};


class QtExecutableStrategy : public Strategy
{
public:
    void create(std::string projectName, std::filesystem::path dirPath) const override
    {
        std::ofstream cmakeF(dirPath / "CMakeLists.txt");
        std::ofstream mainF(dirPath / "main.cpp");
        std::ofstream mainWindowSrcF(dirPath / "mainwindow.cpp");
        std::ofstream mainWindowHeaderF(dirPath / "mainwindow.h");

        cmakeF << "cmake_minimum_required(VERSION 3.16)\n"
            << "\n"
            << "project(" << projectName << " VERSION 1.0.0 LANGUAGES CXX)\n"
            << "\n"
            << "set(CMAKE_CXX_STANDARD 17)\n"
            << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
            << "list(APPEND CMAKE_PREFIX_PATH ~/Qt/6.6.0/gcc_64/lib/cmake)\n"
            << "\n"
            << "find_package(Qt6 REQUIRED COMPONENTS Widgets)\n"
            << "qt_standard_project_setup()\n"
            << "\n"
            << "qt_add_executable(" << projectName << "\n"
            << "    mainwindow.cpp\n"
            << "    main.cpp\n"
            << ")\n"
            << "\n"
            << "target_link_libraries(" << projectName << " PRIVATE Qt6::Widgets)\n"
            << "\n"
            << "set_target_properties(" << projectName << " PROPERTIES\n"
            << "    WIN32_EXECUTABLE ON\n"
            << "    MACOSX_BUNDLE ON\n"
            << ")\n";

        mainF << "#include \"mainwindow.h\"\n"
            << "\n"
            << "#include <QApplication>\n"
            << "\n"
            << "int main(int argc, char *argv[])\n"
            << "{\n"
            << "    QApplication a(argc, argv);\n"
            << "    MainWindow w;\n"
            << "    w.show();\n"
            << "    return a.exec();\n"
            << "}\n";

        mainWindowSrcF << "#include \"mainwindow.h\"\n"
            << "\n"
            << "MainWindow::MainWindow(QWidget *parent)\n"
            << "    : QMainWindow(parent)\n"
            << "{\n"
            << "}\n"
            << "\n"
            << "MainWindow::~MainWindow()\n"
            << "{\n"
            << "}\n";

       mainWindowHeaderF << "#pragma once\n"
            << "\n"
            << "#include <QMainWindow>\n"
            << "\n"
            << "class MainWindow : public QMainWindow\n"
            << "{\n"
            << "    Q_OBJECT\n"
            << "\n"
            << "public:\n"
            << "    MainWindow(QWidget *parent = nullptr);\n"
            << "    ~MainWindow();\n"
            << "};\n";
    }
};

class QtLibraryStrategy : public Strategy
{
public:
    void create(std::string projectName, std::filesystem::path dirPath) const override
    {

        std::ofstream cmakeF(dirPath / "CMakeLists.txt");
        std::ofstream srcF(dirPath / (projectName + ".cpp"));
        std::ofstream headerF(dirPath / (projectName + ".h"));


        cmakeF << "qt_add_library(" << projectName << " STATIC\n"
            << "    " << projectName << ".cpp\n"
            << ")\n"
            << "target_link_libraries(" << projectName << " PRIVATE Qt6::Widgets)\n"
            << "target_include_directories(" << projectName << " INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})\n";

        headerF << "#pragma once\n"
            << "\n"
            << "class " << projectName << "\n"
            << "{\n"
            << "public:\n"
            << "    " << projectName << "();\n"
            << "};\n";

        srcF << "#include \"" << projectName << ".h\"\n"
            << "\n"
            << "" << projectName << "::" << projectName << "()\n"
            << "{\n"
            << "}\n";

        
    }
};


class QmlExecutableStrategy : public Strategy
{
public:
    void create(std::string projectName, std::filesystem::path dirPath) const override
    {
        std::ofstream cmakeF(dirPath / "CMakeLists.txt");
        std::ofstream mainF(dirPath / "main.cpp");
        std::ofstream qmlF(dirPath / "Main.qml");

        cmakeF << "cmake_minimum_required(VERSION 3.16)\n"
            << "\n"
            << "project(" << projectName << " VERSION 0.1 LANGUAGES CXX)\n"
            << "\n"
            << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
            << "\n"
            << "list(APPEND CMAKE_PREFIX_PATH \"~/Qt/6.6.0/gcc_64/lib/cmake\")\n"
            << "\n"
            << "find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)\n"
            << "\n"
            << "qt_standard_project_setup()\n"
            << "\n"
            << "qt_add_executable(" << projectName << "\n"
            << "    main.cpp\n"
            << ")\n"
            << "\n"
            << "qt_add_qml_module(" << projectName << "\n"
            << "    URI qml_" << projectName << "\n"
            << "    VERSION 1.0\n"
            << "    QML_FILES Main.qml\n"
            << ")\n"
            << "\n"
            << "# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.\n"
            << "# If you are developing for iOS or macOS you should consider setting an\n"
            << "# explicit, fixed bundle identifier manually though.\n"
            << "set_target_properties(" << projectName << " PROPERTIES\n"
            << "#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example." << projectName << "\n"
            << "    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}\n"
            << "    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}\n"
            << "    MACOSX_BUNDLE TRUE\n"
            << "    WIN32_EXECUTABLE TRUE\n"
            << ")\n"
            << "\n"
            << "target_link_libraries(" << projectName << "\n"
            << "    PRIVATE Qt6::Quick\n"
            << ")\n"
            << "\n"
            << "include(GNUInstallDirs)\n"
            << "install(TARGETS " << projectName << "\n"
            << "    BUNDLE DESTINATION .\n"
            << "    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}\n"
            << "    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}\n"
            << ")\n"
            << "\n";

        mainF << "#include <QGuiApplication>\n"
            << "#include <QQmlApplicationEngine>\n"
            << "\n"
            << "\n"
            << "int main(int argc, char *argv[])\n"
            << "{\n"
            << "    QGuiApplication app(argc, argv);\n"
            << "\n"
            << "    QQmlApplicationEngine engine;\n"
            << "    const QUrl url(u\"qrc:/qml_" << projectName << "/Main.qml\"_qs);\n"
            << "    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,\n"
            << "        &app, []() { QCoreApplication::exit(-1); },\n"
            << "        Qt::QueuedConnection);\n"
            << "    engine.load(url);\n"
            << "\n"
            << "    return app.exec();\n"
            << "}\n"
            << "\n";

        qmlF << "import QtQuick\n"
            << "import QtQuick.Window\n"
            << "\n"
            << "Window {\n"
            << "    width: 640\n"
            << "    height: 480\n"
            << "    visible: true\n"
            << "    title: qsTr(\"Hello World from " << projectName << "\")\n"
            << "}\n";

    }
};

class QmlLibraryStrategy : public Strategy
{
public:
    void create(std::string projectName, std::filesystem::path dirPath) const override
    {
        std::cout << "Not implemented yet. Sorry\n";
    }
};

class CatchTestStrategy : public Strategy
{
public:
    void create(std::string projectName, std::filesystem::path dirPath) const override
    {
        std::ofstream cmakeF(dirPath / "CMakeLists.txt");
        std::ofstream mainF(dirPath / "main.cpp");

        cmakeF  << "cmake_minimum_required(VERSION 3.0.0)\n"
            << "project(" << projectName << ")\n"
            << "\n"
            << "add_compile_options(-fsanitize=address)\n"
            << "add_link_options(-fsanitize=address)\n"
            << "\n"
            << "find_package(Catch2 REQUIRED)\n"
            << "\n"
            << "add_executable(" << projectName << " main.cpp)\n"
            << "\n"
            << "target_link_libraries(" << projectName << " Catch2::Catch2WithMain)\n";

        mainF  << "#include <catch2/catch_test_macros.hpp>\n"
            << "\n"
            << "\n"
            << "TEST_CASE(\"run tests\") {\n"
            << "    REQUIRE(true);\n"
            << "}\n";

    }
};
