<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_bindless_image:

========================================
 Bindless Image Experimental Extension
========================================

API
----

* Enumerations

    * ${x}_bindless_image_exp_version_t
    * ${x}_image_bindless_exp_flags_t

* Structures

    * ${x}_device_pitched_alloc_exp_properties_t
    * ${x}_image_bindless_exp_desc_t
    * ${x}_image_pitched_exp_desc_t

* Functions

    * ${x}MemGetPitchFor2dImage

Bindless Images
~~~~~~~~~~~~~~~

A bindless image is defined as one which provides access to the underlying data via image reference handles.
At the application level, this allows the user to implement programs where the number of images is not known at
compile-time, and store all handles to images irrespective of varying formats and layouts in some container such as a dynamic array.

Currently, in Level Zero, `zeImageCreate` performs the image memory allocation and image handle generation.
This function only allows for the allocation of image memory in an implementation-specific layout.

In this extension, we propose the following additions:
 * Provide a new image descriptor and flags for Bindless images.
 * Support for creation of images on linearly allocated memory backed by USM.
 * Extension API to create an image handle from pitched memory

A "Bindless image" can be created by passing ${x}_image_bindless_exp_desc_t to pNext member of
${x}_image_desc_t and set the flags value as ${X}_IMAGE_BINDLESS_EXP_FLAG_BINDLESS

Programming example with Bindless images
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::

    // Assumed image data on host
    std::vector<float> imageDataHost;

    // 2D image dimensions
    size_t imageWidth = 1024;
    size_t imageHeight = 1024;

    // Single-precision float image format with one channel
    ${x}_image_format_t imageFormat = {
        ZE_IMAGE_FORMAT_LAYOUT_32, ZE_IMAGE_FORMAT_TYPE_FLOAT,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X
    }

    // Create an image descriptor for bindless image
    ${x}_image_desc_t imageDesc = {
        ZE_STRUCTURE_TYPE_IMAGE_DESC,
        nullptr,
        0,
        ZE_IMAGE_TYPE_2D,
        imageFormat,
        128, 128, 0, 0, 0
    };

    ${x}_image_bindless_exp_desc_t bindlessImageDesc = {${X}_STRUCTURE_TYPE_BINDLESS_IMAGE_EXP_DESC};
    bindlessImageDesc.flags = ${X}_IMAGE_BINDLESS_EXP_FLAG_BINDLESS;
    imageDesc.pNext = &bindlessImageDesc;

    // A bindless image is valid on both host and device and can be passed into kernels
    ${x}_image_handle_t hImage;
    ${x}ImageCreate(hContext, hDevice, &imageDesc, &hImage);

    //Copy To new bindless image memory
    ${x}CommandListAppendImageCopyFromMemory(hCommandlist, hImage, imageDataHost.data(), nullptr, nullptr, 0, nullptr);

    // Launch kernel and perform appropriate synchronizations

    // Copy back
    ${x}CommandListAppendImageCopyToMemory(hCommandlist, imageDataHost.data(), hImage, nullptr, nullptr, 0, nullptr);

    // Once all operations are complete we need destroy bindless image handle
    ${x}ImageDestroy(hImage);

Programming example with pitched memory usage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::

    // Retrieve pitched alloc properties specific to device
    ${x}_device_image_properties_t deviceImageProperties = {};
    ${x}_device_pitched_alloc_exp_properties_t pitchedAllocProperties = {};
    pitchedAllocProperties.stype  = ${X}_STRUCTURE_TYPE_PITCHED_ALLOC_DEVICE_EXP_PROPERTIES

    deviceImageProperties.pNext = &pitchedAllocProperties;
    ${x}DeviceGetImageProperties(hDevice, &deviceImageProperties);

    // Assumed image data on host
    std::vector<float> imageDataHost;

    // 2D image dimensions
    size_t imageWidth = 1024;
    size_t imageHeight = 1024;

    //Pitched memory in linear layout
    size_t rowPitch;
    unsigned int elementSize = 128;
    ${x}MemGetPitchFor2dImage(hContext, hDevice, imageWidth, imageHeight, elementSize, &rowPitch);
    size_t allocSize = rowPitch * imageHeight;
    ${x}_device_mem_alloc_desc_t allocDesc = {${X}_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC};
    ${x}MemAllocDevice(hContext, &allocDesc, allocSize, allocSize, hDevice, &pitchedPtr);

    // Declare the copy region for copying
    ${x}_copy_region_t copyRegion = {0, 0, 0, imageWidth * sizeof(float), imageHeight, 0};

    // Copy from host to device
    ${x}CommandListAppendMemoryCopyRegion(hCommandList, pitchedPtr, &copyRegion, pitchedAllocProperties.rowPitch, 0, imageDataHost.data(), &copyRegion, imageWidth * sizeof(float), 0, nullptr, 0, nullptr);

    // Single-precision float image format with one channel
    ${x}_image_format_t imageFormat = {
        ZE_IMAGE_FORMAT_LAYOUT_32, ZE_IMAGE_FORMAT_TYPE_FLOAT,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X
    }
    
    // Create an image descriptor for bindless image
    ${x}_image_desc_t imageDesc = {
        ZE_STRUCTURE_TYPE_IMAGE_DESC,
        nullptr,
        0,
        ZE_IMAGE_TYPE_2D,
        imageFormat,
        128, 128, 0, 0, 0
    };

    ${x}_image_pitched_exp_desc_t pitchedImageDesc = {${X}_STRUCTURE_TYPE_PITCHED_IMAGE_EXP_DESC};
    pitchedImageDesc.ptr = pitchedPtr;
    imageDesc.pNext = &pitchedImageDesc;

    // A image created out of pitched memory is valid on both host and device and can be passed into kernels
    ${x}_image_handle_t hImage;
    ${x}ImageCreate(hContext, hDevice, &imageDesc, &hImage);

    // Launch kernel and perform appropriate synchronizations

    // ...

    // Copy from device to host
    ${x}CommandListAppendMemoryCopyRegion(hCommandList, imageDataHost.data(), &copyRegion, imageWidth * sizeof(float), 0, pitchedPtr, &copyRegion, pitchedAllocProperties.rowPitch, 0, nullptr, 0, nullptr);

    // Once all operations on the image are complete we need destroy image handle and free memory
    ${x}ImageDestroy(hImage);
    ${x}MemFree(hContext, pitchedPtr);