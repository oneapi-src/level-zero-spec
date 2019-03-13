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
* @file xe_driver.hpp
*
* @brief C++ wrapper of Intel Xe Driver APIs
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/driver.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_DRIVER_HPP
#define _XE_DRIVER_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for driver
    class Driver
    {
    protected:

    public:

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xe_init_flag_t
        enum class init_flag_t
        {
            NONE = 0,                                       ///< default behavior

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDriverGetDeviceCount
        /// @returns
        ///     - uint32_t: number of devices available
        /// 
        /// @throws result_t
        inline static uint32_t
        GetDeviceCount(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDriverGetDeviceUniqueIds
        /// @returns
        ///     - device_uuid_t: pointer to an array of unique ids for devices. Caller must supply array.
        /// 
        /// @throws result_t
        inline static device_uuid_t
        GetDeviceUniqueIds(
            uint32_t count                                  ///< [in] size of device unique ids array. Typically, this will be
                                                            ///< ${x}DeviceGetCount.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDriverGetDevice
        /// @returns
        ///     - device_handle_t: pointer to handle of device object created
        /// 
        /// @throws result_t
        inline static device_handle_t
        GetDevice(
            device_uuid_t* pUUID                            ///< [in] unique id of device to retrieve. Use ${x}DriverGetDeviceUniqueIds
                                                            ///< to obtain a unique Id.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDriverInit
        /// @throws result_t
        inline static void
        Init(
            init_flag_t flags                               ///< [in] initialization flags
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeDriverGetVersion
        /// @returns
        ///     - uint32_t: driver version
        /// 
        /// @throws result_t
        inline static uint32_t
        GetVersion(
            void
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_DRIVER_HPP
