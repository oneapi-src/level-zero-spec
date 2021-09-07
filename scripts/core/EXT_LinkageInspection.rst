<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_linkage_inspection:

======================================
 Linkage Inspection Extension
======================================

API
----

* Functions


    * ${x}ModuleListImportsExt
    * ${x}ModuleListUnresolvableImportsExt
    * ${x}ModuleListExportsExt

Linkage Inspection
~~~~~~~~~~~~~~~~~~

Modules support SPIR-V linkage, i.e., modules can import and export global variables and function definitions to/from other modules. This extension provides an API to inspect the linkage properties & requirements of a collection of modules.

Modules may require global variables & functions to be imported before all dependencies are satisfied. The following psuedo-code demonstrates a sequence for inspecting the import requirements of a set of modules:

.. parsed-literal::

       ...
       ${x}_module_build_log_handle_t importlog;
       ${x}_result_t result = ${x}ModuleListImportsExt(numModules, &hModules, &importlog);

       size_t szLog = 0;
       ${x}ModuleBuildLogGetString(importlog, &szLog, nullptr);

       char_t* strLog = allocate(szLog);
       ${x}ModuleBuildLogGetString(importlog, &szLog, strLog);

       // Save log to disk.
       ...

       free(strLog);

       ${x}ModuleBuildLogDestroy(importlog);

Modules may export global variables & functions that can be imported by dependent modules. The following psuedo-code demonstrates a sequence for inspecting the exports of a set of modules:

.. parsed-literal::

       ...
       ${x}_module_build_log_handle_t exportlog;
       ${x}_result_t result = ${x}ModuleListExportsExt(numModules, &hModules, &exportlog);

       size_t szLog = 0;
       ${x}ModuleBuildLogGetString(exportlog, &szLog, nullptr);

       char_t* strLog = allocate(szLog);
       ${x}ModuleBuildLogGetString(exportlog, &szLog, strLog);

       // Save log to disk.
       ...

       free(strLog);

       ${x}ModuleBuildLogDestroy(exportlog);

A set of modules can be checked for unsatisfied import dependencies, i.e., imports required by one of more module in the set that are not met by other modules from within the set. Modules must be added to the set until no unsatisfied import dependencies remain. The following psuedo-code demonstrates a sequence for inspecting the unsatisfied import dependencies of a set of modules:

.. parsed-literal::

       ...
       ${x}_module_build_log_handle_t log;
       ${x}_result_t result = ${x}ModuleListExportsExt(numModules, &hModules, &log);

       size_t szLog = 0;
       ${x}ModuleBuildLogGetString(log, &szLog, nullptr);

       char_t* strLog = allocate(szLog);
       ${x}ModuleBuildLogGetString(log, &szLog, strLog);

       // Save log to disk.
       ...

       free(strLog);

       ${x}ModuleBuildLogDestroy(log);
