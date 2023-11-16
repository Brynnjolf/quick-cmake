## Quick-Cmake: Project File Generator

quick-cmake is used to generate modules for cmake projects.
This involves generating simple filesystem structures for executables or
libraries, that can be used in isolation, or easily linked to a greater project.

#### basic-usage: executables
`$ quick-cmake project`

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

`$ quick-cmake -l project`

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

```
add_subdirectory(project)
target_link_libaries(parent PUBLIC project)
```
the interesting directory structure of the `include/project/project.h` allows
a user to use `#include <project/project.h>` for any target that the library
is linked to. convenient!

