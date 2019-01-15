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
* @file xi_memory.h
*
* @brief Intel Xi Runtime APIs for Memory
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/memory.yml
* @endcond
*
******************************************************************************/
#ifndef _XI_MEMORY_H
#define _XI_MEMORY_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xi_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::xi_mempool_desc_t
#define XI_MEMPOOL_DESC_VERSION  XI_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory allocation flags
typedef enum _xi_memory_flags_t
{
    XI_MEMORY_FLAG_NONE = 0,                        ///< @todo

} xi_memory_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory pool descriptor.
typedef struct _xi_mempool_desc_t
{
    uint32_t version;                               ///< [in] ::XI_MEMPOOL_DESC_VERSION
    uint32_t mask;                                  ///< @todo some kind of device plus tile affinity mask?

} xi_mempool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that will be automatically managed.
/// @details
///     - Managed memory is automatically migrated between the host and memory
///       pool represented by... ?
///     - @todo Comprehend multi-tile.
///     - @todo Host or cross-device allcations?
/// @remarks
///   _Analogues_
///     - **cuMemAllocManaged**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - @todo
xi_result_t __xicall
  xiMemAllocManaged(
    const xi_mempool_desc_t* desc,                  ///< [in] pointer to memory pool descriptor
    xi_memory_flags_t flags,                        ///< [in] flags specifying allocation and usage information
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    xi_device_ptr_t* ptr                            ///< [out] pointer to managed allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory specific to a device.
/// @remarks
///   _Analogues_
///     - **cuMemAlloc**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - @todo
xi_result_t __xicall
  xiMemAlloc(
    const xi_mempool_desc_t* desc,                  ///< [in] pointer to memory pool descriptor
    xi_memory_flags_t flags,                        ///< [in] flags specifying allocation and usage information
    size_t size,                                    ///< [in] size in bytes to allocate
    uint32_t alignment,                             ///< [in] minimum alignment in bytes for the allocation
    xi_device_ptr_t* ptr                            ///< [out] pointer to managed allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated device memory or managed memory.
/// @remarks
///   _Analogues_
///     - **cuMemFree**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - @todo
xi_result_t __xicall
  xiMemFree(
    xi_device_ptr_t ptr                             ///< [in] pointer to memory to free
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory advice hints
typedef enum _xi_memory_advice_t
{
    XI_MEMORY_ADVICE_NONE = 0,                      ///< @todo

} xi_memory_advice_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a memory range.
/// @details
///     - @todo likely will snap to page boundaries
///     - @todo which memory advise hints could/should we support?
/// @remarks
///   _Analogues_
///     - **cuMemAdvise**
/// @returns
/// - ::XI_RESULT_SUCCESS
/// - ::XI_RESULT_ERROR_UNINITIALIZED
/// - @todo
xi_result_t __xicall
  xiMemAdvise(
    const xi_mempool_desc_t* desc,                  ///< [in] pointer to memory pool descriptor to apply advice to
    xi_device_ptr_t ptr,                            ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xi_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    );

#endif // _XI_MEMORY_H
