# Black Box Tests
Black box tests are stored in this folder.   They are meant to demonstrate usage in a basic way. These samples exist as a proof point of integration and more realistic workloads.  Changing configuration settings as demonstrated below allows the application to drive a live simulator via TBX or generate an AUB file for offline analysis and testing.

# xello_world
This example demonstrates loading the runtime directly. It invokes a simple function to copy memory from one buffer to another.

# xello_world_icd
This example leverages the ICD loader to load the runtime dynamically. It invokes a simple function to copy memory from one buffer to another.

# xello_world_icd_clang
This example leverages the ICD loader to load the runtime dynamically. It invokes a simple function to copy memory from one buffer to another. It uses ocloc_shared library to compile OCL C to spirV at runtime.

# Generating ATS AUB files
**AUB file generation during execution is currently the only supported path of driver execution**.  Setting the following compute runtime configuration prior to running the applications will generate an ATS AUB file. Currently only ATS is confirmed as executing on the Fulsim simulator.

**Windows**:  
  * HKLM/Software/Intel/IGFX/OCL/ProductFamilyOverride | REG_SZ | **ats**
  * HKLM/Software/Intel/IGFX/OCL/SetCommandStreamReceiver | REG_DWORD | **0x00000001**
~~~~
    xello_world.exe
  ~~~~

**Linux**:
  * Set the environment variable SetCommandStreamReceiver to **1** and ProductFamilyOverride to **ats** prior to executing
  ~~~~
    SetCommandStreamReceiver=1 ProductFamilyOverride=ats ./xello_world
  ~~~~

# **TODO** Driving a simulator via TBX 
TBX driven simulation during execution is **currently broken**.  By setting the following compute runtime configuration and launching a simulator prior to running the application can initiate a simulator connection.  Example below currently initiates a socket connection with ATS Fulsim.  

**Windows**:  
  * HKLM/Software/Intel/IGFX/OCL/ProductFamilyOverride | REG_SZ | **ats**
  * HKLM/Software/Intel/IGFX/OCL/SetCommandStreamReceiver | REG_DWORD | **0x00000002**
~~~~
    aubload.exe -socket tcp -device ats.2x4x16.a0
    xello_world.exe
  ~~~~

**Linux**:
  * Set the environment variable SetCommandStreamReceiver to **2** and ProductFamilyOverride to **ats** prior to executing
  ~~~~
    ./aubload -socket tcp -device ats.2x4x16.a0
    SetCommandStreamReceiver=2 ProductFamilyOverride=ats ./xello_world
  ~~~~
  
