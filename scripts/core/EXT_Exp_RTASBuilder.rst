<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_rtas_builder:

======================================================
 Ray Tracing Acceleration Structure Builder Extension
======================================================

API
----

* Enumerations


    * ${x}_rtas_builder_exp_version_t
    * ${x}_rtas_device_exp_flags_t
    * ${x}_rtas_format_exp_t
    * ${x}_rtas_builder_exp_flags_t
    * ${x}_rtas_parallel_operation_exp_flags_t
    * ${x}_rtas_builder_geometry_exp_flags_t
    * ${x}_rtas_builder_instance_exp_flags_t
    * ${x}_rtas_builder_build_op_exp_flags_t
    * ${x}_rtas_builder_build_quality_hint_exp_t
    * ${x}_rtas_builder_geometry_type_exp_t
    * ${x}_rtas_builder_input_data_format_exp_t


* Structures


    * ${x}_rtas_builder_exp_desc_t

    * ${x}_rtas_builder_exp_properties_t
    * ${x}_rtas_parallel_operation_exp_properties_t
    * ${x}_rtas_device_exp_properties_t

    * ${x}_rtas_float3_exp_t
    * ${x}_rtas_transform_float3x4_column_major_exp_t
    * ${x}_rtas_transform_float3x4_aligned_column_major_exp_t
    * ${x}_rtas_transform_float3x4_row_major_exp_t
    * ${x}_rtas_aabb_exp_t
    * ${x}_rtas_triangle_indices_uint32_exp_t
    * ${x}_rtas_quad_indices_uint32_exp_t

    * ${x}_rtas_builder_geometry_info_exp_t
    * ${x}_rtas_builder_triangles_geometry_info_exp_t
    * ${x}_rtas_builder_quads_geometry_info_exp_t
    * ${x}_rtas_builder_procedural_geometry_info_exp_t
    * ${x}_rtas_builder_instance_geometry_info_exp_t

    * ${x}_rtas_builder_build_op_exp_desc_t


* Functions


    * ${x}RTASBuilderCreateExp
    * ${x}RTASBuilderGetBuildPropertiesExp
    * ${x}RTASBuilderBuildExp
    * ${x}RTASBuilderDestroyExp

    * ${x}DriverRTASFormatCompatibilityCheckExp

    * ${x}RTASParallelOperationCreateExp
    * ${x}RTASParallelOperationGetPropertiesExp
    * ${x}RTASParallelOperationJoinExp
    * ${x}RTASParallelOperationDestroyExp


============================================
 Ray Tracing Acceleration Structure Builder
============================================

The Ray Tracing Acceleration Structure Builder extension provides the functionality to build ray tracing acceleration structures (RTAS) for 3D scenes on the host for use with GPU devices.

It is the user's responsibility to manage the acceleration structure buffer and scratch buffer resources. The required sizes may be queried via ${x}RTASBuilderGetBuildPropertiesExp. Once built, an acceleration structure is a self-contained entity; any input resources may be released after the successful construction. Note that acceleration structures are non-copyable resources.

Scene Data
-----------

To build an acceleration structure, first setup a scene that consists of one or more geometry infos.

    - ${x}_rtas_builder_triangles_geometry_info_exp_t for triangle meshes,
    - ${x}_rtas_builder_quads_geometry_info_exp_t for quad meshes,
    - ${x}_rtas_builder_procedural_geometry_info_exp_t for procedural primitives with attached axis-aligned bounding-box, and
    - ${x}_rtas_builder_instance_geometry_info_exp_t for instances of other acceleration structures.

The following example creates a ${x}_rtas_builder_triangles_geometry_info_exp_t to specify a triangle mesh:

