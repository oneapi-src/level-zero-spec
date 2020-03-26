/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_device.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Device
 *
 */
#ifndef _ZES_DEVICE_HPP
#define _ZES_DEVICE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZES_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zes
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for driver instance
    class Driver : public ze::Driver
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Driver::Driver;

        ~Driver( void ) = default;

        Driver( Driver const& other ) = delete;
        void operator=( Driver const& other ) = delete;

        Driver( Driver&& other ) = delete;
        void operator=( Driver&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device : public ze::Device
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Device::Device;

        ~Device( void ) = default;

        Device( Device const& other ) = delete;
        void operator=( Device const& other ) = delete;

        Device( Device&& other ) = delete;
        void operator=( Device&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

    };

} // namespace zes

namespace zes
{
} // namespace zes
#endif // defined(__cplusplus)
#endif // _ZES_DEVICE_HPP
