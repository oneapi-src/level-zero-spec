
:orphan:

.. _ZE_extension_rtas:

======================================================
 Ray Tracing Acceleration Structure Extension
======================================================

API
----

* Enumerations


    * :ref:`ze-rtas-builder-ext-version-t`
    * :ref:`ze-rtas-device-ext-flags-t`
    * :ref:`ze-rtas-format-ext-t`
    * :ref:`ze-rtas-builder-ext-flags-t`
    * :ref:`ze-rtas-parallel-operation-ext-flags-t`
    * :ref:`ze-rtas-builder-geometry-ext-flags-t`
    * :ref:`ze-rtas-builder-instance-ext-flags-t`
    * :ref:`ze-rtas-builder-build-op-ext-flags-t`
    * :ref:`ze-rtas-builder-build-quality-hint-ext-t`
    * :ref:`ze-rtas-builder-geometry-type-ext-t`
    * :ref:`ze-rtas-builder-input-data-format-ext-t`


* Structures


    * :ref:`ze-rtas-builder-ext-desc-t`

    * :ref:`ze-rtas-builder-ext-properties-t`
    * :ref:`ze-rtas-parallel-operation-ext-properties-t`
    * :ref:`ze-rtas-device-ext-properties-t`

    * :ref:`ze-rtas-float3-ext-t`
    * :ref:`ze-rtas-transform-float3x4-column-major-ext-t`
    * :ref:`ze-rtas-transform-float3x4-aligned-column-major-ext-t`
    * :ref:`ze-rtas-transform-float3x4-row-major-ext-t`
    * :ref:`ze-rtas-aabb-ext-t`
    * :ref:`ze-rtas-triangle-indices-uint32-ext-t`
    * :ref:`ze-rtas-quad-indices-uint32-ext-t`

    * :ref:`ze-rtas-builder-geometry-info-ext-t`
    * :ref:`ze-rtas-builder-triangles-geometry-info-ext-t`
    * :ref:`ze-rtas-builder-quads-geometry-info-ext-t`
    * :ref:`ze-rtas-builder-procedural-geometry-info-ext-t`
    * :ref:`ze-rtas-builder-instance-geometry-info-ext-t`

    * :ref:`ze-rtas-builder-build-op-ext-desc-t`


* Functions


    * :ref:`zeRTASBuilderCreateExt`
    * :ref:`zeRTASBuilderGetBuildPropertiesExt`
    * :ref:`zeRTASBuilderBuildExt`
    * :ref:`zeRTASBuilderDestroyExt`

    * :ref:`zeRTASBuilderCommandListAppendCopyExt`
    * :ref:`zeDriverRTASFormatCompatibilityCheckExt`

    * :ref:`zeRTASParallelOperationCreateExt`
    * :ref:`zeRTASParallelOperationGetPropertiesExt`
    * :ref:`zeRTASParallelOperationJoinExt`
    * :ref:`zeRTASParallelOperationDestroyExt`


============================================
 Ray Tracing Acceleration Structure
============================================

The Ray Tracing Acceleration Structure extension provides the functionality to build ray tracing acceleration structures (RTAS) for 3D scenes on the host for use with GPU devices.

It is the user's responsibility to manage the acceleration structure buffer and scratch buffer resources. The required sizes may be queried via :ref:`zeRTASBuilderGetBuildPropertiesExt`\. Once built, an acceleration structure is a self-contained entity; any input resources may be released after the successful construction.

Scene Data
-----------

To build an acceleration structure, first setup a scene that consists of one or more geometry infos.

    - :ref:`ze-rtas-builder-triangles-geometry-info-ext-t` for triangle meshes,
    - :ref:`ze-rtas-builder-quads-geometry-info-ext-t` for quad meshes,
    - :ref:`ze-rtas-builder-procedural-geometry-info-ext-t` for procedural primitives with attached axis-aligned bounding-box, and
    - :ref:`ze-rtas-builder-instance-geometry-info-ext-t` for instances of other acceleration structures.

The following example creates a :ref:`ze-rtas-builder-triangles-geometry-info-ext-t` to specify a triangle mesh:

