
:orphan:

.. _ZE_experimental_rtas_builder:

======================================================
 Ray Tracing Acceleration Structure Builder Extension
======================================================

API
----

* Enumerations


    * :ref:`ze-rtas-builder-exp-version-t`
    * :ref:`ze-rtas-device-exp-flags-t`
    * :ref:`ze-rtas-format-exp-t`
    * :ref:`ze-rtas-builder-exp-flags-t`
    * :ref:`ze-rtas-parallel-operation-exp-flags-t`
    * :ref:`ze-rtas-builder-geometry-exp-flags-t`
    * :ref:`ze-rtas-builder-instance-exp-flags-t`
    * :ref:`ze-rtas-builder-build-op-exp-flags-t`
    * :ref:`ze-rtas-builder-build-quality-hint-exp-t`
    * :ref:`ze-rtas-builder-geometry-type-exp-t`
    * :ref:`ze-rtas-builder-input-data-format-exp-t`


* Structures


    * :ref:`ze-rtas-builder-exp-desc-t`

    * :ref:`ze-rtas-builder-exp-properties-t`
    * :ref:`ze-rtas-parallel-operation-exp-properties-t`
    * :ref:`ze-rtas-device-exp-properties-t`

    * :ref:`ze-rtas-float3-exp-t`
    * :ref:`ze-rtas-transform-float3x4-column-major-exp-t`
    * :ref:`ze-rtas-transform-float3x4-aligned-column-major-exp-t`
    * :ref:`ze-rtas-transform-float3x4-row-major-exp-t`
    * :ref:`ze-rtas-aabb-exp-t`
    * :ref:`ze-rtas-triangle-indices-uint32-exp-t`
    * :ref:`ze-rtas-quad-indices-uint32-exp-t`

    * :ref:`ze-rtas-builder-geometry-info-exp-t`
    * :ref:`ze-rtas-builder-triangles-geometry-info-exp-t`
    * :ref:`ze-rtas-builder-quads-geometry-info-exp-t`
    * :ref:`ze-rtas-builder-procedural-geometry-info-exp-t`
    * :ref:`ze-rtas-builder-instance-geometry-info-exp-t`

    * :ref:`ze-rtas-builder-build-op-exp-desc-t`


* Functions


    * :ref:`zeRTASBuilderCreateExp`
    * :ref:`zeRTASBuilderGetBuildPropertiesExp`
    * :ref:`zeRTASBuilderBuildExp`
    * :ref:`zeRTASBuilderDestroyExp`

    * :ref:`zeDriverRTASFormatCompatibilityCheckExp`

    * :ref:`zeRTASParallelOperationCreateExp`
    * :ref:`zeRTASParallelOperationGetPropertiesExp`
    * :ref:`zeRTASParallelOperationJoinExp`
    * :ref:`zeRTASParallelOperationDestroyExp`


============================================
 Ray Tracing Acceleration Structure Builder
============================================

The Ray Tracing Acceleration Structure Builder extension provides the functionality to build ray tracing acceleration structures (RTAS) for 3D scenes on the host for use with GPU devices.

It is the user's responsibility to manage the acceleration structure buffer and scratch buffer resources. The required sizes may be queried via :ref:`zeRTASBuilderGetBuildPropertiesExp`\. Once built, an acceleration structure is a self-contained entity; any input resources may be released after the successful construction. Note that acceleration structures are non-copyable resources.

Scene Data
-----------

To build an acceleration structure, first setup a scene that consists of one or more geometry infos.

    - :ref:`ze-rtas-builder-triangles-geometry-info-exp-t` for triangle meshes,
    - :ref:`ze-rtas-builder-quads-geometry-info-exp-t` for quad meshes,
    - :ref:`ze-rtas-builder-procedural-geometry-info-exp-t` for procedural primitives with attached axis-aligned bounding-box, and
    - :ref:`ze-rtas-builder-instance-geometry-info-exp-t` for instances of other acceleration structures.

The following example creates a :ref:`ze-rtas-builder-triangles-geometry-info-exp-t` to specify a triangle mesh:

