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
* @file xe_memory.h
* 
* @brief Intel Xe Driver APIs for Memory
* 
******************************************************************************/
#ifndef _XE_MEMORY_H
#define _XE_MEMORY_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory allocation flags
XE_DECLARE_ENUM( xe_memory_flags_t )
{
    XE_MEMORY_FLAG_TODO = 0         ///< TODO
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory pool descriptor
typedef struct _xe_mempool_desc_t
{
    uint32_t version;       ///< [in] descriptor version

    // TBD: some kind of device plus tile affinity mask?
} xe_mempool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of xe_mempool_desc_t
#define XE_MEMPOOL_DESC_VERSION   XE_MAKE_VERSION( 1, 0 )

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that will be automatically managed
/// @details
///     - Managed memory is automatically migrated between the host and memory
///       pool represented by... ?
///       - TBD: Comprehend multi-tile.
///       - TBD: Host or cross-device allcations?
/// @remarks _Analogues:_
///     - **cuMemAllocManaged**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - TODO
xe_result_t __xecall
  xeMemAllocManaged(
    xe_mempool_desc_t* desc,        ///< [in] pointer to memory pool descriptor
    xe_memory_flags_t flags,        ///< [in] flags specifying allocation and usage information
    size_t size,                    ///< [in] size in bytes to allocate
    uint32_t alignment,             ///< [in] minimum alignment in bytes for the allocation
    xe_device_ptr_t* ptr            ///< [out] pointer to managed allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory specific to a device 
/// @remarks _Analogues:_
///     - **cuMemAlloc**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - TODO
xe_result_t __xecall
  xeMemAlloc(
    xe_mempool_desc_t* desc,        ///< [in] pointer to memory pool descriptor
    xe_memory_flags_t flags,        ///< [in] flags specifying allocation and usage information
    size_t size,                    ///< [in] size in bytes to allocate
    uint32_t alignment,             ///< [in] minimum alignment in bytes for the allocation
    xe_device_ptr_t* ptr            ///< [out] pointer to managed allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated device memory or managed memory
/// @remarks _Analogues:_
///     - **cuMemFree**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - TODO
xe_result_t __xecall
  xeMemFree(
    xe_device_ptr_t ptr             ///< [in] pointer to memory to free
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory advice hints
XE_DECLARE_ENUM( xe_memory_advice_t )
{
    XE_MEMORY_ADVICE_TODO = 0       ///< TODO
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a memory range
/// @details
///     - TBD: likely will snap to page boundaries
///     - TBD: which memory advise hints could/should we support?
/// @remarks _Analogues:_
///     - **cuMemAdvise**
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - TODO
xe_result_t __xecall
  xeMemAdvise(
    xe_mempool_desc_t* desc,        ///< [in] pointer to memory pool descriptor to apply advice to
    xe_device_ptr_t ptr,            ///< [in] Pointer to the start of the memory range
    size_t size,                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice       ///< [in] Memory advice for the memory range
    );

#endif // _XE_MEMORY_H