.. parsed-literal::

        std::vector<${x}_rtas_triangle_indices_uint32_exp_t> triangleIndexBuffer;
        std::vector<${x}_rtas_float3_exp_t> triangleVertexBuffer;

        // Populate vertex and index buffers
        {
            // ...
        }

        ${x}_rtas_builder_triangles_geometry_info_exp_t mesh;
        memset(&mesh, 0, sizeof(mesh));

        mesh.geometryType = ${X}_RTAS_BUILDER_GEOMETRY_TYPE_EXP_TRIANGLES;
        mesh.geometryFlags = 0;
        mesh.geometryMask = 0xFF;

        mesh.triangleFormat = ${X}_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_TRIANGLE_INDICES_UINT32;
        mesh.triangleCount = triangleIndexBuffer.size();
        mesh.triangleStride = sizeof(${x}_rtas_triangle_indices_uint32_exp_t);
        mesh.pTriangleBuffer = triangleIndexBuffer.data();

        mesh.vertexFormat = ${X}_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_FLOAT3;
        mesh.vertexCount = triangleVertexBuffer.size();
        mesh.vertexStride = sizeof(${x}_rtas_float3_exp_t);
        mesh.pVertexBuffer = triangleVertexBuffer.data();

Geometry is considered to be opaque by default, enabling a fast mode where traversal does not return to the caller of ray tracing for each triangle or quad hit. To process each triangle or quad hit by some any-hit shader, the `geometryFlags` member of the geometry infos must include the ${X}_RTAS_BUILDER_GEOMETRY_EXP_FLAG_NON_OPAQUE flag. The proper data formats of the triangle index- and vertex- buffers are specified, including the strides, and a pointer to the first element for each buffer.

To refer to multiple geometries that make a scene, pointers to geometry info structures can be put into an array as follows:

.. parsed-literal::

        std::vector<${x}_rtas_builder_geometry_info_exp_t*> geometries;
        geometries.push_back((${x}_rtas_builder_geometry_info_exp_t*)&mesh0);
        geometries.push_back((${x}_rtas_builder_geometry_info_exp_t*)&mesh1);
        ...

This completes the definition of the geometry for the scene for which to construct the acceleration structure.

Device Properties
------------------

The next step is to query the target device for acceleration structure properties.

.. parsed-literal::

        ${x}_rtas_device_exp_properties_t rtasDeviceProps;
        rtasDeviceProps.stype = ${X}_STRUCTURE_TYPE_RTAS_DEVICE_EXP_PROPERTIES;
        rtasDeviceProps.pNext = nullptr;

        ${x}_device_properties_t deviceProps;
        deviceProps.stype = ${X}_STRUCTURE_TYPE_DEVICE_PROPERTIES;
        deviceProps.pNext = &rtasDeviceProps;

        ${x}DeviceGetProperties(hDevice, &deviceProps);


The device properties contain information (a device-specific ray tracing acceleration structure format) that is required to complete an RTAS build operation.


Acceleration Structure Builder
-------------------------------

With the scene data prepared and relevant device properties known, create a ray tracing acceleration structure builder object and query for the necessary build properties.

.. parsed-literal::

        ${x}_rtas_builder_exp_desc_t desc;
        desc.stype = ${X}_STRUCTURE_TYPE_RTAS_BUILDER_EXP_DESC;
        desc.pNext = nullptr;
        desc.builderVersion = ${X}_RTAS_BUILDER_EXP_VERSION_CURRENT;

        ${x}_rtas_builder_exp_handle_t hBuilder = nullptr;
        ${x}_result_t result = ${x}RTASBuilderCreateExp(hDriver, &desc, &hBuilder);
        assert(result == ${X}_RESULT_SUCCESS);

        ${x}_rtas_builder_exp_properties_t builderProps;
        builderProps.stype = ${X}_STRUCTURE_TYPE_RTAS_BUILDER_EXP_PROPERTIES;
        builderProps.pNext = nullptr;

        ${x}_rtas_builder_build_op_exp_desc_t buildOpDesc;
        buildOpDesc.stype = ${X}_STRUCTURE_TYPE_RTAS_BUILDER_BUILD_OP_EXP_DESC;
        buildOpDesc.pNext = nullptr;
        buildOpDesc.rtasFormat = rtasDeviceProps.rtasFormat;
        buildOpDesc.buildQuality = ${X}_RTAS_BUILDER_BUILD_QUALITY_HINT_EXP_MEDIUM;
        buildOpDesc.buildFlags = 0;
        buildOpDesc.ppGeometries = geometries.data();
        buildOpDesc.numGeometries = geometries.size();

        result = ${x}RTASBuilderGetBuildPropertiesExp(hBuilder, &buildOpDesc, &builderProps);
        assert(result == ${X}_RESULT_SUCCESS);

