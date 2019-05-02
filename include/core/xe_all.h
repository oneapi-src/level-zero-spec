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
* @file xe_all.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/api_all.h.mako
* @endcond
*
******************************************************************************/
#ifndef _XE_ALL_H
#define _XE_ALL_H
#if defined(__cplusplus)
#pragma once
#endif

#include "xe_barrier.h"
#include "xe_cl_interop.h"
#include "xe_cmdlist.h"
#include "xe_cmdqueue.h"
#include "xe_copy.h"
#include "xe_device.h"
#include "xe_driver.h"
#include "xe_event.h"
#include "xe_fence.h"
#include "xe_image.h"
#include "xe_memory.h"
#include "xe_module.h"
#include "xe_residency.h"
#include "xe_sampler.h"

///////////////////////////////////////////////////////////////////////////////
typedef struct _xe_apitable_t
{
    xe_pfnCommandListAppendBarrier_t                   pfnCommandListAppendBarrier;
    xe_pfnCommandListAppendMemoryRangesBarrier_t       pfnCommandListAppendMemoryRangesBarrier;
    xe_pfnDeviceSystemBarrier_t                        pfnDeviceSystemBarrier;
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLMemory_t                     pfnDeviceRegisterCLMemory;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLProgram_t                    pfnDeviceRegisterCLProgram;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLCommandQueue_t               pfnDeviceRegisterCLCommandQueue;
    #endif // XE_ENABLE_OCL_INTEROP
    xe_pfnCommandListCreate_t                          pfnCommandListCreate;
    xe_pfnCommandListCreateImmediate_t                 pfnCommandListCreateImmediate;
    xe_pfnCommandListDestroy_t                         pfnCommandListDestroy;
    xe_pfnCommandListClose_t                           pfnCommandListClose;
    xe_pfnCommandListReset_t                           pfnCommandListReset;
    xe_pfnCommandListSetParameter_t                    pfnCommandListSetParameter;
    xe_pfnCommandListGetParameter_t                    pfnCommandListGetParameter;
    xe_pfnCommandListResetParameters_t                 pfnCommandListResetParameters;
    xe_pfnCommandListReserveSpace_t                    pfnCommandListReserveSpace;
    xe_pfnCommandQueueCreate_t                         pfnCommandQueueCreate;
    xe_pfnCommandQueueDestroy_t                        pfnCommandQueueDestroy;
    xe_pfnCommandQueueExecuteCommandLists_t            pfnCommandQueueExecuteCommandLists;
    xe_pfnCommandQueueSynchronize_t                    pfnCommandQueueSynchronize;
    xe_pfnCommandListAppendMemoryCopy_t                pfnCommandListAppendMemoryCopy;
    xe_pfnCommandListAppendMemorySet_t                 pfnCommandListAppendMemorySet;
    xe_pfnCommandListAppendImageCopy_t                 pfnCommandListAppendImageCopy;
    xe_pfnCommandListAppendImageCopyRegion_t           pfnCommandListAppendImageCopyRegion;
    xe_pfnCommandListAppendImageCopyToMemory_t         pfnCommandListAppendImageCopyToMemory;
    xe_pfnCommandListAppendImageCopyFromMemory_t       pfnCommandListAppendImageCopyFromMemory;
    xe_pfnCommandListAppendMemoryPrefetch_t            pfnCommandListAppendMemoryPrefetch;
    xe_pfnCommandListAppendMemAdvise_t                 pfnCommandListAppendMemAdvise;
    xe_pfnDeviceGetCount_t                             pfnDeviceGetCount;
    xe_pfnDeviceGet_t                                  pfnDeviceGet;
    xe_pfnDeviceGetSubDevice_t                         pfnDeviceGetSubDevice;
    xe_pfnDeviceGetApiVersion_t                        pfnDeviceGetApiVersion;
    xe_pfnDeviceGetProperties_t                        pfnDeviceGetProperties;
    xe_pfnDeviceGetComputeProperties_t                 pfnDeviceGetComputeProperties;
    xe_pfnDeviceGetMemoryProperties_t                  pfnDeviceGetMemoryProperties;
    xe_pfnDeviceGetP2PProperties_t                     pfnDeviceGetP2PProperties;
    xe_pfnDeviceCanAccessPeer_t                        pfnDeviceCanAccessPeer;
    xe_pfnDeviceSetIntermediateCacheConfig_t           pfnDeviceSetIntermediateCacheConfig;
    xe_pfnDeviceSetLastLevelCacheConfig_t              pfnDeviceSetLastLevelCacheConfig;
    xe_pfnInit_t                                       pfnInit;
    xe_pfnGetDriverVersion_t                           pfnGetDriverVersion;
    xe_pfnEventPoolCreate_t                            pfnEventPoolCreate;
    xe_pfnEventPoolDestroy_t                           pfnEventPoolDestroy;
    xe_pfnEventCreate_t                                pfnEventCreate;
    xe_pfnEventDestroy_t                               pfnEventDestroy;
    xe_pfnEventPoolGetIpcHandle_t                      pfnEventPoolGetIpcHandle;
    xe_pfnEventPoolOpenIpcHandle_t                     pfnEventPoolOpenIpcHandle;
    xe_pfnEventPoolCloseIpcHandle_t                    pfnEventPoolCloseIpcHandle;
    xe_pfnCommandListAppendSignalEvent_t               pfnCommandListAppendSignalEvent;
    xe_pfnCommandListAppendWaitOnEvents_t              pfnCommandListAppendWaitOnEvents;
    xe_pfnEventHostSignal_t                            pfnEventHostSignal;
    xe_pfnEventHostSynchronize_t                       pfnEventHostSynchronize;
    xe_pfnEventQueryStatus_t                           pfnEventQueryStatus;
    xe_pfnCommandListAppendEventReset_t                pfnCommandListAppendEventReset;
    xe_pfnEventReset_t                                 pfnEventReset;
    xe_pfnFenceCreate_t                                pfnFenceCreate;
    xe_pfnFenceDestroy_t                               pfnFenceDestroy;
    xe_pfnFenceHostSynchronize_t                       pfnFenceHostSynchronize;
    xe_pfnFenceQueryStatus_t                           pfnFenceQueryStatus;
    xe_pfnFenceReset_t                                 pfnFenceReset;
    xe_pfnImageGetProperties_t                         pfnImageGetProperties;
    xe_pfnImageCreate_t                                pfnImageCreate;
    xe_pfnImageDestroy_t                               pfnImageDestroy;
    xe_pfnSharedMemAlloc_t                             pfnSharedMemAlloc;
    xe_pfnMemAlloc_t                                   pfnMemAlloc;
    xe_pfnHostMemAlloc_t                               pfnHostMemAlloc;
    xe_pfnMemFree_t                                    pfnMemFree;
    xe_pfnMemGetProperties_t                           pfnMemGetProperties;
    xe_pfnMemGetAddressRange_t                         pfnMemGetAddressRange;
    xe_pfnIpcGetMemHandle_t                            pfnIpcGetMemHandle;
    xe_pfnIpcOpenMemHandle_t                           pfnIpcOpenMemHandle;
    xe_pfnIpcCloseMemHandle_t                          pfnIpcCloseMemHandle;
    xe_pfnModuleCreate_t                               pfnModuleCreate;
    xe_pfnModuleDestroy_t                              pfnModuleDestroy;
    xe_pfnModuleBuildLogDestroy_t                      pfnModuleBuildLogDestroy;
    xe_pfnModuleBuildLogGetString_t                    pfnModuleBuildLogGetString;
    xe_pfnModuleGetNativeBinary_t                      pfnModuleGetNativeBinary;
    xe_pfnModuleGetGlobalPointer_t                     pfnModuleGetGlobalPointer;
    xe_pfnFunctionCreate_t                             pfnFunctionCreate;
    xe_pfnFunctionDestroy_t                            pfnFunctionDestroy;
    xe_pfnModuleGetFunctionPointer_t                   pfnModuleGetFunctionPointer;
    xe_pfnFunctionSetGroupSize_t                       pfnFunctionSetGroupSize;
    xe_pfnFunctionSuggestGroupSize_t                   pfnFunctionSuggestGroupSize;
    xe_pfnFunctionSetArgumentValue_t                   pfnFunctionSetArgumentValue;
    xe_pfnFunctionSetAttribute_t                       pfnFunctionSetAttribute;
    xe_pfnFunctionGetAttribute_t                       pfnFunctionGetAttribute;
    xe_pfnCommandListAppendLaunchFunction_t            pfnCommandListAppendLaunchFunction;
    xe_pfnCommandListAppendLaunchFunctionIndirect_t    pfnCommandListAppendLaunchFunctionIndirect;
    xe_pfnCommandListAppendLaunchMultipleFunctionsIndirect_t   pfnCommandListAppendLaunchMultipleFunctionsIndirect;
    xe_pfnCommandListAppendLaunchHostFunction_t        pfnCommandListAppendLaunchHostFunction;
    xe_pfnDeviceMakeMemoryResident_t                   pfnDeviceMakeMemoryResident;
    xe_pfnDeviceEvictMemory_t                          pfnDeviceEvictMemory;
    xe_pfnDeviceMakeImageResident_t                    pfnDeviceMakeImageResident;
    xe_pfnDeviceEvictImage_t                           pfnDeviceEvictImage;
    xe_pfnSamplerCreate_t                              pfnSamplerCreate;
    xe_pfnSamplerDestroy_t                             pfnSamplerDestroy;
} xe_apitable_t;

#endif // _XE_ALL_H