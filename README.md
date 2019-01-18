Header files are generated using [scripts](/scripts/README.md).  

[Documentation](todo) is generated from source code using Doxygen.  


##If third_party tools are not installed locally, they can be installed
##via irepo (https://github.intel.com/gsdi/irepo).

#Pick the manifest
irepo select third_party/manifests.yml

#Ignore folders not tracked by irepo
irepo ignore-folder .git
irepo ignore-folder build
irepo ignore-folder driver
irepo ignore-folder scripts
irepo ignore-folder tests

#Download and synchronize third_party tools
irepo sync

## Generate Visual Studio project with CMake
mkdir build
cd build
cmake <path_to_source_dir> -G "Visual Studio 15 2017 Win64"
