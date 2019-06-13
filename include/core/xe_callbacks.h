/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
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
*
* @file xe_callbacks.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core
* @endcond
*
******************************************************************************/
#ifndef _XE_CALLBACKS_H
#define _XE_CALLBACKS_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeInit 
typedef struct _xe_init_params_t
{
    xe_init_flag_t flags;
} xe_init_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeInit 
typedef void (__xecall *xe_pfnInitCb_t)(
    xe_init_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _xe_global_callbacks_t
{
    xe_pfnInitCb_t                                                  pfnInitCb;
} xe_global_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGet 
typedef struct _xe_device_get_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    uint32_t* pCount;
    xe_device_handle_t* phDevices;
} xe_device_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGet 
typedef void (__xecall *xe_pfnDeviceGetCb_t)(
    xe_device_get_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetSubDevices 
typedef struct _xe_device_get_sub_devices_params_t
{
    xe_device_handle_t hDevice;
    uint32_t* pCount;
    xe_device_handle_t* phSubdevices;
} xe_device_get_sub_devices_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetSubDevices 
typedef void (__xecall *xe_pfnDeviceGetSubDevicesCb_t)(
    xe_device_get_sub_devices_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetP2PProperties 
typedef struct _xe_device_get_p2_p_properties_params_t
{
    xe_device_handle_t hDevice;
    xe_device_handle_t hPeerDevice;
    xe_device_p2p_properties_t* pP2PProperties;
} xe_device_get_p2_p_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetP2PProperties 
typedef void (__xecall *xe_pfnDeviceGetP2PPropertiesCb_t)(
    xe_device_get_p2_p_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceCanAccessPeer 
typedef struct _xe_device_can_access_peer_params_t
{
    xe_device_handle_t hDevice;
    xe_device_handle_t hPeerDevice;
    xe_bool_t* value;
} xe_device_can_access_peer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceCanAccessPeer 
typedef void (__xecall *xe_pfnDeviceCanAccessPeerCb_t)(
    xe_device_can_access_peer_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceSetIntermediateCacheConfig 
typedef struct _xe_device_set_intermediate_cache_config_params_t
{
    xe_device_handle_t hDevice;
    xe_cache_config_t CacheConfig;
} xe_device_set_intermediate_cache_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceSetIntermediateCacheConfig 
typedef void (__xecall *xe_pfnDeviceSetIntermediateCacheConfigCb_t)(
    xe_device_set_intermediate_cache_config_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceSetLastLevelCacheConfig 
typedef struct _xe_device_set_last_level_cache_config_params_t
{
    xe_device_handle_t hDevice;
    xe_cache_config_t CacheConfig;
} xe_device_set_last_level_cache_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceSetLastLevelCacheConfig 
typedef void (__xecall *xe_pfnDeviceSetLastLevelCacheConfigCb_t)(
    xe_device_set_last_level_cache_config_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceSystemBarrier 
typedef struct _xe_device_system_barrier_params_t
{
    xe_device_handle_t hDevice;
} xe_device_system_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceSystemBarrier 
typedef void (__xecall *xe_pfnDeviceSystemBarrierCb_t)(
    xe_device_system_barrier_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceRegisterCLMemory 
#if XE_ENABLE_OCL_INTEROP
typedef struct _xe_device_register_cl_memory_params_t
{
    xe_device_handle_t hDevice;
    cl_context context;
    cl_mem mem;
    void** ptr;
} xe_device_register_cl_memory_params_t;
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceRegisterCLMemory 
#if XE_ENABLE_OCL_INTEROP
typedef void (__xecall *xe_pfnDeviceRegisterCLMemoryCb_t)(
    xe_device_register_cl_memory_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceRegisterCLProgram 
#if XE_ENABLE_OCL_INTEROP
typedef struct _xe_device_register_cl_program_params_t
{
    xe_device_handle_t hDevice;
    cl_context context;
    cl_program program;
    xe_module_handle_t* phModule;
} xe_device_register_cl_program_params_t;
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceRegisterCLProgram 
#if XE_ENABLE_OCL_INTEROP
typedef void (__xecall *xe_pfnDeviceRegisterCLProgramCb_t)(
    xe_device_register_cl_program_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceRegisterCLCommandQueue 
#if XE_ENABLE_OCL_INTEROP
typedef struct _xe_device_register_cl_command_queue_params_t
{
    xe_device_handle_t hDevice;
    cl_context context;
    cl_command_queue command_queue;
    xe_command_queue_handle_t* phCommandQueue;
} xe_device_register_cl_command_queue_params_t;
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceRegisterCLCommandQueue 
#if XE_ENABLE_OCL_INTEROP
typedef void (__xecall *xe_pfnDeviceRegisterCLCommandQueueCb_t)(
    xe_device_register_cl_command_queue_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceMakeMemoryResident 
typedef struct _xe_device_make_memory_resident_params_t
{
    xe_device_handle_t hDevice;
    void* ptr;
    size_t size;
} xe_device_make_memory_resident_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceMakeMemoryResident 
typedef void (__xecall *xe_pfnDeviceMakeMemoryResidentCb_t)(
    xe_device_make_memory_resident_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceEvictMemory 
typedef struct _xe_device_evict_memory_params_t
{
    xe_device_handle_t hDevice;
    void* ptr;
    size_t size;
} xe_device_evict_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceEvictMemory 
typedef void (__xecall *xe_pfnDeviceEvictMemoryCb_t)(
    xe_device_evict_memory_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceMakeImageResident 
typedef struct _xe_device_make_image_resident_params_t
{
    xe_device_handle_t hDevice;
    xe_image_handle_t hImage;
} xe_device_make_image_resident_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceMakeImageResident 
typedef void (__xecall *xe_pfnDeviceMakeImageResidentCb_t)(
    xe_device_make_image_resident_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceEvictImage 
typedef struct _xe_device_evict_image_params_t
{
    xe_device_handle_t hDevice;
    xe_image_handle_t hImage;
} xe_device_evict_image_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceEvictImage 
typedef void (__xecall *xe_pfnDeviceEvictImageCb_t)(
    xe_device_evict_image_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device callback functions pointers
typedef struct _xe_device_callbacks_t
{
    xe_pfnDeviceGetCb_t                                             pfnGetCb;
    xe_pfnDeviceGetSubDevicesCb_t                                   pfnGetSubDevicesCb;
    xe_pfnDeviceGetP2PPropertiesCb_t                                pfnGetP2PPropertiesCb;
    xe_pfnDeviceCanAccessPeerCb_t                                   pfnCanAccessPeerCb;
    xe_pfnDeviceSetIntermediateCacheConfigCb_t                      pfnSetIntermediateCacheConfigCb;
    xe_pfnDeviceSetLastLevelCacheConfigCb_t                         pfnSetLastLevelCacheConfigCb;
    xe_pfnDeviceSystemBarrierCb_t                                   pfnSystemBarrierCb;
#if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLMemoryCb_t                                pfnRegisterCLMemoryCb;
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLProgramCb_t                               pfnRegisterCLProgramCb;
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLCommandQueueCb_t                          pfnRegisterCLCommandQueueCb;
#endif // XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceMakeMemoryResidentCb_t                              pfnMakeMemoryResidentCb;
    xe_pfnDeviceEvictMemoryCb_t                                     pfnEvictMemoryCb;
    xe_pfnDeviceMakeImageResidentCb_t                               pfnMakeImageResidentCb;
    xe_pfnDeviceEvictImageCb_t                                      pfnEvictImageCb;
} xe_device_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGet 
typedef struct _xe_device_group_get_params_t
{
    uint32_t* pCount;
    xe_device_group_handle_t* phDeviceGroups;
} xe_device_group_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGet 
typedef void (__xecall *xe_pfnDeviceGroupGetCb_t)(
    xe_device_group_get_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetDriverVersion 
typedef struct _xe_device_group_get_driver_version_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    uint32_t* version;
} xe_device_group_get_driver_version_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetDriverVersion 
typedef void (__xecall *xe_pfnDeviceGroupGetDriverVersionCb_t)(
    xe_device_group_get_driver_version_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetApiVersion 
typedef struct _xe_device_group_get_api_version_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_api_version_t* version;
} xe_device_group_get_api_version_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetApiVersion 
typedef void (__xecall *xe_pfnDeviceGroupGetApiVersionCb_t)(
    xe_device_group_get_api_version_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetDeviceProperties 
typedef struct _xe_device_group_get_device_properties_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_device_properties_t* pDeviceProperties;
} xe_device_group_get_device_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetDeviceProperties 
typedef void (__xecall *xe_pfnDeviceGroupGetDevicePropertiesCb_t)(
    xe_device_group_get_device_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetComputeProperties 
typedef struct _xe_device_group_get_compute_properties_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_device_compute_properties_t* pComputeProperties;
} xe_device_group_get_compute_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetComputeProperties 
typedef void (__xecall *xe_pfnDeviceGroupGetComputePropertiesCb_t)(
    xe_device_group_get_compute_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetMemoryProperties 
typedef struct _xe_device_group_get_memory_properties_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    uint32_t* pCount;
    xe_device_memory_properties_t* pMemProperties;
} xe_device_group_get_memory_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetMemoryProperties 
typedef void (__xecall *xe_pfnDeviceGroupGetMemoryPropertiesCb_t)(
    xe_device_group_get_memory_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetMemoryAccessProperties 
typedef struct _xe_device_group_get_memory_access_properties_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_device_memory_access_properties_t* pMemAccessProperties;
} xe_device_group_get_memory_access_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetMemoryAccessProperties 
typedef void (__xecall *xe_pfnDeviceGroupGetMemoryAccessPropertiesCb_t)(
    xe_device_group_get_memory_access_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetCacheProperties 
typedef struct _xe_device_group_get_cache_properties_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_device_cache_properties_t* pCacheProperties;
} xe_device_group_get_cache_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetCacheProperties 
typedef void (__xecall *xe_pfnDeviceGroupGetCachePropertiesCb_t)(
    xe_device_group_get_cache_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetImageProperties 
typedef struct _xe_device_group_get_image_properties_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_device_image_properties_t* pImageProperties;
} xe_device_group_get_image_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetImageProperties 
typedef void (__xecall *xe_pfnDeviceGroupGetImagePropertiesCb_t)(
    xe_device_group_get_image_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupAllocSharedMem 
typedef struct _xe_device_group_alloc_shared_mem_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_device_handle_t hDevice;
    xe_device_mem_alloc_flag_t device_flags;
    uint32_t ordinal;
    xe_host_mem_alloc_flag_t host_flags;
    size_t size;
    size_t alignment;
    void** ptr;
} xe_device_group_alloc_shared_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupAllocSharedMem 
typedef void (__xecall *xe_pfnDeviceGroupAllocSharedMemCb_t)(
    xe_device_group_alloc_shared_mem_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupAllocDeviceMem 
typedef struct _xe_device_group_alloc_device_mem_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_device_handle_t hDevice;
    xe_device_mem_alloc_flag_t flags;
    uint32_t ordinal;
    size_t size;
    size_t alignment;
    void** ptr;
} xe_device_group_alloc_device_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupAllocDeviceMem 
typedef void (__xecall *xe_pfnDeviceGroupAllocDeviceMemCb_t)(
    xe_device_group_alloc_device_mem_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupAllocHostMem 
typedef struct _xe_device_group_alloc_host_mem_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_host_mem_alloc_flag_t flags;
    size_t size;
    size_t alignment;
    void** ptr;
} xe_device_group_alloc_host_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupAllocHostMem 
typedef void (__xecall *xe_pfnDeviceGroupAllocHostMemCb_t)(
    xe_device_group_alloc_host_mem_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupFreeMem 
typedef struct _xe_device_group_free_mem_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    void* ptr;
} xe_device_group_free_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupFreeMem 
typedef void (__xecall *xe_pfnDeviceGroupFreeMemCb_t)(
    xe_device_group_free_mem_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetMemProperties 
typedef struct _xe_device_group_get_mem_properties_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    const void* ptr;
    xe_memory_allocation_properties_t* pMemProperties;
    xe_device_handle_t* phDevice;
} xe_device_group_get_mem_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetMemProperties 
typedef void (__xecall *xe_pfnDeviceGroupGetMemPropertiesCb_t)(
    xe_device_group_get_mem_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetMemAddressRange 
typedef struct _xe_device_group_get_mem_address_range_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    const void* ptr;
    void** pBase;
    size_t* pSize;
} xe_device_group_get_mem_address_range_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetMemAddressRange 
typedef void (__xecall *xe_pfnDeviceGroupGetMemAddressRangeCb_t)(
    xe_device_group_get_mem_address_range_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupGetMemIpcHandle 
typedef struct _xe_device_group_get_mem_ipc_handle_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    const void* ptr;
    xe_ipc_mem_handle_t* pIpcHandle;
} xe_device_group_get_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupGetMemIpcHandle 
typedef void (__xecall *xe_pfnDeviceGroupGetMemIpcHandleCb_t)(
    xe_device_group_get_mem_ipc_handle_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupOpenMemIpcHandle 
typedef struct _xe_device_group_open_mem_ipc_handle_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    xe_device_handle_t hDevice;
    xe_ipc_mem_handle_t handle;
    xe_ipc_memory_flag_t flags;
    void** ptr;
} xe_device_group_open_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupOpenMemIpcHandle 
typedef void (__xecall *xe_pfnDeviceGroupOpenMemIpcHandleCb_t)(
    xe_device_group_open_mem_ipc_handle_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGroupCloseMemIpcHandle 
typedef struct _xe_device_group_close_mem_ipc_handle_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    const void* ptr;
} xe_device_group_close_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGroupCloseMemIpcHandle 
typedef void (__xecall *xe_pfnDeviceGroupCloseMemIpcHandleCb_t)(
    xe_device_group_close_mem_ipc_handle_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of DeviceGroup callback functions pointers
typedef struct _xe_device_group_callbacks_t
{
    xe_pfnDeviceGroupGetCb_t                                        pfnGetCb;
    xe_pfnDeviceGroupGetDriverVersionCb_t                           pfnGetDriverVersionCb;
    xe_pfnDeviceGroupGetApiVersionCb_t                              pfnGetApiVersionCb;
    xe_pfnDeviceGroupGetDevicePropertiesCb_t                        pfnGetDevicePropertiesCb;
    xe_pfnDeviceGroupGetComputePropertiesCb_t                       pfnGetComputePropertiesCb;
    xe_pfnDeviceGroupGetMemoryPropertiesCb_t                        pfnGetMemoryPropertiesCb;
    xe_pfnDeviceGroupGetMemoryAccessPropertiesCb_t                  pfnGetMemoryAccessPropertiesCb;
    xe_pfnDeviceGroupGetCachePropertiesCb_t                         pfnGetCachePropertiesCb;
    xe_pfnDeviceGroupGetImagePropertiesCb_t                         pfnGetImagePropertiesCb;
    xe_pfnDeviceGroupAllocSharedMemCb_t                             pfnAllocSharedMemCb;
    xe_pfnDeviceGroupAllocDeviceMemCb_t                             pfnAllocDeviceMemCb;
    xe_pfnDeviceGroupAllocHostMemCb_t                               pfnAllocHostMemCb;
    xe_pfnDeviceGroupFreeMemCb_t                                    pfnFreeMemCb;
    xe_pfnDeviceGroupGetMemPropertiesCb_t                           pfnGetMemPropertiesCb;
    xe_pfnDeviceGroupGetMemAddressRangeCb_t                         pfnGetMemAddressRangeCb;
    xe_pfnDeviceGroupGetMemIpcHandleCb_t                            pfnGetMemIpcHandleCb;
    xe_pfnDeviceGroupOpenMemIpcHandleCb_t                           pfnOpenMemIpcHandleCb;
    xe_pfnDeviceGroupCloseMemIpcHandleCb_t                          pfnCloseMemIpcHandleCb;
} xe_device_group_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandQueueCreate 
typedef struct _xe_command_queue_create_params_t
{
    xe_device_handle_t hDevice;
    const xe_command_queue_desc_t* desc;
    xe_command_queue_handle_t* phCommandQueue;
} xe_command_queue_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandQueueCreate 
typedef void (__xecall *xe_pfnCommandQueueCreateCb_t)(
    xe_command_queue_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandQueueDestroy 
typedef struct _xe_command_queue_destroy_params_t
{
    xe_command_queue_handle_t hCommandQueue;
} xe_command_queue_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandQueueDestroy 
typedef void (__xecall *xe_pfnCommandQueueDestroyCb_t)(
    xe_command_queue_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandQueueExecuteCommandLists 
typedef struct _xe_command_queue_execute_command_lists_params_t
{
    xe_command_queue_handle_t hCommandQueue;
    uint32_t numCommandLists;
    xe_command_list_handle_t* phCommandLists;
    xe_fence_handle_t hFence;
} xe_command_queue_execute_command_lists_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandQueueExecuteCommandLists 
typedef void (__xecall *xe_pfnCommandQueueExecuteCommandListsCb_t)(
    xe_command_queue_execute_command_lists_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandQueueSynchronize 
typedef struct _xe_command_queue_synchronize_params_t
{
    xe_command_queue_handle_t hCommandQueue;
    uint32_t timeout;
} xe_command_queue_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandQueueSynchronize 
typedef void (__xecall *xe_pfnCommandQueueSynchronizeCb_t)(
    xe_command_queue_synchronize_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandQueue callback functions pointers
typedef struct _xe_command_queue_callbacks_t
{
    xe_pfnCommandQueueCreateCb_t                                    pfnCreateCb;
    xe_pfnCommandQueueDestroyCb_t                                   pfnDestroyCb;
    xe_pfnCommandQueueExecuteCommandListsCb_t                       pfnExecuteCommandListsCb;
    xe_pfnCommandQueueSynchronizeCb_t                               pfnSynchronizeCb;
} xe_command_queue_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListCreate 
typedef struct _xe_command_list_create_params_t
{
    xe_device_handle_t hDevice;
    const xe_command_list_desc_t* desc;
    xe_command_list_handle_t* phCommandList;
} xe_command_list_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListCreate 
typedef void (__xecall *xe_pfnCommandListCreateCb_t)(
    xe_command_list_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListCreateImmediate 
typedef struct _xe_command_list_create_immediate_params_t
{
    xe_device_handle_t hDevice;
    const xe_command_queue_desc_t* altdesc;
    xe_command_list_handle_t* phCommandList;
} xe_command_list_create_immediate_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListCreateImmediate 
typedef void (__xecall *xe_pfnCommandListCreateImmediateCb_t)(
    xe_command_list_create_immediate_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListDestroy 
typedef struct _xe_command_list_destroy_params_t
{
    xe_command_list_handle_t hCommandList;
} xe_command_list_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListDestroy 
typedef void (__xecall *xe_pfnCommandListDestroyCb_t)(
    xe_command_list_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListClose 
typedef struct _xe_command_list_close_params_t
{
    xe_command_list_handle_t hCommandList;
} xe_command_list_close_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListClose 
typedef void (__xecall *xe_pfnCommandListCloseCb_t)(
    xe_command_list_close_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListReset 
typedef struct _xe_command_list_reset_params_t
{
    xe_command_list_handle_t hCommandList;
} xe_command_list_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListReset 
typedef void (__xecall *xe_pfnCommandListResetCb_t)(
    xe_command_list_reset_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListSetParameter 
typedef struct _xe_command_list_set_parameter_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_command_list_parameter_t parameter;
    uint32_t value;
} xe_command_list_set_parameter_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListSetParameter 
typedef void (__xecall *xe_pfnCommandListSetParameterCb_t)(
    xe_command_list_set_parameter_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListGetParameter 
typedef struct _xe_command_list_get_parameter_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_command_list_parameter_t parameter;
    uint32_t* value;
} xe_command_list_get_parameter_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListGetParameter 
typedef void (__xecall *xe_pfnCommandListGetParameterCb_t)(
    xe_command_list_get_parameter_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListResetParameters 
typedef struct _xe_command_list_reset_parameters_params_t
{
    xe_command_list_handle_t hCommandList;
} xe_command_list_reset_parameters_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListResetParameters 
typedef void (__xecall *xe_pfnCommandListResetParametersCb_t)(
    xe_command_list_reset_parameters_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListReserveSpace 
typedef struct _xe_command_list_reserve_space_params_t
{
    xe_command_list_handle_t hCommandList;
    size_t size;
    void** ptr;
} xe_command_list_reserve_space_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListReserveSpace 
typedef void (__xecall *xe_pfnCommandListReserveSpaceCb_t)(
    xe_command_list_reserve_space_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendBarrier 
typedef struct _xe_command_list_append_barrier_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_event_handle_t hSignalEvent;
    uint32_t numWaitEvents;
    xe_event_handle_t* phWaitEvents;
} xe_command_list_append_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendBarrier 
typedef void (__xecall *xe_pfnCommandListAppendBarrierCb_t)(
    xe_command_list_append_barrier_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemoryRangesBarrier 
typedef struct _xe_command_list_append_memory_ranges_barrier_params_t
{
    xe_command_list_handle_t hCommandList;
    uint32_t numRanges;
    const size_t* pRangeSizes;
    const void** pRanges;
    xe_event_handle_t hSignalEvent;
    uint32_t numWaitEvents;
    xe_event_handle_t* phWaitEvents;
} xe_command_list_append_memory_ranges_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemoryRangesBarrier 
typedef void (__xecall *xe_pfnCommandListAppendMemoryRangesBarrierCb_t)(
    xe_command_list_append_memory_ranges_barrier_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemoryCopy 
typedef struct _xe_command_list_append_memory_copy_params_t
{
    xe_command_list_handle_t hCommandList;
    void* dstptr;
    const void* srcptr;
    size_t size;
    xe_event_handle_t hEvent;
} xe_command_list_append_memory_copy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemoryCopy 
typedef void (__xecall *xe_pfnCommandListAppendMemoryCopyCb_t)(
    xe_command_list_append_memory_copy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemorySet 
typedef struct _xe_command_list_append_memory_set_params_t
{
    xe_command_list_handle_t hCommandList;
    void* ptr;
    int value;
    size_t size;
    xe_event_handle_t hEvent;
} xe_command_list_append_memory_set_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemorySet 
typedef void (__xecall *xe_pfnCommandListAppendMemorySetCb_t)(
    xe_command_list_append_memory_set_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemoryCopyRegion 
typedef struct _xe_command_list_append_memory_copy_region_params_t
{
    xe_command_list_handle_t hCommandList;
    void* dstptr;
    xe_copy_region_t* dstRegion;
    uint32_t dstPitch;
    const void* srcptr;
    xe_copy_region_t* srcRegion;
    uint32_t srcPitch;
    xe_event_handle_t hEvent;
} xe_command_list_append_memory_copy_region_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemoryCopyRegion 
typedef void (__xecall *xe_pfnCommandListAppendMemoryCopyRegionCb_t)(
    xe_command_list_append_memory_copy_region_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendImageCopy 
typedef struct _xe_command_list_append_image_copy_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_image_handle_t hDstImage;
    xe_image_handle_t hSrcImage;
    xe_event_handle_t hEvent;
} xe_command_list_append_image_copy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendImageCopy 
typedef void (__xecall *xe_pfnCommandListAppendImageCopyCb_t)(
    xe_command_list_append_image_copy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendImageCopyRegion 
typedef struct _xe_command_list_append_image_copy_region_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_image_handle_t hDstImage;
    xe_image_handle_t hSrcImage;
    xe_image_region_t* pDstRegion;
    xe_image_region_t* pSrcRegion;
    xe_event_handle_t hEvent;
} xe_command_list_append_image_copy_region_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendImageCopyRegion 
typedef void (__xecall *xe_pfnCommandListAppendImageCopyRegionCb_t)(
    xe_command_list_append_image_copy_region_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendImageCopyToMemory 
typedef struct _xe_command_list_append_image_copy_to_memory_params_t
{
    xe_command_list_handle_t hCommandList;
    void* dstptr;
    xe_image_handle_t hSrcImage;
    xe_image_region_t* pSrcRegion;
    xe_event_handle_t hEvent;
} xe_command_list_append_image_copy_to_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendImageCopyToMemory 
typedef void (__xecall *xe_pfnCommandListAppendImageCopyToMemoryCb_t)(
    xe_command_list_append_image_copy_to_memory_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendImageCopyFromMemory 
typedef struct _xe_command_list_append_image_copy_from_memory_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_image_handle_t hDstImage;
    const void* srcptr;
    xe_image_region_t* pDstRegion;
    xe_event_handle_t hEvent;
} xe_command_list_append_image_copy_from_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendImageCopyFromMemory 
typedef void (__xecall *xe_pfnCommandListAppendImageCopyFromMemoryCb_t)(
    xe_command_list_append_image_copy_from_memory_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemoryPrefetch 
typedef struct _xe_command_list_append_memory_prefetch_params_t
{
    xe_command_list_handle_t hCommandList;
    const void* ptr;
    size_t size;
} xe_command_list_append_memory_prefetch_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemoryPrefetch 
typedef void (__xecall *xe_pfnCommandListAppendMemoryPrefetchCb_t)(
    xe_command_list_append_memory_prefetch_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemAdvise 
typedef struct _xe_command_list_append_mem_advise_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_device_handle_t hDevice;
    const void* ptr;
    size_t size;
    xe_memory_advice_t advice;
} xe_command_list_append_mem_advise_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemAdvise 
typedef void (__xecall *xe_pfnCommandListAppendMemAdviseCb_t)(
    xe_command_list_append_mem_advise_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendSignalEvent 
typedef struct _xe_command_list_append_signal_event_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_event_handle_t hEvent;
} xe_command_list_append_signal_event_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendSignalEvent 
typedef void (__xecall *xe_pfnCommandListAppendSignalEventCb_t)(
    xe_command_list_append_signal_event_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendWaitOnEvents 
typedef struct _xe_command_list_append_wait_on_events_params_t
{
    xe_command_list_handle_t hCommandList;
    uint32_t numEvents;
    xe_event_handle_t* phEvents;
} xe_command_list_append_wait_on_events_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendWaitOnEvents 
typedef void (__xecall *xe_pfnCommandListAppendWaitOnEventsCb_t)(
    xe_command_list_append_wait_on_events_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendEventReset 
typedef struct _xe_command_list_append_event_reset_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_event_handle_t hEvent;
} xe_command_list_append_event_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendEventReset 
typedef void (__xecall *xe_pfnCommandListAppendEventResetCb_t)(
    xe_command_list_append_event_reset_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendLaunchFunction 
typedef struct _xe_command_list_append_launch_function_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_function_handle_t hFunction;
    const xe_thread_group_dimensions_t* pLaunchFuncArgs;
    xe_event_handle_t hSignalEvent;
    uint32_t numWaitEvents;
    xe_event_handle_t* phWaitEvents;
} xe_command_list_append_launch_function_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendLaunchFunction 
typedef void (__xecall *xe_pfnCommandListAppendLaunchFunctionCb_t)(
    xe_command_list_append_launch_function_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendLaunchFunctionIndirect 
typedef struct _xe_command_list_append_launch_function_indirect_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_function_handle_t hFunction;
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer;
    xe_event_handle_t hSignalEvent;
    uint32_t numWaitEvents;
    xe_event_handle_t* phWaitEvents;
} xe_command_list_append_launch_function_indirect_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendLaunchFunctionIndirect 
typedef void (__xecall *xe_pfnCommandListAppendLaunchFunctionIndirectCb_t)(
    xe_command_list_append_launch_function_indirect_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendLaunchMultipleFunctionsIndirect 
typedef struct _xe_command_list_append_launch_multiple_functions_indirect_params_t
{
    xe_command_list_handle_t hCommandList;
    uint32_t numFunctions;
    xe_function_handle_t* phFunctions;
    const uint32_t* pNumLaunchArguments;
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer;
    xe_event_handle_t hSignalEvent;
    uint32_t numWaitEvents;
    xe_event_handle_t* phWaitEvents;
} xe_command_list_append_launch_multiple_functions_indirect_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendLaunchMultipleFunctionsIndirect 
typedef void (__xecall *xe_pfnCommandListAppendLaunchMultipleFunctionsIndirectCb_t)(
    xe_command_list_append_launch_multiple_functions_indirect_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendLaunchHostFunction 
typedef struct _xe_command_list_append_launch_host_function_params_t
{
    xe_command_list_handle_t hCommandList;
    xe_host_pfn_t pfnHostFunc;
    void* pUserData;
    xe_event_handle_t hSignalEvent;
    uint32_t numWaitEvents;
    xe_event_handle_t* phWaitEvents;
} xe_command_list_append_launch_host_function_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendLaunchHostFunction 
typedef void (__xecall *xe_pfnCommandListAppendLaunchHostFunctionCb_t)(
    xe_command_list_append_launch_host_function_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList callback functions pointers
typedef struct _xe_command_list_callbacks_t
{
    xe_pfnCommandListCreateCb_t                                     pfnCreateCb;
    xe_pfnCommandListCreateImmediateCb_t                            pfnCreateImmediateCb;
    xe_pfnCommandListDestroyCb_t                                    pfnDestroyCb;
    xe_pfnCommandListCloseCb_t                                      pfnCloseCb;
    xe_pfnCommandListResetCb_t                                      pfnResetCb;
    xe_pfnCommandListSetParameterCb_t                               pfnSetParameterCb;
    xe_pfnCommandListGetParameterCb_t                               pfnGetParameterCb;
    xe_pfnCommandListResetParametersCb_t                            pfnResetParametersCb;
    xe_pfnCommandListReserveSpaceCb_t                               pfnReserveSpaceCb;
    xe_pfnCommandListAppendBarrierCb_t                              pfnAppendBarrierCb;
    xe_pfnCommandListAppendMemoryRangesBarrierCb_t                  pfnAppendMemoryRangesBarrierCb;
    xe_pfnCommandListAppendMemoryCopyCb_t                           pfnAppendMemoryCopyCb;
    xe_pfnCommandListAppendMemorySetCb_t                            pfnAppendMemorySetCb;
    xe_pfnCommandListAppendMemoryCopyRegionCb_t                     pfnAppendMemoryCopyRegionCb;
    xe_pfnCommandListAppendImageCopyCb_t                            pfnAppendImageCopyCb;
    xe_pfnCommandListAppendImageCopyRegionCb_t                      pfnAppendImageCopyRegionCb;
    xe_pfnCommandListAppendImageCopyToMemoryCb_t                    pfnAppendImageCopyToMemoryCb;
    xe_pfnCommandListAppendImageCopyFromMemoryCb_t                  pfnAppendImageCopyFromMemoryCb;
    xe_pfnCommandListAppendMemoryPrefetchCb_t                       pfnAppendMemoryPrefetchCb;
    xe_pfnCommandListAppendMemAdviseCb_t                            pfnAppendMemAdviseCb;
    xe_pfnCommandListAppendSignalEventCb_t                          pfnAppendSignalEventCb;
    xe_pfnCommandListAppendWaitOnEventsCb_t                         pfnAppendWaitOnEventsCb;
    xe_pfnCommandListAppendEventResetCb_t                           pfnAppendEventResetCb;
    xe_pfnCommandListAppendLaunchFunctionCb_t                       pfnAppendLaunchFunctionCb;
    xe_pfnCommandListAppendLaunchFunctionIndirectCb_t               pfnAppendLaunchFunctionIndirectCb;
    xe_pfnCommandListAppendLaunchMultipleFunctionsIndirectCb_t      pfnAppendLaunchMultipleFunctionsIndirectCb;
    xe_pfnCommandListAppendLaunchHostFunctionCb_t                   pfnAppendLaunchHostFunctionCb;
} xe_command_list_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceCreate 
typedef struct _xe_fence_create_params_t
{
    xe_command_queue_handle_t hCommandQueue;
    const xe_fence_desc_t* desc;
    xe_fence_handle_t* phFence;
} xe_fence_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceCreate 
typedef void (__xecall *xe_pfnFenceCreateCb_t)(
    xe_fence_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceDestroy 
typedef struct _xe_fence_destroy_params_t
{
    xe_fence_handle_t hFence;
} xe_fence_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceDestroy 
typedef void (__xecall *xe_pfnFenceDestroyCb_t)(
    xe_fence_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceHostSynchronize 
typedef struct _xe_fence_host_synchronize_params_t
{
    xe_fence_handle_t hFence;
    uint32_t timeout;
} xe_fence_host_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceHostSynchronize 
typedef void (__xecall *xe_pfnFenceHostSynchronizeCb_t)(
    xe_fence_host_synchronize_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceQueryStatus 
typedef struct _xe_fence_query_status_params_t
{
    xe_fence_handle_t hFence;
} xe_fence_query_status_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceQueryStatus 
typedef void (__xecall *xe_pfnFenceQueryStatusCb_t)(
    xe_fence_query_status_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceReset 
typedef struct _xe_fence_reset_params_t
{
    xe_fence_handle_t hFence;
} xe_fence_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceReset 
typedef void (__xecall *xe_pfnFenceResetCb_t)(
    xe_fence_reset_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Fence callback functions pointers
typedef struct _xe_fence_callbacks_t
{
    xe_pfnFenceCreateCb_t                                           pfnCreateCb;
    xe_pfnFenceDestroyCb_t                                          pfnDestroyCb;
    xe_pfnFenceHostSynchronizeCb_t                                  pfnHostSynchronizeCb;
    xe_pfnFenceQueryStatusCb_t                                      pfnQueryStatusCb;
    xe_pfnFenceResetCb_t                                            pfnResetCb;
} xe_fence_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolCreate 
typedef struct _xe_event_pool_create_params_t
{
    xe_device_group_handle_t hDeviceGroup;
    const xe_event_pool_desc_t* desc;
    uint32_t numDevices;
    xe_device_handle_t* phDevices;
    xe_event_pool_handle_t* phEventPool;
} xe_event_pool_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolCreate 
typedef void (__xecall *xe_pfnEventPoolCreateCb_t)(
    xe_event_pool_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolDestroy 
typedef struct _xe_event_pool_destroy_params_t
{
    xe_event_pool_handle_t hEventPool;
} xe_event_pool_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolDestroy 
typedef void (__xecall *xe_pfnEventPoolDestroyCb_t)(
    xe_event_pool_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolGetIpcHandle 
typedef struct _xe_event_pool_get_ipc_handle_params_t
{
    xe_event_pool_handle_t hEventPool;
    xe_ipc_event_pool_handle_t* phIpc;
} xe_event_pool_get_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolGetIpcHandle 
typedef void (__xecall *xe_pfnEventPoolGetIpcHandleCb_t)(
    xe_event_pool_get_ipc_handle_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolOpenIpcHandle 
typedef struct _xe_event_pool_open_ipc_handle_params_t
{
    xe_device_handle_t hDevice;
    xe_ipc_event_pool_handle_t hIpc;
    xe_event_pool_handle_t* phEventPool;
} xe_event_pool_open_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolOpenIpcHandle 
typedef void (__xecall *xe_pfnEventPoolOpenIpcHandleCb_t)(
    xe_event_pool_open_ipc_handle_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolCloseIpcHandle 
typedef struct _xe_event_pool_close_ipc_handle_params_t
{
    xe_event_pool_handle_t hEventPool;
} xe_event_pool_close_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolCloseIpcHandle 
typedef void (__xecall *xe_pfnEventPoolCloseIpcHandleCb_t)(
    xe_event_pool_close_ipc_handle_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of EventPool callback functions pointers
typedef struct _xe_event_pool_callbacks_t
{
    xe_pfnEventPoolCreateCb_t                                       pfnCreateCb;
    xe_pfnEventPoolDestroyCb_t                                      pfnDestroyCb;
    xe_pfnEventPoolGetIpcHandleCb_t                                 pfnGetIpcHandleCb;
    xe_pfnEventPoolOpenIpcHandleCb_t                                pfnOpenIpcHandleCb;
    xe_pfnEventPoolCloseIpcHandleCb_t                               pfnCloseIpcHandleCb;
} xe_event_pool_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventCreate 
typedef struct _xe_event_create_params_t
{
    xe_event_pool_handle_t hEventPool;
    const xe_event_desc_t* desc;
    xe_event_handle_t* phEvent;
} xe_event_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventCreate 
typedef void (__xecall *xe_pfnEventCreateCb_t)(
    xe_event_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventDestroy 
typedef struct _xe_event_destroy_params_t
{
    xe_event_handle_t hEvent;
} xe_event_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventDestroy 
typedef void (__xecall *xe_pfnEventDestroyCb_t)(
    xe_event_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventHostSignal 
typedef struct _xe_event_host_signal_params_t
{
    xe_event_handle_t hEvent;
} xe_event_host_signal_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventHostSignal 
typedef void (__xecall *xe_pfnEventHostSignalCb_t)(
    xe_event_host_signal_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventHostSynchronize 
typedef struct _xe_event_host_synchronize_params_t
{
    xe_event_handle_t hEvent;
    uint32_t timeout;
} xe_event_host_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventHostSynchronize 
typedef void (__xecall *xe_pfnEventHostSynchronizeCb_t)(
    xe_event_host_synchronize_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventQueryStatus 
typedef struct _xe_event_query_status_params_t
{
    xe_event_handle_t hEvent;
} xe_event_query_status_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventQueryStatus 
typedef void (__xecall *xe_pfnEventQueryStatusCb_t)(
    xe_event_query_status_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventReset 
typedef struct _xe_event_reset_params_t
{
    xe_event_handle_t hEvent;
} xe_event_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventReset 
typedef void (__xecall *xe_pfnEventResetCb_t)(
    xe_event_reset_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Event callback functions pointers
typedef struct _xe_event_callbacks_t
{
    xe_pfnEventCreateCb_t                                           pfnCreateCb;
    xe_pfnEventDestroyCb_t                                          pfnDestroyCb;
    xe_pfnEventHostSignalCb_t                                       pfnHostSignalCb;
    xe_pfnEventHostSynchronizeCb_t                                  pfnHostSynchronizeCb;
    xe_pfnEventQueryStatusCb_t                                      pfnQueryStatusCb;
    xe_pfnEventResetCb_t                                            pfnResetCb;
} xe_event_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeImageGetProperties 
typedef struct _xe_image_get_properties_params_t
{
    xe_device_handle_t hDevice;
    const xe_image_desc_t* desc;
    xe_image_properties_t* pImageProperties;
} xe_image_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeImageGetProperties 
typedef void (__xecall *xe_pfnImageGetPropertiesCb_t)(
    xe_image_get_properties_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeImageCreate 
typedef struct _xe_image_create_params_t
{
    xe_device_handle_t hDevice;
    const xe_image_desc_t* desc;
    xe_image_handle_t* phImage;
} xe_image_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeImageCreate 
typedef void (__xecall *xe_pfnImageCreateCb_t)(
    xe_image_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeImageDestroy 
typedef struct _xe_image_destroy_params_t
{
    xe_image_handle_t hImage;
} xe_image_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeImageDestroy 
typedef void (__xecall *xe_pfnImageDestroyCb_t)(
    xe_image_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Image callback functions pointers
typedef struct _xe_image_callbacks_t
{
    xe_pfnImageGetPropertiesCb_t                                    pfnGetPropertiesCb;
    xe_pfnImageCreateCb_t                                           pfnCreateCb;
    xe_pfnImageDestroyCb_t                                          pfnDestroyCb;
} xe_image_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleCreate 
typedef struct _xe_module_create_params_t
{
    xe_device_handle_t hDevice;
    const xe_module_desc_t* desc;
    xe_module_handle_t* phModule;
    xe_module_build_log_handle_t* phBuildLog;
} xe_module_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleCreate 
typedef void (__xecall *xe_pfnModuleCreateCb_t)(
    xe_module_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleDestroy 
typedef struct _xe_module_destroy_params_t
{
    xe_module_handle_t hModule;
} xe_module_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleDestroy 
typedef void (__xecall *xe_pfnModuleDestroyCb_t)(
    xe_module_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleGetNativeBinary 
typedef struct _xe_module_get_native_binary_params_t
{
    xe_module_handle_t hModule;
    size_t* pSize;
    uint8_t* pModuleNativeBinary;
} xe_module_get_native_binary_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleGetNativeBinary 
typedef void (__xecall *xe_pfnModuleGetNativeBinaryCb_t)(
    xe_module_get_native_binary_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleGetGlobalPointer 
typedef struct _xe_module_get_global_pointer_params_t
{
    xe_module_handle_t hModule;
    const char* pGlobalName;
    void** pPtr;
} xe_module_get_global_pointer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleGetGlobalPointer 
typedef void (__xecall *xe_pfnModuleGetGlobalPointerCb_t)(
    xe_module_get_global_pointer_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleGetFunctionPointer 
typedef struct _xe_module_get_function_pointer_params_t
{
    xe_module_handle_t hModule;
    const char* pFunctionName;
    void** pfnFunction;
} xe_module_get_function_pointer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleGetFunctionPointer 
typedef void (__xecall *xe_pfnModuleGetFunctionPointerCb_t)(
    xe_module_get_function_pointer_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module callback functions pointers
typedef struct _xe_module_callbacks_t
{
    xe_pfnModuleCreateCb_t                                          pfnCreateCb;
    xe_pfnModuleDestroyCb_t                                         pfnDestroyCb;
    xe_pfnModuleGetNativeBinaryCb_t                                 pfnGetNativeBinaryCb;
    xe_pfnModuleGetGlobalPointerCb_t                                pfnGetGlobalPointerCb;
    xe_pfnModuleGetFunctionPointerCb_t                              pfnGetFunctionPointerCb;
} xe_module_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleBuildLogDestroy 
typedef struct _xe_module_build_log_destroy_params_t
{
    xe_module_build_log_handle_t hModuleBuildLog;
} xe_module_build_log_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleBuildLogDestroy 
typedef void (__xecall *xe_pfnModuleBuildLogDestroyCb_t)(
    xe_module_build_log_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleBuildLogGetString 
typedef struct _xe_module_build_log_get_string_params_t
{
    xe_module_build_log_handle_t hModuleBuildLog;
    size_t* pSize;
    char* pBuildLog;
} xe_module_build_log_get_string_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleBuildLogGetString 
typedef void (__xecall *xe_pfnModuleBuildLogGetStringCb_t)(
    xe_module_build_log_get_string_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ModuleBuildLog callback functions pointers
typedef struct _xe_module_build_log_callbacks_t
{
    xe_pfnModuleBuildLogDestroyCb_t                                 pfnDestroyCb;
    xe_pfnModuleBuildLogGetStringCb_t                               pfnGetStringCb;
} xe_module_build_log_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionCreate 
typedef struct _xe_function_create_params_t
{
    xe_module_handle_t hModule;
    const xe_function_desc_t* desc;
    xe_function_handle_t* phFunction;
} xe_function_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionCreate 
typedef void (__xecall *xe_pfnFunctionCreateCb_t)(
    xe_function_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionDestroy 
typedef struct _xe_function_destroy_params_t
{
    xe_function_handle_t hFunction;
} xe_function_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionDestroy 
typedef void (__xecall *xe_pfnFunctionDestroyCb_t)(
    xe_function_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionSetGroupSize 
typedef struct _xe_function_set_group_size_params_t
{
    xe_function_handle_t hFunction;
    uint32_t groupSizeX;
    uint32_t groupSizeY;
    uint32_t groupSizeZ;
} xe_function_set_group_size_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionSetGroupSize 
typedef void (__xecall *xe_pfnFunctionSetGroupSizeCb_t)(
    xe_function_set_group_size_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionSuggestGroupSize 
typedef struct _xe_function_suggest_group_size_params_t
{
    xe_function_handle_t hFunction;
    uint32_t globalSizeX;
    uint32_t globalSizeY;
    uint32_t globalSizeZ;
    uint32_t* groupSizeX;
    uint32_t* groupSizeY;
    uint32_t* groupSizeZ;
} xe_function_suggest_group_size_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionSuggestGroupSize 
typedef void (__xecall *xe_pfnFunctionSuggestGroupSizeCb_t)(
    xe_function_suggest_group_size_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionSetArgumentValue 
typedef struct _xe_function_set_argument_value_params_t
{
    xe_function_handle_t hFunction;
    uint32_t argIndex;
    size_t argSize;
    const void* pArgValue;
} xe_function_set_argument_value_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionSetArgumentValue 
typedef void (__xecall *xe_pfnFunctionSetArgumentValueCb_t)(
    xe_function_set_argument_value_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionSetAttribute 
typedef struct _xe_function_set_attribute_params_t
{
    xe_function_handle_t hFunction;
    xe_function_set_attribute_t attr;
    uint32_t value;
} xe_function_set_attribute_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionSetAttribute 
typedef void (__xecall *xe_pfnFunctionSetAttributeCb_t)(
    xe_function_set_attribute_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionGetAttribute 
typedef struct _xe_function_get_attribute_params_t
{
    xe_function_handle_t hFunction;
    xe_function_get_attribute_t attr;
    uint32_t* pValue;
} xe_function_get_attribute_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionGetAttribute 
typedef void (__xecall *xe_pfnFunctionGetAttributeCb_t)(
    xe_function_get_attribute_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Function callback functions pointers
typedef struct _xe_function_callbacks_t
{
    xe_pfnFunctionCreateCb_t                                        pfnCreateCb;
    xe_pfnFunctionDestroyCb_t                                       pfnDestroyCb;
    xe_pfnFunctionSetGroupSizeCb_t                                  pfnSetGroupSizeCb;
    xe_pfnFunctionSuggestGroupSizeCb_t                              pfnSuggestGroupSizeCb;
    xe_pfnFunctionSetArgumentValueCb_t                              pfnSetArgumentValueCb;
    xe_pfnFunctionSetAttributeCb_t                                  pfnSetAttributeCb;
    xe_pfnFunctionGetAttributeCb_t                                  pfnGetAttributeCb;
} xe_function_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeSamplerCreate 
typedef struct _xe_sampler_create_params_t
{
    xe_device_handle_t hDevice;
    const xe_sampler_desc_t* desc;
    xe_sampler_handle_t* phSampler;
} xe_sampler_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeSamplerCreate 
typedef void (__xecall *xe_pfnSamplerCreateCb_t)(
    xe_sampler_create_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeSamplerDestroy 
typedef struct _xe_sampler_destroy_params_t
{
    xe_sampler_handle_t hSampler;
} xe_sampler_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeSamplerDestroy 
typedef void (__xecall *xe_pfnSamplerDestroyCb_t)(
    xe_sampler_destroy_params_t* params,
    xe_result_t result,
    void* pGlobalUserData,
    void** ppLocalUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sampler callback functions pointers
typedef struct _xe_sampler_callbacks_t
{
    xe_pfnSamplerCreateCb_t                                         pfnCreateCb;
    xe_pfnSamplerDestroyCb_t                                        pfnDestroyCb;
} xe_sampler_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _xe_callbacks_t
{
    xe_global_callbacks_t               Global;
    xe_device_callbacks_t               Device;
    xe_device_group_callbacks_t         DeviceGroup;
    xe_command_queue_callbacks_t        CommandQueue;
    xe_command_list_callbacks_t         CommandList;
    xe_fence_callbacks_t                Fence;
    xe_event_pool_callbacks_t           EventPool;
    xe_event_callbacks_t                Event;
    xe_image_callbacks_t                Image;
    xe_module_callbacks_t               Module;
    xe_module_build_log_callbacks_t     ModuleBuildLog;
    xe_function_callbacks_t             Function;
    xe_sampler_callbacks_t              Sampler;
} xe_callbacks_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_CALLBACKS_H