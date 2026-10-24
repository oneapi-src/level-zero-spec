
:orphan:

.. _ZE_external_semaphores:

=============================================
 External Semaphores Extension Specification
=============================================

.. rst-class:: ext-version

*Introduced in Level Zero version 1.12*

API
----

* Functions

    * :ref:`zeDeviceImportExternalSemaphoreExt`
    * :ref:`zeDeviceReleaseExternalSemaphoreExt`
    * :ref:`zeCommandListAppendSignalExternalSemaphoreExt`
    * :ref:`zeCommandListAppendWaitExternalSemaphoreExt`
    * :ref:`zeCommandQueueSignalExternalSemaphoreExt`
    * :ref:`zeCommandQueueWaitExternalSemaphoreExt`

* Enumerations

    * :ref:`ze-external-semaphore-ext-version-t`
    * :ref:`ze-external-semaphore-ext-flags-t`

* Structures

    * :ref:`ze-external-semaphore-ext-desc-t`
    * :ref:`ze-external-semaphore-win32-ext-desc-t`
    * :ref:`ze-external-semaphore-fd-ext-desc-t`
    * :ref:`ze-external-semaphore-signal-params-ext-t`
    * :ref:`ze-external-semaphore-wait-params-ext-t`

External Semaphores
~~~~~~~~~~~~~~~~~~~
Currently L0 supports importing external buffers and images from other graphics APIs such as DX12 and Vulkan, but does not support importing external semaphores.
The only solution that exists is to do synchronization at the host level, which may not be applicable for interop
with a fullying asynchronous rendering pipeline. Therefore, we need a new API that will accept the external semaphores
from other graphics APIs for synchronization to support interoperability. To this end, this extension introduces
APIs to import external semaphores, to append wait/signal using semaphores in the command list, and to release imported external semaphores.

Semantics and Behavior model
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. The semaphore signal command waits for a list of events to complete and then signals a list of semaphore objects.
2. The semaphore wait command waits for a list of events to complete and waits on a list of semaphore objects.
3. phWaitEvents points to the list of events that need to complete before :ref:`zeCommandListAppendSignalExternalSemaphoreExt` or :ref:`zeCommandListAppendWaitExternalSemaphoreExt` can be executed. If phWaitEvents is NULL, then the command does not wait on any event to complete.
4. Signal/Wait on the semaphore are async non blocking operation which doesn't cause serialization within a queue.
5. Application must perform semaphore signal and waits in alternate manner and order producer first. Repetitive signals and wait on same semaphore object is not supported.
6. The semaphore objects are currently only allowed to be imported into L0 and therefore the semaphore semantics/definitions of the exporter API needs to be honoured by the application.
7. Resetting semaphore object needs to be handled by the exporter as L0 capabilities are only to import and perform operations on the semaphore object itself.
8. :ref:`zeCommandListAppendSignalExternalSemaphoreExt` and :ref:`zeCommandListAppendWaitExternalSemaphoreExt` calls must only be executed on an immediate commandlist.
9. :ref:`zeCommandQueueSignalExternalSemaphoreExt` and :ref:`zeCommandQueueWaitExternalSemaphoreExt` place the same signal and wait operations on a command queue instead. The value is taken at submission rather than when the operation is appended, so a command list recorded once may be replayed with :ref:`zeCommandQueueExecuteCommandLists` against a different semaphore value each time. The operation is ordered against the other submissions to that queue.

Following pseudo-code demonstrates a sequence for importing external semaphore from Vulkan and using it in L0:

.. parsed-literal::
    // Import external semaphore from Vulkan
    VkSemaphore vkSemaphore = ...;  // Create Vulkan semaphores
    void ``*``\vkSemHandle = ...; //export VK semaphore

    :ref:`ze-external-semaphore-win32-ext-desc-t` win32Desc = {};
    win32Desc.handle = vkSemHandle;
    :ref:`ze-external-semaphore-ext-desc-t` desc = {:ref:`ZE_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_EXT_DESC <ze-structure-type-t>`\, &win32Desc, :ref:`ZE_EXTERNAL_SEMAPHORE_EXT_FLAG_OPAQUE_WIN32 <ze-external-semaphore-ext-flags-t>`\};

    ze_external_semaphore_ext_handle_t semaphore0 = nullptr;
    :ref:`zeDeviceImportExternalSemaphoreExt`\(device, &semaphore0, &desc);

    // Create command list and command queue
    ze_command_list_handle_t commandList = ...;
    ze_command_queue_handle_t commandQueue = ...;

    // Append wait on external semaphore in the command list and then launch kernel
    :ref:`ze-external-semaphore-wait-params-ext-t` waitParams = {};
    waitParams.pNext = nullptr;
    :ref:`zeCommandListAppendWaitExternalSemaphoreExt`\(commandList, &semaphore0, &waitParams, 1, event0, 0, nullptr);
    :ref:`zeCommandListAppendLaunchKernel`\(commandList, kernel, ..., event1, 1, &event0);

    // Append signal on external semaphore in the command after completion of kernel execution
    :ref:`ze-external-semaphore-signal-params-ext-t` signalParams = {};
    signalParams.pNext = nullptr;
    :ref:`zeCommandListAppendLaunchKernel`\(commandList, kernel, ..., event2, 0, nullptr);
    :ref:`zeCommandListAppendSignalExternalSemaphoreExt`\(commandList, &semaphore0, &signalParams, 1, event3, 1, &event2);

Queue-level signal and wait
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The command list functions above take their semaphore value when the operation is appended. That suits an
immediate command list, where appending is submitting, but it cannot express a value that changes per
submission: an application that records a command list once and replays it with
:ref:`zeCommandQueueExecuteCommandLists` would reuse the value captured at record time, and would have to
re-record the list for every new value.

:ref:`zeCommandQueueSignalExternalSemaphoreExt` and :ref:`zeCommandQueueWaitExternalSemaphoreExt` close that gap by
placing the operation on the command queue instead, taking the value at submission. The recorded command
list stays unmodified and reusable, and the operation is honoured in the queue's submission order.

Following pseudo-code demonstrates waiting on an imported semaphore before a recorded command list runs, and
signalling it once that command list completes:

.. parsed-literal::
    // Import the external semaphore as above
    ze_external_semaphore_ext_handle_t semaphore0 = nullptr;
    :ref:`zeDeviceImportExternalSemaphoreExt`\(device, &desc, &semaphore0);

    // Record the command list once, up front
    ze_command_list_handle_t commandList = ...;
    :ref:`zeCommandListAppendLaunchKernel`\(commandList, kernel, ..., nullptr, 0, nullptr);
    :ref:`zeCommandListClose`\(commandList);

    // Wait for the producer to reach the agreed value before the recorded work runs
    :ref:`ze-external-semaphore-wait-params-ext-t` waitParams = {};
    waitParams.value = producerValue;
    :ref:`zeCommandQueueWaitExternalSemaphoreExt`\(commandQueue, 1, &semaphore0, &waitParams, nullptr, 0, nullptr);

    :ref:`zeCommandQueueExecuteCommandLists`\(commandQueue, 1, &commandList, nullptr);

    // Signal the consumer once the submitted work completes
    :ref:`ze-external-semaphore-signal-params-ext-t` signalParams = {};
    signalParams.value = consumerValue;
    :ref:`zeCommandQueueSignalExternalSemaphoreExt`\(commandQueue, 1, &semaphore0, &signalParams, nullptr, 0, nullptr);