.. parsed-literal::

        std::vector<:ref:`ze-rtas-triangle-indices-uint32-exp-t`\> triangleIndexBuffer;
        std::vector<:ref:`ze-rtas-float3-exp-t`\> triangleVertexBuffer;

        // Populate vertex and index buffers
        {
            // ...
        }

        :ref:`ze-rtas-builder-triangles-geometry-info-exp-t` mesh;
        memset(&mesh, 0, sizeof(mesh));

        mesh.geometryType = :ref:`ZE_RTAS_BUILDER_GEOMETRY_TYPE_EXP_TRIANGLES <ze-rtas-builder-geometry-type-exp-t>`\;
        mesh.geometryFlags = 0;
        mesh.geometryMask = 0xFF;

        mesh.triangleFormat = :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_TRIANGLE_INDICES_UINT32 <ze-rtas-builder-input-data-format-exp-t>`\;
        mesh.triangleCount = triangleIndexBuffer.size();
        mesh.triangleStride = sizeof(:ref:`ze-rtas-triangle-indices-uint32-exp-t`\);
        mesh.pTriangleBuffer = triangleIndexBuffer.data();

        mesh.vertexFormat = :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXP_FLOAT3 <ze-rtas-builder-input-data-format-exp-t>`\;
        mesh.vertexCount = triangleVertexBuffer.size();
        mesh.vertexStride = sizeof(:ref:`ze-rtas-float3-exp-t`\);
        mesh.pVertexBuffer = triangleVertexBuffer.data();

Geometry is considered to be opaque by default, enabling a fast mode where traversal does not return to the caller of ray tracing for each triangle or quad hit. To process each triangle or quad hit by some any-hit shader, the `geometryFlags` member of the geometry infos must include the :ref:`ZE_RTAS_BUILDER_GEOMETRY_EXP_FLAG_NON_OPAQUE <ze-rtas-builder-geometry-exp-flags-t>` flag. The proper data formats of the triangle index- and vertex- buffers are specified, including the strides, and a pointer to the first element for each buffer.

To refer to multiple geometries that make a scene, pointers to geometry info structures can be put into an array as follows:

.. parsed-literal::

        std::vector<:ref:`ze-rtas-builder-geometry-info-exp-t`\*> geometries;
        geometries.push_back((:ref:`ze-rtas-builder-geometry-info-exp-t`\*)&mesh0);
        geometries.push_back((:ref:`ze-rtas-builder-geometry-info-exp-t`\*)&mesh1);
        ...

This completes the definition of the geometry for the scene for which to construct the acceleration structure.

Device Properties
------------------

The next step is to query the target device for acceleration structure properties.

.. parsed-literal::

        :ref:`ze-rtas-device-exp-properties-t` rtasDeviceProps;
        rtasDeviceProps.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_DEVICE_EXP_PROPERTIES <ze-structure-type-t>`\;
        rtasDeviceProps.pNext = nullptr;

        :ref:`ze-device-properties-t` deviceProps;
        deviceProps.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>`\;
        deviceProps.pNext = &rtasDeviceProps;

        :ref:`zeDeviceGetProperties`\(hDevice, &deviceProps);


The device properties contain information (a device-specific ray tracing acceleration structure format) that is required to complete an RTAS build operation.


Acceleration Structure Builder
-------------------------------

With the scene data prepared and relevant device properties known, create a ray tracing acceleration structure builder object and query for the necessary build properties.

