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
* @file xet_device.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/device.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_DEVICE_HPP
#define _XET_DEVICE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device group
    class DeviceGroup : public xe::DeviceGroup
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Re-use the existing DDI table definition for 'core' callbacks
        using core_callbacks_t = xe_dditable_t;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Re-use the existing DDI table definition for 'extended' callbacks
        using extended_callbacks_t = xex_dditable_t;


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using xe::DeviceGroup::DeviceGroup;

        ~DeviceGroup( void ) = default;

        DeviceGroup( DeviceGroup const& other ) = delete;
        void operator=( DeviceGroup const& other ) = delete;

        DeviceGroup( DeviceGroup&& other ) = delete;
        void operator=( DeviceGroup&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

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
        ///       threads with the same device group handle.
        /// @throws result_t
        void __xecall
        SetTracingPrologue(
            core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
            extended_callbacks_t* pExtendedCbs = nullptr    ///< [in][optional] pointer to table of 'extended' callback function
                                                            ///< pointers
            );

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
        ///       threads with the same device group handle.
        /// @throws result_t
        void __xecall
        SetTracingEpilogue(
            core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
            extended_callbacks_t* pExtendedCbs = nullptr    ///< [in][optional] pointer to table of 'extended' callback function
                                                            ///< pointers
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device : public xe::Device
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using xe::Device::Device;

        ~Device( void ) = default;

        Device( Device const& other ) = delete;
        void operator=( Device const& other ) = delete;

        Device( Device&& other ) = delete;
        void operator=( Device&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Activates metric groups.
        /// 
        /// @details
        ///     - MetricGroup must be active until MetricQueryGetDeta and
        ///       ::MetricTracerClose.
        ///     - Conflicting metric groups cannot be activated, in such case tha call
        ///       would fail.
        /// @throws result_t
        void __xecall
        ActivateMetricGroups(
            uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
            MetricGroup** ppMetricGroups                    ///< [in][range(0, count)] handles of the metric groups to activate. NULL
                                                            ///< to deactivate.
            );

    };

} // namespace xet

namespace xet
{
} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_DEVICE_HPP
