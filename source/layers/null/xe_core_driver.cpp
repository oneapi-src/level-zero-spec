/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
* The source code contained or described herein and all documents related to the  
* source code ("Material") are owned by Intel Corporation or its suppliers or  
* licensors. Title to the Material remains with Intel Corporation or its suppliers  
* and licensors. The Material contains trade secrets and proprietary and confidential  
* information of Intel or its suppliers and licensors. The Material is protected by  
* worldwide copyright and trade secret laws and treaty provisions. No part of the  
* Material may be used, copied, reproduced, modified, published, uploaded, posted  
* transmitted, distributed, or disclosed in any way without Intel's prior express  
* written permission.  
*
* No license under any patent, copyright, trade secret or other intellectual  
* property right is granted to or conferred upon you by disclosure or delivery  
* of the Materials, either expressly, by implication, inducement, estoppel  
* or otherwise. Any license under such intellectual property rights must be  
* express and approved by Intel in writing.  
* @endcond
*
* @file xe_core_driver.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/nullddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_null.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeInit
xe_result_t __xecall
xeInit_null(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    // global functions need to be handled manually by the driver
    result = driver.xeInit( flags );

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetDriverVersion
xe_result_t __xecall
xeDeviceGroupGetDriverVersion_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of device group
    uint32_t* version                               ///< [out] driver version
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeGetDeviceGroups
xe_result_t __xecall
xeGetDeviceGroups_null(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_group_handle_t* pDeviceGroups         ///< [in,out][optional][range(0, *pCount)] array of handle of device groups
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    // global functions need to be handled manually by the driver
    result = driver.xeGetDeviceGroups( pCount, pDeviceGroups );

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetDevices
xe_result_t __xecall
xeDeviceGroupGetDevices_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_handle_t* pDevices                    ///< [in,out][optional][range(0, *pCount)] array of handle of devices
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    for( size_t i = 0; ( nullptr != pDevices ) && ( i < *pCount ); ++i )
        pDevices[ i ] = reinterpret_cast<xe_device_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGetSubDevice
xe_result_t __xecall
xeDeviceGetSubDevice_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phSubDevice = reinterpret_cast<xe_device_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetApiVersion
xe_result_t __xecall
xeDeviceGroupGetApiVersion_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetProperties
xe_result_t __xecall
xeDeviceGroupGetProperties_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetComputeProperties
xe_result_t __xecall
xeDeviceGroupGetComputeProperties_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemoryProperties
xe_result_t __xecall
xeDeviceGroupGetMemoryProperties_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGetP2PProperties
xe_result_t __xecall
xeDeviceGetP2PProperties_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceCanAccessPeer
xe_result_t __xecall
xeDeviceCanAccessPeer_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_bool_t* value                                ///< [out] returned access capability
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSetIntermediateCacheConfig
xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSetLastLevelCacheConfig
xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueCreate
xe_result_t __xecall
xeCommandQueueCreate_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueDestroy
xe_result_t __xecall
xeCommandQueueDestroy_null(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueExecuteCommandLists
xe_result_t __xecall
xeCommandQueueExecuteCommandLists_null(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    xe_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                    ///< to execute
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueSynchronize
xe_result_t __xecall
xeCommandQueueSynchronize_null(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListCreate
xe_result_t __xecall
xeCommandListCreate_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phCommandList = reinterpret_cast<xe_command_list_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListCreateImmediate
xe_result_t __xecall
xeCommandListCreateImmediate_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phCommandList = reinterpret_cast<xe_command_list_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListDestroy
xe_result_t __xecall
xeCommandListDestroy_null(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListClose
xe_result_t __xecall
xeCommandListClose_null(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListReset
xe_result_t __xecall
xeCommandListReset_null(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListSetParameter
xe_result_t __xecall
xeCommandListSetParameter_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListGetParameter
xe_result_t __xecall
xeCommandListGetParameter_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
    uint32_t* value                                 ///< [out] value of attribute
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListResetParameters
xe_result_t __xecall
xeCommandListResetParameters_null(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListReserveSpace
xe_result_t __xecall
xeCommandListReserveSpace_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendBarrier
xe_result_t __xecall
xeCommandListAppendBarrier_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryRangesBarrier
xe_result_t __xecall
xeCommandListAppendMemoryRangesBarrier_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numRanges,                             ///< [in] number of memory ranges
    const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
    const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSystemBarrier
xe_result_t __xecall
xeDeviceSystemBarrier_null(
    xe_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLMemory
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLMemory_null(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the memory
    cl_mem mem,                                     ///< [in] the OpenCL memory to register
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLProgram
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLProgram_null(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the program
    cl_program program,                             ///< [in] the OpenCL program to register
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phModule = reinterpret_cast<xe_module_handle_t>( driver.get() );
    return result;
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLCommandQueue
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLCommandQueue_null(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the command queue
    cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phCommandQueue = reinterpret_cast<xe_command_queue_handle_t>( driver.get() );
    return result;
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryCopy
xe_result_t __xecall
xeCommandListAppendMemoryCopy_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemorySet
xe_result_t __xecall
xeCommandListAppendMemorySet_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    int value,                                      ///< [in] value to initialize memory to
    size_t size,                                    ///< [in] size in bytes to initailize
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryCopyRegion
xe_result_t __xecall
xeCommandListAppendMemoryCopyRegion_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_copy_region_t* dstRegion,                    ///< [in] pointer to destination region to copy to
    uint32_t dstPitch,                              ///< [in] destination pitch in bytes
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    xe_copy_region_t* srcRegion,                    ///< [in] pointer to source region to copy from
    uint32_t srcPitch,                              ///< [in] source pitch in bytes
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopy
xe_result_t __xecall
xeCommandListAppendImageCopy_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyRegion
xe_result_t __xecall
xeCommandListAppendImageCopyRegion_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyToMemory
xe_result_t __xecall
xeCommandListAppendImageCopyToMemory_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyFromMemory
xe_result_t __xecall
xeCommandListAppendImageCopyFromMemory_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryPrefetch
xe_result_t __xecall
xeCommandListAppendMemoryPrefetch_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t count                                    ///< [in] size in bytes of the memory range to prefetch
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemAdvise
xe_result_t __xecall
xeCommandListAppendMemAdvise_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolCreate
xe_result_t __xecall
xeEventPoolCreate_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolDestroy
xe_result_t __xecall
xeEventPoolDestroy_null(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventCreate
xe_result_t __xecall
xeEventCreate_null(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phEvent = reinterpret_cast<xe_event_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventDestroy
xe_result_t __xecall
xeEventDestroy_null(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolGetIpcHandle
xe_result_t __xecall
xeEventPoolGetIpcHandle_null(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolOpenIpcHandle
xe_result_t __xecall
xeEventPoolOpenIpcHandle_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
    xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phEventPool = reinterpret_cast<xe_event_pool_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolCloseIpcHandle
xe_result_t __xecall
xeEventPoolCloseIpcHandle_null(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendSignalEvent
xe_result_t __xecall
xeCommandListAppendSignalEvent_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendWaitOnEvents
xe_result_t __xecall
xeCommandListAppendWaitOnEvents_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    xe_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                    ///< continuing
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventHostSignal
xe_result_t __xecall
xeEventHostSignal_null(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventHostSynchronize
xe_result_t __xecall
xeEventHostSynchronize_null(
    xe_event_handle_t hEvent,                       ///< [in] handle of the event
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeEventQueryStatus;
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventQueryStatus
xe_result_t __xecall
xeEventQueryStatus_null(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendEventReset
xe_result_t __xecall
xeCommandListAppendEventReset_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventReset
xe_result_t __xecall
xeEventReset_null(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceCreate
xe_result_t __xecall
xeFenceCreate_null(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phFence = reinterpret_cast<xe_fence_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceDestroy
xe_result_t __xecall
xeFenceDestroy_null(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceHostSynchronize
xe_result_t __xecall
xeFenceHostSynchronize_null(
    xe_fence_handle_t hFence,                       ///< [in] handle of the fence
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                    ///< if MAX_UINT32, then function will not return until complete or device
                                                    ///< is lost.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceQueryStatus
xe_result_t __xecall
xeFenceQueryStatus_null(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceReset
xe_result_t __xecall
xeFenceReset_null(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageGetProperties
xe_result_t __xecall
xeImageGetProperties_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageCreate
xe_result_t __xecall
xeImageCreate_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phImage = reinterpret_cast<xe_image_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageDestroy
xe_result_t __xecall
xeImageDestroy_null(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupAllocSharedMem
xe_result_t __xecall
xeDeviceGroupAllocSharedMem_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupAllocDeviceMem
xe_result_t __xecall
xeDeviceGroupAllocDeviceMem_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupAllocHostMem
xe_result_t __xecall
xeDeviceGroupAllocHostMem_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupFreeMem
xe_result_t __xecall
xeDeviceGroupFreeMem_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr                                 ///< [in] pointer to memory to free
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemProperties
xe_result_t __xecall
xeDeviceGroupGetMemProperties_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemAddressRange
xe_result_t __xecall
xeDeviceGroupGetMemAddressRange_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemIpcHandle
xe_result_t __xecall
xeDeviceGroupGetMemIpcHandle_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupOpenMemIpcHandle
xe_result_t __xecall
xeDeviceGroupOpenMemIpcHandle_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupCloseMemIpcHandle
xe_result_t __xecall
xeDeviceGroupCloseMemIpcHandle_null(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleCreate
xe_result_t __xecall
xeModuleCreate_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phModule = reinterpret_cast<xe_module_handle_t>( driver.get() );
    if( nullptr != phBuildLog ) *phBuildLog = reinterpret_cast<xe_module_build_log_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleDestroy
xe_result_t __xecall
xeModuleDestroy_null(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleBuildLogDestroy
xe_result_t __xecall
xeModuleBuildLogDestroy_null(
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleBuildLogGetString
xe_result_t __xecall
xeModuleBuildLogGetString_null(
    xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetNativeBinary
xe_result_t __xecall
xeModuleGetNativeBinary_null(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetGlobalPointer
xe_result_t __xecall
xeModuleGetGlobalPointer_null(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    const char* pGlobalName,                        ///< [in] name of function in global
    void** pPtr                                     ///< [out] device visible pointer
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionCreate
xe_result_t __xecall
xeFunctionCreate_null(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phFunction = reinterpret_cast<xe_function_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionDestroy
xe_result_t __xecall
xeFunctionDestroy_null(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetFunctionPointer
xe_result_t __xecall
xeModuleGetFunctionPointer_null(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetGroupSize
xe_result_t __xecall
xeFunctionSetGroupSize_null(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSuggestGroupSize
xe_result_t __xecall
xeFunctionSuggestGroupSize_null(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension.
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetArgumentValue
xe_result_t __xecall
xeFunctionSetArgumentValue_null(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetAttribute
xe_result_t __xecall
xeFunctionSetAttribute_null(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function.
    xe_function_set_attribute_t attr,               ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionGetAttribute
xe_result_t __xecall
xeFunctionGetAttribute_null(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_get_attribute_t attr,               ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchFunction
xe_result_t __xecall
xeCommandListAppendLaunchFunction_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] launch function arguments.
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchFunctionIndirect
xe_result_t __xecall
xeCommandListAppendLaunchFunctionIndirect_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchMultipleFunctionsIndirect
xe_result_t __xecall
xeCommandListAppendLaunchMultipleFunctionsIndirect_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
    xe_function_handle_t* phFunctions,              ///< [in][range(0, numFunctions)] handles of the function objects
    const uint32_t* pNumLaunchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of launch arguments; value must be less-than or equal-to
                                                    ///< numFunctions
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in][range(0, numFunctions)] pointer to device buffer that will
                                                    ///< contain a contiguous array of launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchHostFunction
xe_result_t __xecall
xeCommandListAppendLaunchHostFunction_null(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData,                                ///< [in] pointer to user data to pass to host function.
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceMakeMemoryResident
xe_result_t __xecall
xeDeviceMakeMemoryResident_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceEvictMemory
xe_result_t __xecall
xeDeviceEvictMemory_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceMakeImageResident
xe_result_t __xecall
xeDeviceMakeImageResident_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceEvictImage
xe_result_t __xecall
xeDeviceEvictImage_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeSamplerCreate
xe_result_t __xecall
xeSamplerCreate_null(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
    xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    *phSampler = reinterpret_cast<xe_sampler_handle_t>( driver.get() );
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeSamplerDestroy
xe_result_t __xecall
xeSamplerDestroy_null(
    xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    )
{
    xe_result_t result = XE_RESULT_SUCCESS;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;


    pDdiTable->pfnInit                                   = xeInit_null;

    pDdiTable->pfnGetDeviceGroups                        = xeGetDeviceGroups_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetSubDevice                           = xeDeviceGetSubDevice_null;

    pDdiTable->pfnGetP2PProperties                       = xeDeviceGetP2PProperties_null;

    pDdiTable->pfnCanAccessPeer                          = xeDeviceCanAccessPeer_null;

    pDdiTable->pfnSetIntermediateCacheConfig             = xeDeviceSetIntermediateCacheConfig_null;

    pDdiTable->pfnSetLastLevelCacheConfig                = xeDeviceSetLastLevelCacheConfig_null;

    pDdiTable->pfnSystemBarrier                          = xeDeviceSystemBarrier_null;

#if XE_ENABLE_OCL_INTEROP
    pDdiTable->pfnRegisterCLMemory                       = xeDeviceRegisterCLMemory_null;
#endif

#if XE_ENABLE_OCL_INTEROP
    pDdiTable->pfnRegisterCLProgram                      = xeDeviceRegisterCLProgram_null;
#endif

#if XE_ENABLE_OCL_INTEROP
    pDdiTable->pfnRegisterCLCommandQueue                 = xeDeviceRegisterCLCommandQueue_null;
#endif

    pDdiTable->pfnMakeMemoryResident                     = xeDeviceMakeMemoryResident_null;

    pDdiTable->pfnEvictMemory                            = xeDeviceEvictMemory_null;

    pDdiTable->pfnMakeImageResident                      = xeDeviceMakeImageResident_null;

    pDdiTable->pfnEvictImage                             = xeDeviceEvictImage_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_group_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetDriverVersion                       = xeDeviceGroupGetDriverVersion_null;

    pDdiTable->pfnGetDevices                             = xeDeviceGroupGetDevices_null;

    pDdiTable->pfnGetApiVersion                          = xeDeviceGroupGetApiVersion_null;

    pDdiTable->pfnGetProperties                          = xeDeviceGroupGetProperties_null;

    pDdiTable->pfnGetComputeProperties                   = xeDeviceGroupGetComputeProperties_null;

    pDdiTable->pfnGetMemoryProperties                    = xeDeviceGroupGetMemoryProperties_null;

    pDdiTable->pfnAllocSharedMem                         = xeDeviceGroupAllocSharedMem_null;

    pDdiTable->pfnAllocDeviceMem                         = xeDeviceGroupAllocDeviceMem_null;

    pDdiTable->pfnAllocHostMem                           = xeDeviceGroupAllocHostMem_null;

    pDdiTable->pfnFreeMem                                = xeDeviceGroupFreeMem_null;

    pDdiTable->pfnGetMemProperties                       = xeDeviceGroupGetMemProperties_null;

    pDdiTable->pfnGetMemAddressRange                     = xeDeviceGroupGetMemAddressRange_null;

    pDdiTable->pfnGetMemIpcHandle                        = xeDeviceGroupGetMemIpcHandle_null;

    pDdiTable->pfnOpenMemIpcHandle                       = xeDeviceGroupOpenMemIpcHandle_null;

    pDdiTable->pfnCloseMemIpcHandle                      = xeDeviceGroupCloseMemIpcHandle_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandQueueProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xeCommandQueueCreate_null;

    pDdiTable->pfnDestroy                                = xeCommandQueueDestroy_null;

    pDdiTable->pfnExecuteCommandLists                    = xeCommandQueueExecuteCommandLists_null;

    pDdiTable->pfnSynchronize                            = xeCommandQueueSynchronize_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xeCommandListCreate_null;

    pDdiTable->pfnCreateImmediate                        = xeCommandListCreateImmediate_null;

    pDdiTable->pfnDestroy                                = xeCommandListDestroy_null;

    pDdiTable->pfnClose                                  = xeCommandListClose_null;

    pDdiTable->pfnReset                                  = xeCommandListReset_null;

    pDdiTable->pfnSetParameter                           = xeCommandListSetParameter_null;

    pDdiTable->pfnGetParameter                           = xeCommandListGetParameter_null;

    pDdiTable->pfnResetParameters                        = xeCommandListResetParameters_null;

    pDdiTable->pfnReserveSpace                           = xeCommandListReserveSpace_null;

    pDdiTable->pfnAppendBarrier                          = xeCommandListAppendBarrier_null;

    pDdiTable->pfnAppendMemoryRangesBarrier              = xeCommandListAppendMemoryRangesBarrier_null;

    pDdiTable->pfnAppendMemoryCopy                       = xeCommandListAppendMemoryCopy_null;

    pDdiTable->pfnAppendMemorySet                        = xeCommandListAppendMemorySet_null;

    pDdiTable->pfnAppendMemoryCopyRegion                 = xeCommandListAppendMemoryCopyRegion_null;

    pDdiTable->pfnAppendImageCopy                        = xeCommandListAppendImageCopy_null;

    pDdiTable->pfnAppendImageCopyRegion                  = xeCommandListAppendImageCopyRegion_null;

    pDdiTable->pfnAppendImageCopyToMemory                = xeCommandListAppendImageCopyToMemory_null;

    pDdiTable->pfnAppendImageCopyFromMemory              = xeCommandListAppendImageCopyFromMemory_null;

    pDdiTable->pfnAppendMemoryPrefetch                   = xeCommandListAppendMemoryPrefetch_null;

    pDdiTable->pfnAppendMemAdvise                        = xeCommandListAppendMemAdvise_null;

    pDdiTable->pfnAppendSignalEvent                      = xeCommandListAppendSignalEvent_null;

    pDdiTable->pfnAppendWaitOnEvents                     = xeCommandListAppendWaitOnEvents_null;

    pDdiTable->pfnAppendEventReset                       = xeCommandListAppendEventReset_null;

    pDdiTable->pfnAppendLaunchFunction                   = xeCommandListAppendLaunchFunction_null;

    pDdiTable->pfnAppendLaunchFunctionIndirect           = xeCommandListAppendLaunchFunctionIndirect_null;

    pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect  = xeCommandListAppendLaunchMultipleFunctionsIndirect_null;

    pDdiTable->pfnAppendLaunchHostFunction               = xeCommandListAppendLaunchHostFunction_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFenceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xeFenceCreate_null;

    pDdiTable->pfnDestroy                                = xeFenceDestroy_null;

    pDdiTable->pfnHostSynchronize                        = xeFenceHostSynchronize_null;

    pDdiTable->pfnQueryStatus                            = xeFenceQueryStatus_null;

    pDdiTable->pfnReset                                  = xeFenceReset_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xeEventPoolCreate_null;

    pDdiTable->pfnDestroy                                = xeEventPoolDestroy_null;

    pDdiTable->pfnGetIpcHandle                           = xeEventPoolGetIpcHandle_null;

    pDdiTable->pfnOpenIpcHandle                          = xeEventPoolOpenIpcHandle_null;

    pDdiTable->pfnCloseIpcHandle                         = xeEventPoolCloseIpcHandle_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xeEventCreate_null;

    pDdiTable->pfnDestroy                                = xeEventDestroy_null;

    pDdiTable->pfnHostSignal                             = xeEventHostSignal_null;

    pDdiTable->pfnHostSynchronize                        = xeEventHostSynchronize_null;

    pDdiTable->pfnQueryStatus                            = xeEventQueryStatus_null;

    pDdiTable->pfnReset                                  = xeEventReset_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetImageProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = xeImageGetProperties_null;

    pDdiTable->pfnCreate                                 = xeImageCreate_null;

    pDdiTable->pfnDestroy                                = xeImageDestroy_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xeModuleCreate_null;

    pDdiTable->pfnDestroy                                = xeModuleDestroy_null;

    pDdiTable->pfnGetNativeBinary                        = xeModuleGetNativeBinary_null;

    pDdiTable->pfnGetGlobalPointer                       = xeModuleGetGlobalPointer_null;

    pDdiTable->pfnGetFunctionPointer                     = xeModuleGetFunctionPointer_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleBuildLogProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnDestroy                                = xeModuleBuildLogDestroy_null;

    pDdiTable->pfnGetString                              = xeModuleBuildLogGetString_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFunctionProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_function_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xeFunctionCreate_null;

    pDdiTable->pfnDestroy                                = xeFunctionDestroy_null;

    pDdiTable->pfnSetGroupSize                           = xeFunctionSetGroupSize_null;

    pDdiTable->pfnSuggestGroupSize                       = xeFunctionSuggestGroupSize_null;

    pDdiTable->pfnSetArgumentValue                       = xeFunctionSetArgumentValue_null;

    pDdiTable->pfnSetAttribute                           = xeFunctionSetAttribute_null;

    pDdiTable->pfnGetAttribute                           = xeFunctionGetAttribute_null;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetSamplerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( driver.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = xeSamplerCreate_null;

    pDdiTable->pfnDestroy                                = xeSamplerDestroy_null;

    return result;
}

#if defined(__cplusplus)
};
#endif
