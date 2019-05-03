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
* @file xet_power.cpp
*
* @brief Intel Xe Level-Zero Tool APIs for Power
*
* DO NOT EDIT: generated from /scripts/tools/power.yml
*
******************************************************************************/
#if defined(XET_CPP)
#include "../include/xet_power.hpp"
#else
#include "../include/xet_power.h"
#endif
#if !defined(XET_NULLDRV)
#include "power.h"
#endif

#include <exception>    // @todo: move to common and/or precompiled header
#include <new>

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize power management features
/// 
/// @details
///     - Initializes internal structures to support power management features.
/// 
/// @remarks
///   _Analogues_
///     - **nvmlInit**
///     - **rsmi_init**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hDevice
///         + nullptr == pPowerHandle
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {a404cb701cd912894f627de52e4c8a9187ebe36e2c378c223ed0d4586165e11d}
///
__xedllexport xe_result_t __xecall
xetDevicePowerInit(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t flags,                                 ///< [in] bitfield of ::xet_power_init_flags_t
    xet_power_handle_t* pPowerHandle                ///< [out] handle for accessing power features of the device
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pPowerHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle(hDevice)->powerInit(flags, pPowerHandle);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Removes access to power management features
/// 
/// @remarks
///   _Analogues_
///     - **nvmlShutdown**
///     - **rsmi_shut_down**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b232ea6c58649237a037b203ed32b8b70e08cc7a0d50cc55310b8d1cb0be947c}
///
__xedllexport xe_result_t __xecall
xetDevicePowerShutdown(
    xet_power_handle_t hPower                       ///< [in] handle of the power object
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerShutdown(hPower);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current average power limit information for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {3b4449758678c2a04c962c674750d3ae20f841b3d18732988dad8599bac3bbd3}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [out] information about the average power limit
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimit ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetAveragePowerLimit(hPower, pLimit);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current burst power limit information for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {952166e5956173840e65e91d77dde5baea150672a542ea004ce25dff1b66d28b}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [out] information about the burst power limit
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimit ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetBurstPowerLimit(hPower, pLimit);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current peak power limit information for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {db79da6715d7c925f63cd55b6468a8e886c7cde2504d2c97cdbbb4a0bafd38a6}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [out] information about the peak power limit
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimit ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetPeakPowerLimit(hPower, pLimit);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get all current power limits for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {d946009eab1a7f8afa9a3aab53b2479677c0830511bb24299d275bf433dfe422}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetAllPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the average/burst/peak power limits
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimits ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetAllPowerLimits(hPower, pLimits);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get default power limits for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b4e446a08a701e5039417810002aadf62a90e40414ddb8301e0190216b9e8a13}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetDefaultPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [out] information about the default average/burst/peak power limits
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimits ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetDefaultPowerLimits(hPower, pLimits);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the average power limit for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {f433bdf3444120c099d47623ae86516fb7dc3823e6bee5532eb8f04d805856c4}
///
__xedllexport xe_result_t __xecall
xetDevicePowerSetAveragePowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_average_limit_t* pLimit               ///< [in] information about the average power limit
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimit ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerSetAveragePowerLimit(hPower, pLimit);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the burst power limit for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {d256fbde406ef390ef20627ba168f687670f2530df779c1662d38f6a48744f68}
///
__xedllexport xe_result_t __xecall
xetDevicePowerSetBurstPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_burst_limit_t* pLimit                 ///< [in] information about the burst power limit
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimit ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerSetBurstPowerLimit(hPower, pLimit);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the peak power limit for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimit
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {89bef0eaa517c02c2ad98b4225d43328d0ffebb225e7f37ec695c04b5675137c}
///
__xedllexport xe_result_t __xecall
xetDevicePowerSetPeakPowerLimit(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_peak_limit_t* pLimit                  ///< [in] information about the peak power limit
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimit ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerSetPeakPowerLimit(hPower, pLimit);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the average/burst/peak power limits for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pLimits
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {5548d42f3c752c7e22ea0a90d1112f72384edb783713278b191a8b46bef780b9}
///
__xedllexport xe_result_t __xecall
xetDevicePowerSetPowerLimits(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_power_limits_t* pLimits                     ///< [in] information about the average/burst/peak power limits
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pLimits ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerSetPowerLimits(hPower, pLimits);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
/// 
/// @details
///     - Average power = delta(energyMillijoules) / delta(timeMilliseconds)
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pEnergyMillijoules
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {be946648d872ef2ded827822314afc4b9c755e9f40577cd9964cb88e8457b55c}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetEnergyCounter(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint64_t* pEnergyMillijoules                    ///< [out] the energy counter in millijoules
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pEnergyMillijoules ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetEnergyCounter(hPower, pEnergyMillijoules);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current Turbo mode for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pTurboMode
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {1382fc86ba78d1c184e8b3109c80b3667f1236d01bc7ac5930a59e5bfe2ec07a}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t* pTurboMode                    ///< [out] turbo mode currently in effect
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pTurboMode ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetTurboMode(hPower, pTurboMode);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current Turbo mode for a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {d20931d5688a597cd82408b10ff8768b080d82d6432300d22ddcae4976e411f9}
///
__xedllexport xe_result_t __xecall
xetDevicePowerSetTurboMode(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    xet_turbo_mode_t pTurboMode                     ///< [in] new turbo mode
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerSetTurboMode(hPower, pTurboMode);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the number of frequency domains on the device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pNumFreqDomains
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {fe9ddf15d352d38a404c31ae03f50cffa009ed6499558036604fafc8b02e4fa2}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFreqDomainCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pNumFreqDomains                       ///< [out] the number of frequency domains
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pNumFreqDomains ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFreqDomainCount(hPower, pNumFreqDomains);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get a handle to a frequency domain
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == phFreqDomain
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {d2d36368a00867ea871eb49dc1f6c9d4b9f420f6e7a74923fcb0391f485c8fd4}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFreqDomainGetHandle(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t ordinal,                               ///< [in] frequency domain index [0 .. ::xetPowerFreqDomainCount - 1]
    xet_freq_domain_handle_t* phFreqDomain          ///< [out] pointer to handle of frequency domain object
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == phFreqDomain ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFreqDomainGetHandle(hPower, ordinal, phFreqDomain);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the properties for a frequency domain
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFreqDomain
///         + nullptr == pFreqDomainProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {09a81e773d28ffcda7ba9293ed6edbc8aeaec277a2fc35fee6e5c243cea603af}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFreqDomainGetProperties(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_freq_domain_properties_t* pFreqDomainProperties ///< [out] pointer to properties for the frequency domain
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hFreqDomain ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFreqDomainProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFreqDomainGetProperties(hFreqDomain, pFreqDomainProperties);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get supported frequency points for frequency domains with clock type
///        ::XET_CLOCK_PLL
/// 
/// @details
///     - The total available list of frequencies can be found in
///       ::xet_freq_domain_properties_t.numClockPoints.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFreqDomain
///         + nullptr == pClocksMHz
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {8f9dc2f38aab993de3874716af5ecf7bb2c12a6baa75c47a40c5dc81c99436a1}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFreqDomainGetSupportedClocks(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockPoints,                        ///< [in] number of elements in pClocksMHz
    uint32_t* pClocksMHz                            ///< [out] pointer to array of frequencies
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hFreqDomain ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pClocksMHz ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFreqDomainGetSupportedClocks(hFreqDomain, numClockPoints, pClocksMHz);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get supported frequency dividers for frequency domains with clock type
///        ::XET_CLOCK_DIVIDER
/// 
/// @details
///     - The total available list of frequencies can be found in
///       ::xet_freq_domain_properties_t.numClockDividers.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFreqDomain
///         + nullptr == pDividers
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {e172022f4e84fd5ee36d2b1e1b4e60e59d0eb00ce5aced7b8cf12fa5c897558b}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFreqDomainGetSupportedClockDividers(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t numClockDividers,                      ///< [in] number of elements in pDividers
    xet_clock_divider_t* pDividers                  ///< [out] pointer to array of dividers
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hFreqDomain ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pDividers ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFreqDomainGetSupportedClockDividers(hFreqDomain, numClockDividers, pDividers);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the frequency range for a frequency domain with clock type
///        ::XET_CLOCK_PLL.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFreqDomain
///         + nullptr == pMinClockMHz
///         + nullptr == pMaxClockMHz
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {de487ca738b799f26abff1b6816b7675d595d6c5dd3366368e45e55766bdb36d}
///
__xedllexport xe_result_t __xecall
xetDevicexetPowerFreqDomainGetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pMinClockMHz,                         ///< [out] min clock frequency in units of MHz
    uint32_t* pMaxClockMHz                          ///< [out] max clock frequency in units of MHz
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hFreqDomain ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pMinClockMHz ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pMaxClockMHz ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->$tPowerFreqDomainGetClockRange(hFreqDomain, pMinClockMHz, pMaxClockMHz);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the frequency range for a frequency domain with clock type
///        ::XET_CLOCK_PLL.
/// 
/// @details
///     - Turbo (dynamic hardware frequency management) will select frequencies
///       between this range based on the current Turbo mode in effect.
///     - Setting minClockMHz = maxClockMHz will fix the frequency for that
///       frequency domain.
///     - Setting minClockMHz = 0 will instruct the hardware to use the default
///       min value.
///     - Setting maxClockMHz = 0 will instruct the hardware to use the default
///       max value.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFreqDomain
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b5124ee671b829e6e8f6ff2d0fe9c930a78442b06a1dd721f92bef583f5a9ae2}
///
__xedllexport xe_result_t __xecall
xetDevicexetPowerFreqDomainSetClockRange(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t minClockMHz,                           ///< [in] min clock frequency in units of MHz
    uint32_t maxClockMHz                            ///< [in] max clock frequency in units of MHz
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hFreqDomain ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->$tPowerFreqDomainSetClockRange(hFreqDomain, minClockMHz, maxClockMHz);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency divider for a frequency domain with clock type
///        ::XET_CLOCK_DIVIDER
/// 
/// @details
///     - This disables dynamic frequency divider management running on the
///       hardware.
///     - Setting pClockDivider to nullptr will enable dynamic frequency divider
///       management.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFreqDomain
///         + nullptr == pClockDividerRequest
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {804518977b67afcd474e636ce06ed8c6507469b1c4f4d74f3b16d5ff49950364}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFreqDomainSetClockDivider(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    xet_clock_divider_t* pClockDividerRequest       ///< [out] pointer to frequency divider request
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hFreqDomain ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pClockDividerRequest ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFreqDomainSetClockDivider(hFreqDomain, pClockDividerRequest);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hFreqDomain
///         + nullptr == pFreqRequestMHz
///         + nullptr == pFreqResolvedMHz
///         + nullptr == pFreqThrottleReasons
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {33281dc0a7e1ede0b6cb6afd143ff2d66ca28889fa6e0c6493e01dbe38c9efa9}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetCurrentFrequency(
    xet_freq_domain_handle_t hFreqDomain,           ///< [in] handle of the frequency domain
    uint32_t* pFreqRequestMHz,                      ///< [out] current frequency in MHz requested by the driver
    uint32_t* pFreqResolvedMHz,                     ///< [out] the actual frequency in MHz
    xet_freq_throttle_reasons_t* pFreqThrottleReasons   ///< [out] the reason the resolved frequency is lower than the request
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hFreqDomain ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFreqRequestMHz ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFreqResolvedMHz ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFreqThrottleReasons ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetCurrentFrequency(hFreqDomain, pFreqRequestMHz, pFreqResolvedMHz, pFreqThrottleReasons);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get number of fans on the device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pFanCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b7ff9171fa156748775caeb63ea402ea5a8c8e692f66dd8522dc9219d214aced}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFanCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pFanCount                             ///< [out] the number of fans on the device
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFanCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFanCount(hPower, pFanCount);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan properties for one of the fans on a device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pFanProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {71f0406064da6707b05d7254045018e9dc563200108fda68ac933f486e7e1b23}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFanGetProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xet_fan_properties_t* pFanProperties            ///< [out] pointer to storage for fan properties
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFanProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFanGetProperties(hPower, fanIndex, pFanProperties);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan speed table
/// 
/// @details
///     - Set pFanSpeedTable = nullptr to find out the current number of fan
///       speed points in the table.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pNumFanPoints
///         + nullptr == pFanPoints
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {fd58b6535039b2cc1ab061f8201fc6aca42ccd26850363c06340a4db964cd294}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFanGetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
    uint32_t* pNumFanPoints,                        ///< [in/out] input number of elements in pFanSpeedTable array; output
                                                    ///< number of elements returned
    xet_fan_point_t* pFanPoints                     ///< [out] pointer to an array of temperature/fan-speed points
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pNumFanPoints ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFanPoints ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFanGetSpeedTable(hPower, fanIndex, fanSpeedInRpm, pNumFanPoints, pFanPoints);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan speed table
/// 
/// @details
///     - Use ::xetPowerGetFanCapabilities to determine acceptable units for fan
///       speed (percent, RPM).
///     - Fan points should be ordered according to increasing temperature.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pFanPoints
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {bdf979052f32fe2dbac060c7db55868afdcd88425b8244af061340aae12a4c26}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFanSetSpeedTable(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t fanIndex,                              ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFanPoints,                          ///< [in] number of points in pFanSpeedTable array
    xet_fan_point_t* pFanPoints                     ///< [in] pointer to an array of temperature/fan-speed points
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFanPoints ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFanSetSpeedTable(hPower, fanIndex, numFanPoints, pFanPoints);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current fan speeds
/// 
/// @details
///     - The array pFanSpeed must contain at least numFans entries.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pFanSpeed
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {f0e4334eb3a074297f582b47441c6e72f742e438125fe2768823e7b2fe9d4327}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFanGetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xe_bool_t fanSpeedInRpm,                        ///< [in] true will request fan speeds in RPM, otherwise in percentage
    xet_fan_speed_info_t* pFanSpeed                 ///< [out] pointer to an array of current fan speeds
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFanSpeed ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFanGetSpeed(hPower, startFanIndex, numFans, fanSpeedInRpm, pFanSpeed);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan speeds
/// 
/// @details
///     - Use t_fan_speed_info_t.fanSpeedMode to set whether the speed should be
///       fixed or dynamically controlled
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pFanSpeed
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {8014ca14c29fe661b02647e1b7922563d98f1172c3e8d88759ae29ecaccabd95}
///
__xedllexport xe_result_t __xecall
xetDevicePowerFanSetSpeed(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startFanIndex,                         ///< [in] fan index [0 .. ::xetPowerFanCount - 1]
    uint32_t numFans,                               ///< [in] pFanSpeed will contain results for fan index
                                                    ///< (startFanIndex)..(startFanIndex + numFans - 1)
    xet_fan_speed_info_t* pFanSpeed                 ///< [in] pointer to an array of current fan speeds
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pFanSpeed ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerFanSetSpeed(hPower, startFanIndex, numFans, pFanSpeed);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get number of temperature sensors on the device
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pSensorCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b0912099d1ee2419d11d0d4f9a3976747827d0fc0d883df63b31405a1ea763ca}
///
__xedllexport xe_result_t __xecall
xetDevicePowerTemperatureSensorCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pSensorCount                          ///< [out] the number of temperature sensors on the device
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pSensorCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerTemperatureSensorCount(hPower, pSensorCount);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperatures sensor properties
/// 
/// @details
///     - Temperature sensor index 0 is special - it gives the maximum
///       temperature across all sensors
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {6bf12538fac0640f7321b9f4491a4dbc2f3194e2aebc0ed8631f3926dba0983f}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetTemperatureProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    xet_temperature_properties_t* pProperties       ///< [out] pointer to properties for this sensor
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetTemperatureProperties(hPower, sensorIndex, pProperties);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current temperatures
/// 
/// @details
///     - Temperature sensor index 0 is special - it gives the maximum
///       temperature across all sensors
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pTemperatures
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {c3f0231ebff9acb2c858a318c27872a150b9dda39898fc65eefd78ebb749cd68}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetTemperature(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startSensorIndex,                      ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint32_t numSensors,                            ///< [in] pTemperatures will contain results for sensors index
                                                    ///< (startSensorIndex)..(startSensorIndex + numSensors - 1)
    uint16_t* pTemperatures                         ///< [out] pointer to an array of temperatures in units of degrees celsius
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pTemperatures ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetTemperature(hPower, startSensorIndex, numSensors, pTemperatures);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature threshold
/// 
/// @details
///     - Check ::xet_temperature_properties_t.canChangeThreshold to determine
///       if the threshold can be changed.
///     - On most systems, there is only one threshold and sensorIndex should be
///       0.
///     - **This is an overclocking feature and will void device warranty**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {3159f44c098f5900e634b619a73c114a93235578cb7d277f8e10b78a8221a72f}
///
__xedllexport xe_result_t __xecall
xetDevicePowerSetTemperatureThreshold(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t sensorIndex,                           ///< [in] sensor index [0 .. ::xetPowerTemperatureSensorCount]
    uint16_t maxTemperature                         ///< [in] temperature threshold in degrees celsius beyond which frequency
                                                    ///< will be throttled
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerSetTemperatureThreshold(hPower, sensorIndex, maxTemperature);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get number of activity counters
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pActivityCount
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {dcd9c3bb949a50f306b553227ca4e82841f86e296bb99d57af8721b7b426eb66}
///
__xedllexport xe_result_t __xecall
xetDevicePowerActivityCount(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t* pActivityCount                        ///< [out] the number of activity counters on the device
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pActivityCount ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerActivityCount(hPower, pActivityCount);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get activity counter properties
/// 
/// @details
///     - Activity counter index 0 is special - it acculates activity across all
///       blocks.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pProperties
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {b657facf779485529c321b0407b965eaed21bd436ef4489123f45c2f2bda69fb}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetActivityProperties(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t activityIndex,                         ///< [in] activity counter index [0 .. ::xetPowerActivityCount]
    xet_activity_properties_t* pProperties          ///< [out] pointer to properties for this activity counter
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetActivityProperties(hPower, activityIndex, pProperties);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get activity counters
/// 
/// @details
///     - Activity counter index 0 is special - it acculates activity across all
///       blocks.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hPower
///         + nullptr == pCounters
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {9967af787ead5192222ef3a289dacde7a9b3d70d85c24732ced031211e09b24d}
///
__xedllexport xe_result_t __xecall
xetDevicePowerGetActivityCounters(
    xet_power_handle_t hPower,                      ///< [in] handle of the power object
    uint32_t startCounterIndex,                     ///< [in] sensor index [0 .. ::xetPowerActivityCount]
    uint32_t numCounters,                           ///< [in] pCounters will contain results for activity counter index
                                                    ///< (startCounterIndex)..(startCounterIndex + numCounters - 1)
    xet_activity_counters_t* pCounters              ///< [out] pointer to an array of activity counter data
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;
            // Check parameters
            if( nullptr == hPower ) return XE_RESULT_ERROR_INVALID_PARAMETER;
            if( nullptr == pCounters ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin
#if defined(XE_NULLDRV)
        return XE_RESULT_SUCCESS;
#else
        return L0::Device::fromHandle()->powerGetActivityCounters(hPower, startCounterIndex, numCounters, pCounters);
#endif
        /// @end
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

