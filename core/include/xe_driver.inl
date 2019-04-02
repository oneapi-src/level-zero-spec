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
* @file xe_driver.inl
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/driver.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_DRIVER_INL
#define _XE_DRIVER_INL
#if defined(__cplusplus)
#pragma once
#include "xe_driver.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDriverGetDeviceCount
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGetCount**
    /// 
    /// @returns
    ///     - uint32_t: number of devices available
    /// 
    /// @throws result_t
    inline uint32_t 
    Driver::GetDeviceCount(
        void
        )
    {
        // auto result = ::xeDriverGetDeviceCount( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Driver::GetDeviceCount");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDriverGetDevice
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuDeviceGet**
    ///     - clGetDeviceIDs
    /// 
    /// @returns
    ///     - ::device_handle_t: pointer to handle of device object created
    /// 
    /// @throws result_t
    inline device_handle_t 
    Driver::GetDevice(
        void
        )
    {
        // auto result = ::xeDriverGetDevice( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Driver::GetDevice");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDriverInit
    /// 
    /// @details
    ///     - Only one instance of a driver per process can be loaded.
    ///     - There is no reference tracking if multiple drivers are initialized.
    ///     - If this function is not called then all other functions will return
    ///       ::RESULT_ERROR_UNINITIALIZED.
    ///     - This function is thread-safe for scenarios where multiple libraries
    ///       may initialize the driver simultaneously.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuInit**
    /// 
    /// @throws result_t
    inline void 
    Driver::Init(
        void
        )
    {
        // auto result = ::xeDriverInit( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Driver::Init");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeDriverGetVersion
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
    inline uint32_t 
    Driver::GetVersion(
        void
        )
    {
        // auto result = ::xeDriverGetVersion( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Driver::GetVersion");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_DRIVER_INL