.. parsed-literal::

        :ref:`ze-rtas-builder-exp-desc-t` desc;
        desc.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_BUILDER_EXP_DESC <ze-structure-type-t>`\;
        desc.pNext = nullptr;
        desc.builderVersion = :ref:`ZE_RTAS_BUILDER_EXP_VERSION_CURRENT <ze-rtas-builder-exp-version-t>`\;

        ze_rtas_builder_exp_handle_t hBuilder = nullptr;
        :ref:`ze-result-t` result = :ref:`zeRTASBuilderCreateExp`\(hDriver, &desc, &hBuilder);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

        :ref:`ze-rtas-builder-exp-properties-t` builderProps;
        builderProps.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_BUILDER_EXP_PROPERTIES <ze-structure-type-t>`\;
        builderProps.pNext = nullptr;

        :ref:`ze-rtas-builder-build-op-exp-desc-t` buildOpDesc;
        buildOpDesc.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_BUILDER_BUILD_OP_EXP_DESC <ze-structure-type-t>`\;
        buildOpDesc.pNext = nullptr;
        buildOpDesc.rtasFormat = rtasDeviceProps.rtasFormat;
        buildOpDesc.buildQuality = :ref:`ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXP_MEDIUM <ze-rtas-builder-build-quality-hint-exp-t>`\;
        buildOpDesc.buildFlags = 0;
        buildOpDesc.ppGeometries = geometries.data();
        buildOpDesc.numGeometries = geometries.size();

        result = :ref:`zeRTASBuilderGetBuildPropertiesExp`\(hBuilder, &buildOpDesc, &builderProps);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

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

        :ref:`ze-raytracing-mem-alloc-ext-desc-t` rtasMemAllocDesc;
        rtasMemAllocDesc.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_RAYTRACING_EXT_PROPERTIES <ze-structure-type-t>`\;
        rtasMemAllocDesc.pNext = nullptr;
        rtasMemAllocDesc.flags = 0;

        :ref:`ze-device-mem-alloc-desc-t` deviceMemAllocDesc;
        deviceMemAllocDesc.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC <ze-structure-type-t>`\;
        deviceMemAllocDesc.pNext = &rtasMemAllocDesc;
        deviceMemAllocDesc.flags = :ref:`ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_CACHED <ze-device-mem-alloc-flags-t>`\;
        deviceMemAllocDesc.ordinal = 0;

        :ref:`ze-host-mem-alloc-desc-t` hostMemAllocDesc;
        hostMemAllocDesc.stype = :ref:`ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC <ze-structure-type-t>`\;
        hostMemAllocDesc.pNext = nullptr;
        hostMemAllocDesc.flags = :ref:`ZE_HOST_MEM_ALLOC_FLAG_BIAS_CACHED <ze-host-mem-alloc-flags-t>`\;

        void* pRtasBuffer = nullptr;
        result = :ref:`zeMemAllocShared`\(hContext, &deviceMemAllocDesc, &hostMemAllocDesc, builderProps.rtasBufferSizeBytesMaxRequired, rtasDeviceProps.rtasBufferAlignment, hDevice, &pRtasBuffer);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

Executing an Acceleration Structure Build
------------------------------------------

Single-Threaded Build
^^^^^^^^^^^^^^^^^^^^^^

A single-threaded acceleration structure build on the host is initiated using :ref:`zeRTASBuilderBuildExp`\.

.. parsed-literal::

        result = :ref:`zeRTASBuilderBuildExp`\(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBuffer, builderProps.rtasBufferSizeBytesMaxRequired, nullptr, nullptr, nullptr, nullptr);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

When the build completes successfully the acceleration structure buffer is ready for use by the ray tracing API.

Parallel Build
^^^^^^^^^^^^^^^

In order to speed up the build operation using multiple worker threads, a parallel operation object can be associated with the build operation and joined with the application-provided worker threads as in the following example:

    **Note**
    The following example uses `oneTBB <https://spec.oneapi.io/versions/latest/elements/oneTBB/source/nested-index.html>`_ to dispatch worker threads, but this is not a requirement.

