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
* @file xe_driver.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/driver.yml
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the Xe driver and must be called before any other API
///        function.
/// 
/// @details
///     - If this function is not called then all other functions will return
///       ::XE_RESULT_ERROR_UNINITIALIZED.
///     - Only one instance of a driver per process will be initialized.
///     - This function is thread-safe for scenarios where multiple libraries
///       may initialize the driver simultaneously.
/// 
/// @remarks
///   _Analogues_
///     - **cuInit**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
xe_result_t __xecall
xeInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto result = xe_lib::lib.Init();
    if( XE_RESULT_SUCCESS != result )
        return result;

    auto pfnInit = xe_lib::lib.ddiTable.Global.pfnInit;

#if _DEBUG
    if( nullptr == pfnInit )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnInit( flags );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the current version of the installed driver for the specified
///        device group.
/// 
/// @details
///     - The driver version is a non-zero, monotonically increasing value where
///       higher values always indicate a more recent version.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDriverGetVersion**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDeviceGroup
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceGroupGetDriverVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of device group
    uint32_t* version                               ///< [out] driver version
    )
{
    auto pfnGetDriverVersion = xe_lib::lib.ddiTable.DeviceGroup.pfnGetDriverVersion;

#if _DEBUG
    if( nullptr == pfnGetDriverVersion )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnGetDriverVersion( hDeviceGroup, version );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize the Xe:: driver and must be called before any other API
    ///        function.
    /// 
    /// @details
    ///     - If this function is not called then all other functions will return
    ///       ::RESULT_ERROR_UNINITIALIZED.
    ///     - Only one instance of a driver per process will be initialized.
    ///     - This function is thread-safe for scenarios where multiple libraries
    ///       may initialize the driver simultaneously.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuInit**
    /// 
    /// @throws result_t
    void __xecall
    Init(
        init_flag_t flags                               ///< [in] initialization flags
        )
    {
        // auto result = ::xeInit( handle, flags );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "Init");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the current version of the installed driver for the specified
    ///        device group.
    /// 
    /// @details
    ///     - The driver version is a non-zero, monotonically increasing value where
    ///       higher values always indicate a more recent version.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDriverGetVersion**
    /// 
    /// @returns
    ///     - uint32_t: driver version
    /// 
    /// @throws result_t
    uint32_t __xecall
    DeviceGroup::GetDriverVersion(
        void
        )
    {
        // auto result = ::xeDeviceGroupGetDriverVersion( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::DeviceGroup::GetDriverVersion");

        return uint32_t{};
    }

} // namespace xe

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts init_flag_t to std::string
    std::string to_string( xe::init_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );
        if( 0 == bits ) return std::string("{}");
        std::string str;
        if( static_cast<uint32_t>(xe::init_flag_t::NONE) & bits )
            str += "xe::init_flag_t::NONE | ";
        if( static_cast<uint32_t>(xe::init_flag_t::GPU_ONLY) & bits )
            str += "xe::init_flag_t::GPU_ONLY | ";
        return "{ " + str.substr(0, str.size() - 3) + " }";
    }

#endif // _DEBUG
