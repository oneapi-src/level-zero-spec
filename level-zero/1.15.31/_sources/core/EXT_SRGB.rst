
:orphan:

.. _ZE_extension_srgb:

======================================
 sRGB Extension
======================================

API
----

* Structures

    * :ref:`ze-srgb-ext-desc-t`

sRGB
~~~~

Device capabilities may include native support for sRGB image formats. sRGB images may benefit from hardware acceleration on devices that include native support for sRGB. The following psuedo-code demonstrates a sequence for creating an sRGB image:

.. parsed-literal::

       // Specify single component FLOAT32 format
       :ref:`ze-image-format-t` format = {
           :ref:`ZE_IMAGE_FORMAT_LAYOUT_32 <ze-image-format-layout-t>`\, :ref:`ZE_IMAGE_FORMAT_TYPE_FLOAT <ze-image-format-type-t>`\,
           :ref:`ZE_IMAGE_FORMAT_SWIZZLE_R <ze-image-format-swizzle-t>`\, :ref:`ZE_IMAGE_FORMAT_SWIZZLE_0 <ze-image-format-swizzle-t>`\, :ref:`ZE_IMAGE_FORMAT_SWIZZLE_0 <ze-image-format-swizzle-t>`\, :ref:`ZE_IMAGE_FORMAT_SWIZZLE_1 <ze-image-format-swizzle-t>`
       };

       // Specify sRGB image format
       :ref:`ze-srgb-ext-desc-t` isSRGB = {
           :ref:`ZE_STRUCTURE_TYPE_SRGB_EXT_DESC <ze-structure-type-t>`\,
           nullptr,
           true
       };

       :ref:`ze-image-desc-t` imageDesc = {
           :ref:`ZE_STRUCTURE_TYPE_IMAGE_DESC <ze-structure-type-t>`\,
           &isSRGB,
           0, // read-only
           :ref:`ZE_IMAGE_TYPE_2D <ze-image-type-t>`\,
           format,
           128, 128, 0, 0, 0
       };
       ze_image_handle_t hImage;
       :ref:`zeImageCreate`\(hContext, hDevice, &imageDesc, &hImage);

       // upload contents from host pointer
       :ref:`zeCommandListAppendImageCopyFromMemory`\(hCommandList, hImage, nullptr, pImageData, nullptr, 0, nullptr);
       ...
