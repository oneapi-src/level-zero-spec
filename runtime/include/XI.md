# Runtime API Programming Guide
The following documents the high-level programming models and guidelines.

@cond DEV
DO NOT EDIT: generated from /scripts/templates/runtime.md.mako
@endcond

The Intel Xi Runtime API provides...

todo: 
- all types follow **xi_\<name\>_t** convention
- all macros and enumerator values use all caps **XI_\<SCOPE\>_\<NAME\>** convention
- all functions use **xi\<Actor\>\<Action\>\<Object\>** convention
- all function input parameters precede output parameters

todo:
- all apis return ::xi_result_t.
- apis are gaurenteed to never throw exceptions. etc.

![Context Hierarchy](../images/context.png?raw=true)

- A context manages memory, command queues and programs for execution on one or more devices

- A device represents a physical device in the system that can support Xi.
- More than one device may be avilable in the system.

The following sample code demonstrates a basic initialization sequence:
```c
    ...
```

todo

