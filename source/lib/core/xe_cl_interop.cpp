/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_cl_interop.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for OpenCL Interopability
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/cl_interop.yml
 * @endcond
 *
 */
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL memory with 'One API'
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceRegisterCLMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the memory
    cl_mem mem,                                     ///< [in] the OpenCL memory to register
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    auto pfnRegisterCLMemory = xe_lib::context.ddiTable.Device.pfnRegisterCLMemory;
    if( nullptr == pfnRegisterCLMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnRegisterCLMemory( hDevice, context, mem, ptr );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL program with 'One API'
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == phModule
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceRegisterCLProgram(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the program
    cl_program program,                             ///< [in] the OpenCL program to register
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    )
{
    auto pfnRegisterCLProgram = xe_lib::context.ddiTable.Device.pfnRegisterCLProgram;
    if( nullptr == pfnRegisterCLProgram )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnRegisterCLProgram( hDevice, context, program, phModule );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL command queue with 'One API'
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == phCommandQueue
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::XE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
xe_result_t __xecall
xeDeviceRegisterCLCommandQueue(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the command queue
    cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    auto pfnRegisterCLCommandQueue = xe_lib::context.ddiTable.Device.pfnRegisterCLCommandQueue;
    if( nullptr == pfnRegisterCLCommandQueue )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
}
#endif // XE_ENABLE_OCL_INTEROP

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL memory with 'One API'
    /// 
    /// @returns
    ///     - void*: pointer to device allocation
    /// 
    /// @throws result_t
    void* __xecall
    Device::RegisterCLMemory(
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem                                      ///< [in] the OpenCL memory to register
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::xeDeviceRegisterCLMemory(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            context,
            mem,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::RegisterCLMemory" );

        return ptr;
    }
#endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL program with 'One API'
    /// 
    /// @returns
    ///     - Module*: pointer to handle of module object created
    /// 
    /// @throws result_t
    Module* __xecall
    Device::RegisterCLProgram(
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program                              ///< [in] the OpenCL program to register
        )
    {
        xe_module_handle_t hModule;

        auto result = static_cast<result_t>( ::xeDeviceRegisterCLProgram(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            context,
            program,
            &hModule ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::RegisterCLProgram" );

        Module* pModule = nullptr;

        try
        {
            pModule = new Module( reinterpret_cast<module_handle_t>( hModule ), this, m_desc );
        }
        catch( std::bad_alloc& )
        {
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Device::RegisterCLProgram" );
        }

        return pModule;
    }
#endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL command queue with 'One API'
    /// 
    /// @returns
    ///     - CommandQueue*: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* __xecall
    Device::RegisterCLCommandQueue(
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
        )
    {
        xe_command_queue_handle_t hCommandQueue;

        auto result = static_cast<result_t>( ::xeDeviceRegisterCLCommandQueue(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            context,
            command_queue,
            &hCommandQueue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::RegisterCLCommandQueue" );

        CommandQueue* pCommandQueue = nullptr;

        try
        {
            pCommandQueue = new CommandQueue( reinterpret_cast<command_queue_handle_t>( hCommandQueue ), this, m_desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandQueue;
            pCommandQueue = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "xe::Device::RegisterCLCommandQueue" );
        }

        return pCommandQueue;
    }
#endif // XE_ENABLE_OCL_INTEROP

} // namespace xe

namespace xe
{
} // namespace xe
