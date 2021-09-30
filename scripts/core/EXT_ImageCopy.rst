<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_image_copy:

======================================
 Image Copy Extension
======================================

API
----

* Functions


    * ${x}CommandListAppendImageCopyToMemoryExt
    * ${x}CommandListAppendImageCopyFromMemoryExt


* Enumerations


    * ${x}_image_copy_ext_version_t

Image Copy
~~~~~~~~~~

Sometimes it is desired to copy the contents of an image object to a buffer object, i.e., linear un-formatted memory, e.g., for use in a different library. The ${x}CommandListAppendImageCopyToMemory API call can be used to for this purpose if no padding is desired in the buffer being written into. The CommandListAppendImageCopyToMemoryExt call can be used to copy pixel values from an image object into a destination buffer with padding. Padding can be specified in both row pitch as well as slice pitch for 3D images/2D image stacks. The slice pitch must be set to 0 when performing this operation with 2D images.

The following psuedo-code demonstrates a sequence for copying a 32x32 patch out of an image object to a buffer with row pitch set to 64:

.. parsed-literal::

       ...
       // Create image region descriptor
       ze_image_region_t srcReg = {
         0,  // originX
         0,  // originY
         0,  // originZ
         32, // width
         32, // height
         0   // depth
       };


       ${x}_result_t result = ${x}CommandListAppendImageCopyToMemoryExt(hCmdList, &dst, hSrcImage, &srcRegion, 64, 0, nullptr, 0, nullptr);

Similarly, sometimes it is desired to copy the contents of a buffer object, i.e., linear un-formatted memory, to an image object, e.g., if the contents of the image are being imported from a different library. The ${x}CommandListAppendImageCopyFromMemory API call can be used to for this purpose if no padding is present in the buffer being read from. The CommandListAppendImageCopyFromMemoryExt call can be used to copy pixel values from the source buffer with padding into an image object. Padding can be specified in both row pitch as well as slice pitch for 3D images/2D image stacks. The slice pitch must be set to 0 when performing this operation with 2D images.

The following psuedo-code demonstrates a sequence for copying a 32x32 patch from a buffer with row pitch equal to 64 into an image object with row pitch:

.. parsed-literal::

       ...
       // Create image region descriptor
       ze_image_region_t srcReg = {
         0,  // originX
         0,  // originY
         0,  // originZ
         32, // width
         32, // height
         0   // depth
       };


       ${x}_result_t result = ${x}CommandListAppendImageCopyToMemoryExt(hCmdList, hDstImage, &src, &srcRegion, 64, 0, nullptr, 0, nullptr);
