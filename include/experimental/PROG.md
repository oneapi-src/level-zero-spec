# Programming Guide (Experimental)

[DO NOT EDIT]: # (generated from /scripts/experimental/PROG.md)

The following documents the high-level programming models and guidelines.  

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

## Table of Contents
* [Initialization](#init)
* [Device-Specific Commands](#dsc)
* [Command Graphs](#cg)
* [Future](#fut)

# <a name="init">Initialization</a>
The driver must be initialized by calling ::xexInit after calling ::xeInit and before calling any other experimental function.
Simultaneous calls to ::xexInit are thread-safe.

# <a name="dsc">Device-Specific Commands</a>
::xexCommandListReserveSpace provides direct access to the command list's command buffers in order to allow unrestricted access the device's capabilities.
The application is solely responsible for ensuring the commands are valid and correct for the specific device.

```c
    void* ptr = nullptr;
    xexCommandListReserveSpace(hCommandList, sizeof(blob), &ptr);
    ::memcpy(ptr, blob, sizeof(blob));
```

# <a name="cg">Command Graphs</a>
Goals:
- ability to represent non-linear dependencies between programs to be executed
- ability to represent flow-control
- ability to represent scheduling and distribution across multiple sub-devices

# <a name="fut">Future</a>
The following is a list a features that are still being defined for inclusion:
- **Predicated Execution**
    + ability to cull program execution within a command list, based on device-generated value(s)
- **Execution Flow-Control**
    + ability to describe loops and if-else-then type program execution within a command list, based on device-generated value(s)

