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
* @file icd_loader.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/icd_loader.h.mako
* @endcond
*
******************************************************************************/
#ifndef _XE_LOADER_H
#define _XE_LOADER_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_all.h"

typedef struct _cl_mem* cl_mem;
typedef struct _cl_command_queue* cl_command_queue;
typedef struct _cl_context* cl_context;
typedef struct _cl_program* cl_program;

typedef xe_result_t (__xecall *pfn_xeCommandListEncodeExecutionBarrier)(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    );
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLMemory)(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the memory
    cl_mem mem,                                     ///< [in] the OpenCL memory to register
    void** ptr                                      ///< [out] pointer to device allocation
    );
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLProgram)(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the program
    cl_program program,                             ///< [in] the OpenCL program to register
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    );
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLCommandQueue)(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the command queue
    cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    );
#endif // XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceCreateCommandGraph)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_graph_desc_t* desc,            ///< [in] pointer to command graph descriptor
    xe_command_graph_handle_t* phCommandGraph       ///< [out] pointer to handle of command graph object created
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphDestroy)(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to destroy
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphClose)(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to close
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphReset)(
    xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to reset
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateCommandList)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCopyCommandList)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_command_list_handle_t hCommandList,          ///< [in] handle to command list to copy
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );
typedef xe_result_t (__xecall *pfn_xeCommandListDestroy)(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    );
typedef xe_result_t (__xecall *pfn_xeCommandListClose)(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    );
typedef xe_result_t (__xecall *pfn_xeCommandListReset)(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    );
typedef xe_result_t (__xecall *pfn_xeCommandListSetParameter)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    );
typedef xe_result_t (__xecall *pfn_xeCommandListGetParameter)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
    uint32_t* value                                 ///< [out] value of attribute
    );
typedef xe_result_t (__xecall *pfn_xeCommandListResetParameters)(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeCommandLists)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numCommandLists,                       ///< [in] number of command lists to encode
    xe_command_list_handle_t* phCommandLists        ///< [in] list of handles of the command lists to encode for execution
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeCommands)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_command_format_t format,                     ///< [in] format of the command blob
    size_t size,                                    ///< [in] size (in bytes) of the command blob
    void* pBlob                                     ///< [in] pointer to blob of commands to encode into the command list
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateCommandQueue)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    );
typedef xe_result_t (__xecall *pfn_xeCommandQueueDestroy)(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    );
typedef xe_result_t (__xecall *pfn_xeCommandQueueEnqueueCommandLists)(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to enqueue
    xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to enqueue for execution
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    );
typedef xe_result_t (__xecall *pfn_xeCommandQueueSynchronize)(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if MAX_UINT32, then function will not
                                                    ///< return until complete.
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeMemoryCopy)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size                                     ///< [in] size in bytes to copy
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeMemorySet)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    int value,                                      ///< [in] value to initialize memory to
    size_t size                                     ///< [in] size in bytes to initailize
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeImageCopy)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage                     ///< [in] handle of source image to copy from
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeImageCopyRegion)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion                   ///< [in][optional] source region descriptor
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeImageCopyToMemory)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion                   ///< [in][optional] source region descriptor
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeImageCopyFromMemory)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    const void* srcptr                              ///< [in] pointer to source memory to copy from
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeMemoryPrefetch)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory region to prefetch
    size_t count                                    ///< [in] size in bytes of the memory region to prefetch
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeMemAdvise)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    );
typedef xe_result_t (__xecall *pfn_xeDriverGetDeviceCount)(
    uint32_t* count                                 ///< [out] number of devices available
    );
typedef xe_result_t (__xecall *pfn_xeDriverGetDeviceUniqueIds)(
    uint32_t count,                                 ///< [in] size of device unique ids array. Typically, this will be
                                                    ///< ${x}DeviceGetCount.
    uint32_t* pUniqueIds                            ///< [out] pointer to an array of unique ids for devices. Caller must
                                                    ///< supply array.
    );
typedef xe_result_t (__xecall *pfn_xeDriverGetDevice)(
    uint32_t uniqueId,                              ///< [in] unique id of device to retrieve. Use ${x}DriverGetDeviceUniqueIds
                                                    ///< to obtain a unique Id.
    xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetSubDevice)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetApiVersion)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_api_version_t* version                       ///< [out] api version
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetProperties)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetComputeProperties)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetMemoryProperties)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetLinkProperties)(
    uint32_t srcOrdinal,                            ///< [in] source device ordinal
    uint32_t dstOrdinal,                            ///< [in] destination device ordinal
    xe_device_link_properties_t* pLinkProperties    ///< [out] link properties between source and destination devices
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCanAccessPeer)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    bool* value                                     ///< [out] returned access capability
    );
typedef xe_result_t (__xecall *pfn_xeDeviceSetIntermediateCacheConfig)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    );
typedef xe_result_t (__xecall *pfn_xeDeviceSetLastLevelCacheConfig)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    );
typedef xe_result_t (__xecall *pfn_xeDriverInit)(
    xe_init_flag_t flags                            ///< [in] initialization flags
    );
typedef xe_result_t (__xecall *pfn_xeDriverGetVersion)(
    uint32_t* version                               ///< [out] driver version
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateEvent)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    );
typedef xe_result_t (__xecall *pfn_xeDevicePlaceEvent)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    void* ptr,                                      ///< [in] pointer to the device pointer where the event should be placed
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    );
typedef xe_result_t (__xecall *pfn_xeEventDestroy)(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeSignalEvent)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeWaitOnEvent)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeSignalMultipleEvents)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeWaitOnMultipleEvents)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    );
typedef xe_result_t (__xecall *pfn_xeHostSignalEvent)(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    );
typedef xe_result_t (__xecall *pfn_xeHostWaitOnEvent)(
    xe_event_handle_t hEvent,                       ///< [in] handle of the event
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if MAX_UINT32, then function will not
                                                    ///< return until complete.
    );
typedef xe_result_t (__xecall *pfn_xeHostSignalMultipleEvents)(
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    );
typedef xe_result_t (__xecall *pfn_xeHostWaitOnMultipleEvents)(
    uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
    xe_event_handle_t* phEvents,                    ///< [in] pointer to array of handles of the events
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if MAX_UINT32, then function will not
                                                    ///< return until complete.
    );
