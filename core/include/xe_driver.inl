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
    /// @brief C++ wrapper for ::xeInit
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
    Init(
        init_flag_t flags                               ///< [in] initialization flags
        )
    {
        // auto result = ::xeInit( handle, flags );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "Init");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeGetDriverVersion
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
    GetDriverVersion(
        void
        )
    {
        // auto result = ::xeGetDriverVersion( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "GetDriverVersion");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_DRIVER_INL