.. parsed-literal::

        std::vector<:ref:`ze-rtas-triangle-indices-uint32-ext-t`\> triangleIndexBuffer;
        std::vector<:ref:`ze-rtas-float3-ext-t`\> triangleVertexBuffer;

        // Populate vertex and index buffers
        {
            // ...
        }

        :ref:`ze-rtas-builder-triangles-geometry-info-ext-t` mesh;
        memset(&mesh, 0, sizeof(mesh));

        mesh.geometryType = :ref:`ZE_RTAS_BUILDER_GEOMETRY_TYPE_EXT_TRIANGLES <ze-rtas-builder-geometry-type-ext-t>`\;
        mesh.geometryFlags = 0;
        mesh.geometryMask = 0xFF;

        mesh.triangleFormat = :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXT_TRIANGLE_INDICES_UINT32 <ze-rtas-builder-input-data-format-ext-t>`\;
        mesh.triangleCount = triangleIndexBuffer.size();
        mesh.triangleStride = sizeof(:ref:`ze-rtas-triangle-indices-uint32-ext-t`\);
        mesh.pTriangleBuffer = triangleIndexBuffer.data();

        mesh.vertexFormat = :ref:`ZE_RTAS_BUILDER_INPUT_DATA_FORMAT_EXT_FLOAT3 <ze-rtas-builder-input-data-format-ext-t>`\;
        mesh.vertexCount = triangleVertexBuffer.size();
        mesh.vertexStride = sizeof(:ref:`ze-rtas-float3-ext-t`\);
        mesh.pVertexBuffer = triangleVertexBuffer.data();

Geometry is considered to be opaque by default, enabling a fast mode where traversal does not return to the caller of ray tracing for each triangle or quad hit. To process each triangle or quad hit by some any-hit shader, the `geometryFlags` member of the geometry infos must include the :ref:`ZE_RTAS_BUILDER_GEOMETRY_EXT_FLAG_NON_OPAQUE <ze-rtas-builder-geometry-ext-flags-t>` flag. The proper data formats of the triangle index- and vertex- buffers are specified, including the strides, and a pointer to the first element for each buffer.

To refer to multiple geometries that make a scene, pointers to geometry info structures can be put into an array as follows:

.. parsed-literal::

        std::vector<:ref:`ze-rtas-builder-geometry-info-ext-t`\*> geometries;
        geometries.push_back((:ref:`ze-rtas-builder-geometry-info-ext-t`\*)&mesh0);
        geometries.push_back((:ref:`ze-rtas-builder-geometry-info-ext-t`\*)&mesh1);
        ...

This completes the definition of the geometry for the scene for which to construct the acceleration structure.

Device Properties
------------------

The next step is to query the target device for acceleration structure properties.

.. parsed-literal::

        :ref:`ze-rtas-device-ext-properties-t` rtasDeviceProps;
        rtasDeviceProps.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_DEVICE_EXT_PROPERTIES <ze-structure-type-t>`\;
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

        :ref:`ze-rtas-builder-ext-desc-t` desc;
        desc.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_BUILDER_EXT_DESC <ze-structure-type-t>`\;
        desc.pNext = nullptr;
        desc.builderVersion = :ref:`ZE_RTAS_BUILDER_EXT_VERSION_CURRENT <ze-rtas-builder-ext-version-t>`\;

        ze_rtas_builder_ext_handle_t hBuilder = nullptr;
        :ref:`ze-result-t` result = :ref:`zeRTASBuilderCreateExt`\(hDriver, &desc, &hBuilder);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

        :ref:`ze-rtas-builder-ext-properties-t` builderProps;
        builderProps.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_BUILDER_EXT_PROPERTIES <ze-structure-type-t>`\;
        builderProps.pNext = nullptr;

        :ref:`ze-rtas-builder-build-op-ext-desc-t` buildOpDesc;
        buildOpDesc.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_BUILDER_BUILD_OP_EXT_DESC <ze-structure-type-t>`\;
        buildOpDesc.pNext = nullptr;
        buildOpDesc.rtasFormat = rtasDeviceProps.rtasFormat;
        buildOpDesc.buildQuality = :ref:`ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXT_MEDIUM <ze-rtas-builder-build-quality-hint-ext-t>`\;
        buildOpDesc.buildFlags = 0;
        buildOpDesc.ppGeometries = geometries.data();
        buildOpDesc.numGeometries = geometries.size();

        result = :ref:`zeRTASBuilderGetBuildPropertiesExt`\(hBuilder, &buildOpDesc, &builderProps);
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

The acceleration structure buffer holds the built ray tracing acceleration structure. Typically a host allocation is used to build the acceleration structure to be later copied into a device buffer using the :ref:`zeRTASBuilderCommandListAppendCopyExt` function.

.. parsed-literal::

        // allocate host memory to build the acceleration structure into
        void* pRtasBufferHost = aligned_alloc(rtasDeviceProps.rtasBufferAlignment, builderProps.rtasBufferSizeBytesMaxRequired);

        // create a device allocation to later copy the build acceleration structure into
        :ref:`ze-raytracing-mem-alloc-ext-desc-t` rtasMemAllocDesc;
        rtasMemAllocDesc.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_RAYTRACING_EXT_PROPERTIES <ze-structure-type-t>`\;
        rtasMemAllocDesc.pNext = nullptr;
        rtasMemAllocDesc.flags = 0;

        :ref:`ze-device-mem-alloc-desc-t` deviceMemAllocDesc;
        deviceMemAllocDesc.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC <ze-structure-type-t>`\;
        deviceMemAllocDesc.pNext = &rtasMemAllocDesc;
        deviceMemAllocDesc.flags = :ref:`ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_CACHED <ze-device-mem-alloc-flags-t>`\;
        deviceMemAllocDesc.ordinal = 0;

        void* pRtasBufferDevice = nullptr;
        result = :ref:`zeMemAllocDevice`\(hContext, &deviceMemAllocDesc, builderProps.rtasBufferSizeBytesMaxRequired, rtasDeviceProps.rtasBufferAlignment, hDevice, &pRtasBufferDevice);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

Executing an Acceleration Structure Build
------------------------------------------

Single-Threaded Build
^^^^^^^^^^^^^^^^^^^^^^

A single-threaded acceleration structure build on the host is initiated using :ref:`zeRTASBuilderBuildExt`\.

.. parsed-literal::

        result = :ref:`zeRTASBuilderBuildExt`\(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBufferHost, builderProps.rtasBufferSizeBytesMaxRequired, nullptr, nullptr, nullptr, nullptr);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

When the build completes successfully the acceleration structure buffer is ready for use by the ray tracing API.

Parallel Build
^^^^^^^^^^^^^^^

In order to speed up the build operation using multiple worker threads, a parallel operation object can be associated with the build operation and joined with the application-provided worker threads as in the following example:

    **Note**
    The following example uses `oneTBB <https://spec.oneapi.io/versions/latest/elements/oneTBB/source/nested-index.html>`_ to dispatch worker threads, but this is not a requirement.

