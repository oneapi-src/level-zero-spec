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
* @file xe_common.h
*
* @brief Intel Xe Level-Zero API common types
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/common.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_COMMON_H
#define _XE_COMMON_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_XE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include <stdint.h>
#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_MAKE_VERSION
/// @brief Generates generic Xe API versions
#define XE_MAKE_VERSION( _major, _minor )  (( _major << 16 )|( _minor & 0x0000ffff))
#endif // XE_MAKE_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_MAJOR_VERSION
/// @brief Extracts Xe API major version
#define XE_MAJOR_VERSION( _ver )  ( _ver >> 16 )
#endif // XE_MAJOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_MINOR_VERSION
/// @brief Extracts Xe API minor version
#define XE_MINOR_VERSION( _ver )  ( _ver & 0x0000ffff )
#endif // XE_MINOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef __xecall
#if defined(_WIN32)
/// @brief Calling convention for all API functions
#define __xecall  __cdecl
#else
#define __xecall  
#endif // defined(_WIN32)
#endif // __xecall

///////////////////////////////////////////////////////////////////////////////
#ifndef __xedllexport
#if defined(_WIN32)
/// @brief Microsoft-specific dllexport storage-class attribute
#define __xedllexport  __declspec(dllexport)
#else
#define __xedllexport  
#endif // defined(_WIN32)
#endif // __xedllexport

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_ENABLE_OCL_INTEROP
#if !defined(XE_ENABLE_OCL_INTEROP)
/// @brief Disable OpenCL interoperability functions if not explicitly defined
#define XE_ENABLE_OCL_INTEROP  0
#endif // !defined(XE_ENABLE_OCL_INTEROP)
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief compiler-independent type
typedef uint8_t xe_bool_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's device group object
typedef struct _xe_device_group_handle_t *xe_device_group_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's device object
typedef struct _xe_device_handle_t *xe_device_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command queue object
typedef struct _xe_command_queue_handle_t *xe_command_queue_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command list object
typedef struct _xe_command_list_handle_t *xe_command_list_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's fence object
typedef struct _xe_fence_handle_t *xe_fence_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's event pool object
typedef struct _xe_event_pool_handle_t *xe_event_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's event object
typedef struct _xe_event_handle_t *xe_event_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's image object
typedef struct _xe_image_handle_t *xe_image_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's module object
typedef struct _xe_module_handle_t *xe_module_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of module's build log object
typedef struct _xe_module_build_log_handle_t *xe_module_build_log_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's function object
typedef struct _xe_function_handle_t *xe_function_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's sampler object
typedef struct _xe_sampler_handle_t *xe_sampler_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC handle to a memory allocation
typedef struct _xe_ipc_mem_handle_t *xe_ipc_mem_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC handle to a event pool allocation
typedef struct _xe_ipc_event_pool_handle_t *xe_ipc_event_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef XE_BIT
/// @brief Generic macro for enumerator bit masks
#define XE_BIT( _i )  ( 1 << _i )
#endif // XE_BIT

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
/// 
/// @remarks
///   _Analogues_
///     - **CUresult**
typedef enum _xe_result_t
{
    XE_RESULT_SUCCESS = 0,                          ///< success
    XE_RESULT_NOT_READY = 1,                        ///< synchronization primitive not signaled
    XE_RESULT_ERROR_UNINITIALIZED,                  ///< driver is not initialized
    XE_RESULT_ERROR_DEVICE_LOST,                    ///< device hung, reset, was removed, or driver update occurred
    XE_RESULT_ERROR_UNSUPPORTED,                    ///< device does not support feature requested
    XE_RESULT_ERROR_INVALID_ARGUMENT,               ///< invalid argument provided
    XE_RESULT_ERROR_OUT_OF_HOST_MEMORY,             ///< insufficient host memory to satisfy call
    XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY,           ///< insufficient device memory to satisfy call
    XE_RESULT_ERROR_MODULE_BUILD_FAILURE,           ///< error in building module
    XE_RESULT_ERROR_UNKNOWN = 0x7fffffff,           ///< unknown or internal error

} xe_result_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_device_uuid_t
typedef struct _xe_device_uuid_t xe_device_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_device_properties_t
typedef struct _xe_device_properties_t xe_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_device_compute_properties_t
typedef struct _xe_device_compute_properties_t xe_device_compute_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_device_memory_properties_t
typedef struct _xe_device_memory_properties_t xe_device_memory_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_device_image_properties_t
typedef struct _xe_device_image_properties_t xe_device_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_device_p2p_properties_t
typedef struct _xe_device_p2p_properties_t xe_device_p2p_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_command_queue_desc_t
typedef struct _xe_command_queue_desc_t xe_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_command_list_desc_t
typedef struct _xe_command_list_desc_t xe_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_copy_region_t
typedef struct _xe_copy_region_t xe_copy_region_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_image_region_t
typedef struct _xe_image_region_t xe_image_region_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_event_pool_desc_t
typedef struct _xe_event_pool_desc_t xe_event_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_event_desc_t
typedef struct _xe_event_desc_t xe_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_fence_desc_t
typedef struct _xe_fence_desc_t xe_fence_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_image_format_desc_t
typedef struct _xe_image_format_desc_t xe_image_format_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_image_desc_t
typedef struct _xe_image_desc_t xe_image_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_image_properties_t
typedef struct _xe_image_properties_t xe_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_memory_allocation_properties_t
typedef struct _xe_memory_allocation_properties_t xe_memory_allocation_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_module_desc_t
typedef struct _xe_module_desc_t xe_module_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_function_desc_t
typedef struct _xe_function_desc_t xe_function_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_thread_group_dimensions_t
typedef struct _xe_thread_group_dimensions_t xe_thread_group_dimensions_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare xe_sampler_desc_t
typedef struct _xe_sampler_desc_t xe_sampler_desc_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_COMMON_H
