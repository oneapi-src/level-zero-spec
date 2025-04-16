
:orphan:

.. _ZE_experimental_bindless_image:

========================================
 Bindless Image Experimental Extension
========================================

API
----

* Enumerations

    * :ref:`ze-bindless-image-exp-version-t`
    * :ref:`ze-image-bindless-exp-flags-t`

* Structures

    * :ref:`ze-device-pitched-alloc-exp-properties-t`
    * :ref:`ze-image-bindless-exp-desc-t`
    * :ref:`ze-image-pitched-exp-desc-t`

* Functions

    * :ref:`zeMemGetPitchFor2dImage`
    * :ref:`zeImageGetDeviceOffsetExp`

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
 * Create Bindless sampled images

A "Bindless image" can be created by passing :ref:`ze-image-bindless-exp-desc-t` to pNext member of
:ref:`ze-image-desc-t` and set the flags value as :ref:`ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS <ze-image-bindless-exp-flags-t>`

A "Bindless sampled image" can be created by passing :ref:`ze-image-bindless-exp-desc-t` to pNext member of
:ref:`ze-image-desc-t` and setting the flags to a combination of :ref:`ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS <ze-image-bindless-exp-flags-t>` and :ref:`ZE_IMAGE_BINDLESS_EXP_FLAG_SAMPLED_IMAGE <ze-image-bindless-exp-flags-t>`
When image view is created from bindless sampled image, sampling modes can be redefined by passing sampler descriptor in pNext field of :ref:`ze-image-bindless-exp-desc-t` struct.
Image view created from bindless sampled image without setting :ref:`ZE_IMAGE_BINDLESS_EXP_FLAG_SAMPLED_IMAGE <ze-image-bindless-exp-flags-t>` is an unsampled image.
Sampled image view can be created from bindless unsampled image by setting :ref:`ZE_IMAGE_BINDLESS_EXP_FLAG_SAMPLED_IMAGE <ze-image-bindless-exp-flags-t>` and passing sampler descriptor in pNext field of :ref:`ze-image-bindless-exp-desc-t` struct.

This extension is complimentary to and may be used in conjunction with the `ZE_extension_image_view <https://oneapi-src.github.io/level-zero-spec/level-zero/latest/core/EXT_ImageView.html#image-view-extension>`_ extension

Programming example with Bindless images
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::

    // Assumed image data on host
    std::vector<float> imageDataHost;

    // 2D image dimensions
    size_t imageWidth = 1024;
    size_t imageHeight = 1024;

    // Single-precision float image format with one channel
    :ref:`ze-image-format-t` imageFormat = {
        ZE_IMAGE_FORMAT_LAYOUT_32, ZE_IMAGE_FORMAT_TYPE_FLOAT,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X
    }

    // Create an image descriptor for bindless image
    :ref:`ze-image-desc-t` imageDesc = {
        ZE_STRUCTURE_TYPE_IMAGE_DESC,
        nullptr,
        0,
        ZE_IMAGE_TYPE_2D,
        imageFormat,
        128, 128, 0, 0, 0
    };

    :ref:`ze-image-bindless-exp-desc-t` bindlessImageDesc = {:ref:`ZE_STRUCTURE_TYPE_BINDLESS_IMAGE_EXP_DESC <ze-structure-type-t>`\};
    bindlessImageDesc.flags = :ref:`ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS <ze-image-bindless-exp-flags-t>`\;
    imageDesc.pNext = &bindlessImageDesc;

    // A bindless image is valid on both host and device and can be passed into kernels
    // When passing :ref:`ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS <ze-image-bindless-exp-flags-t>` to zeImageCreate, only the backing memory is allocated for Image
    ze_image_handle_t hImage;
    :ref:`zeImageCreate`\(hContext, hDevice, &imageDesc, &hImage);

    //Copy To new bindless image memory
    :ref:`zeCommandListAppendImageCopyFromMemory`\(hCommandlist, hImage, imageDataHost.data(), nullptr, nullptr, 0, nullptr);

    // Launch kernel and perform appropriate synchronizations

    // Copy back
    :ref:`zeCommandListAppendImageCopyToMemory`\(hCommandlist, imageDataHost.data(), hImage, nullptr, nullptr, 0, nullptr);

    // Further image views can be created from the existing memory allocated using bindless flags
    ze_image_handle_t hImageView;
    :ref:`zeImageViewCreateExt`\(hContext, hDevice, &imageDesc, hImage, &hImageView);

    // New image view can be separately used by users and destroyed
    // ...

    // Once all operations are complete we need destroy bindless image handle(s)
    :ref:`zeImageDestroy`\(hImageView);
    :ref:`zeImageDestroy`\(hImage);

