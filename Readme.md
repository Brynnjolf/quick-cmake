<div align="center">

# Quick-Cmake
### Project File Generator
[![CMake on a single platform](https://github.com/Brynnjolf/quick-cmake/actions/workflows/cmake-single-platform.yml/badge.svg?branch=master)](https://github.com/Brynnjolf/quick-cmake/actions/workflows/cmake-single-platform.yml)
[![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=flat&logo=cmake&logoColor=white)](https://cmake.org/documentation/)
</div>

quick-cmake is used to generate modules for cmake projects.
This involves generating simple filesystem structures for executables or
libraries, that can be used in isolation, or easily linked to a greater project.

### Usage

`$ quick-cmake [options] <path> [<name>]`

**path** is the location at which the new cmake project is created.

**name** is the name of the project (and default target) that will be generated.
if **name** is not included, it will be set as the name of the directory at **path**.

#### basic-usage: executables
`$ quick-cmake "project"`

Generates a cmake executable in the `project/` directory, creating the dir if it
does not exist. It will not overwrite an existing Cmake project.

The above command will result in this directory structure:

```
project
|
├── CMakeLists.txt
└── main.cpp

0 directories, 2 files
```

#### basic-usage: libraries

`$ quick-cmake -l "project"`

generates a cmake library at `project/`. It will have the following structure:

```
project
|
├── CMakeLists.txt
├── include
│   └── project
│       └── project.h
└── src
    └── project.cpp

3 directories, 3 files
```
This library can then be easily linked to a parent project by simply calling

```cmake
add_subdirectory(project)
target_link_libaries(parent PUBLIC project)
```
the interesting directory structure of the `include/project/project.h` allows
a user to use `#include <project/project.h>` for any target that the library
is linked to. convenient!

## Options

**-l**: create's a cmake library module instead of an executable.

**--fmt \<format\>**: set's the format of the created project. This allows for quick
generation of "templated" libraries.

available `<format>` arguments are:
- **Qt** - Qt widgets application
- **Qml** - Qml application
- **Catch** - Catch2 test executable (this will override the "library" option)
