<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_image_format_support:

======================================
Image Format Support Extension
======================================

API
----

* Macros

    * ${X}_IMAGE_FORMAT_SUPPORT_EXT_NAME

* Enumerations

    * ${x}_image_format_support_ext_version_t
    * ${x}_structure_type_t
        * ${X}_STRUCTURE_TYPE_IMAGE_FORMAT_SUPPORT_EXT_PROPERTIES

* Structures

    * ${x}_image_format_support_ext_properties_t

Image Format Support Query
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Image Format Support extension provides a standardized mechanism to query whether a specific image format is supported on a target device. This eliminates the need for upper layers to maintain device-specific format support tables or use probabilistic methods (such as attempting image creation and handling failures) to determine format compatibility.

By chaining the ${x}_image_format_support_ext_properties_t structure to ${x}_image_properties_t when calling ${x}ImageGetProperties, applications can directly query format support. The Level Zero driver populates the `supported` field based on the image descriptor and device handle provided.

**Key Benefits:**

* Eliminates hard-coded device-specific image format tables in upper layers
* Removes the need for trial-and-error image creation to test format support
* Provides up-to-date format support information directly from the driver
* Enables efficient format validation before resource allocation

Usage
~~~~~

To query image format support, create a ${x}_image_format_support_ext_properties_t structure and chain it to ${x}_image_properties_t via the pNext member. The driver will populate the `supported` field during the ${x}ImageGetProperties call.

Example Usage
-------------

Single Image Format Validation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    ze_result_t checkImageFormatSupport(ze_device_handle_t device, 
                                       const ze_image_desc_t* imageDesc) {
        // Create the extension struct
        ze_image_format_support_ext_properties_t formatSupport = {};
        formatSupport.stype = ZE_STRUCTURE_TYPE_IMAGE_FORMAT_SUPPORT_EXT_PROPERTIES;
        formatSupport.pNext = nullptr;
        formatSupport.supported = false;
        
        // Create the properties struct and chain the extension
        ze_image_properties_t imageProperties = {};
        imageProperties.stype = ZE_STRUCTURE_TYPE_IMAGE_PROPERTIES;
        imageProperties.pNext = &formatSupport;
        
        // Query the properties - this will populate the supported field
        // The device and imageDesc are passed directly to zeImageGetProperties
        ze_result_t result = zeImageGetProperties(device, imageDesc, &imageProperties);
        
        if (result == ZE_RESULT_SUCCESS) {
            if (formatSupport.supported) {
                printf("Image format is supported\n");
            } else {
                printf("Image format is not supported\n");
            }
        }
        
        return result;
    }

Testing Multiple Image Formats on the Same Device
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    ze_result_t testMultipleImageFormats(ze_device_handle_t device) {
        // Define different image formats to test
        ze_image_format_t formats[] = {
            {ZE_IMAGE_FORMAT_LAYOUT_32, ZE_IMAGE_FORMAT_TYPE_UINT,
             ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_0,
             ZE_IMAGE_FORMAT_SWIZZLE_0, ZE_IMAGE_FORMAT_SWIZZLE_1},
            {ZE_IMAGE_FORMAT_LAYOUT_8_8_8_8, ZE_IMAGE_FORMAT_TYPE_UNORM,
             ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_G,
             ZE_IMAGE_FORMAT_SWIZZLE_B, ZE_IMAGE_FORMAT_SWIZZLE_A},
            {ZE_IMAGE_FORMAT_LAYOUT_16_16_16_16, ZE_IMAGE_FORMAT_TYPE_FLOAT,
             ZE_IMAGE_FORMAT_SWIZZLE_R, ZE_IMAGE_FORMAT_SWIZZLE_G,
             ZE_IMAGE_FORMAT_SWIZZLE_B, ZE_IMAGE_FORMAT_SWIZZLE_A}
        };
        
        for (size_t i = 0; i < sizeof(formats) / sizeof(formats[0]); i++) {
            ze_image_desc_t imageDesc = {};
            imageDesc.stype = ZE_STRUCTURE_TYPE_IMAGE_DESC;
            imageDesc.type = ZE_IMAGE_TYPE_2D;
            imageDesc.format = formats[i];
            imageDesc.width = 1024;
            imageDesc.height = 1024;
            imageDesc.depth = 1;
            
            ze_image_format_support_ext_properties_t formatSupport = {};
            formatSupport.stype = ZE_STRUCTURE_TYPE_IMAGE_FORMAT_SUPPORT_EXT_PROPERTIES;
            formatSupport.pNext = nullptr;
            formatSupport.supported = false;

            ze_image_properties_t imageProperties = {};
            imageProperties.stype = ZE_STRUCTURE_TYPE_IMAGE_PROPERTIES;
            imageProperties.pNext = &formatSupport;
            
            ze_result_t result = zeImageGetProperties(device, &imageDesc, &imageProperties);
            
            if (result == ZE_RESULT_SUCCESS) {
                printf("Format %zu: %s\n", i,
                       formatSupport.supported ? "SUPPORTED" : "NOT SUPPORTED");
            }
        }
        
        return ZE_RESULT_SUCCESS;
    }

Testing the Same Image Format Across Multiple Devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    ze_result_t testMultiDevice(ze_driver_handle_t driver) {
        uint32_t deviceCount = 0;
        zeDeviceGet(driver, &deviceCount, nullptr);
      
        std::vector<ze_device_handle_t> devices(deviceCount);
        zeDeviceGet(driver, &deviceCount, devices.data());
        
        // Define the image format to test
        ze_image_desc_t testImageDesc = {};
        testImageDesc.stype = ZE_STRUCTURE_TYPE_IMAGE_DESC;
        testImageDesc.type = ZE_IMAGE_TYPE_2D;
        testImageDesc.format.layout = ZE_IMAGE_FORMAT_LAYOUT_32;
        testImageDesc.format.type = ZE_IMAGE_FORMAT_TYPE_FLOAT;
        testImageDesc.format.x = ZE_IMAGE_FORMAT_SWIZZLE_R;
        testImageDesc.format.y = ZE_IMAGE_FORMAT_SWIZZLE_0;
        testImageDesc.format.z = ZE_IMAGE_FORMAT_SWIZZLE_0;
        testImageDesc.format.w = ZE_IMAGE_FORMAT_SWIZZLE_1;
        testImageDesc.width = 2048;
        testImageDesc.height = 2048;
        testImageDesc.depth = 1;
        
        printf("Testing format support across %u devices:\n", deviceCount);
        
        for (uint32_t i = 0; i < deviceCount; i++) {
            ze_image_format_support_ext_properties_t formatSupport = {};
            formatSupport.stype = ZE_STRUCTURE_TYPE_IMAGE_FORMAT_SUPPORT_EXT_PROPERTIES;
            formatSupport.pNext = nullptr;
            formatSupport.supported = false;
            
            ze_image_properties_t imageProperties = {};
            imageProperties.stype = ZE_STRUCTURE_TYPE_IMAGE_PROPERTIES;
            imageProperties.pNext = &formatSupport;
            
            ze_result_t result = zeImageGetProperties(devices[i], &testImageDesc, 
                                                      &imageProperties);
            
            if (result == ZE_RESULT_SUCCESS) {
                printf("  Device %u: %s\n", i,
                       formatSupport.supported ? "✓ SUPPORTED" : "✗ NOT SUPPORTED");
            } else {
                printf("  Device %u: Query failed with error code %x\n", i, result);
            }
        }
        
        return ZE_RESULT_SUCCESS;
    }
