# Runtime API Programming Guide
The following documents the high-level programming models and guidelines.

## Introduction
The Intel Xe Runtime API provides...

### Naming Convention
todo: 
- all types follow **xe_\<name\>_t** convention
- all macros and enumerator values use all caps **XE_\<SCOPE\>_\<NAME\>** convention
- all functions use **xe\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

### Error Handling
todo:
- all apis return ::xe_result_t.
- apis are gaurenteed to never throw exceptions. etc.

## Driver and Device
todo

### Initialization
The following sample code demonstrates a basic initialization sequence:
```c
    ...
```

## Memory Allocation
todo

