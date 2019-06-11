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
* @file xet_tracing.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for API Tracing
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/tracing.yml
* @endcond
*
******************************************************************************/
#include "xet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **before** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == pCoreCbs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetDeviceSetTracingPrologue(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    xet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
    xet_extended_callbacks_t* pExtendedCbs          ///< [in][optional] pointer to table of 'extended' callback function
                                                    ///< pointers
    )
{
    auto pfnSetTracingPrologue = xet_lib::context.ddiTable.Device.pfnSetTracingPrologue;

#if _DEBUG
    if( nullptr == pfnSetTracingPrologue )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetTracingPrologue( hDevice, pCoreCbs, pExtendedCbs );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **after** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == pCoreCbs
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetDeviceSetTracingEpilogue(
    xet_device_handle_t hDevice,                    ///< [in] handle of the device
    xet_core_callbacks_t* pCoreCbs,                 ///< [in] pointer to table of 'core' callback function pointers
    xet_extended_callbacks_t* pExtendedCbs          ///< [in][optional] pointer to table of 'extended' callback function
                                                    ///< pointers
    )
{
    auto pfnSetTracingEpilogue = xet_lib::context.ddiTable.Device.pfnSetTracingEpilogue;

#if _DEBUG
    if( nullptr == pfnSetTracingEpilogue )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnSetTracingEpilogue( hDevice, pCoreCbs, pExtendedCbs );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the collection of callbacks to be executed **before** driver
    ///        execution.
    /// 
    /// @details
    ///     - The application only needs to set the function pointers it is
    ///       interested in receiving; all others should be 'nullptr'
    ///     - The application must ensure that no other threads are executing
    ///       functions for which the tracing functions are changing.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @throws result_t
    void __xecall
    Device::SetTracingPrologue(
        core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
        extended_callbacks_t* pExtendedCbs              ///< [in][optional] pointer to table of 'extended' callback function
                                                        ///< pointers
        )
    {
        auto result = static_cast<result_t>( ::xetDeviceSetTracingPrologue(
            reinterpret_cast<xet_device_handle_t>( getHandle() ),
            reinterpret_cast<xet_core_callbacks_t*>( pCoreCbs ),
            reinterpret_cast<xet_extended_callbacks_t*>( pExtendedCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Device::SetTracingPrologue" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the collection of callbacks to be executed **after** driver
    ///        execution.
    /// 
    /// @details
    ///     - The application only needs to set the function pointers it is
    ///       interested in receiving; all others should be 'nullptr'
    ///     - The application must ensure that no other threads are executing
    ///       functions for which the tracing functions are changing.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same device handle.
    /// 
    /// @throws result_t
    void __xecall
    Device::SetTracingEpilogue(
        core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
        extended_callbacks_t* pExtendedCbs              ///< [in][optional] pointer to table of 'extended' callback function
                                                        ///< pointers
        )
    {
        auto result = static_cast<result_t>( ::xetDeviceSetTracingEpilogue(
            reinterpret_cast<xet_device_handle_t>( getHandle() ),
            reinterpret_cast<xet_core_callbacks_t*>( pCoreCbs ),
            reinterpret_cast<xet_extended_callbacks_t*>( pExtendedCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xet::Device::SetTracingEpilogue" );
    }

} // namespace xet

namespace xet
{
} // namespace xet
