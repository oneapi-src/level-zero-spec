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
* @file xe_common.hpp
*
* @brief C++ wrapper of Intel Xe Driver API common types
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/common.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_COMMON_HPP
#define _XE_COMMON_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_all.h"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief naming consistency
    using float_t = ::float_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief naming consistency
    using double_t = ::double_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's device object
    class Device;
    using device_handle_t = Device*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command queue object
    class CommandQueue;
    using command_queue_handle_t = CommandQueue*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command list object
    class CommandList;
    using command_list_handle_t = CommandList*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command graph object
    class CommandGraph;
    using command_graph_handle_t = CommandGraph*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's fence object
    class Fence;
    using fence_handle_t = Fence*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's semaphore object
    class Semaphore;
    using semaphore_handle_t = Semaphore*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's event object
    class Event;
    using event_handle_t = Event*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's image object
    class Image;
    using image_handle_t = Image*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's module object
    class Module;
    using module_handle_t = Module*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of module's build log object
    class ModuleBuildLog;
    using module_build_log_handle_t = ModuleBuildLog*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's function object
    class Function;
    using function_handle_t = Function*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's sampler object
    class Sampler;
    using sampler_handle_t = Sampler*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief IPC handle to a memory allocation
    using ipc_mem_handle_t = ::xe_ipc_mem_handle_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Semaphore value type
    using semaphore_value_t = ::xe_semaphore_value_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Defines Return/Error codes
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **CUresult**
    enum class result_t
    {
        SUCCESS = 0,                                    ///< success
        NOT_READY = 1,                                  ///< synchronization primitive not signaled
        ERROR_UNINITIALIZED,                            ///< driver is not initialized
        ERROR_DEVICE_LOST,                              ///< device hung, reset, was removed, or driver update occurred
        ERROR_UNSUPPORTED,                              ///< device does not support feature requested
        ERROR_INVALID_PARAMETER,                        ///< invalid parameter provided
        ERROR_OUT_OF_HOST_MEMORY,                       ///< insufficient host memory to satisfy call
        ERROR_OUT_OF_DEVICE_MEMORY,                     ///< insufficient device memory to satisfy call
        ERROR_MODULE_BUILD_FAILURE,                     ///< error in building module
        ERROR_UNKNOWN = 0x7fffffff,                     ///< unknown or internal error

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_COMMON_HPP
