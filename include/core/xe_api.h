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
* @file xe_api.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core
* @endcond
*
******************************************************************************/
#ifndef _XE_API_H
#define _XE_API_H
#if defined(__cplusplus)
#pragma once
#endif

#include "xe_driver.h"
#include "xe_context.h"
#include "xe_device.h"
#include "xe_cmdqueue.h"
#include "xe_cmdlist.h"
#include "xe_barrier.h"
#include "xe_cl_interop.h"
#include "xe_copy.h"
#include "xe_event.h"
#include "xe_fence.h"
#include "xe_image.h"
#include "xe_memory.h"
#include "xe_module.h"
#include "xe_residency.h"
#include "xe_sampler.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList functions pointers
typedef struct _xe_command_list_apitable_t
{
    xe_pfnCommandListCreate_t                                   pfnCreate;
    xe_pfnCommandListCreateImmediate_t                          pfnCreateImmediate;
    xe_pfnCommandListDestroy_t                                  pfnDestroy;
    xe_pfnCommandListClose_t                                    pfnClose;
    xe_pfnCommandListReset_t                                    pfnReset;
    xe_pfnCommandListSetParameter_t                             pfnSetParameter;
    xe_pfnCommandListGetParameter_t                             pfnGetParameter;
    xe_pfnCommandListResetParameters_t                          pfnResetParameters;
    xe_pfnCommandListReserveSpace_t                             pfnReserveSpace;
    xe_pfnCommandListAppendBarrier_t                            pfnAppendBarrier;
    xe_pfnCommandListAppendMemoryRangesBarrier_t                pfnAppendMemoryRangesBarrier;
    xe_pfnCommandListAppendMemoryCopy_t                         pfnAppendMemoryCopy;
    xe_pfnCommandListAppendMemorySet_t                          pfnAppendMemorySet;
    xe_pfnCommandListAppendMemoryCopyRegion_t                   pfnAppendMemoryCopyRegion;
    xe_pfnCommandListAppendImageCopy_t                          pfnAppendImageCopy;
    xe_pfnCommandListAppendImageCopyRegion_t                    pfnAppendImageCopyRegion;
    xe_pfnCommandListAppendImageCopyToMemory_t                  pfnAppendImageCopyToMemory;
    xe_pfnCommandListAppendImageCopyFromMemory_t                pfnAppendImageCopyFromMemory;
    xe_pfnCommandListAppendMemoryPrefetch_t                     pfnAppendMemoryPrefetch;
    xe_pfnCommandListAppendMemAdvise_t                          pfnAppendMemAdvise;
    xe_pfnCommandListAppendSignalEvent_t                        pfnAppendSignalEvent;
    xe_pfnCommandListAppendWaitOnEvents_t                       pfnAppendWaitOnEvents;
    xe_pfnCommandListAppendEventReset_t                         pfnAppendEventReset;
    xe_pfnCommandListAppendLaunchFunction_t                     pfnAppendLaunchFunction;
    xe_pfnCommandListAppendLaunchFunctionIndirect_t             pfnAppendLaunchFunctionIndirect;
    xe_pfnCommandListAppendLaunchMultipleFunctionsIndirect_t    pfnAppendLaunchMultipleFunctionsIndirect;
    xe_pfnCommandListAppendLaunchHostFunction_t                 pfnAppendLaunchHostFunction;
} xe_command_list_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandListProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_command_list_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetCommandListProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetCommandListProcAddrTable_t)(
    xe_api_version_t,
    xe_command_list_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device functions pointers
typedef struct _xe_device_apitable_t
{
    xe_pfnDeviceGetSubDevice_t                                  pfnGetSubDevice;
    xe_pfnDeviceGetP2PProperties_t                              pfnGetP2PProperties;
    xe_pfnDeviceCanAccessPeer_t                                 pfnCanAccessPeer;
    xe_pfnDeviceSetIntermediateCacheConfig_t                    pfnSetIntermediateCacheConfig;
    xe_pfnDeviceSetLastLevelCacheConfig_t                       pfnSetLastLevelCacheConfig;
    xe_pfnDeviceSystemBarrier_t                                 pfnSystemBarrier;
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLMemory_t                              pfnRegisterCLMemory;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLProgram_t                             pfnRegisterCLProgram;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLCommandQueue_t                        pfnRegisterCLCommandQueue;
    #endif // XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceMakeMemoryResident_t                            pfnMakeMemoryResident;
    xe_pfnDeviceEvictMemory_t                                   pfnEvictMemory;
    xe_pfnDeviceMakeImageResident_t                             pfnMakeImageResident;
    xe_pfnDeviceEvictImage_t                                    pfnEvictImage;
} xe_device_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_device_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetDeviceProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetDeviceProcAddrTable_t)(
    xe_api_version_t,
    xe_device_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandQueue functions pointers
typedef struct _xe_command_queue_apitable_t
{
    xe_pfnCommandQueueCreate_t                                  pfnCreate;
    xe_pfnCommandQueueDestroy_t                                 pfnDestroy;
    xe_pfnCommandQueueExecuteCommandLists_t                     pfnExecuteCommandLists;
    xe_pfnCommandQueueSynchronize_t                             pfnSynchronize;
} xe_command_queue_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandQueueProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_command_queue_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetCommandQueueProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetCommandQueueProcAddrTable_t)(
    xe_api_version_t,
    xe_command_queue_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Context functions pointers
typedef struct _xe_context_apitable_t
{
    xe_pfnContextCreate_t                                       pfnCreate;
    xe_pfnContextDestroy_t                                      pfnDestroy;
    xe_pfnContextAllocSharedMem_t                               pfnAllocSharedMem;
    xe_pfnContextAllocDeviceMem_t                               pfnAllocDeviceMem;
    xe_pfnContextAllocHostMem_t                                 pfnAllocHostMem;
    xe_pfnContextFreeMem_t                                      pfnFreeMem;
    xe_pfnContextGetMemProperties_t                             pfnGetMemProperties;
    xe_pfnContextGetMemAddressRange_t                           pfnGetMemAddressRange;
    xe_pfnContextGetMemIpcHandle_t                              pfnGetMemIpcHandle;
    xe_pfnContextOpenMemIpcHandle_t                             pfnOpenMemIpcHandle;
    xe_pfnContextCloseMemIpcHandle_t                            pfnCloseMemIpcHandle;
} xe_context_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetContextProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_context_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetContextProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetContextProcAddrTable_t)(
    xe_api_version_t,
    xe_context_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of DeviceGroup functions pointers
typedef struct _xe_device_group_apitable_t
{
    xe_pfnDeviceGroupGetDriverVersion_t                         pfnGetDriverVersion;
    xe_pfnDeviceGroupGetDevices_t                               pfnGetDevices;
    xe_pfnDeviceGroupGetApiVersion_t                            pfnGetApiVersion;
    xe_pfnDeviceGroupGetProperties_t                            pfnGetProperties;
    xe_pfnDeviceGroupGetComputeProperties_t                     pfnGetComputeProperties;
    xe_pfnDeviceGroupGetMemoryProperties_t                      pfnGetMemoryProperties;
} xe_device_group_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceGroupProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_device_group_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetDeviceGroupProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetDeviceGroupProcAddrTable_t)(
    xe_api_version_t,
    xe_device_group_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Fence functions pointers
typedef struct _xe_fence_apitable_t
{
    xe_pfnFenceCreate_t                                         pfnCreate;
    xe_pfnFenceDestroy_t                                        pfnDestroy;
    xe_pfnFenceHostSynchronize_t                                pfnHostSynchronize;
    xe_pfnFenceQueryStatus_t                                    pfnQueryStatus;
    xe_pfnFenceReset_t                                          pfnReset;
} xe_fence_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFenceProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_fence_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetFenceProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetFenceProcAddrTable_t)(
    xe_api_version_t,
    xe_fence_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of EventPool functions pointers
typedef struct _xe_event_pool_apitable_t
{
    xe_pfnEventPoolCreate_t                                     pfnCreate;
    xe_pfnEventPoolDestroy_t                                    pfnDestroy;
    xe_pfnEventPoolGetIpcHandle_t                               pfnGetIpcHandle;
    xe_pfnEventPoolOpenIpcHandle_t                              pfnOpenIpcHandle;
    xe_pfnEventPoolCloseIpcHandle_t                             pfnCloseIpcHandle;
} xe_event_pool_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventPoolProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_event_pool_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetEventPoolProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetEventPoolProcAddrTable_t)(
    xe_api_version_t,
    xe_event_pool_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Event functions pointers
typedef struct _xe_event_apitable_t
{
    xe_pfnEventCreate_t                                         pfnCreate;
    xe_pfnEventDestroy_t                                        pfnDestroy;
    xe_pfnEventHostSignal_t                                     pfnHostSignal;
    xe_pfnEventHostSynchronize_t                                pfnHostSynchronize;
    xe_pfnEventQueryStatus_t                                    pfnQueryStatus;
    xe_pfnEventReset_t                                          pfnReset;
} xe_event_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_event_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetEventProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetEventProcAddrTable_t)(
    xe_api_version_t,
    xe_event_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Image functions pointers
typedef struct _xe_image_apitable_t
{
    xe_pfnImageGetProperties_t                                  pfnGetProperties;
    xe_pfnImageCreate_t                                         pfnCreate;
    xe_pfnImageDestroy_t                                        pfnDestroy;
} xe_image_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetImageProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_image_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetImageProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetImageProcAddrTable_t)(
    xe_api_version_t,
    xe_image_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module functions pointers
typedef struct _xe_module_apitable_t
{
    xe_pfnModuleCreate_t                                        pfnCreate;
    xe_pfnModuleDestroy_t                                       pfnDestroy;
    xe_pfnModuleGetNativeBinary_t                               pfnGetNativeBinary;
    xe_pfnModuleGetGlobalPointer_t                              pfnGetGlobalPointer;
    xe_pfnModuleGetFunctionPointer_t                            pfnGetFunctionPointer;
} xe_module_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_module_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetModuleProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetModuleProcAddrTable_t)(
    xe_api_version_t,
    xe_module_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ModuleBuildLog functions pointers
typedef struct _xe_module_build_log_apitable_t
{
    xe_pfnModuleBuildLogDestroy_t                               pfnDestroy;
    xe_pfnModuleBuildLogGetString_t                             pfnGetString;
} xe_module_build_log_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleBuildLogProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_module_build_log_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetModuleBuildLogProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetModuleBuildLogProcAddrTable_t)(
    xe_api_version_t,
    xe_module_build_log_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Function functions pointers
typedef struct _xe_function_apitable_t
{
    xe_pfnFunctionCreate_t                                      pfnCreate;
    xe_pfnFunctionDestroy_t                                     pfnDestroy;
    xe_pfnFunctionSetGroupSize_t                                pfnSetGroupSize;
    xe_pfnFunctionSuggestGroupSize_t                            pfnSuggestGroupSize;
    xe_pfnFunctionSetArgumentValue_t                            pfnSetArgumentValue;
    xe_pfnFunctionSetAttribute_t                                pfnSetAttribute;
    xe_pfnFunctionGetAttribute_t                                pfnGetAttribute;
} xe_function_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFunctionProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_function_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetFunctionProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetFunctionProcAddrTable_t)(
    xe_api_version_t,
    xe_function_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sampler functions pointers
typedef struct _xe_sampler_apitable_t
{
    xe_pfnSamplerCreate_t                                       pfnCreate;
    xe_pfnSamplerDestroy_t                                      pfnDestroy;
} xe_sampler_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetSamplerProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_sampler_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetSamplerProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetSamplerProcAddrTable_t)(
    xe_api_version_t,
    xe_sampler_apitable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global functions pointers
typedef struct _xe_global_apitable_t
{
    xe_pfnInit_t                                                pfnInit;
    xe_pfnGetDeviceGroups_t                                     pfnGetDeviceGroups;
} xe_global_apitable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetGlobalProcAddrTable(
    xe_api_version_t version, ///< [in] API version requested
    xe_global_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetGlobalProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetGlobalProcAddrTable_t)(
    xe_api_version_t,
    xe_global_apitable_t*
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_API_H