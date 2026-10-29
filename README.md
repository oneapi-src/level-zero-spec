# Contents
This repo contains the following:
- API specification in YaML
- API programming guide in Markdown
- API C/C++ header files (generated)
- API Python module (generated)
- Sample C++ wrapper (generated)
- Sample C/C++ import library (generated)

# Source Code Generation
Code is generated using included [Python scripts](/scripts/README.md).  

# Documentation
Documentation is generated from source code using Doxygen.

# Third-Party Tools
Contains requirements for building spec. Compiler tools for building need to be manually installed for Windows.

# Building
Project is defined using [CMake](https://cmake.org/).

**Windows**:
Requires Visual Studio (or Build Tools) with the Desktop development with C++
workload, CMake, and Ninja on PATH. Generate the source files first using the
[Python scripts](scripts/README.md), disabling their built-in build step with
`--!build`. From an x64 Native Tools Command Prompt (or a shell initialized with
`vcvars64.bat`), configure and build from the repository root:
~~~~
cmake -B build -S . -G Ninja -D CMAKE_BUILD_TYPE=Release
cmake --build build --parallel
~~~~
Runtime binaries will be in **build/bin** and static libraries in **build/lib**.
Use `-D CMAKE_BUILD_TYPE=Debug` at configure time for a Debug build. Use a fresh
build directory when switching from a Visual Studio or NMake generator to Ninja.

**Linux**:
Executable and binaries will be in **build/bin**
~~~~
mkdir build
cd build
cmake {path_to_source_dir}
make
~~~~
