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
* @file xe_context.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Context
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/context.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a context.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateContext**
///     - cuCtxCreate
///     - cuCtxGetCurrent
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == phDevice
///         + nullptr == phContext
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeContextCreate(
    uint32_t numDevices,                            ///< [in] number of devices in phDevice
    xe_device_handle_t* phDevice,                   ///< [in][range(0, numDevices)] pointer to array of handle of the device
                                                    ///< objects
    xe_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
    )
{
    auto pfnCreate = xe_lib::lib.xeContext.pfnCreate;

#if _DEBUG
    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnCreate( numDevices, phDevice, phContext );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a context.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the context before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this context
///     - The application may **not** call this function from simultaneous
///       threads with the same context handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseContext**
///     - cuCtxDestroy
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hContext
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeContextDestroy(
    xe_context_handle_t hContext                    ///< [in] handle of context object to destroy
    )
{
    auto pfnDestroy = xe_lib::lib.xeContext.pfnDestroy;

#if _DEBUG
    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnDestroy( hContext );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Context::Context( 
        void
        )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a context.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateContext**
    ///     - cuCtxCreate
    ///     - cuCtxGetCurrent
    /// 
    /// @returns
    ///     - Context: pointer to handle of context object created
    /// 
    /// @throws result_t
    Context* __xecall
    Context::Create(
        uint32_t numDevices,                            ///< [in] number of devices in phDevice
        Device* phDevice                                ///< [in][range(0, numDevices)] pointer to array of pointer to the device
                                                        ///< objects
        )
    {
        // auto result = ::xeContextCreate( handle, numDevices, phDevice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::Create");

        return (Context*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a context.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the context before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this context
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same context handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseContext**
    ///     - cuCtxDestroy
    /// 
    /// @throws result_t
    void __xecall
    Context::Destroy(
        Context* pContext                               ///< [in] pointer to context object to destroy
        )
    {
        // auto result = ::xeContextDestroy( handle, pContext );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Context::Destroy");
    }

} // namespace xe

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::device_mem_alloc_flag_t to std::string
    std::string to_string( xe::Context::device_mem_alloc_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(xe::Context::device_mem_alloc_flag_t::DEFAULT) & bits )
            str += "xe::Context::device_mem_alloc_flag_t::DEFAULT | ";
        if( static_cast<uint32_t>(xe::Context::device_mem_alloc_flag_t::BIAS_CACHED) & bits )
            str += "xe::Context::device_mem_alloc_flag_t::BIAS_CACHED | ";
        if( static_cast<uint32_t>(xe::Context::device_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
            str += "xe::Context::device_mem_alloc_flag_t::BIAS_UNCACHED | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::host_mem_alloc_flag_t to std::string
    std::string to_string( xe::Context::host_mem_alloc_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(xe::Context::host_mem_alloc_flag_t::DEFAULT) & bits )
            str += "xe::Context::host_mem_alloc_flag_t::DEFAULT | ";
        if( static_cast<uint32_t>(xe::Context::host_mem_alloc_flag_t::BIAS_CACHED) & bits )
            str += "xe::Context::host_mem_alloc_flag_t::BIAS_CACHED | ";
        if( static_cast<uint32_t>(xe::Context::host_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
            str += "xe::Context::host_mem_alloc_flag_t::BIAS_UNCACHED | ";
        if( static_cast<uint32_t>(xe::Context::host_mem_alloc_flag_t::BIAS_WRITE_COMBINED) & bits )
            str += "xe::Context::host_mem_alloc_flag_t::BIAS_WRITE_COMBINED | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::memory_allocation_properties_version_t to std::string
    std::string to_string( xe::Context::memory_allocation_properties_version_t val )
    {
        switch( val )
        {
        case xe::Context::memory_allocation_properties_version_t::CURRENT:
            return std::string("xe::Context::memory_allocation_properties_version_t::CURRENT");
        };
        return std::string("xe::Context::memory_allocation_properties_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::memory_type_t to std::string
    std::string to_string( xe::Context::memory_type_t val )
    {
        switch( val )
        {
        case xe::Context::memory_type_t::UNKNOWN:
            return std::string("xe::Context::memory_type_t::UNKNOWN");
        case xe::Context::memory_type_t::HOST:
            return std::string("xe::Context::memory_type_t::HOST");
        case xe::Context::memory_type_t::DEVICE:
            return std::string("xe::Context::memory_type_t::DEVICE");
        case xe::Context::memory_type_t::SHARED:
            return std::string("xe::Context::memory_type_t::SHARED");
        };
        return std::string("xe::Context::memory_type_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::ipc_memory_flag_t to std::string
    std::string to_string( xe::Context::ipc_memory_flag_t val )
    {
        switch( val )
        {
        case xe::Context::ipc_memory_flag_t::NONE:
            return std::string("xe::Context::ipc_memory_flag_t::NONE");
        };
        return std::string("xe::Context::ipc_memory_flag_t::?");
    }


#endif // _DEBUG
