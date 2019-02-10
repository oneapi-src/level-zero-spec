# Source Code
Header files are generated using [scripts](/scripts/README.md).  

# Documentation
[Documentation](/html/index.html) is generated from source code using Doxygen.  

# Third-Party Tools
Tools can be acquired via instructions in [third_party](/third_party/README.md).

# Building
Project is defined using [CMake](https://cmake.org/).
**Windows**:
Generating Visual Studio Project
~~~~
mkdir build
cd build
cmake {path_to_source_dir} -G "Visual Studio 15 2017 Win64"
~~~~

**Linux**:
~~~~
mkdir build
cd build
cmake {path_to_source_dir}
make
~~~~

# Unit Level tests
[Unit level tests](/tests/unit_tests/README.md) are written using GoogleTest and GoogleMock.