typedef xe_result_t (__xecall *pfn_xeEventQueryStatus)(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    );
typedef xe_result_t (__xecall *pfn_xeEventQueryElapsedTime)(
    xe_event_handle_t hEventStart,                  ///< [in] handle of the start event
    xe_event_handle_t hEventEnd,                    ///< [in] handle of the end event
    double_t* pTime                                 ///< [out] time in milliseconds
    );
typedef xe_result_t (__xecall *pfn_xeEventQueryMetricsData)(
    xe_event_handle_t hEventStart,                  ///< [in] handle of the start event
    xe_event_handle_t hEventEnd,                    ///< [in] handle of the end event
    size_t reportSize,                              ///< [in] size of the report data buffer in bytes
    uint32_t* pReportData                           ///< [out] report data buffer
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeEventReset)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    );
typedef xe_result_t (__xecall *pfn_xeEventReset)(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    );
typedef xe_result_t (__xecall *pfn_xeCommandQueueCreateFence)(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    );
typedef xe_result_t (__xecall *pfn_xeFenceDestroy)(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    );
typedef xe_result_t (__xecall *pfn_xeHostWaitOnFence)(
    xe_fence_handle_t hFence,                       ///< [in] handle of the fence
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if MAX_UINT32, then function will not
                                                    ///< return until complete.
    );
typedef xe_result_t (__xecall *pfn_xeHostWaitOnMultipleFences)(
    uint32_t numFences,                             ///< [in] number of fences in hFences
    xe_fence_handle_t* phFences,                    ///< [in] pointer to array of handles of the fences
    xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
    uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                    ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                    ///< must be zero.
    uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                    ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                    ///< must be zero.
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                    ///< before returning; if zero, then only a single status check is made
                                                    ///< before immediately returning; if MAX_UINT32, then function will not
                                                    ///< return until complete.
    );
typedef xe_result_t (__xecall *pfn_xeFenceQueryStatus)(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    );
typedef xe_result_t (__xecall *pfn_xeFenceQueryElapsedTime)(
    xe_fence_handle_t hFenceStart,                  ///< [in] handle of the fence
    xe_fence_handle_t hFenceEnd,                    ///< [in] handle of the fence
    double_t* pTime                                 ///< [out] time in milliseconds
    );
typedef xe_result_t (__xecall *pfn_xeFenceReset)(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateImage)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    );
typedef xe_result_t (__xecall *pfn_xeImageDestroy)(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    );
typedef xe_result_t (__xecall *pfn_xeCreateMemAllocator)(
    xe_mem_allocator_handle_t* phMemAllocHandle     ///< [out] Returned memory allocator handle
    );
typedef xe_result_t (__xecall *pfn_xeMemAllocatorDestroy)(
    xe_mem_allocator_handle_t hMemAllocHandle       ///< [in] handle of memory allocator to destroy
    );
typedef xe_result_t (__xecall *pfn_xeSharedMemAlloc)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    );
typedef xe_result_t (__xecall *pfn_xeMemAlloc)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    );
typedef xe_result_t (__xecall *pfn_xeHostMemAlloc)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    );
typedef xe_result_t (__xecall *pfn_xeMemFree)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr                                 ///< [in] pointer to memory to free
    );
typedef xe_result_t (__xecall *pfn_xeMemGetProperty)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_property_t property,                  ///< [in] Property of the allocation to query
    void* pValue                                    ///< [out] Value of the queried property
    );
typedef xe_result_t (__xecall *pfn_xeMemGetAddressRange)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [out] Returned base address of the allocation (optional)
    size_t* pSize                                   ///< [out] Returned size of the allocation (optional)
    );
typedef xe_result_t (__xecall *pfn_xeIpcGetMemHandle)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    );
typedef xe_result_t (__xecall *pfn_xeIpcOpenMemHandle)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    );
typedef xe_result_t (__xecall *pfn_xeIpcCloseMemHandle)(
    xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateModule)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
    );
typedef xe_result_t (__xecall *pfn_xeModuleDestroy)(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    );
typedef xe_result_t (__xecall *pfn_xeModuleBuildLogDestroy)(
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    );
typedef xe_result_t (__xecall *pfn_xeModuleBuildLogGetString)(
    xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [out] size of build log string.
    const char** pBuildLog                          ///< [out] pointer to null-terminated string of the log.
    );
typedef xe_result_t (__xecall *pfn_xeModuleGetNativeBinary)(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    uint32_t* pSize,                                ///< [out] size of native binary.
    char** pModuleNativeBinary                      ///< [out] pointer to native binary
    );
typedef xe_result_t (__xecall *pfn_xeModuleCreateFunction)(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    );
typedef xe_result_t (__xecall *pfn_xeFunctionDestroy)(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    );
typedef xe_result_t (__xecall *pfn_xeModuleGetFunctionPointer)(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    );
typedef xe_result_t (__xecall *pfn_xeFunctionSetGroupSize)(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    );
typedef xe_result_t (__xecall *pfn_xeFunctionSuggestGroupSize)(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension.
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
    );
typedef xe_result_t (__xecall *pfn_xeFunctionSetArgumentValue)(
    xe_function_handle_t hFunction,                 ///< [in/out] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in] argument value represented as matching arg type
    );
typedef xe_result_t (__xecall *pfn_xeFunctionSetAttribute)(
    xe_function_handle_t hFunction,                 ///< [in/out] handle of the function.
    xe_function_set_attribute_t attr,               ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    );
typedef xe_result_t (__xecall *pfn_xeFunctionGetAttribute)(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_get_attribute_t attr,               ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeDispatchFunction)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_dispatch_function_arguments_t* pDispatchFuncArgs,  ///< [in] dispatch function arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphEncodeDispatchFunction)(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_dispatch_function_arguments_t* pDispatchFuncArgs,  ///< [in] dispatch function arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeDispatchFunctionIndirect)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,  ///< [in] Pointer to buffer that will contain dispatch arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphEncodeDispatchFunctionIndirect)(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,  ///< [in] Pointer to buffer that will contain dispatch arguments.
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeDispatchHostFunction)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphEncodeDispatchHostFunction)(
    xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    );