Programming example with pitched memory usage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::

    // Retrieve pitched alloc properties specific to device
    :ref:`ze-device-image-properties-t` deviceImageProperties = {};
    :ref:`ze-device-pitched-alloc-exp-properties-t` pitchedAllocProperties = {};
    pitchedAllocProperties.stype  = :ref:`ZE_STRUCTURE_TYPE_PITCHED_ALLOC_DEVICE_EXP_PROPERTIES <ze-structure-type-t>`

    deviceImageProperties.pNext = &pitchedAllocProperties;
    :ref:`zeDeviceGetImageProperties`\(hDevice, &deviceImageProperties);

    // Assumed image data on host
    std::vector<float> imageDataHost;

    // 2D image dimensions
    size_t imageWidth = 1024;
    size_t imageHeight = 1024;

    //Pitched memory in linear layout
    size_t rowPitch;
    unsigned int elementSize = 128;
    :ref:`zeMemGetPitchFor2dImage`\(hContext, hDevice, imageWidth, imageHeight, elementSize, &rowPitch);
    size_t allocSize = rowPitch * imageHeight;
    :ref:`ze-device-mem-alloc-desc-t` allocDesc = {:ref:`ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC <ze-structure-type-t>`\};
    :ref:`zeMemAllocDevice`\(hContext, &allocDesc, allocSize, allocSize, hDevice, &pitchedPtr);

    // Declare the copy region for copying
    :ref:`ze-copy-region-t` copyRegion = {0, 0, 0, imageWidth * sizeof(float), imageHeight, 0};

    // Copy from host to device
    :ref:`zeCommandListAppendMemoryCopyRegion`\(hCommandList, pitchedPtr, &copyRegion, rowPitch, 0, imageDataHost.data(), &copyRegion, imageWidth * sizeof(float), 0, nullptr, 0, nullptr);

    // Single-precision float image format with one channel
    :ref:`ze-image-format-t` imageFormat = {
        ZE_IMAGE_FORMAT_LAYOUT_32, ZE_IMAGE_FORMAT_TYPE_FLOAT,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X
    }
    
    // Create an image descriptor for bindless image
    :ref:`ze-image-desc-t` imageDesc = {
        ZE_STRUCTURE_TYPE_IMAGE_DESC,
        nullptr,
        0,
        ZE_IMAGE_TYPE_2D,
        imageFormat,
        128, 128, 0, 0, 0
    };

    :ref:`ze-image-pitched-exp-desc-t` pitchedImageDesc = {:ref:`ZE_STRUCTURE_TYPE_PITCHED_IMAGE_EXP_DESC <ze-structure-type-t>`\};
    pitchedImageDesc.ptr = pitchedPtr;
    imageDesc.pNext = &pitchedImageDesc;

    // A image created out of pitched memory is valid on both host and device and can be passed into kernels
    ze_image_handle_t hImage;
    :ref:`zeImageCreate`\(hContext, hDevice, &imageDesc, &hImage);

    // Launch kernel and perform appropriate synchronizations

    // ...

    // Copy from device to host
    :ref:`zeCommandListAppendMemoryCopyRegion`\(hCommandList, imageDataHost.data(), &copyRegion, imageWidth * sizeof(float), 0, pitchedPtr, &copyRegion, rowPitch, 0, nullptr, 0, nullptr);

    // Once all operations on the image are complete we need destroy image handle and free memory
    :ref:`zeImageDestroy`\(hImage);
    :ref:`zeMemFree`\(hContext, pitchedPtr);

