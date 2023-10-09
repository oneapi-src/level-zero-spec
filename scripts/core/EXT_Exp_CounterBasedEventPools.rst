<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_event_pool_counter_based:

=====================================
 Counter-Based Event Pools Extension
=====================================

API
----
 
* Enumerations

    * ${x}_event_pool_counter_based_exp_flags_t
    * ${x}_event_pool_counter_based_exp_version_t

* Structures

    * ${x}_event_pool_counter_based_exp_desc_t

Counter-Based Events
~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, events in Level Zero contains one of two states: signaled or not signaled.
Signaling of an event, as well as resetting its state, can be done from either host or
device.

Another way of tracking the state of an event is by using a counter, which is incremented
every time a task has completed in the device. Using a counter-based event may provide
Level Zero driver implementations with the opportunity for both functional and performance
optimizations.

The following recommendations and restrictions apply to counter-based events:

- Counter-based events can be used only with in-orders lists, whether those are regular or immediate.
- Counter-based events must not be reset, i.e., a call to ${x}EventHostReset or ${x}CommandListAppendEventReset
  is not allowed.
- Counter-based events must not be signaled from host, i.e., a call to ${x}EventHostSignal is not allowed.
- Counter-based events may be reused multiple times without a need for reset.
- Counter-based events may be used on multiple command lists.
- Querying a counter-based event queries only the last saved counter value from the last command list that incremented it,
  i.e., a signaled counter-based event always represents the completion of the last call to which it was passed as signal event.
- Synchronizing on a counter-based event waits only the last saved counter value from the last command list that incremented it.
- A counter-based event may be passed as signaling event for a new append call without needing to wait for the signaling of
  the last call where it was used.

Counter-based events can be created by passing ${x}_event_pool_counter_based_exp_desc_t to ${x}EventPoolCreate
as pNext member of ${x}_event_pool_desc_t.

.. parsed-literal::

    uint32_t numEvents = 2;
    ${x}_event_pool_handle_t eventPool = {};
    ${x}_event_pool_desc_t eventPoolDesc = {${X}_STRUCTURE_TYPE_EVENT_POOL_DESC};
    eventPoolDesc.count = numEvents;

    ${x}_event_pool_counter_based_exp_desc_t counterBasedDesc = {${X}_STRUCTURE_TYPE_COUNTER_BASED_EVENT_POOL_EXP_DESC};
    counterBasedDesc.flags = ${X}_EVENT_POOL_COUNTER_BASED_EXP_FLAG_IMMEDIATE;
    eventPoolDesc.pNext = &counterBasedDesc;

    ${x}_result_t = zeEventPoolCreate(context, &eventPoolDesc, 1, &device, &eventPool));
