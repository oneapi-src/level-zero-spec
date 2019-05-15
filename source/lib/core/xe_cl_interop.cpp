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
* @file xe_cl_interop.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for OpenCL Interopability
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cl_interop.yml
* @endcond
*
******************************************************************************/
#include "xe_api.hpp"
#include "xe_ddi.h"
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL memory with Xe
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
    return XE_RESULT_SUCCESS;
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL program with Xe
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
    return XE_RESULT_SUCCESS;
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief Registers OpenCL command queue with Xe
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
    return XE_RESULT_SUCCESS;
}
#endif // XE_ENABLE_OCL_INTEROP

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL memory with Xe::
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
        // auto result = ::xeDeviceRegisterCLMemory( handle, context, mem );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLMemory");

        return (void*)0;
    }
#endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL program with Xe::
    /// 
    /// @returns
    ///     - Module: pointer to handle of module object created
    /// 
    /// @throws result_t
    Module* __xecall
    Device::RegisterCLProgram(
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program                              ///< [in] the OpenCL program to register
        )
    {
        // auto result = ::xeDeviceRegisterCLProgram( handle, context, program );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLProgram");

        return (Module*)0;
    }
#endif // XE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
    /// @brief Registers OpenCL command queue with Xe::
    /// 
    /// @returns
    ///     - CommandQueue: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* __xecall
    Device::RegisterCLCommandQueue(
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
        )
    {
        // auto result = ::xeDeviceRegisterCLCommandQueue( handle, context, command_queue );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Device::RegisterCLCommandQueue");

        return (CommandQueue*)0;
    }
#endif // XE_ENABLE_OCL_INTEROP

} // namespace xe

#ifdef _DEBUG
#endif // _DEBUG
