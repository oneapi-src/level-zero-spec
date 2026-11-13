# Contents
This repo contains the following:
- API specification in YaML
- API programming guides in reStructuredText
- API C header files (generated)
- API Python modules (generated)
- API C++ stub sources (generated), built as a static library to check that the headers compile

The published specification is at https://oneapi-src.github.io/level-zero-spec/.

# Source Code Generation
Code and documentation are generated using the included [Python scripts](/scripts/README.md).
That README lists the requirements and the steps to run them.

# Documentation
Documentation is generated from the YaML and the programming guides using Doxygen, Breathe and Sphinx.
The HTML output is in **docs/html**.

# Third-Party Tools
[third_party/requirements.txt](/third_party/requirements.txt) is the single list of Python packages
for building the spec. Compiler tools for building need to be manually installed for Windows.

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
Generate the source files first using the [Python scripts](scripts/README.md); by default
`run.py` also runs this build. Static libraries will be in **build/lib**.
~~~~
mkdir build
cd build
cmake {path_to_source_dir}
make
~~~~
