============================================================
Tools - Deprecated
============================================================

Everything below is deprecated. Use the replacement where one is listed.

The reference pages are under :doc:`Deprecated APIs <api/deprecated/index>`.

Extensions
----------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :doc:`ZET_experimental_api_tracing <EXT_Exp_APITracing>`
     - 1.14
     - `L0 Loader API Tracing <https://github.com/oneapi-src/level-zero/tree/master/source/layers/tracing>`__
     - Not supported in L0 drivers; tracing moved to the loader.

Functions
---------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :ref:`zetMetricCreateFromProgrammableExp`
     - 1.11
     - :ref:`zetMetricCreateFromProgrammableExp2`
     - 
   * - :ref:`zetMetricGroupCreateExp`
     - 1.12
     - :ref:`zetDeviceCreateMetricGroupsFromMetricsExp`
     - 

Enumeration values
------------------

.. list-table::
   :header-rows: 1
   :widths: 28 6 28 38
   :class: deprecated-table

   * - Name
     - Since
     - Replacement
     - Notes
   * - :ref:`ZET_METRIC_TYPE_IP_EXP <zet-metric-type-t>`
     - 1.7
     - :ref:`ZET_METRIC_TYPE_IP <zet-metric-type-t>`
     - 
   * - :ref:`ZET_STRUCTURE_TYPE_GLOBAL_METRICS_TIMESTAMPS_EXP_PROPERTIES <zet-structure-type-t>`
     - 1.7
     - :ref:`ZET_STRUCTURE_TYPE_METRIC_GLOBAL_TIMESTAMPS_RESOLUTION_EXP <zet-structure-type-t>`
     - 
   * - :ref:`ZET_STRUCTURE_TYPE_METRICS_CALCULATE_EXP_DESC <zet-structure-type-t>`
     - 1.7
     - :ref:`ZET_STRUCTURE_TYPE_METRIC_CALCULATE_EXP_DESC <zet-structure-type-t>`
     - 
