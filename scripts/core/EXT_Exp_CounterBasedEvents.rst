<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_event_counter_based:

=========================
 Counter-Based Events Extension
=========================

API
----
 
* Enumerations

    * ${x}_event_counter_based_exp_flags_t
    * ${x}_event_counter_based_exp_version_t

* Structures

    * ${x}_event_counter_based_exp_desc_t

Counter-Based Events
~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, events in Level Zero contains one of two states: signaled or not signaled.
Signaling of an event, as well as resetting its state, can be done from either host or
device.

Another way of tracking the state of an event is by using a counter, which is incremented
every time a task has completed in the device. Using a counter-based event may be
provide Level Zero driver implementations with the opportunity for both
functional and performance optimizations.

The following recommendations and restrictions apply to counter-based events:

- Counter-based events can be used only with in-orders lists, whether those are regular or immediate.
- Counter-based events must not be reset, i.e., a call to ${x}EventHostSynchronize or ${x}CommandListAppendEventReset
  is not allowed. Counter-based events may be reused multiple times without a need for reset.
- Counter-based events must not be signaled from host, i.e., a call to ${x}EventHostSignal is not allowed.
- Counter-based events may be used on multiple command lists.
- Querying a counter-based event returns only the last saved counter value from the last command list that incremented it.
- Synchronizing on a counter-based event waits only the last saved counter value from the last command list that incremented it.