.. parsed-literal::

        ze_rtas_parallel_operation_exp_handle_t hParallelOperation = nullptr;
        result = :ref:`zeRTASParallelOperationCreateExp`\(hDriver, &hParallelOperation);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

        // Initiate the acceleration structure build operation with a handle
        // of a parallel operation object. This causes the parallel operation to be
        // bound to the build operation and the function returns immediately without
        // building any acceleration structure yet.
        result = :ref:`zeRTASBuilderBuildExp`\(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBuffer, builderProps.rtasBufferSizeBytesMaxRequired, hParallelOperation, nullptr, nullptr, nullptr);
        assert(result == :ref:`ZE_RESULT_EXP_RTAS_BUILD_DEFERRED <ze-result-t>`\);

        // Once the parallel operation is bound to the build operation the number
        // of worker threads to join the parallel operation can be queried.
        :ref:`ze-rtas-parallel-operation-exp-properties-t` parallelOpProps;
        parallelOpProps.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_PARALLEL_OPERATION_EXP_PROPERTIES <ze-structure-type-t>`\;
        parallelOpProps.pNext = nullptr;

        result = :ref:`zeRTASParallelOperationGetPropertiesExp`\(hParallelOperation, &parallelOpProps);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

        // Now worker threads can join the build operation to perform the actual build
        // of the acceleration structure.
        tbb::parallel_for(0, parallelOpProps.maxConcurrency, 1, [&](uint32_t i) {
            :ref:`ze-result-t` buildResult = :ref:`zeRTASParallelOperationJoinExp`\(hParallelOperation);
            assert(buildResult == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);
        });

        // With the parallel operation complete, the parallel operation object can be released.
        result = :ref:`zeRTASParallelOperationDestroyExp`\(hParallelOperation);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

Note that the number of worker threads to be used can only be queried from the parallel operation object after it is bound to the build operation by the call to :ref:`zeRTASBuilderBuildExp`\.


Conservative Acceleration Structure Buffer Size
------------------------------------------------

Sizing the acceleration structure buffer using the `rtasBufferSizeBytesMaxRequired` member of :ref:`ze-rtas-builder-exp-properties-t` guarantees that the build operation will not fail due to an out-of-memory condition. However, this size represents the memory requirement for the worst-case scenario and is larger than is typically needed. To reduce memory usage, the application may attempt to execute a build using an acceleration structure buffer sized to the `rtasBufferSizeBytesExpected` member of :ref:`ze-rtas-builder-exp-properties-t`\. When using the expected size, however, it is possible for the build operation to fail with :ref:`ZE_RESULT_EXP_RTAS_BUILD_RETRY <ze-result-t>`\. If this occurs, the application may resize the acceleration structure buffer with an updated size estimate provided by the builder build API.

.. parsed-literal::

        :ref:`ze-result-t` result;

        void* pRtasBuffer = nullptr;
        size_t rtasBufferSizeBytes = builderProps.rtasBufferSizeBytesExpected;

        while (true)
        {
            pRtasBuffer = allocate_accel_buffer(rtasBufferSizeBytes);

            result = :ref:`zeRTASBuilderBuildExp`\(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, nullptr, nullptr, nullptr, &rtasBufferSizeBytes);

            if (result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\)
            {
                break;
            }

            assert(result == :ref:`ZE_RESULT_EXP_RTAS_BUILD_RETRY <ze-result-t>`\);

            free_accel_buffer(pRtasBuffer);
        }

The loop starts with the minimum acceleration buffer size for which the build will mostly likely succeed. If the build runs out of memory, :ref:`ZE_RESULT_EXP_RTAS_BUILD_RETRY <ze-result-t>` is returned and the build is retried with a larger acceleration structure buffer.

The example above passes a pointer to the `rtasBufferSizeBytes` variable as a parameter to the build API, which it will update with a larger acceleration structure buffer size estimate to be used in the next attempt should the build operation fail. Alternatively, the application could increase the acceleration buffer size for the next attempt by some percentage, which could fail again, or just use the maximum size from the builder properties for the second attempt.

Cleaning Up
------------

Once the acceleration structure has been built, any resources associated with the build may be released. Additionally, any parallel operation objects should be destroyed as well as any builder objects.

.. parsed-literal::

        // Free the scratch buffer
        free(pScratchBuffer);

        // Destroy the builder object
        :ref:`zeRTASBuilderDestroyExp`\(hBuilder);

        // Use the acceleration structure buffer with the ray tracing API
        {
            // ...
        }

        // Release the acceleration structure buffer once it is no longer needed
        :ref:`zeMemFree`\(hContext, pRtasBuffer);
        pRtasBuffer = nullptr;