typedef xe_result_t (__xecall *pfn_xeDeviceMakeMemoryResident)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    );
typedef xe_result_t (__xecall *pfn_xeDeviceEvictMemory)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    );
typedef xe_result_t (__xecall *pfn_xeDeviceMakeImageResident)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    );
typedef xe_result_t (__xecall *pfn_xeDeviceEvictImage)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateSampler)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
    xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    );
typedef xe_result_t (__xecall *pfn_xeSamplerDestroy)(
    xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateSemaphore)(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_semaphore_desc_t* desc,                ///< [in] pointer to semaphore descriptor
    xe_semaphore_handle_t* phSemaphore              ///< [out] pointer to handle of semaphore object created
    );
typedef xe_result_t (__xecall *pfn_xeSemaphoreDestroy)(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of semaphore object to destroy
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeSemaphoreSignal)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore
    xe_semaphore_value_t value                      ///< [in] the value to write on signal
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeSemaphoreWait)(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore
    xe_semaphore_wait_operation_t operation,        ///< [in] wait operation type
    xe_semaphore_value_t value                      ///< [in] the value to wait upon
    );
typedef xe_result_t (__xecall *pfn_xeSemaphoreQueryValue)(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of the semaphore
    );
typedef xe_result_t (__xecall *pfn_xeSemaphoreReset)(
    xe_semaphore_handle_t hSemaphore                ///< [in] handle of the semaphore
    );

typedef struct _xe_dispatch_table_t
{
    pfn_xeCommandListEncodeExecutionBarrier xeCommandListEncodeExecutionBarrier;
#if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLMemory xeDeviceRegisterCLMemory;
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLProgram xeDeviceRegisterCLProgram;
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLCommandQueue xeDeviceRegisterCLCommandQueue;
#endif // XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceCreateCommandGraph xeDeviceCreateCommandGraph;
    pfn_xeCommandGraphDestroy xeCommandGraphDestroy;
    pfn_xeCommandGraphClose xeCommandGraphClose;
    pfn_xeCommandGraphReset xeCommandGraphReset;
    pfn_xeDeviceCreateCommandList xeDeviceCreateCommandList;
    pfn_xeDeviceCopyCommandList xeDeviceCopyCommandList;
    pfn_xeCommandListDestroy xeCommandListDestroy;
    pfn_xeCommandListClose xeCommandListClose;
    pfn_xeCommandListReset xeCommandListReset;
    pfn_xeCommandListSetParameter xeCommandListSetParameter;
    pfn_xeCommandListGetParameter xeCommandListGetParameter;
    pfn_xeCommandListResetParameters xeCommandListResetParameters;
    pfn_xeCommandListEncodeCommandLists xeCommandListEncodeCommandLists;
    pfn_xeCommandListEncodeCommands xeCommandListEncodeCommands;
    pfn_xeDeviceCreateCommandQueue xeDeviceCreateCommandQueue;
    pfn_xeCommandQueueDestroy xeCommandQueueDestroy;
    pfn_xeCommandQueueEnqueueCommandLists xeCommandQueueEnqueueCommandLists;
    pfn_xeCommandQueueSynchronize xeCommandQueueSynchronize;
    pfn_xeCommandListEncodeMemoryCopy xeCommandListEncodeMemoryCopy;
    pfn_xeCommandListEncodeMemorySet xeCommandListEncodeMemorySet;
    pfn_xeCommandListEncodeImageCopy xeCommandListEncodeImageCopy;
    pfn_xeCommandListEncodeImageCopyRegion xeCommandListEncodeImageCopyRegion;
    pfn_xeCommandListEncodeImageCopyToMemory xeCommandListEncodeImageCopyToMemory;
    pfn_xeCommandListEncodeImageCopyFromMemory xeCommandListEncodeImageCopyFromMemory;
    pfn_xeCommandListEncodeMemoryPrefetch xeCommandListEncodeMemoryPrefetch;
    pfn_xeCommandListEncodeMemAdvise xeCommandListEncodeMemAdvise;
    pfn_xeDriverGetDeviceCount xeDriverGetDeviceCount;
    pfn_xeDriverGetDeviceUniqueIds xeDriverGetDeviceUniqueIds;
    pfn_xeDriverGetDevice xeDriverGetDevice;
    pfn_xeDeviceGetSubDevice xeDeviceGetSubDevice;
    pfn_xeDeviceGetApiVersion xeDeviceGetApiVersion;
    pfn_xeDeviceGetProperties xeDeviceGetProperties;
    pfn_xeDeviceGetComputeProperties xeDeviceGetComputeProperties;
    pfn_xeDeviceGetMemoryProperties xeDeviceGetMemoryProperties;
    pfn_xeDeviceGetLinkProperties xeDeviceGetLinkProperties;
    pfn_xeDeviceCanAccessPeer xeDeviceCanAccessPeer;
    pfn_xeDeviceSetIntermediateCacheConfig xeDeviceSetIntermediateCacheConfig;
    pfn_xeDeviceSetLastLevelCacheConfig xeDeviceSetLastLevelCacheConfig;
    pfn_xeDriverInit xeDriverInit;
    pfn_xeDriverGetVersion xeDriverGetVersion;
    pfn_xeDeviceCreateEvent xeDeviceCreateEvent;
    pfn_xeDevicePlaceEvent xeDevicePlaceEvent;
    pfn_xeEventDestroy xeEventDestroy;
    pfn_xeCommandListEncodeSignalEvent xeCommandListEncodeSignalEvent;
    pfn_xeCommandListEncodeWaitOnEvent xeCommandListEncodeWaitOnEvent;
    pfn_xeCommandListEncodeSignalMultipleEvents xeCommandListEncodeSignalMultipleEvents;
    pfn_xeCommandListEncodeWaitOnMultipleEvents xeCommandListEncodeWaitOnMultipleEvents;
    pfn_xeHostSignalEvent xeHostSignalEvent;
    pfn_xeHostWaitOnEvent xeHostWaitOnEvent;
    pfn_xeHostSignalMultipleEvents xeHostSignalMultipleEvents;
    pfn_xeHostWaitOnMultipleEvents xeHostWaitOnMultipleEvents;
    pfn_xeEventQueryStatus xeEventQueryStatus;
    pfn_xeEventQueryElapsedTime xeEventQueryElapsedTime;
    pfn_xeEventQueryMetricsData xeEventQueryMetricsData;
    pfn_xeCommandListEncodeEventReset xeCommandListEncodeEventReset;
    pfn_xeEventReset xeEventReset;
    pfn_xeCommandQueueCreateFence xeCommandQueueCreateFence;
    pfn_xeFenceDestroy xeFenceDestroy;
    pfn_xeHostWaitOnFence xeHostWaitOnFence;
    pfn_xeHostWaitOnMultipleFences xeHostWaitOnMultipleFences;
    pfn_xeFenceQueryStatus xeFenceQueryStatus;
    pfn_xeFenceQueryElapsedTime xeFenceQueryElapsedTime;
    pfn_xeFenceReset xeFenceReset;
    pfn_xeDeviceCreateImage xeDeviceCreateImage;
    pfn_xeImageDestroy xeImageDestroy;
    pfn_xeCreateMemAllocator xeCreateMemAllocator;
    pfn_xeMemAllocatorDestroy xeMemAllocatorDestroy;
    pfn_xeSharedMemAlloc xeSharedMemAlloc;
    pfn_xeMemAlloc xeMemAlloc;
    pfn_xeHostMemAlloc xeHostMemAlloc;
    pfn_xeMemFree xeMemFree;
    pfn_xeMemGetProperty xeMemGetProperty;
    pfn_xeMemGetAddressRange xeMemGetAddressRange;
    pfn_xeIpcGetMemHandle xeIpcGetMemHandle;
    pfn_xeIpcOpenMemHandle xeIpcOpenMemHandle;
    pfn_xeIpcCloseMemHandle xeIpcCloseMemHandle;
    pfn_xeDeviceCreateModule xeDeviceCreateModule;
    pfn_xeModuleDestroy xeModuleDestroy;
    pfn_xeModuleBuildLogDestroy xeModuleBuildLogDestroy;
    pfn_xeModuleBuildLogGetString xeModuleBuildLogGetString;
    pfn_xeModuleGetNativeBinary xeModuleGetNativeBinary;
    pfn_xeModuleCreateFunction xeModuleCreateFunction;
    pfn_xeFunctionDestroy xeFunctionDestroy;
    pfn_xeModuleGetFunctionPointer xeModuleGetFunctionPointer;
    pfn_xeFunctionSetGroupSize xeFunctionSetGroupSize;
    pfn_xeFunctionSuggestGroupSize xeFunctionSuggestGroupSize;
    pfn_xeFunctionSetArgumentValue xeFunctionSetArgumentValue;
    pfn_xeFunctionSetAttribute xeFunctionSetAttribute;
    pfn_xeFunctionGetAttribute xeFunctionGetAttribute;
    pfn_xeCommandListEncodeDispatchFunction xeCommandListEncodeDispatchFunction;
    pfn_xeCommandGraphEncodeDispatchFunction xeCommandGraphEncodeDispatchFunction;
    pfn_xeCommandListEncodeDispatchFunctionIndirect xeCommandListEncodeDispatchFunctionIndirect;
    pfn_xeCommandGraphEncodeDispatchFunctionIndirect xeCommandGraphEncodeDispatchFunctionIndirect;
    pfn_xeCommandListEncodeDispatchHostFunction xeCommandListEncodeDispatchHostFunction;
    pfn_xeCommandGraphEncodeDispatchHostFunction xeCommandGraphEncodeDispatchHostFunction;
    pfn_xeDeviceMakeMemoryResident xeDeviceMakeMemoryResident;
    pfn_xeDeviceEvictMemory xeDeviceEvictMemory;
    pfn_xeDeviceMakeImageResident xeDeviceMakeImageResident;
    pfn_xeDeviceEvictImage xeDeviceEvictImage;
    pfn_xeDeviceCreateSampler xeDeviceCreateSampler;
    pfn_xeSamplerDestroy xeSamplerDestroy;
    pfn_xeDeviceCreateSemaphore xeDeviceCreateSemaphore;
    pfn_xeSemaphoreDestroy xeSemaphoreDestroy;
    pfn_xeCommandListEncodeSemaphoreSignal xeCommandListEncodeSemaphoreSignal;
    pfn_xeCommandListEncodeSemaphoreWait xeCommandListEncodeSemaphoreWait;
    pfn_xeSemaphoreQueryValue xeSemaphoreQueryValue;
    pfn_xeSemaphoreReset xeSemaphoreReset;
} xe_dispatch_table_t;

