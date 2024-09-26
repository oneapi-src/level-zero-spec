<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    t=tags['$t']
    T=t.upper()
%>
:orphan:

.. _ZET_experimental_metric_export_memory:

==============================================
 MetricGroup and Metric Export Memory Extension
==============================================

API
----

* Enumerations

    * ${t}_metric_group_type_exp_flags_t

* Structures

    * ${t}_metric_group_type_exp_t
    * ${t}_export_dma_buf_exp_properties_t

Sample Code
------------

The following pseudo-code demonstrates how to map memory exported by metric groups:

.. parsed-literal::

       // Request Metric group type using `pNext` of ${t}_metric_group_properties_t
       zet_metric_group_type_exp_t metricGroupType;
       metricGroupType.stype = ${T}_STRUCTURE_TYPE_METRIC_GROUP_TYPE_EXP;

       zet_metric_group_properties_t metricGroupProperties;
       metricGroupProperties.stype = ${T}_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES;
       metricGroupProperties.pNext = &metricGroupType;
       zetMetricGroupGetProperties(hMetricGroup, &metricGroupProperties);

       if(metricGroupType.type == ZET_METRIC_GROUP_TYPE_EXP_EXPORT_DMA_BUF){
            zet_export_dma_buf_exp_properties_t dmaBufProperties;
            dmaBufProperties.stype = ${T}_STRUCTURE_TYPE_EXPORT_DMA_EXP_PROPERTIES;
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

       // Request Metric group type using `pNext` of ${t}_metric_properties_t

       zet_metric_properties_t metricProperties;
       metricProperties.stype = ${T}_STRUCTURE_TYPE_METRIC_PROPERTIES;
       zetMetricGetProperties(hMetric, &metricProperties);

       if(metricProperties.metricType == ZET_METRIC_TYPE_EXPORT_DMA_BUF){
            zet_export_dma_buf_exp_properties_t dmaBufProperties;
            dmaBufProperties.stype = ${T}_STRUCTURE_TYPE_EXPORT_DMA_EXP_PROPERTIES;
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
