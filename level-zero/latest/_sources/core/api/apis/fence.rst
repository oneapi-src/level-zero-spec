============================================================
Fence
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Fence Handles
=============


.. _ze-fence-handle-t:

ze_fence_handle_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeFenceCreate`
   | **Used by:** :ref:`zeCommandQueueExecuteCommandLists`, :ref:`zeFenceDestroy`, :ref:`zeFenceHostSynchronize`, :ref:`zeFenceQueryStatus`, :ref:`zeFenceReset`
   | **See also:** :ref:`Fences (Programming Guide) <Fences>`

.. cpp:type:: ze_fence_handle_t

    Handle of driver's fence object.



Fence Functions
===============


.. _zeFenceCreate:

zeFenceCreate
-------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeFenceCreate
    :project: LevelZero


.. _zeFenceDestroy:

zeFenceDestroy
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeFenceDestroy
    :project: LevelZero


.. _zeFenceHostSynchronize:

zeFenceHostSynchronize
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeFenceHostSynchronize
    :project: LevelZero


.. _zeFenceQueryStatus:

zeFenceQueryStatus
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeFenceQueryStatus
    :project: LevelZero


.. _zeFenceReset:

zeFenceReset
------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeFenceReset
    :project: LevelZero



Fence Enums
===========


.. _ze-fence-flags-t:

ze_fence_flags_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-fence-desc-t`

.. doxygentypedef:: ze_fence_flags_t
    :project: LevelZero

.. doxygenenum:: ze_fence_flag_t
    :project: LevelZero


 
Fence Structures
================


.. _ze-fence-desc-t:

ze_fence_desc_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeFenceCreate`

.. doxygenstruct:: ze_fence_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

