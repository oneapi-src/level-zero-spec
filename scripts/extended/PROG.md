${"#"} Programming Guide (Extended)
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    e=tags['$e']
    E=e.upper()
%>
[DO NOT EDIT]: # (generated from /scripts/extended/PROG.md)

The following documents the high-level programming models and guidelines.  

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

${"##"} Table of Contents
* [Command Graphs](#cg)
* [Future](#fut)

${"#"} <a name="cg">Command Graphs</a>
Goals:
- ability to represent non-linear dependencies between programs to be executed
- ability to represent flow-control
- ability to represent scheduling and distribution across multiple sub-devices

${"#"} <a name="fut">Future</a>
The following is a list a features that are still being defined for inclusion:
- **Predicated Execution**
    + ability to cull program execution within a command list, based on device-generated value(s)
- **Execution Flow-Control**
    + ability to describe loops and if-else-then type program execution within a command list, based on device-generated value(s)
- **C++ Interfaces**
    + ability to choose between C and C++ interfaces (e.g., by wrapping C++ interfaces with C interfaces)