inline bool load_xe(void *handle, void *(*funcAddressGetter)(void *handle, const char *funcName), xe_dispatch_table_t *outTable){
    if((0 == funcAddressGetter) || (0 == outTable)){
        return false;
    }
    outTable->xeCommandListEncodeExecutionBarrier = (pfn_xeCommandListEncodeExecutionBarrier)funcAddressGetter(handle, "xeCommandListEncodeExecutionBarrier");
#if XE_ENABLE_OCL_INTEROP
    outTable->xeDeviceRegisterCLMemory = (pfn_xeDeviceRegisterCLMemory)funcAddressGetter(handle, "xeDeviceRegisterCLMemory");
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    outTable->xeDeviceRegisterCLProgram = (pfn_xeDeviceRegisterCLProgram)funcAddressGetter(handle, "xeDeviceRegisterCLProgram");
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    outTable->xeDeviceRegisterCLCommandQueue = (pfn_xeDeviceRegisterCLCommandQueue)funcAddressGetter(handle, "xeDeviceRegisterCLCommandQueue");
#endif // XE_ENABLE_OCL_INTEROP
    outTable->xeDeviceCreateCommandGraph = (pfn_xeDeviceCreateCommandGraph)funcAddressGetter(handle, "xeDeviceCreateCommandGraph");
    outTable->xeCommandGraphDestroy = (pfn_xeCommandGraphDestroy)funcAddressGetter(handle, "xeCommandGraphDestroy");
    outTable->xeCommandGraphClose = (pfn_xeCommandGraphClose)funcAddressGetter(handle, "xeCommandGraphClose");
    outTable->xeCommandGraphReset = (pfn_xeCommandGraphReset)funcAddressGetter(handle, "xeCommandGraphReset");
    outTable->xeDeviceCreateCommandList = (pfn_xeDeviceCreateCommandList)funcAddressGetter(handle, "xeDeviceCreateCommandList");
    outTable->xeDeviceCopyCommandList = (pfn_xeDeviceCopyCommandList)funcAddressGetter(handle, "xeDeviceCopyCommandList");
    outTable->xeCommandListDestroy = (pfn_xeCommandListDestroy)funcAddressGetter(handle, "xeCommandListDestroy");
    outTable->xeCommandListClose = (pfn_xeCommandListClose)funcAddressGetter(handle, "xeCommandListClose");
    outTable->xeCommandListReset = (pfn_xeCommandListReset)funcAddressGetter(handle, "xeCommandListReset");
    outTable->xeCommandListSetParameter = (pfn_xeCommandListSetParameter)funcAddressGetter(handle, "xeCommandListSetParameter");
    outTable->xeCommandListGetParameter = (pfn_xeCommandListGetParameter)funcAddressGetter(handle, "xeCommandListGetParameter");
    outTable->xeCommandListResetParameters = (pfn_xeCommandListResetParameters)funcAddressGetter(handle, "xeCommandListResetParameters");
    outTable->xeCommandListEncodeCommandLists = (pfn_xeCommandListEncodeCommandLists)funcAddressGetter(handle, "xeCommandListEncodeCommandLists");
    outTable->xeCommandListEncodeCommands = (pfn_xeCommandListEncodeCommands)funcAddressGetter(handle, "xeCommandListEncodeCommands");
    outTable->xeDeviceCreateCommandQueue = (pfn_xeDeviceCreateCommandQueue)funcAddressGetter(handle, "xeDeviceCreateCommandQueue");
    outTable->xeCommandQueueDestroy = (pfn_xeCommandQueueDestroy)funcAddressGetter(handle, "xeCommandQueueDestroy");
    outTable->xeCommandQueueEnqueueCommandLists = (pfn_xeCommandQueueEnqueueCommandLists)funcAddressGetter(handle, "xeCommandQueueEnqueueCommandLists");
    outTable->xeCommandQueueSynchronize = (pfn_xeCommandQueueSynchronize)funcAddressGetter(handle, "xeCommandQueueSynchronize");
    outTable->xeCommandListEncodeMemoryCopy = (pfn_xeCommandListEncodeMemoryCopy)funcAddressGetter(handle, "xeCommandListEncodeMemoryCopy");
    outTable->xeCommandListEncodeMemorySet = (pfn_xeCommandListEncodeMemorySet)funcAddressGetter(handle, "xeCommandListEncodeMemorySet");
    outTable->xeCommandListEncodeImageCopy = (pfn_xeCommandListEncodeImageCopy)funcAddressGetter(handle, "xeCommandListEncodeImageCopy");
    outTable->xeCommandListEncodeImageCopyRegion = (pfn_xeCommandListEncodeImageCopyRegion)funcAddressGetter(handle, "xeCommandListEncodeImageCopyRegion");
    outTable->xeCommandListEncodeImageCopyToMemory = (pfn_xeCommandListEncodeImageCopyToMemory)funcAddressGetter(handle, "xeCommandListEncodeImageCopyToMemory");
    outTable->xeCommandListEncodeImageCopyFromMemory = (pfn_xeCommandListEncodeImageCopyFromMemory)funcAddressGetter(handle, "xeCommandListEncodeImageCopyFromMemory");
    outTable->xeCommandListEncodeMemoryPrefetch = (pfn_xeCommandListEncodeMemoryPrefetch)funcAddressGetter(handle, "xeCommandListEncodeMemoryPrefetch");
    outTable->xeCommandListEncodeMemAdvise = (pfn_xeCommandListEncodeMemAdvise)funcAddressGetter(handle, "xeCommandListEncodeMemAdvise");
    outTable->xeDriverGetDeviceCount = (pfn_xeDriverGetDeviceCount)funcAddressGetter(handle, "xeDriverGetDeviceCount");
    outTable->xeDriverGetDeviceUniqueIds = (pfn_xeDriverGetDeviceUniqueIds)funcAddressGetter(handle, "xeDriverGetDeviceUniqueIds");
    outTable->xeDriverGetDevice = (pfn_xeDriverGetDevice)funcAddressGetter(handle, "xeDriverGetDevice");
    outTable->xeDeviceGetSubDevice = (pfn_xeDeviceGetSubDevice)funcAddressGetter(handle, "xeDeviceGetSubDevice");
    outTable->xeDeviceGetApiVersion = (pfn_xeDeviceGetApiVersion)funcAddressGetter(handle, "xeDeviceGetApiVersion");
    outTable->xeDeviceGetProperties = (pfn_xeDeviceGetProperties)funcAddressGetter(handle, "xeDeviceGetProperties");
    outTable->xeDeviceGetComputeProperties = (pfn_xeDeviceGetComputeProperties)funcAddressGetter(handle, "xeDeviceGetComputeProperties");
    outTable->xeDeviceGetMemoryProperties = (pfn_xeDeviceGetMemoryProperties)funcAddressGetter(handle, "xeDeviceGetMemoryProperties");
    outTable->xeDeviceGetLinkProperties = (pfn_xeDeviceGetLinkProperties)funcAddressGetter(handle, "xeDeviceGetLinkProperties");
    outTable->xeDeviceCanAccessPeer = (pfn_xeDeviceCanAccessPeer)funcAddressGetter(handle, "xeDeviceCanAccessPeer");
    outTable->xeDeviceSetIntermediateCacheConfig = (pfn_xeDeviceSetIntermediateCacheConfig)funcAddressGetter(handle, "xeDeviceSetIntermediateCacheConfig");
    outTable->xeDeviceSetLastLevelCacheConfig = (pfn_xeDeviceSetLastLevelCacheConfig)funcAddressGetter(handle, "xeDeviceSetLastLevelCacheConfig");
    outTable->xeDriverInit = (pfn_xeDriverInit)funcAddressGetter(handle, "xeDriverInit");
    outTable->xeDriverGetVersion = (pfn_xeDriverGetVersion)funcAddressGetter(handle, "xeDriverGetVersion");
    outTable->xeDeviceCreateEvent = (pfn_xeDeviceCreateEvent)funcAddressGetter(handle, "xeDeviceCreateEvent");
    outTable->xeDevicePlaceEvent = (pfn_xeDevicePlaceEvent)funcAddressGetter(handle, "xeDevicePlaceEvent");
    outTable->xeEventDestroy = (pfn_xeEventDestroy)funcAddressGetter(handle, "xeEventDestroy");
    outTable->xeCommandListEncodeSignalEvent = (pfn_xeCommandListEncodeSignalEvent)funcAddressGetter(handle, "xeCommandListEncodeSignalEvent");
    outTable->xeCommandListEncodeWaitOnEvent = (pfn_xeCommandListEncodeWaitOnEvent)funcAddressGetter(handle, "xeCommandListEncodeWaitOnEvent");
    outTable->xeCommandListEncodeSignalMultipleEvents = (pfn_xeCommandListEncodeSignalMultipleEvents)funcAddressGetter(handle, "xeCommandListEncodeSignalMultipleEvents");
    outTable->xeCommandListEncodeWaitOnMultipleEvents = (pfn_xeCommandListEncodeWaitOnMultipleEvents)funcAddressGetter(handle, "xeCommandListEncodeWaitOnMultipleEvents");
    outTable->xeHostSignalEvent = (pfn_xeHostSignalEvent)funcAddressGetter(handle, "xeHostSignalEvent");
    outTable->xeHostWaitOnEvent = (pfn_xeHostWaitOnEvent)funcAddressGetter(handle, "xeHostWaitOnEvent");
    outTable->xeHostSignalMultipleEvents = (pfn_xeHostSignalMultipleEvents)funcAddressGetter(handle, "xeHostSignalMultipleEvents");
    outTable->xeHostWaitOnMultipleEvents = (pfn_xeHostWaitOnMultipleEvents)funcAddressGetter(handle, "xeHostWaitOnMultipleEvents");
    outTable->xeEventQueryStatus = (pfn_xeEventQueryStatus)funcAddressGetter(handle, "xeEventQueryStatus");
    outTable->xeEventQueryElapsedTime = (pfn_xeEventQueryElapsedTime)funcAddressGetter(handle, "xeEventQueryElapsedTime");
    outTable->xeEventQueryMetricsData = (pfn_xeEventQueryMetricsData)funcAddressGetter(handle, "xeEventQueryMetricsData");
    outTable->xeCommandListEncodeEventReset = (pfn_xeCommandListEncodeEventReset)funcAddressGetter(handle, "xeCommandListEncodeEventReset");
    outTable->xeEventReset = (pfn_xeEventReset)funcAddressGetter(handle, "xeEventReset");
    outTable->xeCommandQueueCreateFence = (pfn_xeCommandQueueCreateFence)funcAddressGetter(handle, "xeCommandQueueCreateFence");
    outTable->xeFenceDestroy = (pfn_xeFenceDestroy)funcAddressGetter(handle, "xeFenceDestroy");
    outTable->xeHostWaitOnFence = (pfn_xeHostWaitOnFence)funcAddressGetter(handle, "xeHostWaitOnFence");
    outTable->xeHostWaitOnMultipleFences = (pfn_xeHostWaitOnMultipleFences)funcAddressGetter(handle, "xeHostWaitOnMultipleFences");
    outTable->xeFenceQueryStatus = (pfn_xeFenceQueryStatus)funcAddressGetter(handle, "xeFenceQueryStatus");
    outTable->xeFenceQueryElapsedTime = (pfn_xeFenceQueryElapsedTime)funcAddressGetter(handle, "xeFenceQueryElapsedTime");
    outTable->xeFenceReset = (pfn_xeFenceReset)funcAddressGetter(handle, "xeFenceReset");
    outTable->xeDeviceCreateImage = (pfn_xeDeviceCreateImage)funcAddressGetter(handle, "xeDeviceCreateImage");
    outTable->xeImageDestroy = (pfn_xeImageDestroy)funcAddressGetter(handle, "xeImageDestroy");
    outTable->xeCreateMemAllocator = (pfn_xeCreateMemAllocator)funcAddressGetter(handle, "xeCreateMemAllocator");
    outTable->xeMemAllocatorDestroy = (pfn_xeMemAllocatorDestroy)funcAddressGetter(handle, "xeMemAllocatorDestroy");
    outTable->xeSharedMemAlloc = (pfn_xeSharedMemAlloc)funcAddressGetter(handle, "xeSharedMemAlloc");
    outTable->xeMemAlloc = (pfn_xeMemAlloc)funcAddressGetter(handle, "xeMemAlloc");
    outTable->xeHostMemAlloc = (pfn_xeHostMemAlloc)funcAddressGetter(handle, "xeHostMemAlloc");
    outTable->xeMemFree = (pfn_xeMemFree)funcAddressGetter(handle, "xeMemFree");
    outTable->xeMemGetProperty = (pfn_xeMemGetProperty)funcAddressGetter(handle, "xeMemGetProperty");
    outTable->xeMemGetAddressRange = (pfn_xeMemGetAddressRange)funcAddressGetter(handle, "xeMemGetAddressRange");
    outTable->xeIpcGetMemHandle = (pfn_xeIpcGetMemHandle)funcAddressGetter(handle, "xeIpcGetMemHandle");
    outTable->xeIpcOpenMemHandle = (pfn_xeIpcOpenMemHandle)funcAddressGetter(handle, "xeIpcOpenMemHandle");
    outTable->xeIpcCloseMemHandle = (pfn_xeIpcCloseMemHandle)funcAddressGetter(handle, "xeIpcCloseMemHandle");
    outTable->xeDeviceCreateModule = (pfn_xeDeviceCreateModule)funcAddressGetter(handle, "xeDeviceCreateModule");
    outTable->xeModuleDestroy = (pfn_xeModuleDestroy)funcAddressGetter(handle, "xeModuleDestroy");
    outTable->xeModuleBuildLogDestroy = (pfn_xeModuleBuildLogDestroy)funcAddressGetter(handle, "xeModuleBuildLogDestroy");
    outTable->xeModuleBuildLogGetString = (pfn_xeModuleBuildLogGetString)funcAddressGetter(handle, "xeModuleBuildLogGetString");
    outTable->xeModuleGetNativeBinary = (pfn_xeModuleGetNativeBinary)funcAddressGetter(handle, "xeModuleGetNativeBinary");
    outTable->xeModuleCreateFunction = (pfn_xeModuleCreateFunction)funcAddressGetter(handle, "xeModuleCreateFunction");
    outTable->xeFunctionDestroy = (pfn_xeFunctionDestroy)funcAddressGetter(handle, "xeFunctionDestroy");
    outTable->xeModuleGetFunctionPointer = (pfn_xeModuleGetFunctionPointer)funcAddressGetter(handle, "xeModuleGetFunctionPointer");
    outTable->xeFunctionSetGroupSize = (pfn_xeFunctionSetGroupSize)funcAddressGetter(handle, "xeFunctionSetGroupSize");
    outTable->xeFunctionSuggestGroupSize = (pfn_xeFunctionSuggestGroupSize)funcAddressGetter(handle, "xeFunctionSuggestGroupSize");
    outTable->xeFunctionSetArgumentValue = (pfn_xeFunctionSetArgumentValue)funcAddressGetter(handle, "xeFunctionSetArgumentValue");
    outTable->xeFunctionSetAttribute = (pfn_xeFunctionSetAttribute)funcAddressGetter(handle, "xeFunctionSetAttribute");
    outTable->xeFunctionGetAttribute = (pfn_xeFunctionGetAttribute)funcAddressGetter(handle, "xeFunctionGetAttribute");
    outTable->xeCommandListEncodeDispatchFunction = (pfn_xeCommandListEncodeDispatchFunction)funcAddressGetter(handle, "xeCommandListEncodeDispatchFunction");
    outTable->xeCommandGraphEncodeDispatchFunction = (pfn_xeCommandGraphEncodeDispatchFunction)funcAddressGetter(handle, "xeCommandGraphEncodeDispatchFunction");
    outTable->xeCommandListEncodeDispatchFunctionIndirect = (pfn_xeCommandListEncodeDispatchFunctionIndirect)funcAddressGetter(handle, "xeCommandListEncodeDispatchFunctionIndirect");
    outTable->xeCommandGraphEncodeDispatchFunctionIndirect = (pfn_xeCommandGraphEncodeDispatchFunctionIndirect)funcAddressGetter(handle, "xeCommandGraphEncodeDispatchFunctionIndirect");
    outTable->xeCommandListEncodeDispatchHostFunction = (pfn_xeCommandListEncodeDispatchHostFunction)funcAddressGetter(handle, "xeCommandListEncodeDispatchHostFunction");
    outTable->xeCommandGraphEncodeDispatchHostFunction = (pfn_xeCommandGraphEncodeDispatchHostFunction)funcAddressGetter(handle, "xeCommandGraphEncodeDispatchHostFunction");
    outTable->xeDeviceMakeMemoryResident = (pfn_xeDeviceMakeMemoryResident)funcAddressGetter(handle, "xeDeviceMakeMemoryResident");
    outTable->xeDeviceEvictMemory = (pfn_xeDeviceEvictMemory)funcAddressGetter(handle, "xeDeviceEvictMemory");
    outTable->xeDeviceMakeImageResident = (pfn_xeDeviceMakeImageResident)funcAddressGetter(handle, "xeDeviceMakeImageResident");
    outTable->xeDeviceEvictImage = (pfn_xeDeviceEvictImage)funcAddressGetter(handle, "xeDeviceEvictImage");
    outTable->xeDeviceCreateSampler = (pfn_xeDeviceCreateSampler)funcAddressGetter(handle, "xeDeviceCreateSampler");
    outTable->xeSamplerDestroy = (pfn_xeSamplerDestroy)funcAddressGetter(handle, "xeSamplerDestroy");
    outTable->xeDeviceCreateSemaphore = (pfn_xeDeviceCreateSemaphore)funcAddressGetter(handle, "xeDeviceCreateSemaphore");
    outTable->xeSemaphoreDestroy = (pfn_xeSemaphoreDestroy)funcAddressGetter(handle, "xeSemaphoreDestroy");
    outTable->xeCommandListEncodeSemaphoreSignal = (pfn_xeCommandListEncodeSemaphoreSignal)funcAddressGetter(handle, "xeCommandListEncodeSemaphoreSignal");
    outTable->xeCommandListEncodeSemaphoreWait = (pfn_xeCommandListEncodeSemaphoreWait)funcAddressGetter(handle, "xeCommandListEncodeSemaphoreWait");
    outTable->xeSemaphoreQueryValue = (pfn_xeSemaphoreQueryValue)funcAddressGetter(handle, "xeSemaphoreQueryValue");
    outTable->xeSemaphoreReset = (pfn_xeSemaphoreReset)funcAddressGetter(handle, "xeSemaphoreReset");
    if(0 == outTable->xeCommandListEncodeExecutionBarrier){
        return false;
    }
#if XE_ENABLE_OCL_INTEROP
    if(0 == outTable->xeDeviceRegisterCLMemory){
        return false;
    }
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    if(0 == outTable->xeDeviceRegisterCLProgram){
        return false;
    }
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    if(0 == outTable->xeDeviceRegisterCLCommandQueue){
        return false;
    }
#endif // XE_ENABLE_OCL_INTEROP
    if(0 == outTable->xeDeviceCreateCommandGraph){
        return false;
    }
    if(0 == outTable->xeCommandGraphDestroy){
        return false;
    }
    if(0 == outTable->xeCommandGraphClose){
        return false;
    }
    if(0 == outTable->xeCommandGraphReset){
        return false;
    }
    if(0 == outTable->xeDeviceCreateCommandList){
        return false;
    }
    if(0 == outTable->xeDeviceCopyCommandList){
        return false;
    }
    if(0 == outTable->xeCommandListDestroy){
        return false;
    }
    if(0 == outTable->xeCommandListClose){
        return false;
    }
    if(0 == outTable->xeCommandListReset){
        return false;
    }
    if(0 == outTable->xeCommandListSetParameter){
        return false;
    }
    if(0 == outTable->xeCommandListGetParameter){
        return false;
    }
    if(0 == outTable->xeCommandListResetParameters){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeCommandLists){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeCommands){
        return false;
    }
    if(0 == outTable->xeDeviceCreateCommandQueue){
        return false;
    }
    if(0 == outTable->xeCommandQueueDestroy){
        return false;
    }
    if(0 == outTable->xeCommandQueueEnqueueCommandLists){
        return false;
    }
    if(0 == outTable->xeCommandQueueSynchronize){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeMemoryCopy){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeMemorySet){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeImageCopy){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeImageCopyRegion){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeImageCopyToMemory){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeImageCopyFromMemory){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeMemoryPrefetch){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeMemAdvise){
        return false;
    }
    if(0 == outTable->xeDriverGetDeviceCount){
        return false;
    }
    if(0 == outTable->xeDriverGetDeviceUniqueIds){
        return false;
    }
    if(0 == outTable->xeDriverGetDevice){
        return false;
    }
    if(0 == outTable->xeDeviceGetSubDevice){
        return false;
    }
    if(0 == outTable->xeDeviceGetApiVersion){
        return false;
    }
    if(0 == outTable->xeDeviceGetProperties){
        return false;
    }
    if(0 == outTable->xeDeviceGetComputeProperties){
        return false;
    }
    if(0 == outTable->xeDeviceGetMemoryProperties){
        return false;
    }
    if(0 == outTable->xeDeviceGetLinkProperties){
        return false;
    }
    if(0 == outTable->xeDeviceCanAccessPeer){
        return false;
    }
    if(0 == outTable->xeDeviceSetIntermediateCacheConfig){
        return false;
    }
    if(0 == outTable->xeDeviceSetLastLevelCacheConfig){
        return false;
    }
    if(0 == outTable->xeDriverInit){
        return false;
    }
    if(0 == outTable->xeDriverGetVersion){
        return false;
    }
    if(0 == outTable->xeDeviceCreateEvent){
        return false;
    }
    if(0 == outTable->xeDevicePlaceEvent){
        return false;
    }
    if(0 == outTable->xeEventDestroy){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeSignalEvent){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeWaitOnEvent){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeSignalMultipleEvents){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeWaitOnMultipleEvents){
        return false;
    }
    if(0 == outTable->xeHostSignalEvent){
        return false;
    }
    if(0 == outTable->xeHostWaitOnEvent){
        return false;
    }
    if(0 == outTable->xeHostSignalMultipleEvents){
        return false;
    }
    if(0 == outTable->xeHostWaitOnMultipleEvents){
        return false;
    }
    if(0 == outTable->xeEventQueryStatus){
        return false;
    }
    if(0 == outTable->xeEventQueryElapsedTime){
        return false;
    }
    if(0 == outTable->xeEventQueryMetricsData){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeEventReset){
        return false;
    }
    if(0 == outTable->xeEventReset){
        return false;
    }
    if(0 == outTable->xeCommandQueueCreateFence){
        return false;
    }
    if(0 == outTable->xeFenceDestroy){
        return false;
    }
    if(0 == outTable->xeHostWaitOnFence){
        return false;
    }
    if(0 == outTable->xeHostWaitOnMultipleFences){
        return false;
    }
    if(0 == outTable->xeFenceQueryStatus){
        return false;
    }
    if(0 == outTable->xeFenceQueryElapsedTime){
        return false;
    }
    if(0 == outTable->xeFenceReset){
        return false;
    }
    if(0 == outTable->xeDeviceCreateImage){
        return false;
    }
    if(0 == outTable->xeImageDestroy){
        return false;
    }
    if(0 == outTable->xeCreateMemAllocator){
        return false;
    }
    if(0 == outTable->xeMemAllocatorDestroy){
        return false;
    }
    if(0 == outTable->xeSharedMemAlloc){
        return false;
    }
    if(0 == outTable->xeMemAlloc){
        return false;
    }
    if(0 == outTable->xeHostMemAlloc){
        return false;
    }
    if(0 == outTable->xeMemFree){
        return false;
    }
    if(0 == outTable->xeMemGetProperty){
        return false;
    }
    if(0 == outTable->xeMemGetAddressRange){
        return false;
    }
    if(0 == outTable->xeIpcGetMemHandle){
        return false;
    }
    if(0 == outTable->xeIpcOpenMemHandle){
        return false;
    }
    if(0 == outTable->xeIpcCloseMemHandle){
        return false;
    }
    if(0 == outTable->xeDeviceCreateModule){
        return false;
    }
    if(0 == outTable->xeModuleDestroy){
        return false;
    }
    if(0 == outTable->xeModuleBuildLogDestroy){
        return false;
    }
    if(0 == outTable->xeModuleBuildLogGetString){
        return false;
    }
    if(0 == outTable->xeModuleGetNativeBinary){
        return false;
    }
    if(0 == outTable->xeModuleCreateFunction){
        return false;
    }
    if(0 == outTable->xeFunctionDestroy){
        return false;
    }
    if(0 == outTable->xeModuleGetFunctionPointer){
        return false;
    }
    if(0 == outTable->xeFunctionSetGroupSize){
        return false;
    }
    if(0 == outTable->xeFunctionSuggestGroupSize){
        return false;
    }
    if(0 == outTable->xeFunctionSetArgumentValue){
        return false;
    }
    if(0 == outTable->xeFunctionSetAttribute){
        return false;
    }
    if(0 == outTable->xeFunctionGetAttribute){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeDispatchFunction){
        return false;
    }
    if(0 == outTable->xeCommandGraphEncodeDispatchFunction){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeDispatchFunctionIndirect){
        return false;
    }
    if(0 == outTable->xeCommandGraphEncodeDispatchFunctionIndirect){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeDispatchHostFunction){
        return false;
    }
    if(0 == outTable->xeCommandGraphEncodeDispatchHostFunction){
        return false;
    }
    if(0 == outTable->xeDeviceMakeMemoryResident){
        return false;
    }
    if(0 == outTable->xeDeviceEvictMemory){
        return false;
    }
    if(0 == outTable->xeDeviceMakeImageResident){
        return false;
    }
    if(0 == outTable->xeDeviceEvictImage){
        return false;
    }
    if(0 == outTable->xeDeviceCreateSemaphore){
        return false;
    }
    if(0 == outTable->xeSemaphoreDestroy){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeSemaphoreSignal){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeSemaphoreWait){
        return false;
    }
    if(0 == outTable->xeSemaphoreQueryValue){
        return false;
    }
    if(0 == outTable->xeSemaphoreReset){
        return false;
    }
    return true;
}
#endif // _XE_LOADER_H
