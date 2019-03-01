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
* @file xe_memory.hpp
*
* @brief C++ wrapper of Intel Xe Driver APIs for Memory
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/memory.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_MEMORY_HPP
#define _XE_MEMORY_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle to a memory allocator
    using mem_allocator_handle_t = ::xe_mem_allocator_handle_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported device memory allocation flags
    enum class device_mem_alloc_flag_t
    {
        DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
        BIAS_CACHED = XE_BIT( 0 ),                      ///< device should cache allocation
        BIAS_UNCACHED = XE_BIT( 1 ),                    ///< device should not cache allocation (UC)

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported host memory allocation flags
    enum class host_mem_alloc_flag_t
    {
        DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
        BIAS_CACHED = XE_BIT( 0 ),                      ///< host should cache allocation
        BIAS_UNCACHED = XE_BIT( 1 ),                    ///< host should not cache allocation (UC)
        BIAS_WRITE_COMBINED = XE_BIT( 2 ),              ///< host memory should be allocated write-combined (WC)

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Memory allocation type
    enum class memory_type_t
    {
        UNKNOWN = 0,                                    ///< the memory pointed to was not allocated by $Xx
        HOST,                                           ///< the memory pointed to is a host allocation
        DEVICE,                                         ///< the memory pointed to is a device allocation
        SHARED,                                         ///< the memory pointed to is a shared ownership allocation

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported memory allocation query properties
    enum class memory_property_t
    {
        TYPE = 0,                                       ///< returns the type of allocated memory, see ::memory_type_t

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported IPC memory flags
    enum class ipc_memory_flag_t
    {
        NONE = 0,                                       ///< No special flags

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_MEMORY_HPP
