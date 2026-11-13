============================================================
Sampler
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Sampler Handles
===============


.. _ze-sampler-handle-t:

ze_sampler_handle_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zeSamplerCreate`
   | **Used by:** :ref:`zeSamplerDestroy`
   | **See also:** `Sampler (Programming Guide) <../../PROG.html#sampler>`__

.. cpp:type:: ze_sampler_handle_t

    Handle of driver's sampler object.



Sampler Functions
=================


.. _zeSamplerCreate:

zeSamplerCreate
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeSamplerCreate
    :project: LevelZero


.. _zeSamplerDestroy:

zeSamplerDestroy
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zeSamplerDestroy
    :project: LevelZero



Sampler Enums
=============


.. _ze-sampler-address-mode-t:

ze_sampler_address_mode_t
-------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-sampler-desc-t`

.. doxygenenum:: ze_sampler_address_mode_t
    :project: LevelZero


.. _ze-sampler-filter-mode-t:

ze_sampler_filter_mode_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`ze-sampler-desc-t`

.. doxygenenum:: ze_sampler_filter_mode_t
    :project: LevelZero


 
Sampler Structures
==================


.. _ze-sampler-desc-t:

ze_sampler_desc_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zeSamplerCreate`
   | **Goes in pNext of:** :ref:`ze-image-bindless-exp-desc-t`

.. doxygenstruct:: ze_sampler_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

