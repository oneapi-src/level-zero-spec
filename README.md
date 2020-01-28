# Contents
This repo contains the following:
- API specification in YaML
- API programming guide in Markdown
- API C/C++ header files (generated)
- API Python module (generated)
- Sample C++ wrapper (generated)
- Sample C/C++ import library (generated)
- Sample driver loader (generated)
- Sample parameter validation layer (generated)
- Sample "null" driver (generated)
- Simple sample applications

# Source Code Generation
Code is generated using included [Python scripts](/scripts/README.md).  

# Documentation
[Documentation](https://one-api.gitlab-pages.devtools.intel.com/level_zero/) is generated from source code using Doxygen.

# Third-Party Tools
Tools can be acquired via instructions in [third_party](/third_party/README.md).

# Building
Project is defined using [CMake](https://cmake.org/).

**Windows**:
Generating Visual Studio Project.  EXE and binaries will be in **build/bin/{build_config}**
~~~~
mkdir build
cd build
cmake {path_to_source_dir} -G "Visual Studio 15 2017 Win64"
~~~~

**Linux**:
Executable and binaries will be in **build/bin**
~~~~
mkdir build
cd build
cmake {path_to_source_dir}
make
~~~~

# Unit Level tests
[Unit level tests](/tests/unit_tests/README.md) are written using GoogleTest and GoogleMock.
