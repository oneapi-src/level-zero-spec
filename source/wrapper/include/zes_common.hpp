/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_common.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Sysman API common types
 *
 */
#ifndef _ZES_COMMON_HPP
#define _ZES_COMMON_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZES_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zes
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle to a driver instance
    class Driver;
    struct _driver_handle_t;
    using driver_handle_t = _driver_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of device object
    class Device;
    struct _device_handle_t;
    using device_handle_t = _device_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for accessing System Resource Management features of a device
    class Sysman;
    struct _sysman_handle_t;
    using sysman_handle_t = _sysman_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device scheduler queue
    class SysmanScheduler;
    struct _sysman_sched_handle_t;
    using sysman_sched_handle_t = _sysman_sched_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device performance factors
    class SysmanPerformanceFactor;
    struct _sysman_perf_handle_t;
    using sysman_perf_handle_t = _sysman_perf_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device power domain
    class SysmanPower;
    struct _sysman_pwr_handle_t;
    using sysman_pwr_handle_t = _sysman_pwr_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device frequency domain
    class SysmanFrequency;
    struct _sysman_freq_handle_t;
    using sysman_freq_handle_t = _sysman_freq_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device engine group
    class SysmanEngine;
    struct _sysman_engine_handle_t;
    using sysman_engine_handle_t = _sysman_engine_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device standby control
    class SysmanStandby;
    struct _sysman_standby_handle_t;
    using sysman_standby_handle_t = _sysman_standby_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device firmware
    class SysmanFirmware;
    struct _sysman_firmware_handle_t;
    using sysman_firmware_handle_t = _sysman_firmware_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device memory module
    class SysmanMemory;
    struct _sysman_mem_handle_t;
    using sysman_mem_handle_t = _sysman_mem_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman fabric port
    class SysmanFabricPort;
    struct _sysman_fabric_port_handle_t;
    using sysman_fabric_port_handle_t = _sysman_fabric_port_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device temperature sensor
    class SysmanTemperature;
    struct _sysman_temp_handle_t;
    using sysman_temp_handle_t = _sysman_temp_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device power supply
    class SysmanPsu;
    struct _sysman_psu_handle_t;
    using sysman_psu_handle_t = _sysman_psu_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device fan
    class SysmanFan;
    struct _sysman_fan_handle_t;
    using sysman_fan_handle_t = _sysman_fan_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device LED
    class SysmanLed;
    struct _sysman_led_handle_t;
    using sysman_led_handle_t = _sysman_led_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device RAS error set
    class SysmanRas;
    struct _sysman_ras_handle_t;
    using sysman_ras_handle_t = _sysman_ras_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device diagnostics test suite
    class SysmanDiagnostics;
    struct _sysman_diag_handle_t;
    using sysman_diag_handle_t = _sysman_diag_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle for a Sysman device event
    class SysmanEvent;
    struct _sysman_event_handle_t;
    using sysman_event_handle_t = _sysman_event_handle_t*;

} // namespace zes

namespace zes
{
} // namespace zes

namespace zes
{
    using result_t = ze::result_t;
    using exception_t = ze::exception_t;

} // namespace zes
#endif // defined(__cplusplus)
#endif // _ZES_COMMON_HPP
