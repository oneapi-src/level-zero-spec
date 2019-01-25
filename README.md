# Source Code
Header files are generated using [scripts](/scripts/README.md).  

# Documentation
[Documentation](/html/index.html) is generated from source code using Doxygen.  

# Third-Party Tools
If third_party tools are not installed locally, they can be installed
via irepo (https://github.intel.com/gsdi/irepo).

* Pick the manifest
~~~~
irepo select third_party/windows.yml
~~~~

* Ignore folders not tracked by irepo
~~~~
irepo ignore-folder .git
irepo ignore-folder build
irepo ignore-folder core
irepo ignore-folder extended
irepo ignore-folder images
irepo ignore-folder samples
irepo ignore-folder scripts
irepo ignore-folder tests
~~~~

* Download and synchronize third_party tools
~~~~
irepo sync
~~~~

* Generate Visual Studio project with CMake
~~~~
mkdir build
cd build
cmake <path_to_source_dir> -G "Visual Studio 15 2017 Win64"
~~~~