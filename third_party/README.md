# Third-Party Tools
* Third party tools requires access and secure connection to compute runtime repo.

* ssh rsa key can be generated if you don't already have one.
~~~~
ssh-keygen -t rsa
~~~~

* Upload ssh rsa public key to https://gerrit-gfx.intel.com/#/settings/ssh-keys
* Test ssh connection to gerrit for compute-runtimevia:
~~~~
ssh {idsid}@gerrit-gfx.intel.com -p 29418
~~~~

* If third_party tools are not installed locally, they can be installed via irepo (https://github.intel.com/gsdi/irepo).
* Option: add irepo.bat to your PATH

* Pick the manifest
~~~~
cd {workspace root folder}
irepo.bat select third_party/windows.yml
~~~~

* OPTIONAL: Ignore folders not tracked by irepo
~~~~
irepo.bat ignore-folder .git
irepo.bat ignore-folder build
irepo.bat ignore-folder core
irepo.bat ignore-folder extended
irepo.bat ignore-folder images
irepo.bat ignore-folder samples
irepo.bat ignore-folder scripts
irepo.bat ignore-folder tests
~~~~

* Download and synchronize third_party tools
~~~~
irepo.bat sync
~~~~

* Generate Visual Studio project with CMake
~~~~
mkdir build
cd build
cmake <path_to_source_dir> -G "Visual Studio 15 2017 Win64"
~~~~