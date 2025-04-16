
:orphan:

.. _ZET_experimental_metric_export_memory:


=======================================================
MetricGroup and Metric Export Memory Extension
=======================================================

API
----

* Enumerations

    * :ref:`zet-metric-group-type-exp-flags-t`

* Structures

    * :ref:`zet-metric-group-type-exp-t`
    * :ref:`zet-export-dma-buf-exp-properties-t`

Sample Code
------------

The following pseudo-code demonstrates how to map memory exported by metric groups:

.. parsed-literal::

       // Request Metric group type using `pNext` of :ref:`zet-metric-group-properties-t`
       zet_metric_group_type_exp_t metricGroupType;
       metricGroupType.stype = :ref:`ZET_STRUCTURE_TYPE_METRIC_GROUP_TYPE_EXP <zet-structure-type-t>`\;

       zet_metric_group_properties_t metricGroupProperties;
       metricGroupProperties.stype = :ref:`ZET_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES <zet-structure-type-t>`\;
       metricGroupProperties.pNext = &metricGroupType;
       zetMetricGroupGetProperties(hMetricGroup, &metricGroupProperties);

       if(metricGroupType.type == ZET_METRIC_GROUP_TYPE_EXP_EXPORT_DMA_BUF){
            zet_export_dma_buf_exp_properties_t dmaBufProperties;
            dmaBufProperties.stype = :ref:`ZET_STRUCTURE_TYPE_EXPORT_DMA_EXP_PROPERTIES <zet-structure-type-t>`\;
            metricGroupProperties.pNext = &dmaBufProperties;
            zetMetricGroupGetProperties(hMetricGroup, &metricGroupProperties);

            // Import the dma buf
            ze_external_memory_import_fd_t importDmaBuf = {
                .stype = ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
                .flags = ZE_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF,
                .fd = dmaBufProperties.fd;
            };

            ze_device_mem_alloc_desc_t allocDesc = {
                .stype = ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC,
                .pNext = &importDmaBuf,
                .flags = 0,
                .ordinal = 0
            };

            void * pMappedAddress = nullptr;
            zeMemAllocDevice(hContext, &allocDesc, dmaBufProperties.size, 4096, hDevice, &pMappedAddress);
       }

The following pseudo-code demonstrates how to map memory exported by metrics:

.. parsed-literal::

       // Request Metric group type using `pNext` of :ref:`zet-metric-properties-t`

       zet_metric_properties_t metricProperties;
       metricProperties.stype = :ref:`ZET_STRUCTURE_TYPE_METRIC_PROPERTIES <zet-structure-type-t>`\;
       zetMetricGetProperties(hMetric, &metricProperties);

       if(metricProperties.metricType == ZET_METRIC_TYPE_EXP_EXPORT_DMA_BUF){
            zet_export_dma_buf_exp_properties_t dmaBufProperties;
            dmaBufProperties.stype = :ref:`ZET_STRUCTURE_TYPE_EXPORT_DMA_EXP_PROPERTIES <zet-structure-type-t>`\;
            metricProperties.pNext = &dmaBufProperties;
            zetMetricGetProperties(hMetricGroup, &metricProperties);

            // Import the dma buf
            ze_external_memory_import_fd_t importDmaBuf = {
                .stype = ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_FD,
                .flags = ZE_EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF,
                .fd = dmaBufProperties.fd;
            };

            ze_device_mem_alloc_desc_t allocDesc = {
                .stype = ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC,
                .pNext = &importDmaBuf,
                .flags = 0,
                .ordinal = 0
            };

            void * pMappedAddress = nullptr;
            zeMemAllocDevice(hContext, &allocDesc, dmaBufProperties.size, 4096, hDevice, &pMappedAddress);
       }