Note, the parameters of the build operation descriptor, such as acceleration structure build quality, affect the buffer requirements, etc.

An application may create and use a single RTAS builder object, as multiple concurrent build operations may be performed with a single such object.

Buffers
--------

With the builder properties along with everything else known at this point, the resources for the acceleration structure may be allocated.

Scratch Buffer
^^^^^^^^^^^^^^^

A system memory scratch buffer is required to perform the build operation. It is used by the implementation for intermediate storage.

.. parsed-literal::

        void* pScratchBuffer = malloc(builderProps.scratchBufferSizeBytes);

Acceleration Structure Buffer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The acceleration structure buffer is where the ray tracing acceleration structure is written to. It must be accessible on the host as well as the device; consequently, it must be allocated as a USM resource. This example uses the worst-case sizing.

.. parsed-literal::

        ${x}_raytracing_mem_alloc_ext_desc_t rtasMemAllocDesc;
        rtasMemAllocDesc.stype = ${X}_STRUCTURE_TYPE_DEVICE_RAYTRACING_EXT_PROPERTIES;
        rtasMemAllocDesc.pNext = nullptr;
        rtasMemAllocDesc.flags = 0;

        ${x}_device_mem_alloc_desc_t deviceMemAllocDesc;
        deviceMemAllocDesc.stype = ${X}_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC;
        deviceMemAllocDesc.pNext = &rtasMemAllocDesc;
        deviceMemAllocDesc.flags = ${X}_DEVICE_MEM_ALLOC_FLAG_BIAS_CACHED;
        deviceMemAllocDesc.ordinal = 0;

        ${x}_host_mem_alloc_desc_t hostMemAllocDesc;
        hostMemAllocDesc.stype = ${X}_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC;
        hostMemAllocDesc.pNext = nullptr;
        hostMemAllocDesc.flags = ${X}_HOST_MEM_ALLOC_FLAG_BIAS_CACHED;

        void* pRtasBuffer = nullptr;
        result = ${x}MemAllocShared(hContext, &deviceMemAllocDesc, &hostMemAllocDesc, builderProps.rtasBufferSizeBytesMaxRequired, rtasDeviceProps.rtasBufferAlignment, hDevice, &pRtasBuffer);
        assert(result == ${X}_RESULT_SUCCESS);

Executing an Acceleration Structure Build
------------------------------------------

Single-Threaded Build
^^^^^^^^^^^^^^^^^^^^^^

A single-threaded acceleration structure build on the host is initiated using ${x}RTASBuilderBuildExp.

.. parsed-literal::

        result = ${x}RTASBuilderBuildExp(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBuffer, builderProps.rtasBufferSizeBytesMaxRequired, nullptr, nullptr, nullptr, nullptr);
        assert(result == ${X}_RESULT_SUCCESS);

When the build completes successfully the acceleration structure buffer is ready for use by the ray tracing API.

Parallel Build
^^^^^^^^^^^^^^^

In order to speed up the build operation using multiple worker threads, a parallel operation object can be associated with the build operation and joined with the application-provided worker threads as in the following example:

    **Note**
    The following example uses `oneTBB <https://spec.oneapi.io/versions/latest/elements/oneTBB/source/nested-index.html>`_ to dispatch worker threads, but this is not a requirement.