.. parsed-literal::

        ze_rtas_parallel_operation_ext_handle_t hParallelOperation = nullptr;
        result = :ref:`zeRTASParallelOperationCreateExt`\(hDriver, &hParallelOperation);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

        // Initiate the acceleration structure build operation with a handle
        // of a parallel operation object. This causes the parallel operation to be
        // bound to the build operation and the function returns immediately without
        // building any acceleration structure yet.
        result = :ref:`zeRTASBuilderBuildExt`\(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBufferHost, builderProps.rtasBufferSizeBytesMaxRequired, hParallelOperation, nullptr, nullptr, nullptr);
        assert(result == :ref:`ZE_RESULT_EXT_RTAS_BUILD_DEFERRED <ze-result-t>`\);

        // Once the parallel operation is bound to the build operation the number
        // of worker threads to join the parallel operation can be queried.
        :ref:`ze-rtas-parallel-operation-ext-properties-t` parallelOpProps;
        parallelOpProps.stype = :ref:`ZE_STRUCTURE_TYPE_RTAS_PARALLEL_OPERATION_EXT_PROPERTIES <ze-structure-type-t>`\;
        parallelOpProps.pNext = nullptr;

        result = :ref:`zeRTASParallelOperationGetPropertiesExt`\(hParallelOperation, &parallelOpProps);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

        // Now worker threads can join the build operation to perform the actual build
        // of the acceleration structure.
        tbb::parallel_for(0, parallelOpProps.maxConcurrency, 1, [&](uint32_t i) {
            :ref:`ze-result-t` buildResult = :ref:`zeRTASParallelOperationJoinExt`\(hParallelOperation);
            assert(buildResult == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);
        });

        // With the parallel operation complete, the parallel operation object can be released.
        result = :ref:`zeRTASParallelOperationDestroyExt`\(hParallelOperation);
        assert(result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\);

