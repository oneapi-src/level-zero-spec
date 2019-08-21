/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_callbacks.h
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core
 * @endcond
 *
 */
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_init_params_t
{
    xe_init_flag_t* pflags;
} xe_init_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeInit 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnInitCb_t)(
    xe_init_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _xe_global_callbacks_t
{
    xe_pfnInitCb_t                                                  pfnInitCb;
} xe_global_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_params_t
{
    xe_driver_handle_t* phDriver;
    uint32_t** ppCount;
    xe_device_handle_t** pphDevices;
} xe_device_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetCb_t)(
    xe_device_get_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetSubDevices 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_sub_devices_params_t
{
    xe_device_handle_t* phDevice;
    uint32_t** ppCount;
    xe_device_handle_t** pphSubdevices;
} xe_device_get_sub_devices_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetSubDevices 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetSubDevicesCb_t)(
    xe_device_get_sub_devices_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_properties_params_t
{
    xe_device_handle_t* phDevice;
    xe_device_properties_t** ppDeviceProperties;
} xe_device_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetPropertiesCb_t)(
    xe_device_get_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetComputeProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_compute_properties_params_t
{
    xe_device_handle_t* phDevice;
    xe_device_compute_properties_t** ppComputeProperties;
} xe_device_get_compute_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetComputeProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetComputePropertiesCb_t)(
    xe_device_get_compute_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetMemoryProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_memory_properties_params_t
{
    xe_device_handle_t* phDevice;
    uint32_t** ppCount;
    xe_device_memory_properties_t** ppMemProperties;
} xe_device_get_memory_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetMemoryProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetMemoryPropertiesCb_t)(
    xe_device_get_memory_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetMemoryAccessProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_memory_access_properties_params_t
{
    xe_device_handle_t* phDevice;
    xe_device_memory_access_properties_t** ppMemAccessProperties;
} xe_device_get_memory_access_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetMemoryAccessProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetMemoryAccessPropertiesCb_t)(
    xe_device_get_memory_access_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetCacheProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_cache_properties_params_t
{
    xe_device_handle_t* phDevice;
    xe_device_cache_properties_t** ppCacheProperties;
} xe_device_get_cache_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetCacheProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetCachePropertiesCb_t)(
    xe_device_get_cache_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetImageProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_image_properties_params_t
{
    xe_device_handle_t* phDevice;
    xe_device_image_properties_t** ppImageProperties;
} xe_device_get_image_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetImageProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetImagePropertiesCb_t)(
    xe_device_get_image_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceGetP2PProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_get_p2_p_properties_params_t
{
    xe_device_handle_t* phDevice;
    xe_device_handle_t* phPeerDevice;
    xe_device_p2p_properties_t** ppP2PProperties;
} xe_device_get_p2_p_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceGetP2PProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceGetP2PPropertiesCb_t)(
    xe_device_get_p2_p_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceCanAccessPeer 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_can_access_peer_params_t
{
    xe_device_handle_t* phDevice;
    xe_device_handle_t* phPeerDevice;
    xe_bool_t** pvalue;
} xe_device_can_access_peer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceCanAccessPeer 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceCanAccessPeerCb_t)(
    xe_device_can_access_peer_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceSetIntermediateCacheConfig 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_set_intermediate_cache_config_params_t
{
    xe_device_handle_t* phDevice;
    xe_cache_config_t* pCacheConfig;
} xe_device_set_intermediate_cache_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceSetIntermediateCacheConfig 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceSetIntermediateCacheConfigCb_t)(
    xe_device_set_intermediate_cache_config_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceSetLastLevelCacheConfig 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_set_last_level_cache_config_params_t
{
    xe_device_handle_t* phDevice;
    xe_cache_config_t* pCacheConfig;
} xe_device_set_last_level_cache_config_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceSetLastLevelCacheConfig 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceSetLastLevelCacheConfigCb_t)(
    xe_device_set_last_level_cache_config_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceSystemBarrier 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_system_barrier_params_t
{
    xe_device_handle_t* phDevice;
} xe_device_system_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceSystemBarrier 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceSystemBarrierCb_t)(
    xe_device_system_barrier_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceRegisterCLMemory 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
#if XE_ENABLE_OCL_INTEROP
typedef struct _xe_device_register_cl_memory_params_t
{
    xe_device_handle_t* phDevice;
    cl_context* pcontext;
    cl_mem* pmem;
    void*** pptr;
} xe_device_register_cl_memory_params_t;
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceRegisterCLMemory 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
#if XE_ENABLE_OCL_INTEROP
typedef void (__xecall *xe_pfnDeviceRegisterCLMemoryCb_t)(
    xe_device_register_cl_memory_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceRegisterCLProgram 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
#if XE_ENABLE_OCL_INTEROP
typedef struct _xe_device_register_cl_program_params_t
{
    xe_device_handle_t* phDevice;
    cl_context* pcontext;
    cl_program* pprogram;
    xe_module_handle_t** pphModule;
} xe_device_register_cl_program_params_t;
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceRegisterCLProgram 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
#if XE_ENABLE_OCL_INTEROP
typedef void (__xecall *xe_pfnDeviceRegisterCLProgramCb_t)(
    xe_device_register_cl_program_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceRegisterCLCommandQueue 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
#if XE_ENABLE_OCL_INTEROP
typedef struct _xe_device_register_cl_command_queue_params_t
{
    xe_device_handle_t* phDevice;
    cl_context* pcontext;
    cl_command_queue* pcommand_queue;
    xe_command_queue_handle_t** pphCommandQueue;
} xe_device_register_cl_command_queue_params_t;
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceRegisterCLCommandQueue 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
#if XE_ENABLE_OCL_INTEROP
typedef void (__xecall *xe_pfnDeviceRegisterCLCommandQueueCb_t)(
    xe_device_register_cl_command_queue_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceMakeMemoryResident 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_make_memory_resident_params_t
{
    xe_device_handle_t* phDevice;
    void** pptr;
    size_t* psize;
} xe_device_make_memory_resident_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceMakeMemoryResident 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceMakeMemoryResidentCb_t)(
    xe_device_make_memory_resident_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceEvictMemory 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_evict_memory_params_t
{
    xe_device_handle_t* phDevice;
    void** pptr;
    size_t* psize;
} xe_device_evict_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceEvictMemory 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceEvictMemoryCb_t)(
    xe_device_evict_memory_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceMakeImageResident 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_make_image_resident_params_t
{
    xe_device_handle_t* phDevice;
    xe_image_handle_t* phImage;
} xe_device_make_image_resident_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceMakeImageResident 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceMakeImageResidentCb_t)(
    xe_device_make_image_resident_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDeviceEvictImage 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_device_evict_image_params_t
{
    xe_device_handle_t* phDevice;
    xe_image_handle_t* phImage;
} xe_device_evict_image_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDeviceEvictImage 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDeviceEvictImageCb_t)(
    xe_device_evict_image_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device callback functions pointers
typedef struct _xe_device_callbacks_t
{
    xe_pfnDeviceGetCb_t                                             pfnGetCb;
    xe_pfnDeviceGetSubDevicesCb_t                                   pfnGetSubDevicesCb;
    xe_pfnDeviceGetPropertiesCb_t                                   pfnGetPropertiesCb;
    xe_pfnDeviceGetComputePropertiesCb_t                            pfnGetComputePropertiesCb;
    xe_pfnDeviceGetMemoryPropertiesCb_t                             pfnGetMemoryPropertiesCb;
    xe_pfnDeviceGetMemoryAccessPropertiesCb_t                       pfnGetMemoryAccessPropertiesCb;
    xe_pfnDeviceGetCachePropertiesCb_t                              pfnGetCachePropertiesCb;
    xe_pfnDeviceGetImagePropertiesCb_t                              pfnGetImagePropertiesCb;
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
/// @brief Callback function parameters for xeDriverGet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_get_params_t
{
    uint32_t** ppCount;
    xe_driver_handle_t** pphDrivers;
} xe_driver_get_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverGet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverGetCb_t)(
    xe_driver_get_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverGetDriverVersion 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_get_driver_version_params_t
{
    xe_driver_handle_t* phDriver;
    uint32_t** pversion;
} xe_driver_get_driver_version_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverGetDriverVersion 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverGetDriverVersionCb_t)(
    xe_driver_get_driver_version_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverGetApiVersion 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_get_api_version_params_t
{
    xe_driver_handle_t* phDrivers;
    xe_api_version_t** pversion;
} xe_driver_get_api_version_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverGetApiVersion 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverGetApiVersionCb_t)(
    xe_driver_get_api_version_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverGetIPCProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_get_ipc_properties_params_t
{
    xe_driver_handle_t* phDriver;
    xe_driver_ipc_properties_t** ppIPCProperties;
} xe_driver_get_ipc_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverGetIPCProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverGetIPCPropertiesCb_t)(
    xe_driver_get_ipc_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverAllocSharedMem 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_alloc_shared_mem_params_t
{
    xe_driver_handle_t* phDriver;
    xe_device_handle_t* phDevice;
    xe_device_mem_alloc_flag_t* pdevice_flags;
    uint32_t* pordinal;
    xe_host_mem_alloc_flag_t* phost_flags;
    size_t* psize;
    size_t* palignment;
    void*** ppptr;
} xe_driver_alloc_shared_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverAllocSharedMem 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverAllocSharedMemCb_t)(
    xe_driver_alloc_shared_mem_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverAllocDeviceMem 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_alloc_device_mem_params_t
{
    xe_driver_handle_t* phDriver;
    xe_device_handle_t* phDevice;
    xe_device_mem_alloc_flag_t* pflags;
    uint32_t* pordinal;
    size_t* psize;
    size_t* palignment;
    void*** ppptr;
} xe_driver_alloc_device_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverAllocDeviceMem 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverAllocDeviceMemCb_t)(
    xe_driver_alloc_device_mem_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverAllocHostMem 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_alloc_host_mem_params_t
{
    xe_driver_handle_t* phDriver;
    xe_host_mem_alloc_flag_t* pflags;
    size_t* psize;
    size_t* palignment;
    void*** ppptr;
} xe_driver_alloc_host_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverAllocHostMem 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverAllocHostMemCb_t)(
    xe_driver_alloc_host_mem_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverFreeMem 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_free_mem_params_t
{
    xe_driver_handle_t* phDriver;
    void** pptr;
} xe_driver_free_mem_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverFreeMem 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverFreeMemCb_t)(
    xe_driver_free_mem_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverGetMemProperties 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_get_mem_properties_params_t
{
    xe_driver_handle_t* phDriver;
    const void** pptr;
    xe_memory_allocation_properties_t** ppMemProperties;
    xe_device_handle_t** pphDevice;
} xe_driver_get_mem_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverGetMemProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverGetMemPropertiesCb_t)(
    xe_driver_get_mem_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverGetMemAddressRange 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_get_mem_address_range_params_t
{
    xe_driver_handle_t* phDriver;
    const void** pptr;
    void*** ppBase;
    size_t** ppSize;
} xe_driver_get_mem_address_range_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverGetMemAddressRange 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverGetMemAddressRangeCb_t)(
    xe_driver_get_mem_address_range_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverGetMemIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_get_mem_ipc_handle_params_t
{
    xe_driver_handle_t* phDriver;
    const void** pptr;
    xe_ipc_mem_handle_t** ppIpcHandle;
} xe_driver_get_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverGetMemIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverGetMemIpcHandleCb_t)(
    xe_driver_get_mem_ipc_handle_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverOpenMemIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_open_mem_ipc_handle_params_t
{
    xe_driver_handle_t* phDriver;
    xe_device_handle_t* phDevice;
    xe_ipc_mem_handle_t* phandle;
    xe_ipc_memory_flag_t* pflags;
    void*** ppptr;
} xe_driver_open_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverOpenMemIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverOpenMemIpcHandleCb_t)(
    xe_driver_open_mem_ipc_handle_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeDriverCloseMemIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_driver_close_mem_ipc_handle_params_t
{
    xe_driver_handle_t* phDriver;
    const void** pptr;
} xe_driver_close_mem_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeDriverCloseMemIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnDriverCloseMemIpcHandleCb_t)(
    xe_driver_close_mem_ipc_handle_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Driver callback functions pointers
typedef struct _xe_driver_callbacks_t
{
    xe_pfnDriverGetCb_t                                             pfnGetCb;
    xe_pfnDriverGetDriverVersionCb_t                                pfnGetDriverVersionCb;
    xe_pfnDriverGetApiVersionCb_t                                   pfnGetApiVersionCb;
    xe_pfnDriverGetIPCPropertiesCb_t                                pfnGetIPCPropertiesCb;
    xe_pfnDriverAllocSharedMemCb_t                                  pfnAllocSharedMemCb;
    xe_pfnDriverAllocDeviceMemCb_t                                  pfnAllocDeviceMemCb;
    xe_pfnDriverAllocHostMemCb_t                                    pfnAllocHostMemCb;
    xe_pfnDriverFreeMemCb_t                                         pfnFreeMemCb;
    xe_pfnDriverGetMemPropertiesCb_t                                pfnGetMemPropertiesCb;
    xe_pfnDriverGetMemAddressRangeCb_t                              pfnGetMemAddressRangeCb;
    xe_pfnDriverGetMemIpcHandleCb_t                                 pfnGetMemIpcHandleCb;
    xe_pfnDriverOpenMemIpcHandleCb_t                                pfnOpenMemIpcHandleCb;
    xe_pfnDriverCloseMemIpcHandleCb_t                               pfnCloseMemIpcHandleCb;
} xe_driver_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandQueueCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_queue_create_params_t
{
    xe_device_handle_t* phDevice;
    const xe_command_queue_desc_t** pdesc;
    xe_command_queue_handle_t** pphCommandQueue;
} xe_command_queue_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandQueueCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandQueueCreateCb_t)(
    xe_command_queue_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandQueueDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_queue_destroy_params_t
{
    xe_command_queue_handle_t* phCommandQueue;
} xe_command_queue_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandQueueDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandQueueDestroyCb_t)(
    xe_command_queue_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandQueueExecuteCommandLists 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_queue_execute_command_lists_params_t
{
    xe_command_queue_handle_t* phCommandQueue;
    uint32_t* pnumCommandLists;
    xe_command_list_handle_t** pphCommandLists;
    xe_fence_handle_t* phFence;
} xe_command_queue_execute_command_lists_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandQueueExecuteCommandLists 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandQueueExecuteCommandListsCb_t)(
    xe_command_queue_execute_command_lists_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandQueueSynchronize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_queue_synchronize_params_t
{
    xe_command_queue_handle_t* phCommandQueue;
    uint32_t* ptimeout;
} xe_command_queue_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandQueueSynchronize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandQueueSynchronizeCb_t)(
    xe_command_queue_synchronize_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_create_params_t
{
    xe_device_handle_t* phDevice;
    const xe_command_list_desc_t** pdesc;
    xe_command_list_handle_t** pphCommandList;
} xe_command_list_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListCreateCb_t)(
    xe_command_list_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListCreateImmediate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_create_immediate_params_t
{
    xe_device_handle_t* phDevice;
    const xe_command_queue_desc_t** paltdesc;
    xe_command_list_handle_t** pphCommandList;
} xe_command_list_create_immediate_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListCreateImmediate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListCreateImmediateCb_t)(
    xe_command_list_create_immediate_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_destroy_params_t
{
    xe_command_list_handle_t* phCommandList;
} xe_command_list_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListDestroyCb_t)(
    xe_command_list_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListClose 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_close_params_t
{
    xe_command_list_handle_t* phCommandList;
} xe_command_list_close_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListClose 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListCloseCb_t)(
    xe_command_list_close_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_reset_params_t
{
    xe_command_list_handle_t* phCommandList;
} xe_command_list_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListResetCb_t)(
    xe_command_list_reset_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendBarrier 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_barrier_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    xe_event_handle_t** pphWaitEvents;
} xe_command_list_append_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendBarrier 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendBarrierCb_t)(
    xe_command_list_append_barrier_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemoryRangesBarrier 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_memory_ranges_barrier_params_t
{
    xe_command_list_handle_t* phCommandList;
    uint32_t* pnumRanges;
    const size_t** ppRangeSizes;
    const void*** ppRanges;
    xe_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    xe_event_handle_t** pphWaitEvents;
} xe_command_list_append_memory_ranges_barrier_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemoryRangesBarrier 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendMemoryRangesBarrierCb_t)(
    xe_command_list_append_memory_ranges_barrier_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemoryCopy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_memory_copy_params_t
{
    xe_command_list_handle_t* phCommandList;
    void** pdstptr;
    const void** psrcptr;
    size_t* psize;
    xe_event_handle_t* phEvent;
} xe_command_list_append_memory_copy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemoryCopy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendMemoryCopyCb_t)(
    xe_command_list_append_memory_copy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemorySet 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_memory_set_params_t
{
    xe_command_list_handle_t* phCommandList;
    void** pptr;
    int* pvalue;
    size_t* psize;
    xe_event_handle_t* phEvent;
} xe_command_list_append_memory_set_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemorySet 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendMemorySetCb_t)(
    xe_command_list_append_memory_set_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemoryCopyRegion 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_memory_copy_region_params_t
{
    xe_command_list_handle_t* phCommandList;
    void** pdstptr;
    const xe_copy_region_t** pdstRegion;
    uint32_t* pdstPitch;
    const void** psrcptr;
    const xe_copy_region_t** psrcRegion;
    uint32_t* psrcPitch;
    xe_event_handle_t* phEvent;
} xe_command_list_append_memory_copy_region_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemoryCopyRegion 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendMemoryCopyRegionCb_t)(
    xe_command_list_append_memory_copy_region_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendImageCopy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_image_copy_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_image_handle_t* phDstImage;
    xe_image_handle_t* phSrcImage;
    xe_event_handle_t* phEvent;
} xe_command_list_append_image_copy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendImageCopy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendImageCopyCb_t)(
    xe_command_list_append_image_copy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendImageCopyRegion 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_image_copy_region_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_image_handle_t* phDstImage;
    xe_image_handle_t* phSrcImage;
    const xe_image_region_t** ppDstRegion;
    const xe_image_region_t** ppSrcRegion;
    xe_event_handle_t* phEvent;
} xe_command_list_append_image_copy_region_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendImageCopyRegion 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendImageCopyRegionCb_t)(
    xe_command_list_append_image_copy_region_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendImageCopyToMemory 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_image_copy_to_memory_params_t
{
    xe_command_list_handle_t* phCommandList;
    void** pdstptr;
    xe_image_handle_t* phSrcImage;
    const xe_image_region_t** ppSrcRegion;
    xe_event_handle_t* phEvent;
} xe_command_list_append_image_copy_to_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendImageCopyToMemory 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendImageCopyToMemoryCb_t)(
    xe_command_list_append_image_copy_to_memory_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendImageCopyFromMemory 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_image_copy_from_memory_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_image_handle_t* phDstImage;
    const void** psrcptr;
    const xe_image_region_t** ppDstRegion;
    xe_event_handle_t* phEvent;
} xe_command_list_append_image_copy_from_memory_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendImageCopyFromMemory 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendImageCopyFromMemoryCb_t)(
    xe_command_list_append_image_copy_from_memory_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemoryPrefetch 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_memory_prefetch_params_t
{
    xe_command_list_handle_t* phCommandList;
    const void** pptr;
    size_t* psize;
} xe_command_list_append_memory_prefetch_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemoryPrefetch 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendMemoryPrefetchCb_t)(
    xe_command_list_append_memory_prefetch_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendMemAdvise 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_mem_advise_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_device_handle_t* phDevice;
    const void** pptr;
    size_t* psize;
    xe_memory_advice_t* padvice;
} xe_command_list_append_mem_advise_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendMemAdvise 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendMemAdviseCb_t)(
    xe_command_list_append_mem_advise_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendSignalEvent 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_signal_event_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_event_handle_t* phEvent;
} xe_command_list_append_signal_event_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendSignalEvent 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendSignalEventCb_t)(
    xe_command_list_append_signal_event_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendWaitOnEvents 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_wait_on_events_params_t
{
    xe_command_list_handle_t* phCommandList;
    uint32_t* pnumEvents;
    xe_event_handle_t** pphEvents;
} xe_command_list_append_wait_on_events_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendWaitOnEvents 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendWaitOnEventsCb_t)(
    xe_command_list_append_wait_on_events_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendEventReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_event_reset_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_event_handle_t* phEvent;
} xe_command_list_append_event_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendEventReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendEventResetCb_t)(
    xe_command_list_append_event_reset_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendLaunchFunction 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_launch_function_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_function_handle_t* phFunction;
    const xe_thread_group_dimensions_t** ppLaunchFuncArgs;
    xe_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    xe_event_handle_t** pphWaitEvents;
} xe_command_list_append_launch_function_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendLaunchFunction 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendLaunchFunctionCb_t)(
    xe_command_list_append_launch_function_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendLaunchFunctionIndirect 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_launch_function_indirect_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_function_handle_t* phFunction;
    const xe_thread_group_dimensions_t** ppLaunchArgumentsBuffer;
    xe_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    xe_event_handle_t** pphWaitEvents;
} xe_command_list_append_launch_function_indirect_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendLaunchFunctionIndirect 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendLaunchFunctionIndirectCb_t)(
    xe_command_list_append_launch_function_indirect_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendLaunchMultipleFunctionsIndirect 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_launch_multiple_functions_indirect_params_t
{
    xe_command_list_handle_t* phCommandList;
    uint32_t* pnumFunctions;
    xe_function_handle_t** pphFunctions;
    const uint32_t** ppNumLaunchArguments;
    const xe_thread_group_dimensions_t** ppLaunchArgumentsBuffer;
    xe_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    xe_event_handle_t** pphWaitEvents;
} xe_command_list_append_launch_multiple_functions_indirect_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendLaunchMultipleFunctionsIndirect 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendLaunchMultipleFunctionsIndirectCb_t)(
    xe_command_list_append_launch_multiple_functions_indirect_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeCommandListAppendLaunchHostFunction 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_command_list_append_launch_host_function_params_t
{
    xe_command_list_handle_t* phCommandList;
    xe_host_pfn_t* ppfnHostFunc;
    void** ppUserData;
    xe_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    xe_event_handle_t** pphWaitEvents;
} xe_command_list_append_launch_host_function_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeCommandListAppendLaunchHostFunction 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnCommandListAppendLaunchHostFunctionCb_t)(
    xe_command_list_append_launch_host_function_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_fence_create_params_t
{
    xe_command_queue_handle_t* phCommandQueue;
    const xe_fence_desc_t** pdesc;
    xe_fence_handle_t** pphFence;
} xe_fence_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFenceCreateCb_t)(
    xe_fence_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_fence_destroy_params_t
{
    xe_fence_handle_t* phFence;
} xe_fence_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFenceDestroyCb_t)(
    xe_fence_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceHostSynchronize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_fence_host_synchronize_params_t
{
    xe_fence_handle_t* phFence;
    uint32_t* ptimeout;
} xe_fence_host_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceHostSynchronize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFenceHostSynchronizeCb_t)(
    xe_fence_host_synchronize_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceQueryStatus 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_fence_query_status_params_t
{
    xe_fence_handle_t* phFence;
} xe_fence_query_status_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceQueryStatus 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFenceQueryStatusCb_t)(
    xe_fence_query_status_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFenceReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_fence_reset_params_t
{
    xe_fence_handle_t* phFence;
} xe_fence_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFenceReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFenceResetCb_t)(
    xe_fence_reset_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_pool_create_params_t
{
    xe_driver_handle_t* phDriver;
    const xe_event_pool_desc_t** pdesc;
    uint32_t* pnumDevices;
    xe_device_handle_t** pphDevices;
    xe_event_pool_handle_t** pphEventPool;
} xe_event_pool_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventPoolCreateCb_t)(
    xe_event_pool_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_pool_destroy_params_t
{
    xe_event_pool_handle_t* phEventPool;
} xe_event_pool_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventPoolDestroyCb_t)(
    xe_event_pool_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolGetIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_pool_get_ipc_handle_params_t
{
    xe_event_pool_handle_t* phEventPool;
    xe_ipc_event_pool_handle_t** pphIpc;
} xe_event_pool_get_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolGetIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventPoolGetIpcHandleCb_t)(
    xe_event_pool_get_ipc_handle_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolOpenIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_pool_open_ipc_handle_params_t
{
    xe_driver_handle_t* phDriver;
    xe_ipc_event_pool_handle_t* phIpc;
    xe_event_pool_handle_t** pphEventPool;
} xe_event_pool_open_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolOpenIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventPoolOpenIpcHandleCb_t)(
    xe_event_pool_open_ipc_handle_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventPoolCloseIpcHandle 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_pool_close_ipc_handle_params_t
{
    xe_event_pool_handle_t* phEventPool;
} xe_event_pool_close_ipc_handle_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventPoolCloseIpcHandle 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventPoolCloseIpcHandleCb_t)(
    xe_event_pool_close_ipc_handle_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_create_params_t
{
    xe_event_pool_handle_t* phEventPool;
    const xe_event_desc_t** pdesc;
    xe_event_handle_t** pphEvent;
} xe_event_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventCreateCb_t)(
    xe_event_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_destroy_params_t
{
    xe_event_handle_t* phEvent;
} xe_event_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventDestroyCb_t)(
    xe_event_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventHostSignal 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_host_signal_params_t
{
    xe_event_handle_t* phEvent;
} xe_event_host_signal_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventHostSignal 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventHostSignalCb_t)(
    xe_event_host_signal_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventHostSynchronize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_host_synchronize_params_t
{
    xe_event_handle_t* phEvent;
    uint32_t* ptimeout;
} xe_event_host_synchronize_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventHostSynchronize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventHostSynchronizeCb_t)(
    xe_event_host_synchronize_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventQueryStatus 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_query_status_params_t
{
    xe_event_handle_t* phEvent;
} xe_event_query_status_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventQueryStatus 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventQueryStatusCb_t)(
    xe_event_query_status_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeEventReset 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_event_reset_params_t
{
    xe_event_handle_t* phEvent;
} xe_event_reset_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeEventReset 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnEventResetCb_t)(
    xe_event_reset_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_image_get_properties_params_t
{
    xe_device_handle_t* phDevice;
    const xe_image_desc_t** pdesc;
    xe_image_properties_t** ppImageProperties;
} xe_image_get_properties_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeImageGetProperties 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnImageGetPropertiesCb_t)(
    xe_image_get_properties_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeImageCreate 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_image_create_params_t
{
    xe_device_handle_t* phDevice;
    const xe_image_desc_t** pdesc;
    xe_image_handle_t** pphImage;
} xe_image_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeImageCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnImageCreateCb_t)(
    xe_image_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeImageDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_image_destroy_params_t
{
    xe_image_handle_t* phImage;
} xe_image_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeImageDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnImageDestroyCb_t)(
    xe_image_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_module_create_params_t
{
    xe_device_handle_t* phDevice;
    const xe_module_desc_t** pdesc;
    xe_module_handle_t** pphModule;
    xe_module_build_log_handle_t** pphBuildLog;
} xe_module_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnModuleCreateCb_t)(
    xe_module_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_module_destroy_params_t
{
    xe_module_handle_t* phModule;
} xe_module_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnModuleDestroyCb_t)(
    xe_module_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleGetNativeBinary 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_module_get_native_binary_params_t
{
    xe_module_handle_t* phModule;
    size_t** ppSize;
    uint8_t** ppModuleNativeBinary;
} xe_module_get_native_binary_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleGetNativeBinary 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnModuleGetNativeBinaryCb_t)(
    xe_module_get_native_binary_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleGetGlobalPointer 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_module_get_global_pointer_params_t
{
    xe_module_handle_t* phModule;
    const char** ppGlobalName;
    void*** ppptr;
} xe_module_get_global_pointer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleGetGlobalPointer 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnModuleGetGlobalPointerCb_t)(
    xe_module_get_global_pointer_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleGetFunctionPointer 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_module_get_function_pointer_params_t
{
    xe_module_handle_t* phModule;
    const char** ppFunctionName;
    void*** ppfnFunction;
} xe_module_get_function_pointer_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleGetFunctionPointer 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnModuleGetFunctionPointerCb_t)(
    xe_module_get_function_pointer_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_module_build_log_destroy_params_t
{
    xe_module_build_log_handle_t* phModuleBuildLog;
} xe_module_build_log_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleBuildLogDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnModuleBuildLogDestroyCb_t)(
    xe_module_build_log_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeModuleBuildLogGetString 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_module_build_log_get_string_params_t
{
    xe_module_build_log_handle_t* phModuleBuildLog;
    size_t** ppSize;
    char** ppBuildLog;
} xe_module_build_log_get_string_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeModuleBuildLogGetString 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnModuleBuildLogGetStringCb_t)(
    xe_module_build_log_get_string_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_function_create_params_t
{
    xe_module_handle_t* phModule;
    const xe_function_desc_t** pdesc;
    xe_function_handle_t** pphFunction;
} xe_function_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFunctionCreateCb_t)(
    xe_function_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_function_destroy_params_t
{
    xe_function_handle_t* phFunction;
} xe_function_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFunctionDestroyCb_t)(
    xe_function_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionSetGroupSize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_function_set_group_size_params_t
{
    xe_function_handle_t* phFunction;
    uint32_t* pgroupSizeX;
    uint32_t* pgroupSizeY;
    uint32_t* pgroupSizeZ;
} xe_function_set_group_size_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionSetGroupSize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFunctionSetGroupSizeCb_t)(
    xe_function_set_group_size_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionSuggestGroupSize 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_function_suggest_group_size_params_t
{
    xe_function_handle_t* phFunction;
    uint32_t* pglobalSizeX;
    uint32_t* pglobalSizeY;
    uint32_t* pglobalSizeZ;
    uint32_t** pgroupSizeX;
    uint32_t** pgroupSizeY;
    uint32_t** pgroupSizeZ;
} xe_function_suggest_group_size_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionSuggestGroupSize 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFunctionSuggestGroupSizeCb_t)(
    xe_function_suggest_group_size_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionSetArgumentValue 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_function_set_argument_value_params_t
{
    xe_function_handle_t* phFunction;
    uint32_t* pargIndex;
    size_t* pargSize;
    const void** ppArgValue;
} xe_function_set_argument_value_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionSetArgumentValue 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFunctionSetArgumentValueCb_t)(
    xe_function_set_argument_value_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionSetAttribute 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_function_set_attribute_params_t
{
    xe_function_handle_t* phFunction;
    xe_function_set_attribute_t* pattr;
    uint32_t* pvalue;
} xe_function_set_attribute_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionSetAttribute 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFunctionSetAttributeCb_t)(
    xe_function_set_attribute_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeFunctionGetAttribute 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_function_get_attribute_params_t
{
    xe_function_handle_t* phFunction;
    xe_function_get_attribute_t* pattr;
    uint32_t** ppValue;
} xe_function_get_attribute_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeFunctionGetAttribute 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnFunctionGetAttributeCb_t)(
    xe_function_get_attribute_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_sampler_create_params_t
{
    xe_device_handle_t* phDevice;
    const xe_sampler_desc_t** pdesc;
    xe_sampler_handle_t** pphSampler;
} xe_sampler_create_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeSamplerCreate 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnSamplerCreateCb_t)(
    xe_sampler_create_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for xeSamplerDestroy 
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value
typedef struct _xe_sampler_destroy_params_t
{
    xe_sampler_handle_t* phSampler;
} xe_sampler_destroy_params_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for xeSamplerDestroy 
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data
typedef void (__xecall *xe_pfnSamplerDestroyCb_t)(
    xe_sampler_destroy_params_t* params,
    xe_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
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
    xe_driver_callbacks_t               Driver;
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