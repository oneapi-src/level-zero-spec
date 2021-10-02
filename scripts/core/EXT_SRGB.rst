<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_srgb:

======================================
 sRGB Extension
======================================

API
----

* Structures

    * ${x}_srgb_ext_desc_t

sRGB
~~~~

Device capabilities may include native support for sRGB image formats. sRGB images may benefit from hardware acceleration on devices that include native support for sRGB. The following psuedo-code demonstrates a sequence for creating an sRGB image:

.. parsed-literal::

       // Specify single component FLOAT32 format
       ${x}_image_format_t format = {
           ${X}_IMAGE_FORMAT_LAYOUT_32, ${X}_IMAGE_FORMAT_TYPE_FLOAT,
           ${X}_IMAGE_FORMAT_SWIZZLE_R, ${X}_IMAGE_FORMAT_SWIZZLE_0, ${X}_IMAGE_FORMAT_SWIZZLE_0, ${X}_IMAGE_FORMAT_SWIZZLE_1
       };

       // Specify sRGB image format
       ${x}_srgb_ext_desc_t isSRGB = {
           ${X}_STRUCTURE_TYPE_SRGB_EXT_DESC,
           nullptr,
           true
       };

       ${x}_image_desc_t imageDesc = {
           ${X}_STRUCTURE_TYPE_IMAGE_DESC,
           &isSRGB,
           0, // read-only
           ${X}_IMAGE_TYPE_2D,
           format,
           128, 128, 0, 0, 0
       };
       ${x}_image_handle_t hImage;
       ${x}ImageCreate(hContext, hDevice, &imageDesc, &hImage);

       // upload contents from host pointer
       ${x}CommandListAppendImageCopyFromMemory(hCommandList, hImage, nullptr, pImageData, nullptr, 0, nullptr);
       ...