Note that the number of worker threads to be used can only be queried from the parallel operation object after it is bound to the build operation by the call to :ref:`zeRTASBuilderBuildExt`\.

Acceleration Structure Copy
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Once the acceleration structure got build into the host buffer, one can use the :ref:`zeRTASBuilderCommandListAppendCopyExt` function to copy the acceleration structure to the device. The acceleration structure is generally non-copyable using standard copy operation, thus this special copy function must be used.

.. parsed-literal::

        :ref:`zeRTASBuilderCommandListAppendCopyExt`\(hCommandList, pRtasBufferDevice, pRtasBufferHost, builderProps.rtasBufferSizeBytesMaxRequired, nullptr, 0, nullptr);


As soon as the copy is finished, the acceleration strucuture is ready to be used on the device. Alternatively, one can also use a shared USM allocation to build the acceleration structure into and skip the explicit copy.

Conservative Acceleration Structure Buffer Size
------------------------------------------------

Sizing the acceleration structure buffer using the `rtasBufferSizeBytesMaxRequired` member of :ref:`ze-rtas-builder-ext-properties-t` guarantees that the build operation will not fail due to an out-of-memory condition. However, this size represents the memory requirement for the worst-case scenario and is larger than is typically needed. To reduce memory usage, the application may attempt to execute a build using an acceleration structure buffer sized to the `rtasBufferSizeBytesExpected` member of :ref:`ze-rtas-builder-ext-properties-t`\. When using the expected size, however, it is possible for the build operation to fail with :ref:`ZE_RESULT_EXT_RTAS_BUILD_RETRY <ze-result-t>`\. If this occurs, the application may resize the acceleration structure buffer with an updated size estimate provided by the RTAS build.

.. parsed-literal::

        :ref:`ze-result-t` result;

        void* pRtasBufferHost = nullptr;
        size_t rtasBufferSizeBytes = builderProps.rtasBufferSizeBytesExpected;

        while (true)
        {
            pRtasBufferHost = aligned_alloc(rtasDeviceProps.rtasBufferAlignment, rtasBufferSizeBytes);

            result = :ref:`zeRTASBuilderBuildExt`\(hBuilder, &buildOpDesc, pScratchBuffer, builderProps.scratchBufferSizeBytes, pRtasBufferHost, rtasBufferSizeBytes, nullptr, nullptr, nullptr, &rtasBufferSizeBytes);

            if (result == :ref:`ZE_RESULT_SUCCESS <ze-result-t>`\)
            {
                break;
            }

            assert(result == :ref:`ZE_RESULT_EXT_RTAS_BUILD_RETRY <ze-result-t>`\);

            free(pRtasBufferHost);
        }

The loop starts with the minimum acceleration buffer size for which the build will mostly likely succeed. If the build runs out of memory, :ref:`ZE_RESULT_EXT_RTAS_BUILD_RETRY <ze-result-t>` is returned and the build is retried with a larger acceleration structure buffer.

The example above passes a pointer to the `rtasBufferSizeBytes` variable as a parameter to the build API, which it will update with a larger acceleration structure buffer size estimate to be used in the next attempt should the build operation fail. Alternatively, the application could increase the acceleration buffer size for the next attempt by some percentage, which could fail again, or just use the maximum size from the builder properties for the second attempt.

Cleaning Up
------------

Once the acceleration structure has been built, any resources associated with the build may be released. Additionally, any parallel operation objects should be destroyed as well as any builder objects.

.. parsed-literal::

        // Free the scratch buffer
        free(pScratchBuffer);

        // Free host version of acceleration structure
        free(pRtasBufferHost);

        // Destroy the builder object
        :ref:`zeRTASBuilderDestroyExt`\(hBuilder);

        // Use the acceleration structure buffer with the ray tracing API
        {
            // ...
        }

        // Release the device acceleration structure buffer once it is no longer needed
        :ref:`zeMemFree`\(hContext, pRtasBufferDevice);
