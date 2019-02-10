
# Unit Level Tests
Unit level tests (ULTs) are stored in this folder and leverage GoogleTest and GoogleMock located installed on the system or in the third_party folder. 

* **All new functional driver code should have corresponding ULTs for rapid feedback**.
* ULTs should be as focused as possible to enhance readability and facilitate regression debug.
* ULTs should be written in a test-driven approach to help enforce proper coverage of all new features.
* ULTs are designed to support testing of multiple generations and product families of hardware.  
    - Currently, the tests are hard-coded to behave as though the target gpu is Skylake Gen9.  
    - A command line option will be added to specify other targets in the near future.
- HW specific tests such as ones relying on HW specific *types* should be prefixed as in **HWTEST_F**. 
- HW specific tests can target specific generations such as **GEN9TEST_F**.
- Product family specific tests can target specific families such as **SKLTEST_F**.

**Core driver code**
Core driver code may reside in this folder from time to time depending on various stages of iterative development.  Core driver code should ultimately reside in a folder in the base directory.  Core driver code that happens to be in here should be treated as heavily under development and is not yet available in the core driver library.  **Functionality ready for external usage must be put in the proper core driver library folder**.

# Test Samples
One or more samples may exist in this folder as a proof point of integration and more realistic workloads.  One such example is currently located in **test_sample.cpp**.  By default it behaves like a ULT.  Changing configuration settings as demonstrated below allows it to feed a live simulator via TBX or generate an AUB file for offline analysis and testing.

# Generating AUB files
AUB file generation during ULT execution is **disabled by default**.  Setting the following compute runtime configuration prior to running the ULTs can generate one or more AUB files. Example below generates the default product family (currently Skylake) Fulsim AUB file(s).

**Windows**:  
  * HKLM/Software/Intel/IGFX/OCL/SetCommandStreamReceiver | REG_DWORD | **0x00000001**
~~~~
    level_zero_unit_tests.exe
  ~~~~

**Linux**:
  * Set the environment variable SetCommandStreamReceiver to **1** prior to executing ULTs
  ~~~~
    SetCommandStreamReceiver=1 ./level_zero_unit_tests
  ~~~~

# Driving a simulator via TBX
TBX driven simulation during ULT execution is **disabled by default**.  By setting the following compute runtime configuration and launching a simulator prior to running the ULTs can initiate a simulator connection.  Example below currently initiates a socket connection with the default product family (currently Skylake) Fulsim.  

**Windows**:  
  * HKLM/Software/Intel/IGFX/OCL/SetCommandStreamReceiver | REG_DWORD | **0x00000002**
~~~~
    aubload.exe -socket tcp -device skl.3.a0
    level_zero_unit_tests.exe
  ~~~~

**Linux**:
  * Set the environment variable SetCommandStreamReceiver to **2** prior to executing ULTs
  ~~~~
    ./aubload -socket tcp -device skl.3.a0
    SetCommandStreamReceiver=2 ./level_zero_unit_tests
  ~~~~
  
