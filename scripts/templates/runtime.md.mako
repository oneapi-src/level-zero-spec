# Runtime API Programming Guide
The following documents the high-level programming models and guidelines.

@cond DEV
DO NOT EDIT: generated from /scripts/templates/runtime.md.mako
@endcond

## Introduction
The Intel ${Xx} Runtime API provides...

### Naming Convention
todo: 
- all types follow **${x}_\<name\>_t** convention
- all macros and enumerator values use all caps **${X}_\<SCOPE\>_\<NAME\>** convention
- all functions use **${x}\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

### Error Handling
todo:
- all apis return ::${x}_result_t.
- apis are gaurenteed to never throw exceptions. etc.

## Runtime, Context and Device
todo

### Initialization
The following sample code demonstrates a basic initialization sequence:
```c
    ...
```

## Memory Allocation
todo

