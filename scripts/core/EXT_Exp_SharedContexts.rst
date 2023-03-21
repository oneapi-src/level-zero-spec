<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_shared_contexts:

=====================================
 Shared-Contexts Extension
=====================================

API
----

* Enumerations


    * ${x}_shared_contexts_exp_version_t


* Functions

    * ${x}MemGetAllocPropertiesExp
    * ${x}DriverGetSharedContextExp
    * ${x}DriverAddContextToSharedExp

Shared Contexts
~~~~~~~~~~~~~~~~~~~~~~~~~~

Contexts provide a way to isolate resources in an Level Zero application. Specifically,
USM allocations are created with a context handle and can be used only with
other objects (like command lists) that have been created with the same context.

To be able to use those resources in applications where USM pointers
(and not their contexts) are exchanged between multiple libraries, the concept
of shared contexts interfaces is defined.

A shared context is an Level Zero context handle that encompases a set of contexts
handles. Any Level Zero object belonging to one of the contexts
associated with the shared context can be used and interact with an object of the other
peer contexts. Ownership of L0 objects is not transferred, however.

A given context can only belong to a single shared context, and once created,
a shared context can be used normally in any API. Objects created using
the shared context handle implicitly belong to all the contexts associated with
it. A shared context remains valid until its last context is destroyed.