Programming example with Bindless sampled images
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::

    // 2D image dimensions
    size_t imageWidth = 1024;
    size_t imageHeight = 1024;

    // Single-precision float image format with one channel
    :ref:`ze-image-format-t` imageFormat = {
        ZE_IMAGE_FORMAT_LAYOUT_32, ZE_IMAGE_FORMAT_TYPE_FLOAT,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X
    }

    // Define sampler descriptor
    :ref:`ze-sampler-desc-t` samplerDesc = {
        ZE_STRUCTURE_TYPE_SAMPLER_DESC,
        nullptr,
        ZE_SAMPLER_ADDRESS_MODE_CLAMP,
        ZE_SAMPLER_FILTER_MODE_LINEAR,
        true
    };

    // Create an image descriptor for bindless image
    :ref:`ze-image-desc-t` imageDesc = {
        ZE_STRUCTURE_TYPE_IMAGE_DESC,
        nullptr,
        0,
        ZE_IMAGE_TYPE_2D,
        imageFormat,
        imageWidth, imageHeight, 0, 0, 0
    };

    :ref:`ze-image-bindless-exp-desc-t` bindlessImageDesc = {ZE_STRUCTURE_TYPE_BINDLESS_IMAGE_EXP_DESC};
    bindlessImageDesc.flags = ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS | ZE_IMAGE_BINDLESS_EXP_FLAG_SAMPLED_IMAGE;
    imageDesc.pNext = &bindlessImageDesc;

    bindlessImageDesc.pNext = &samplerDesc;

    // Create bindless sampled image
    // pass ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS and ZE_IMAGE_BINDLESS_EXP_FLAG_SAMPLED_IMAGE to zeImageCreate(),
    ze_image_handle_t hImage;
    :ref:`zeImageCreate`\(hContext, hDevice, &imageDesc, &hImage);

    // Create an image view from bindless sampled image
    // define sampler descriptor for view
    :ref:`ze-sampler-desc-t` samplerDescForView = {
        ZE_STRUCTURE_TYPE_SAMPLER_DESC,
        nullptr,
        ZE_SAMPLER_ADDRESS_MODE_CLAMP,
        ZE_SAMPLER_FILTER_MODE_NEAREST,
        true
    };

    :ref:`ze-image-format-t` imageViewFormat = {
        ZE_IMAGE_FORMAT_LAYOUT_32, ZE_IMAGE_FORMAT_TYPE_UINT,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X,
        ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_X
    }

    // image descriptor for bindless image view
    :ref:`ze-image-desc-t` imageViewDesc = {
        ZE_STRUCTURE_TYPE_IMAGE_DESC,
        nullptr,
        0,
        ZE_IMAGE_TYPE_2D,
        imageViewFormat,
        128, 128, 0, 0, 0
    };
    imageViewDesc.pNext = &bindlessImageDesc;
    bindlessImageDesc.pNext = &samplerDescForView;
    ze_image_handle_t hImageView;

    :ref:`zeImageViewCreateExt`\(hContext, hDevice, &imageViewDesc, hImage, &hImageView);

    // If ZE_IMAGE_BINDLESS_EXP_FLAG_SAMPLED_IMAGE is not set, unsampled image is created
    ze_image_handle_t hUnsampledImageView;
    bindlessImageDesc.flags = ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS;
    bindlessImageDesc.pNext = nullptr;
    :ref:`zeImageViewCreateExt`\(hContext, hDevice, &imageViewDesc, hImage, &hUnsampledImageView);

    // Create an image view from bindless unsampled image
    ze_image_handle_t hUnsampledImage;
    ze_image_handle_t hSampledImageView;
    bindlessImageDesc.flags = ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS;
    bindlessImageDesc.pNext = nullptr;
    imageDesc.pNext = &bindlessImageDesc;

    // create unsampled image
    :ref:`zeImageCreate`\(hContext, hDevice, &imageDesc, &hUnsampledImage);

    bindlessImageDesc.flags = ZE_IMAGE_BINDLESS_EXP_FLAG_BINDLESS | ZE_IMAGE_BINDLESS_EXP_FLAG_SAMPLED_IMAGE;
    bindlessImageDesc.pNext = &samplerDescForView;
    :ref:`zeImageViewCreateExt`\(hContext, hDevice, &imageDesc, hUnsampledImage, &hSampledImageView);
