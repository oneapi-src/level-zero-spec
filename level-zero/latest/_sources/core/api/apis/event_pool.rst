============================================================
Event Pool
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Event Pool Handles
==================


.. _ze-event-pool-handle-t:

ze_event_pool_handle_t
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeEventPoolCreate`, :ref:`zeEventPoolOpenIpcHandle`, :ref:`zeEventGetEventPool`
   | **Used by:** :ref:`zeEventPoolDestroy`, :ref:`zeEventCreate`, :ref:`zeEventPoolGetIpcHandle`, :ref:`zeEventPoolCloseIpcHandle`, :ref:`zeEventPoolGetContextHandle`, :ref:`zeEventPoolGetFlags`
   | **See also:** :ref:`Events (Programming Guide) <Events>`

.. cpp:type:: ze_event_pool_handle_t

    Handle of driver's event pool object.



Event Pool Functions
====================


.. _zeEventPoolCreate:

zeEventPoolCreate
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventPoolCreate
    :project: LevelZero


.. _zeEventPoolDestroy:

zeEventPoolDestroy
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventPoolDestroy
    :project: LevelZero


.. _zeEventPoolGetIpcHandle:

zeEventPoolGetIpcHandle
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventPoolGetIpcHandle
    :project: LevelZero


.. _zeEventPoolOpenIpcHandle:

zeEventPoolOpenIpcHandle
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventPoolOpenIpcHandle
    :project: LevelZero


.. _zeEventPoolCloseIpcHandle:

zeEventPoolCloseIpcHandle
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeEventPoolCloseIpcHandle
    :project: LevelZero


.. _zeEventPoolPutIpcHandle:

zeEventPoolPutIpcHandle
-----------------------

.. rst-class:: api-version

*Added in version 1.6*

.. doxygenfunction:: zeEventPoolPutIpcHandle
    :project: LevelZero


.. _zeEventPoolGetContextHandle:

zeEventPoolGetContextHandle
---------------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeEventPoolGetContextHandle
    :project: LevelZero


.. _zeEventPoolGetFlags:

zeEventPoolGetFlags
-------------------

.. rst-class:: api-version

*Added in version 1.9*

.. doxygenfunction:: zeEventPoolGetFlags
    :project: LevelZero



Event Pool Enums
================


.. _ze-event-pool-flags-t:

ze_event_pool_flags_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeEventPoolGetFlags`
   | **Member of:** :ref:`ze-event-pool-desc-t`

.. doxygentypedef:: ze_event_pool_flags_t
    :project: LevelZero

.. doxygenenum:: ze_event_pool_flag_t
    :project: LevelZero


 
Event Pool Structures
=====================


.. _ze-event-pool-desc-t:

ze_event_pool_desc_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeEventPoolCreate`
   | **pNext may point to:** :ref:`ze-event-pool-counter-based-exp-desc-t`

.. doxygenstruct:: ze_event_pool_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