.. parsed-literal::

        ${x}_rtas_parallel_operation_exp_handle_t hParallelOperation = nullptr;
        result = ${x}RTASParallelOperationCreateExp(hDriver, &hParallelOperation);
        assert(result == ${X}_RESULT_SUCCESS);

        // Initiate the acceleration structure build operation with a handle
        // of a parallel operation object. This causes the parallel operation to be
        // bound to the build operation and the function returns immediately without
        // building any acceleration structure yet.
        result = ${x}RTASBuilderBuildExp(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBuffer, builderProps.rtasBufferSizeBytesMaxRequired, hParallelOperation, nullptr, nullptr, nullptr);
        assert(result == ${X}_RESULT_EXP_RTAS_BUILD_DEFERRED);

        // Once the parallel operation is bound to the build operation the number
        // of worker threads to join the parallel operation can be queried.
        ${x}_rtas_parallel_operation_exp_properties_t parallelOpProps;
        parallelOpProps.stype = ${X}_STRUCTURE_TYPE_RTAS_PARALLEL_OPERATION_EXP_PROPERTIES;
        parallelOpProps.pNext = nullptr;

        result = ${x}RTASParallelOperationGetPropertiesExp(hParallelOperation, &parallelOpProps);
        assert(result == ${X}_RESULT_SUCCESS);

        // Now worker threads can join the build operation to perform the actual build
        // of the acceleration structure.
        tbb::parallel_for(0, parallelOpProps.maxConcurrency, 1, [&](uint32_t i) {
            ${x}_result_t buildResult = ${x}RTASParallelOperationJoinExp(hParallelOperation);
            assert(buildResult == ${X}_RESULT_SUCCESS);
        });

        // With the parallel operation complete, the parallel operation object can be released.
        result = ${x}RTASParallelOperationDestroyExp(hParallelOperation);
        assert(result == ${X}_RESULT_SUCCESS);

Note that the number of worker threads to be used can only be queried from the parallel operation object after it is bound to the build operation by the call to ${x}RTASBuilderBuildExp.


Conservative Acceleration Structure Buffer Size
------------------------------------------------

Sizing the acceleration structure buffer using the `rtasBufferSizeBytesMaxRequired` member of ${x}_rtas_builder_exp_properties_t guarantees that the build operation will not fail due to an out-of-memory condition. However, this size represents the memory requirement for the worst-case scenario and is larger than is typically needed. To reduce memory usage, the application may attempt to execute a build using an acceleration structure buffer sized to the `rtasBufferSizeBytesExpected` member of ${x}_rtas_builder_exp_properties_t. When using the expected size, however, it is possible for the build operation to fail with ${X}_RESULT_EXP_RTAS_BUILD_RETRY. If this occurs, the application may resize the acceleration structure buffer with an updated size estimate provided by the builder build API.

.. parsed-literal::

        ${x}_result_t result;

        void* pRtasBuffer = nullptr;
        size_t rtasBufferSizeBytes = builderProps.rtasBufferSizeBytesExpected;

        while (true)
        {
            pRtasBuffer = allocate_accel_buffer(rtasBufferSizeBytes);

            result = ${x}RTASBuilderBuildExp(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, nullptr, nullptr, nullptr, &rtasBufferSizeBytes);

            if (result == ${X}_RESULT_SUCCESS)
            {
                break;
            }

            assert(result == ${X}_RESULT_EXP_RTAS_BUILD_RETRY);

            free_accel_buffer(pRtasBuffer);
        }

The loop starts with the minimum acceleration buffer size for which the build will mostly likely succeed. If the build runs out of memory, ${X}_RESULT_EXP_RTAS_BUILD_RETRY is returned and the build is retried with a larger acceleration structure buffer.

The example above passes a pointer to the `rtasBufferSizeBytes` variable as a parameter to the build API, which it will update with a larger acceleration structure buffer size estimate to be used in the next attempt should the build operation fail. Alternatively, the application could increase the acceleration buffer size for the next attempt by some percentage, which could fail again, or just use the maximum size from the builder properties for the second attempt.

Cleaning Up
------------

Once the acceleration structure has been built, any resources associated with the build may be released. Additionally, any parallel operation objects should be destroyed as well as any builder objects.

.. parsed-literal::

        // Free the scratch buffer
        free(pScratchBuffer);

        // Destroy the builder object
        ${x}RTASBuilderDestroyExp(hBuilder);

        // Use the acceleration structure buffer with the ray tracing API
        {
            // ...
        }

        // Release the acceleration structure buffer once it is no longer needed
        ${x}MemFree(hContext, pRtasBuffer);
        pRtasBuffer = nullptr;
