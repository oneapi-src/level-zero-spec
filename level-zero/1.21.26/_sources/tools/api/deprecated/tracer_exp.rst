============================================================
Tracer Exp - Deprecated
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Tracer Exp - Deprecated Handles
===============================


.. _zet-tracer-exp-handle-t:

zet_tracer_exp_handle_t
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.14. Only used by the deprecated API Tracing extension. Use `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__ instead.

.. container:: api-usage

   | **Obtained from:** :ref:`zetTracerExpCreate`
   | **Used by:** :ref:`zetTracerExpDestroy`, :ref:`zetTracerExpSetPrologues`, :ref:`zetTracerExpSetEpilogues`, :ref:`zetTracerExpSetEnabled`

.. cpp:type:: zet_tracer_exp_handle_t

    Handle of tracer object.



Tracer Exp - Deprecated Functions
=================================


.. _zetTracerExpCreate:

zetTracerExpCreate
------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.14. Not supported in L0 drivers; tracing moved to the loader. Use `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__ instead.

.. doxygenfunction:: zetTracerExpCreate
    :project: LevelZero


.. _zetTracerExpDestroy:

zetTracerExpDestroy
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.14. Not supported in L0 drivers; tracing moved to the loader. Use `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__ instead.

.. doxygenfunction:: zetTracerExpDestroy
    :project: LevelZero


.. _zetTracerExpSetPrologues:

zetTracerExpSetPrologues
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.14. Not supported in L0 drivers; tracing moved to the loader. Use `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__ instead.

.. doxygenfunction:: zetTracerExpSetPrologues
    :project: LevelZero


.. _zetTracerExpSetEpilogues:

zetTracerExpSetEpilogues
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.14. Not supported in L0 drivers; tracing moved to the loader. Use `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__ instead.

.. doxygenfunction:: zetTracerExpSetEpilogues
    :project: LevelZero


.. _zetTracerExpSetEnabled:

zetTracerExpSetEnabled
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.14. Not supported in L0 drivers; tracing moved to the loader. Use `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__ instead.

.. doxygenfunction:: zetTracerExpSetEnabled
    :project: LevelZero




Tracer Exp - Deprecated Typedefs
================================


.. _zet-core-callbacks-t:

zet_core_callbacks_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.14. Not supported in L0 drivers; tracing moved to the loader. Use `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__ instead.

.. container:: api-usage

   | **Used by:** :ref:`zetTracerExpSetPrologues`, :ref:`zetTracerExpSetEpilogues`

.. doxygentypedef:: zet_core_callbacks_t
    :project: LevelZero

 
Tracer Exp - Deprecated Structures
==================================


.. _zet-tracer-exp-desc-t:

zet_tracer_exp_desc_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. rst-class:: api-deprecated

**Deprecated** since 1.14. Not supported in L0 drivers; tracing moved to the loader. Use `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__ instead.

.. container:: api-usage

   | **Used by:** :ref:`zetTracerExpCreate`

.. doxygenstruct:: zet_tracer_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:

