/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_device.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Device
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/device.yml
 * @endcond
 *
 */
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
        ///       ::xetMetricTracerClose.
        ///     - Conflicting metric groups cannot be activated, in such case tha call
        ///       would fail.
        /// @throws result_t
        void __xecall
        ActivateMetricGroups(
            uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
            MetricGroup** ppMetricGroups = nullptr          ///< [in][optional][range(0, count)] handles of the metric groups to
                                                            ///< activate. NULL to deactivate.
            );

    };

} // namespace xet

namespace xet
{
} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_DEVICE_HPP
