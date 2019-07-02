/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xet_sysman.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for System Resource Management (SMI)
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/tools/sysman.yml
 * @endcond
 *
 */
#ifndef _XET_SYSMAN_HPP
#define _XET_SYSMAN_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define XET_STRING_PROPERTY_SIZE  32
#endif // XET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef XET_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define XET_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // XET_FAN_TEMP_SPEED_PAIR_COUNT

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_DEVICE_PROP_COLD_SHUTDOWN
    using device_prop_driver_cold_shutdown_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_DEVICE_PROP_COLD_RESET
    using device_prop_driver_cold_reset_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PSU_PROP_AMP_LIMIT
    using psu_prop_amp_limit_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PSU_PROP_FAN_FAILURE
    using psu_prop_fan_failure_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PSU_PROP_TEMPERATURE
    using psu_prop_temperature_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PSU_PROP_AMPS
    using psu_prop_amps_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FAN_PROP_MAX_RPM
    using fan_prop_max_rpm_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FAN_PROP_MAX_TABLE_SIZE
    using fan_prop_max_table_size_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FAN_PROP_SPEED_RPM
    using fan_prop_speed_rpm_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FAN_PROP_SPEED_PERCENT
    using fan_prop_speed_percent_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_LED_PROP_RGB_CAP
    using led_prop_rgb_cap_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWR_PROP_ACCEL_ASSETS.
    /// 
    /// @details
    ///     - Bitfield of (1<<::xet_accel_asset_t)
    using pwr_prop_accel_assets_t = uint64_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWR_PROP_MAX_LIMIT
    /// 
    /// @details
    ///     - Units are in millwatts
    using pwr_prop_max_limit_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWR_PROP_ENERGY_COUNTER
    /// 
    /// @details
    ///     - Units are in millijoules
    using pwr_prop_energy_counter_t = uint64_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FREQ_PROP_ACCEL_ASSETS
    /// 
    /// @details
    ///     - Bitfield of (1<<::xet_accel_asset_t)
    using freq_prop_accel_assets_t = uint64_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FREQ_PROP_FREQ_TDP
    /// 
    /// @details
    ///     - In units of MHz
    using freq_prop_freq_tdp_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FREQ_PROP_FREQ_EFFICIENT
    /// 
    /// @details
    ///     - In units of MHz
    using freq_prop_freq_efficient_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FREQ_PROP_FREQ_REQUEST
    /// 
    /// @details
    ///     - In units of MHz
    using freq_prop_freq_request_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FREQ_PROP_FREQ_RESOLVED
    /// 
    /// @details
    ///     - In units of MHz
    using freq_prop_freq_resolved_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FREQ_PROP_THROTTLE_REASONS
    /// 
    /// @details
    ///     - Bitfield of ::xet_freq_throttle_reasons_t
    using freq_prop_throttle_reasons_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_FREQ_PROP_THROTTLE_TIME
    /// 
    /// @details
    ///     - In units of microseconds
    using freq_prop_throttle_time_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWRWELL_PROP_ACCEL_ASSETS
    /// 
    /// @details
    ///     - Bitfield of (1<<::xet_accel_asset_t)
    using pwrwell_prop_accel_assets_t = uint64_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWRWELL_PROP_PROMO_CAP
    using pwrwell_prop_promo_cap_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWRWELL_PROP_SLEEP_COUNTER
    /// 
    /// @details
    ///     - Monotonic counter in units of seconds.
    using pwrwell_prop_sleep_counter_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWRWELL_PROP_IDLE_COUNTER
    /// 
    /// @details
    ///     - Monotonic counter in units of seconds.
    using pwrwell_prop_idle_counter_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWRWELL_PROP_ACTIVE_COUNTER
    /// 
    /// @details
    ///     - Monotonic counter in units of seconds.
    using pwrwell_prop_active_counter_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWRWELL_PROP_WAKE_COUNTER
    /// 
    /// @details
    ///     - Monotonic counter.
    using pwrwell_prop_wake_counter_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_PWRWELL_PROP_EXEC_COUNTER
    /// 
    /// @details
    ///     - Monotonic counter.
    using pwrwell_prop_exec_counter_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_ACCEL_PROP_ACCEL_ASSETS
    /// 
    /// @details
    ///     - Bitfield of (1<<::xet_accel_asset_t)
    using accel_prop_accel_assets_t = uint64_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_ACCEL_PROP_ACTIVE_COUNTER
    /// 
    /// @details
    ///     - Monotonic counter in units of seconds.
    using accel_prop_active_counter_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_ACCEL_PROP_IDLE_COUNTER
    /// 
    /// @details
    ///     - Monotonic counter in units of seconds.
    using accel_prop_idle_counter_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_MEM_PROP_ECC_CAP
    using mem_prop_ecc_cap_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_MEM_PROP_ECC_CLEAR
    using mem_prop_ecc_clear_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_MEM_PROP_ECC_POISON
    using mem_prop_ecc_poison_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_LINK_PROP_PWR_CAP
    using link_prop_pwr_cap_t = xe::bool_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_LINK_PROP_MAX_PACKET_SIZE
    using link_prop_max_packet_size_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Data for the property ::XET_LINK_PROP_REPLAY_COUNTER
    using link_prop_replay_counter_t = uint32_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for SMI of a device group
    class Sysman
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief SMI initialization flags (bitfield)
        enum class init_flags_t
        {
            NONE = 0,                                       ///< default initialization
            WRITE = XE_BIT( 0 ),                            ///< request write/control access to resources

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resource container types
        enum class res_container_type_t
        {
            UNIT = 0,                                       ///< Unit resource container
            BOARD,                                          ///< Board resource container
            DEVICE,                                         ///< Device resource container
            SUBDEVICE,                                      ///< Sub-device resource container
            MAX_TYPES,                                      ///< The number of resource container types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resource types
        enum class resource_type_t
        {
            PSU = 0,                                        ///< PSU resource
            TEMP,                                           ///< Temperature sensor resource
            FAN,                                            ///< Fan resource
            LED,                                            ///< LED resource
            FIRMWARE,                                       ///< Firmware resource
            PWR,                                            ///< Power domain resource
            FREQ,                                           ///< Frequency domain resource
            PWRWELL,                                        ///< Power-well resource
            ACCEL,                                          ///< Accelerator asset resource
            MEMORY,                                         ///< Memory resource
            LINK,                                           ///< Link resource
            MAX_TYPES,                                      ///< The number of resource types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event types
        enum class event_type_t
        {
            FREQ_THROTTLED = 0,                             ///< The frequency is being throttled
            FREQ_POLICY_CHANGED,                            ///< Another API client has modified frequency domain properties
            GPU_ERRORS,                                     ///< GPU hardware errors have occurred
            RESET,                                          ///< Device reset has occurred
            HANG,                                           ///< Device hang has occurred
            MEM_ERRORS,                                     ///< ECC correctable errors have occurred in a memory resource
            LINK_ERRORS,                                    ///< Link replays have occured in a link resource
            COUNT,                                          ///< The number of event types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resource container universal unique id (UUID)
        struct res_container_uuid_t
        {
            uint8_t id[XE_MAX_UUID_SIZE];                   ///< [out] resource container universal unique id

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Generic information about a resource container
        struct res_container_info_t
        {
            res_container_uuid_t uuid;                      ///< [out] UUID for the resource container
            res_container_type_t type;                      ///< [out] Type of resource container
            xe::bool_t haveParent;                          ///< [out] Indicates if this resource container has a parent container
            uint32_t numChildren;                           ///< [out] The number of child resource containers
            uint32_t numPeers;                              ///< [out] The number of resource containers connected with peer-to-peer
                                                            ///< links
            uint32_t numResourcesByType[resource_type_t::MAX_TYPES];///< [out] The number of resources of each type attached to this resource
                                                            ///< container (not in the child resource containers)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resource universal unique id (UUID)
        struct resource_uuid_t
        {
            uint8_t id[XE_MAX_UUID_SIZE];                   ///< [out] resource universal unique id

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Generic information about a resource
        struct resource_info_t
        {
            resource_uuid_t uuid;                           ///< [out] UUID for the resource
            resource_type_t type;                           ///< [out] Type of resource
            res_container_uuid_t resContainerUuid;          ///< [out] UUID for the resource container where this resouce is located

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event data
        struct event_data_t
        {
            res_container_uuid_t uuid;                      ///< [out] The UUID of the resource container that generated the event
            uint32_t events;                                ///< [out] Bitfield of events (1<<::xet_sysman_event_type_t) that have been
                                                            ///< triggered.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_handle_t m_handle = nullptr;             ///< [in] handle of SMI object
        DeviceGroup* m_pDeviceGroup;                    ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Sysman( void ) = delete;
        Sysman( 
            sysman_handle_t handle,                         ///< [in] handle of SMI object
            DeviceGroup* pDeviceGroup                       ///< [in] pointer to owner object
            );

        ~Sysman( void ) = default;

        Sysman( Sysman const& other ) = delete;
        void operator=( Sysman const& other ) = delete;

        Sysman( Sysman&& other ) = delete;
        void operator=( Sysman&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevicegroup( void ) const { return m_pDeviceGroup; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a handle to access SMI features
        /// 
        /// @details
        ///     - Initializes internal structures to support SMI features.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **nvmlInit**
        ///     - **rsmi_init**
        /// @returns
        ///     - Sysman*: handle for accessing SMI features
        /// 
        /// @throws result_t
        static Sysman* __xecall
        Create(
            DeviceGroup* pDeviceGroup,                      ///< [in] pointer to the device group
            uint32_t flags                                  ///< [in] bitfield of ::xet_sysman_init_flags_t
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a Sysman handle
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **nvmlShutdown**
        ///     - **rsmi_shut_down**
        /// @throws result_t
        static void __xecall
        Destroy(
            Sysman* pSysman                                 ///< [in][release] SMI handle to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves resource containers of a given type
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - SysmanResContainer*: array of handle of resource containers
        /// 
        /// @throws result_t
        void __xecall
        GetResourceContainers(
            res_container_type_t type,                      ///< [in] The type of resource containers to enumerate
            uint32_t* pCount,                               ///< [in,out] Pointer to the number of resource containers.
                                                            ///< If count is zero, then the driver will update the value with the total
                                                            ///< number of resource containers of the given type that are available.
                                                            ///< If count is non-zero, then driver will only retrieve that number of
                                                            ///< resource containers of the given type starting from index 0.
                                                            ///< If count is larger than the number of resource containers available,
                                                            ///< then the driver will update the value with the correct number of
                                                            ///< resource containers of a given type that are available.
            SysmanResContainer** ppResContainers = nullptr  ///< [out][optional][range(0, *pCount)] array of pointer to resource
                                                            ///< containers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves the resource container for a device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - SysmanResContainer*: Resource container for the specified device.
        /// 
        /// @throws result_t
        SysmanResContainer* __xecall
        GetDeviceResourceContainer(
            xe::Device* pDevice                             ///< [in] Handle to the device. It must be a member of the same Device
                                                            ///< Group as hSysman was created from.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves the resource container based on its UUID
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - SysmanResContainer*: Resource container with UUID.
        /// 
        /// @throws result_t
        SysmanResContainer* __xecall
        GetResourceContainerByUuid(
            res_container_uuid_t* uuid                      ///< [in] UUID for the resource container.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Register to receive events
        /// 
        /// @details
        ///     - This will only register the specified list of events. If other events
        ///       have been registered, notifications for them will continue.
        ///     - Applies only to devices in the specified SMI handle.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        RegisterEvents(
            SysmanResContainer* pResource,                  ///< [in] Handle of the resource container. Events from any contained
                                                            ///< devices will be registered.
                                                            ///< If the handle is ::XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE, events
                                                            ///< from all devices will be registered.
            uint32_t events                                 ///< [in] Bitfield of events to register.
                                                            ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                            ///< Set to (~0) to register to receive all events.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Unregister events
        /// 
        /// @details
        ///     - This will only unregister the specified list of events. If other
        ///       events have been registered, notifications for them will continue.
        ///     - Applies only to devices in the specified SMI handle.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        UnregisterEvents(
            SysmanResContainer* pResource,                  ///< [in] Handle of the resource container. Events from any contained
                                                            ///< devices will be unregistered.
                                                            ///< If the handle is ::XET_INVALID_SYSMAN_RES_CONTAINER_HANDLE, events
                                                            ///< from all devices will be unregistered.
            uint32_t events                                 ///< [in] Bitfield of events to unregister.
                                                            ///< Construct by ORing (1<<::xet_sysman_event_type_t).
                                                            ///< Set to (~0) to unregister all events.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Listen for events
        /// 
        /// @details
        ///     - This will only unregister the specified list of events. If other
        ///       events have been registered, notifications for them will continue.
        ///     - Applies only to devices in the specified SMI handle.
        ///     - At most, one event data per device will be returned.
        ///     - If event data is returned, the corresponding event status is cleared.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        ListenEvents(
            xe::bool_t block,                               ///< [in] If set to true, the call will block the calling thread
            uint32_t* pCount,                               ///< [in,out] Pointer to the number of elements in the array pointed to by pEventData.
                                                            ///< If size is zero, then the driver will update the value with the number
                                                            ///< of elements needed to retrieve the list of events.
                                                            ///< If size is less than that required to store the list of events, the
                                                            ///< driver will update the value with the required number of elements and
                                                            ///< return an error.
                                                            ///< If size is larger than that required to store the list of events, the
                                                            ///< driver will update the value with the number of elements actually returned.
            event_data_t* pEventData                        ///< [in] Pointer to an array of event data
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for SMI resource container
    class SysmanResContainer
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Accelerator assets
        enum class accel_asset_t
        {
            PCIE_CONTROLLER = 0,                            ///< PCIe controller
            IDI_MEM_CONTROLLER,                             ///< IDI memory controller
            HBM_MEM_CONTROLLER,                             ///< HBM memory controller
            L3_CACHE,                                       ///< L3 cache
            BLILTTER,                                       ///< Blitter
            VIDEO_DECODER,                                  ///< Video decoder
            VIDEO_ENCODER,                                  ///< Video encoder
            VIDEO_PROCESSING,                               ///< Video processing
            _3D_FF,                                         ///< 3D fixed-function hardware
            _3D_RENDER,                                     ///< 3D programmable shader units
            COMPUTE,                                        ///< Compute units
            SYSTOLIC,                                       ///< Systolic array
            RAYTRACING,                                     ///< Raytracing hardware
            LOCAL_MEM,                                      ///< Local memory
            LINK,                                           ///< High speed link
            MAX_TYPES,                                      ///< The number of accelerator asset types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Board resource container properties
        enum class board_properties_t
        {
            BOARD_PROP_SERIAL_NUMBER = 0,                   ///< (ro static) The serial number of a board container
            BOARD_PROP_BOARD_NUMBER,                        ///< (ro static) The board number of a board container

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI bar types
        enum class pci_bar_type_t
        {
            CONFIG = 0,                                     ///< PCI configuration space
            MMIO,                                           ///< MMIO registers
            VRAM,                                           ///< VRAM aperture
            ROM,                                            ///< ROM aperture
            VGA_IO,                                         ///< Legacy VGA IO ports
            VGA_MEM,                                        ///< Legacy VGA memory
            INDIRECT_IO,                                    ///< Indirect IO port access
            INDIRECT_MEM,                                   ///< Indirect memory access
            OTHER,                                          ///< Other type of PCI bar

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Hardware error types
        enum class hw_error_type_t
        {
            HW_ERROR_MESSAGING = 0,                         ///< Error while sending messages between sub-devices
            HW_ERROR_SGUNIT,                                ///< Error handling transactions between PCI config space, MMIO registers,
                                                            ///< local memory and sub-devices
            HW_ERROR_GSC,                                   ///< Authentication errors
            HW_ERROR_DISPLAY,                               ///< Display sub-system single-bit correctable errors
            HW_ERROR_GPU_EU_GRF,                            ///< Execution unit (EU) register file single-bit correctable errors
            HW_ERROR_GPU_EU_INSTCACHE,                      ///< Execution unit (EU) instruction cache single-bit correctable errors
            HW_ERROR_GPU_SLM,                               ///< Execution unit (EU) shared local memory single-bit correctable errors
            HW_ERROR_GPU_SAMPLER,                           ///< Sampler single-bit correctable errors
            HW_ERROR_GPU_GUC,                               ///< Micro-controller SRAM single-bit correctable errors
            HW_ERROR_GPU_L3,                                ///< L3 single-bit correctable errors
            HW_ERROR_GPU_ALL,                               ///< Total count of GPU errors
            HW_ERROR_PCI,                                   ///< PCIe correctable or non-fatal errors
            HW_ERROR_PCI_ROUTING,                           ///< Errors routing PCIe traffic to/from sub-devices
            HW_ERROR_SOC,                                   ///< Errors in other parts of the device
            HW_ERROR_COUNT,                                 ///< Maximum number of hardware error types

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device resource container properties
        enum class device_properties_t
        {
            DEVICE_PROP_BRAND = 0,                          ///< (ro static) The brand name of the device
            DEVICE_PROP_MODEL,                              ///< (ro static) The model name of the device
            DEVICE_PROP_DEVICEID,                           ///< (ro static) The device ID of the device
            DEVICE_PROP_VENDOR_NAME,                        ///< (ro static) The vendor name of the device
            DEVICE_PROP_ACCEL_ASSETS,                       ///< (ro static) The accelerator assets available in the device
            DEVICE_PROP_DRIVER_VERSION,                     ///< (ro static) The driver version associated with the device
            DEVICE_PROP_BARS,                               ///< (ro static) The bars configured for the device
            DEVICE_PROP_ERROR_STATS,                        ///< (ro dynamic) Error stats for the device
            DEVICE_PROP_COLD_SHUTDOWN,                      ///< (wo dynamic) Cold shudown the device
            DEVICE_PROP_COLD_RESET,                         ///< (wo dynamic) Cold reset the device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_BOARD_PROP_SERIAL_NUMBER
        struct board_prop_serial_number_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_BOARD_PROP_BOARD_NUMBER
        struct board_prop_board_number_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for a PCI bar
        struct pci_bar_info_t
        {
            pci_bar_type_t type;                            ///< [out] The type of bar
            uint64_t base;                                  ///< [out] Base address of the bar.
            uint64_t size;                                  ///< [out] Size of the bar.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_BRAND
        struct device_prop_brand_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_MODEL
        struct device_prop_model_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_DEVICEID
        struct device_prop_deviceid_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_VENDOR_NAME
        struct device_prop_vendor_name_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data about one type of accelerator asset
        struct device_prop_accel_asset_t
        {
            accel_asset_t type;                             ///< [out] The type of asset
            uint32_t numBlocks;                             ///< [out] The number of blocks of this asset type
            uint32_t numEngines;                            ///< [out] The number of submission engines for this type of asset

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_DEVICE_PROP_ACCEL_ASSETS
        struct device_prop_accel_assets_t
        {
            uint64_t assetBitfield;                         ///< [out] A bitfield of assets available in the resource container
            device_prop_accel_asset_t assetInfo[accel_asset_t::MAX_TYPES];  ///< [out] Information about each asset.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_DEVICE_PROP_DRIVER_VERSION
        struct device_prop_driver_version_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_DEVICE_PROP_BARS
        struct device_prop_bars_t
        {
            uint32_t num;                                   ///< [out] The number of bars
            const pci_bar_info_t* pBars;                    ///< [out][range(0, num-1)] Information about each bar.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_DEVICE_PROP_ERROR_STATS
        struct device_prop_error_stats_t
        {
            uint32_t TotalNonFatalError;                    ///< [out] The total number of non-fatal hardware errors that have occurred
                                                            ///< since the driver booted
            uint32_t errors[hw_error_type_t::HW_ERROR_COUNT];   ///< [out] Error counters for each type (::xet_hw_error_type_t) of hardware
                                                            ///< error.
            uint32_t NumResets;                             ///< [out] The total number of hardware resets that have been performed
                                                            ///< since the driver booted
            uint32_t NumHangs;                              ///< [out] The total number of hardware hangs that have occurred since the
                                                            ///< driver booted
            uint32_t NumColdResets;                         ///< [out] The total number of cold resets that have been performanced
                                                            ///< since the driver booted

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        res_container_handle_t m_handle = nullptr;      ///< [in] handle of the resource container
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanResContainer( void ) = delete;
        SysmanResContainer( 
            res_container_handle_t handle,                  ///< [in] handle of the resource container
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanResContainer( void ) = default;

        SysmanResContainer( SysmanResContainer const& other ) = delete;
        void operator=( SysmanResContainer const& other ) = delete;

        SysmanResContainer( SysmanResContainer&& other ) = delete;
        void operator=( SysmanResContainer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get generic information about a resource container
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Sysman::res_container_info_t: Generic information about the resource container.
        /// 
        /// @throws result_t
        Sysman::res_container_info_t __xecall
        GetInfo(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get parent resource container
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - SysmanResContainer*: Handle of the parent resource container.
        /// 
        /// @throws result_t
        SysmanResContainer* __xecall
        GetParent(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get children resource containers
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - SysmanResContainer*: array of handle of resource containers
        /// 
        /// @throws result_t
        void __xecall
        GetChildren(
            uint32_t* pCount,                               ///< [in,out] Pointer to the number of child resource containers.
                                                            ///< If count is zero, then the driver will update the value with the total
                                                            ///< number of child resource containers.
                                                            ///< If count is non-zero, then driver will only retrieve that number of
                                                            ///< child resource containers starting from index 0.
                                                            ///< If count is larger than the number of child resource containers
                                                            ///< available, then the driver will update the value with the correct
                                                            ///< number of child resource containers.
            SysmanResContainer** ppResContainers = nullptr  ///< [out][optional][range(0, *pCount)] array of pointer to resource
                                                            ///< containers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get peer resource containers
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - SysmanResContainer*: array of handle of resource containers
        /// 
        /// @throws result_t
        void __xecall
        GetPeers(
            uint32_t* pCount,                               ///< [in,out] Pointer to the number of peer resource containers.
                                                            ///< If count is zero, then the driver will update the value with the total
                                                            ///< number of peer resource containers.
                                                            ///< If count is non-zero, then driver will only retrieve that number of
                                                            ///< peer resource containers starting from index 0.
                                                            ///< If count is larger than the number of peer resource containers
                                                            ///< available, then the driver will update the value with the correct
                                                            ///< number of peer resource containers.
            SysmanResContainer** ppResContainers = nullptr  ///< [out][optional][range(0, *pCount)] array of pointer to resource
                                                            ///< containers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get human-readable name for an accelerator asset
        /// @throws result_t
        void __xecall
        GetAccelAssetName(
            accel_asset_t type,                             ///< [in] The type of accelerator asset
            const char** ppName                             ///< [in] Pointer to the string will be stored here
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves resources of a given type located in a container
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetResources(
            Sysman::resource_type_t type,                   ///< [in] The type of resources to enumerate
            uint32_t* pCount,                               ///< [in,out] Pointer to the number of resource.
                                                            ///< If count is zero, then the driver will update the value with the total
                                                            ///< number of resources of the given type that are available.
                                                            ///< If count is non-zero, then driver will only retrieve that number of
                                                            ///< resources of the given type starting from index 0.
                                                            ///< If count is larger than the number of resources available, then the
                                                            ///< driver will update the value with the correct number of resources of a
                                                            ///< given type that are available.
            SysmanResource** ppResources = nullptr          ///< [in][optional][range(0, *pCount)] array of pointer to resources
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get board property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetBoardProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const board_properties_t* pIndexes,             ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get device property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetDeviceProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const device_properties_t* pIndexes,            ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set new values of device properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetDeviceProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const device_properties_t* pIndexes,            ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for SMI resource
    class SysmanResource
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PSU voltage status
        enum class psu_voltage_status_t
        {
            NORMAL = 0,                                     ///< No unusual voltages have been detected
            OVER,                                           ///< Over-voltage has occurred
            UNDER,                                          ///< Under-voltage has occurred

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PSU resource properties
        enum class psu_properties_t
        {
            PSU_PROP_AMP_LIMIT = 0,                         ///< (ro static) The maximum electrical current in Amperes that can be
                                                            ///< drawn
            PSU_PROP_VOLTAGE_STATUS,                        ///< (ro dynamic) Indicates if under or over voltage has occurred (one of
                                                            ///< ::xet_psu_voltage_status_t)
            PSU_PROP_FAN_FAILURE,                           ///< (ro dynamic) Indicates if the fan has failed
            PSU_PROP_TEMPERATURE,                           ///< (ro dynamic) Read the current heatsink temperature in degrees celcius
            PSU_PROP_AMPS,                                  ///< (ro dynamic) Read the amps being drawn in Amperes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature sensor resource properties
        enum class temp_properties_t
        {
            TEMP_PROP_TEMPERATURE = 0,                      ///< (ro dynamic) The current temperature of the sensor in degrees celcius

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan resource speed mode
        enum class fan_speed_mode_t
        {
            FIXED = 0,                                      ///< The fan speed is currently set to a fixed value
            TABLE,                                          ///< The fan speed is currently controlled dynamically by hardware based on
                                                            ///< a temp/speed table

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan speed units
        enum class fan_speed_units_t
        {
            RPM = 0,                                        ///< The fan speed is in units of revolutions per minute (rpm)
            PERCENT,                                        ///< The fan speed is a percentage of the maximum speed of the fan

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan resource properties
        enum class fan_properties_t
        {
            FAN_PROP_MAX_RPM = 0,                           ///< (ro static) The maximum RPM of the fan
            FAN_PROP_MAX_TABLE_SIZE,                        ///< (ro static) The maximum number of points in the fan temp/speed table
            FAN_PROP_SPEED_RPM,                             ///< (ro dynamic) The current fan speed in units of revolutions per minute
                                                            ///< (rpm)
            FAN_PROP_SPEED_PERCENT,                         ///< (ro dynamic) The current fan speed as a percentage of the maximum
                                                            ///< speed of that fan
            FAN_PROP_MODE,                                  ///< (ro dynamic) The current fan speed mode (one of
                                                            ///< ::xet_fan_speed_mode_t)
            FAN_PROP_FIXED_SPEED,                           ///< (rw dynamic) Read/write the fixed speed setting for the fan
            FAN_PROP_SPEED_TABLE,                           ///< (rw dynamic) Read/write the fan speed table

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief LED resource properties
        enum class led_properties_t
        {
            LED_PROP_RGB_CAP = 0,                           ///< (ro static) Indicates if the LED is RGB capable
            LED_PROP_STATE,                                 ///< (rw dynaic) The LED state (on/off and color)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Firmware resource properties
        enum class firmware_properties_t
        {
            FIRMWARE_PROP_NAME = 0,                         ///< (ro static) Name encoded in the loaded firmware image
            FIRMWARE_PROP_VERSION,                          ///< (ro static) The version of the loaded firmware image
            FIRMWARE_PROP_CHECK,                            ///< (ro dynamic) Verify the checksum of the loaded firmware image
            FIRMWARE_PROP_FLASH,                            ///< (wo dynamically) Flash a new firmware image

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Power domain resource properties
        enum class pwr_properties_t
        {
            PWR_PROP_ACCEL_ASSETS = 0,                      ///< (ro static) List of accelerator assets that contribute to this power
                                                            ///< domain
            PWR_PROP_MAX_LIMIT,                             ///< (ro static) The maximum power limit that can be requested
            PWR_PROP_ENERGY_COUNTER,                        ///< (ro dynamic) The value of the monotonic energy counter
            PWR_PROP_SUSTAINED_LIMIT,                       ///< (rw dynamic) The sustained power limit
            PWR_PROP_BURST_LIMIT,                           ///< (rw dynamic) The burst power limit
            PWR_PROP_PEAK_LIMIT,                            ///< (rw dynamic) The peak power limit

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::xet_pwr_prop_sustained_limit_t
        enum class pwr_sustained_limit_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency domain types
        enum class freq_domain_type_t
        {
            INDEPENDENT = 0,                                ///< The frequency of this domain can be managed independently of other
                                                            ///< domains
            DEPENDENT,                                      ///< The frequency of this domain is dependent on another domain through a
                                                            ///< clock divider

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief DVFS mode
        enum class dvfs_mode_t
        {
            MIN = 0,                                        ///< Fixed minimum frequency will be requested unless specific applications
                                                            ///< request otherwise.
            EFFICIENT,                                      ///< Dynamic frequency management that prefers power saving over
                                                            ///< performance.
            STABLE,                                         ///< Fixed frequency that should not be throttled under normal operating
                                                            ///< conditions.
            DEFAULT,                                        ///< Dynamic frequency management that balances power and performance.
            AGGRESSIVE,                                     ///< Dynamic frequency management that trades more power for better
                                                            ///< performance.
            MAX,                                            ///< Fixed maximum frequency.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency throttle reasons
        enum class freq_throttle_reasons_t
        {
            NONE = 0,                                       ///< frequency not throttled
            AVE_PWR_CAP = XE_BIT( 0 ),                      ///< frequency throttled due to average power excursion (PL1)
            BURST_PWR_CAP = XE_BIT( 1 ),                    ///< frequency throttled due to burst power excursion (PL2)
            CURRENT_LIMIT = XE_BIT( 2 ),                    ///< frequency throttled due to current excursion (PL4)
            THERMAL_LIMIT = XE_BIT( 3 ),                    ///< frequency throttled due to thermal excursion (T > TjMax)
            PSU_ALERT = XE_BIT( 4 ),                        ///< frequency throttled due to power supply assertion
            SW_RANGE = XE_BIT( 5 ),                         ///< frequency throttled due to software supplied frequency range
            HW_RANGE = XE_BIT( 6 ),                         ///< frequency throttled due to a sub block that has a lower frequency
                                                            ///< range when it receives clocks

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency domain resource properties
        enum class freq_properties_t
        {
            FREQ_PROP_ACCEL_ASSETS = 0,                     ///< (ro static) List of accelerator assets that are connected to this
                                                            ///< power domain
            FREQ_PROP_DOMAIN_TYPE,                          ///< (ro static) The type of frequency domain (one of
                                                            ///< ::xet_freq_domain_type_t)
            FREQ_PROP_AVAIL_CLOCKS,                         ///< (ro static) Available frequency clocks that this domain can run at.
            FREQ_PROP_AVAIL_DIVIDERS,                       ///< (ro static) Available dividers that this domain can run with.
            FREQ_PROP_SRC_FREQ,                             ///< (ro static) Get the UUID of the source frequency domain resource if
                                                            ///< the type is dependent.
            FREQ_PROP_DVFS_MODE,                            ///< (rw dynamic) The operating mode of dynamic frequency management for
                                                            ///< this domain (one of ::xet_dvfs_mode_t).
            FREQ_PROP_FREQ_RANGE,                           ///< (rw dynamic) The frequencies between which dynamic frequency
                                                            ///< management operates.
            FREQ_PROP_FREQ_TDP,                             ///< (ro dynamic) The maximum frequency supported under the current TDP
                                                            ///< conditions
            FREQ_PROP_FREQ_EFFICIENT,                       ///< (ro dynamic) The efficient minimum frequency
            FREQ_PROP_FREQ_REQUEST,                         ///< (ro dynamic) The current frequency request.
            FREQ_PROP_FREQ_RESOLVED,                        ///< (ro dynamic) The resolved frequency.
            FREQ_PROP_FREQ_DIVIDER,                         ///< (rw dynamic) The current frequency divider for dependent frequency
                                                            ///< domains.
            FREQ_PROP_THROTTLE_REASONS,                     ///< (ro dynamic) The reasons that the frequency is being limited by the
                                                            ///< PCU.
            FREQ_PROP_THROTTLE_TIME,                        ///< (ro dynamic) The total time that the frequency has been limited by the
                                                            ///< PCU.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Power-well domain promotion modes
        enum class pwrwell_promo_mode_t
        {
            IMMEDIATE = 0,                                  ///< The power-well will shutdown immediately when all contained units are
                                                            ///< idle.
            EFFICIENT,                                      ///< Favor energy savings over performance. The power-well is more likely
                                                            ///< to shutdown when all contained units are idle, even if this will cause
                                                            ///< some performance degredation.
            DEFAULT,                                        ///< Best compromise between performance and energy savings.
            PERFORMANCE,                                    ///< Favor performance over energy savings. The power-well is more likely
                                                            ///< to stay on when all contained units are idle since it has dedicated
                                                            ///< that more work will be executing shortly.
            NEVER,                                          ///< The power-well will never shutdown. This can improve performance but
                                                            ///< uses more energy.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Power-well domain resource properties
        enum class pwrwell_properties_t
        {
            PWRWELL_PROP_ACCEL_ASSETS = 0,                  ///< (ro static) List of accelerator assets that are connected to this
                                                            ///< power-well domain
            PWRWELL_PROP_PROMO_CAP,                         ///< (ro static) Find out if the power-well domain has a programmable
                                                            ///< promotion setting
            PWRWELL_PROP_PROMO_MODE,                        ///< (rw dynamic) The current promotion mode
            PWRWELL_PROP_SLEEP_COUNTER,                     ///< (ro dynamic) The monotonic counter for the amount of time the
                                                            ///< power-well is off
            PWRWELL_PROP_IDLE_COUNTER,                      ///< (ro dynamic) The monotonic counter for the amount of time the
                                                            ///< power-well is on but not executing any accelerator workloads
            PWRWELL_PROP_ACTIVE_COUNTER,                    ///< (ro dynamic) The monotonic counter for the amount of time the
                                                            ///< power-well is on and executing accelerator workloads
            PWRWELL_PROP_WAKE_COUNTER,                      ///< (ro dynamic) The monotonic counter for the number of times that the
                                                            ///< power-well has transitioned from a sleep state to a powered on state
            PWRWELL_PROP_EXEC_COUNTER,                      ///< (ro dynamic) The monotonic counter for the number of times that the
                                                            ///< power-well has transitioned from a sleep or idle state to an active
                                                            ///< state

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Accelerator asset resource properties
        enum class accel_properties_t
        {
            ACCEL_PROP_ACCEL_ASSETS = 0,                    ///< (ro static) List of accelerator assets that contribute to counters in
                                                            ///< this resource
            ACCEL_PROP_ACTIVE_COUNTER,                      ///< (ro dynamic) The total wall time accelerator assets in this resource
                                                            ///< are active.
            ACCEL_PROP_IDLE_COUNTER,                        ///< (ro dynamic) The total wall time no accelerator assets in this
                                                            ///< resource are active

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory resource types
        enum class mem_type_t
        {
            HBM = 0,                                        ///< HBM memory
            DDR,                                            ///< DDR memory
            SRAM,                                           ///< SRAM memory
            L1,                                             ///< L1 cache
            L3,                                             ///< L3 cache
            GRF,                                            ///< Execution unit register file
            SLM,                                            ///< Execution unit shared local memory

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory retire reasons
        enum class mem_retire_reason_t
        {
            MULTIPLE_SINGLE_BIT_ERRORS = 0,                 ///< Memory page has been retired due to multiple single bit ECC errors
            DOUBLE_BIT_ERRORS,                              ///< Memory page has been retired due to one or more double bit ECC errors

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory resource properties
        enum class mem_properties_t
        {
            MEM_PROP_TYPE = 0,                              ///< (ro static) The type of memory covered by this resource (one of
                                                            ///< ::xet_mem_type_t)
            MEM_PROP_ECC_CAP,                               ///< (ro static) Indicates if this memory resource supports ECC/RAS
                                                            ///< features
            MEM_PROP_BAD_LIST,                              ///< (ro static) Get the list of pages that have been permanently marked
                                                            ///< bad
            MEM_PROP_UTILIZATION,                           ///< (ro dynamic) Get current allocated/unallocated size
            MEM_PROP_BANDWIDTH,                             ///< (ro dynamic) Get current read/write bandwidth counters and maximum
                                                            ///< bandwidth
            MEM_PROP_ECC_ENABLED,                           ///< (rw dynamic) Determine if ECC is enabled/disabled or change this
                                                            ///< setting
            MEM_PROP_ECC_COUNTERS,                          ///< (ro dynamic) ECC error counters
            MEM_PROP_ECC_CLEAR,                             ///< (wo dynamic) Clear ECC error counters
            MEM_PROP_ECC_POISON,                            ///< (wo dynamic) Poison the memory resource

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Link resource types
        enum class link_type_t
        {
            PCI = 0,                                        ///< PCI connection
            PEER_TO_PEER,                                   ///< Peer-to-peer connection

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Link resource properties
        enum class link_properties_t
        {
            LINK_PROP_TYPE = 0,                             ///< (ro static) The type of link (one of ::xet_link_type_t)
            LINK_PROP_BUS_ADDRESS,                          ///< (ro static) The bus address of the link
            LINK_PROP_PWR_CAP,                              ///< (ro static) Indicates if the link frequency can adjust to control
                                                            ///< power
            LINK_PROP_AVAIL_SPEEDS,                         ///< (ro static) Available link speeds
            LINK_PROP_MAX_PACKET_SIZE,                      ///< (ro static) Available link speeds
            LINK_PROP_BANDWIDTH,                            ///< (ro dynamic) Available link speeds
            LINK_PROP_REPLAY_COUNTER,                       ///< (ro dynamic) Total number of packet replays that have occurred
            LINK_PROP_SPEED,                                ///< (ro dynamic) Current link speed
            LINK_PROP_SPEED_RANGE,                          ///< (wo dynamic) Set the min/max speeds between which the link can operate

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PSU_PROP_VOLTAGE_STATUS
        struct psu_prop_voltage_status_t
        {
            psu_voltage_status_t status;                    ///< [out] The current PSU voltage status)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan temperature/speed pair
        struct fan_temp_speed_t
        {
            uint32_t temperature;                           ///< [in,out] Temperature in degrees celcius
            uint32_t speed;                                 ///< [in,out] The speed of the fan
            fan_speed_units_t units;                        ///< [in,out] The units of the member speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_MODE
        struct fan_prop_mode_t
        {
            fan_speed_mode_t mode;                          ///< [in,out] The current fan speed mode (one of ::xet_fan_speed_mode_t)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_FIXED_SPEED
        struct fan_prop_fixed_speed_t
        {
            uint32_t speed;                                 ///< [in,out] The speed of the fan
            fan_speed_units_t units;                        ///< [in,out] The units of the member speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FAN_PROP_SPEED_TABLE
        struct fan_prop_speed_table_t
        {
            uint32_t* pCount;                               ///< [in,out] The number of temp/speed pairs.
                                                            ///< When reading the current fan speed table, this will be set to the
                                                            ///< number of points returned.
                                                            ///< When setting the fan speed table, this specifies the number of valid
                                                            ///< points in the table.
            fan_temp_speed_t points[XET_FAN_TEMP_SPEED_PAIR_COUNT]; ///< [in,out][range(0, *pCount)] Array of temperature/fan speed pairs

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LED_PROP_STATE
        struct led_prop_state_t
        {
            xe::bool_t isOn;                                ///< [in,out] Indicates if the LED is on or off
            uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
            uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
            uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_FIRMWARE_PROP_NAME
        struct firmware_prop_name_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_FIRMWARE_PROP_VERSION
        struct firmware_prop_version_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FIRMWARE_PROP_CHECK
        struct firmware_prop_check_t
        {
            uint32_t checksum;                              ///< [out] The calculated checksum of the loaded firmware image

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FIRMWARE_PROP_FLASH
        struct firmware_prop_flash_t
        {
            void* pImage;                                   ///< [in] Pointer to the image to be flashed
            uint32_t size;                                  ///< [in] Size in bytes of the image pointed to by pImage

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_SUSTAINED_LIMIT
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency if
        ///       the power averaged over a window (typically seconds) exceeds this
        ///       limit.
        struct pwr_prop_sustained_limit_t
        {
            pwr_sustained_limit_version_t version = pwr_sustained_limit_version_t::CURRENT; ///< [in] ::XET_PWR_SUSTAINED_LIMIT_VERSION_CURRENT
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts
            uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_BURST_LIMIT
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency of
        ///       the device if the power averaged over a few milliseconds exceeds a
        ///       limit known as PL2. Typically PL2 > PL1 so that it permits the
        ///       frequency to burst higher for short periods than would be otherwise
        ///       permitted by PL1.
        struct pwr_prop_burst_limit_t
        {
            xe::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWR_PROP_PEAK_LIMIT
        /// 
        /// @details
        ///     - The power controller (Punit) will preemptively throttle the operating
        ///       frequency of the device when the instantaneous power exceeds this
        ///       limit. The limit is known as PL4. It expresses the maximum power that
        ///       can be drawn from the power supply.
        ///     - If this power limit is removed or set too high, the power supply will
        ///       generate an interrupt when it detects an overcurrent condition and the
        ///       power controller will throttle the device frequencies down to min. It
        ///       is thus better to tune the PL4 value in order to avoid such
        ///       excursions.
        struct pwr_prop_peak_limit_t
        {
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency divider element
        /// 
        /// @details
        ///     - The frequency of a domain of type ::XET_FREQ_DOMAIN_TYPE_DEPENDENT is
        ///       obtained by the formula:
        ///     - freq = source domain freq * numerator / denominator
        struct freq_divider_t
        {
            uint16_t numerator;                             ///< [in,out] numerator of the ratio
            uint16_t denominator;                           ///< [in,out] denominator of the ratio

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_DOMAIN_TYPE
        struct freq_prop_domain_type_t
        {
            freq_domain_type_t type;                        ///< [out] The type of frequency domain

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_AVAIL_CLOCKS
        /// 
        /// @details
        ///     - The list is ordered from the smallest frequency to the largest
        ///       frequency.
        struct freq_prop_avail_clocks_t
        {
            uint32_t num;                                   ///< [out] The number of clocks
            const uint32_t* pClocks;                        ///< [out] Array of clock frequencies in MHz ordered from smallest to
                                                            ///< largest.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_AVAIL_DIVIDERS
        /// 
        /// @details
        ///     - The list is ordered from the smallest ratio to the largest ratio.
        struct freq_prop_avail_dividers_t
        {
            uint32_t num;                                   ///< [out] The number of dividers
            const freq_divider_t* pDividers;                ///< [out] Array of numerator/denominator for each divider

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_SRC_FREQ
        struct freq_prop_src_freq_t
        {
            Sysman::resource_uuid_t uuid;                   ///< [out] The resource UUID of the source frequency domain

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_DVFS_MODE
        struct freq_prop_dvfs_mode_t
        {
            dvfs_mode_t mode;                               ///< [in,out] The DVFS operating mode

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_FREQ_RANGE
        struct freq_prop_freq_range_t
        {
            uint32_t min;                                   ///< [in,out] Minimum frequency in MHz
            uint16_t max;                                   ///< [in,out] Maximum frequency in MHz

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_FREQ_PROP_FREQ_DIVIDER
        struct freq_prop_freq_divider_t
        {
            freq_divider_t divider;                         ///< [in,out] The frequency divider

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_PWRWELL_PROP_PROMO_MODE
        struct pwrwell_prop_promo_mode_t
        {
            pwrwell_promo_mode_t mode;                      ///< [in,out] Current promotion mode

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retired page info
        struct mem_retire_info_t
        {
            uint64_t address;                               ///< [out] The address of the page
            mem_retire_reason_t reason;                     ///< [out] The reason the page was retired

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_TYPE
        struct mem_prop_type_t
        {
            mem_type_t type;                                ///< [out] The memory type

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_BAD_LIST
        struct mem_prop_bad_list_t
        {
            uint32_t* pCount;                               ///< [in,out] The number of elements in pList
                                                            ///< If pCount is zero, then the driver will update the value with the
                                                            ///< number of elements needed to store the bad list.
                                                            ///< If pCount is less than that required to store the bad list, the driver
                                                            ///< will update the value with the required number of elements and return
                                                            ///< an error.
                                                            ///< If pCount is larger than that required to store the bad list, the
                                                            ///< driver will update the value with the number of elements actually returned.
            mem_retire_info_t* pList;                       ///< [in] Pointer to storage for information about each bad page.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_UTILIZATION
        struct mem_prop_utilization_t
        {
            uint64_t allocated;                             ///< [out] The total allocated bytes
            uint64_t unallocated;                           ///< [out] The total unallocated bytes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_BANDWIDTH
        struct mem_prop_bandwidth_t
        {
            uint32_t readCounter;                           ///< [out] Total bytes read from memory
            uint32_t writeCounter;                          ///< [out] Total bytes written to memory
            uint32_t maxBandwidth;                          ///< [out] Current maximum bandwidth in units of bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_MEM_PROP_ECC_COUNTERS
        struct mem_prop_ecc_counters_t
        {
            uint32_t parityErrors;                          ///< [out] Total parity errors that have occurred
            uint32_t correctableErrors;                     ///< [out] Total correctable errors that have occurred
            uint32_t uncorrectableErrors;                   ///< [out] Total uncorrectable errors that have occurred
            uint32_t retiredPages;                          ///< [out] Total number of pages that have been retired
            uint32_t badPages;                              ///< [out] Total number of pages that have been permanently marked as bad

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Link speed element
        struct link_speed_t
        {
            uint32_t numLanes;                              ///< [out] The number of lanes used by the link
            uint32_t speed;                                 ///< [out] The frequency of the link in units of MHz
            uint32_t bandwidth;                             ///< [out] The maximum bandwidth in units of bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_LINK_PROP_TYPE
        struct link_prop_type_t
        {
            link_type_t type;                               ///< [out] The type of link

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for property ::XET_LINK_PROP_BUS_ADDRESS
        struct link_prop_bus_address_t
        {
            int8_t str[XET_STRING_PROPERTY_SIZE];           ///< [out] NULL terminated string value

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_AVAIL_SPEEDS
        /// 
        /// @details
        ///     - The list is ordered from the smallest ratio to the largest ratio.
        struct link_prop_avail_speeds_t
        {
            uint32_t num;                                   ///< [out] The number of elements in pList
            const link_speed_t* pList;                      ///< [out][range(0, num-1)] Pointer to an array of link speeds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_BANDWIDTH
        struct link_prop_bandwidth_t
        {
            uint32_t recvCounter;                           ///< [out] Total bytes received across the link
            uint32_t sendCounter;                           ///< [out] Total bytes sent across the link
            uint32_t maxBandwidth;                          ///< [out] Maximum bytes/sec that can be transfered acros the link

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_SPEED
        struct link_prop_speed_t
        {
            const link_speed_t* pSpeed;                     ///< [out] Pointer to the current speed configuration

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Data for the property ::XET_LINK_PROP_SPEED_RANGE
        struct link_prop_speed_range_t
        {
            const link_speed_t* pMinSpeed;                  ///< [out] Pointer to the min speed configuration (one of those in the
                                                            ///< array returned by property ::XET_LINK_PROP_AVAIL_SPEEDS)
            const link_speed_t* pMaxSpeed;                  ///< [out] Pointer to the max speed configuration (one of those in the
                                                            ///< array returned by property ::XET_LINK_PROP_AVAIL_SPEEDS)

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        resource_handle_t m_handle = nullptr;           ///< [in] handle of resource
        SysmanResContainer* m_pResContainer;            ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanResource( void ) = delete;
        SysmanResource( 
            resource_handle_t handle,                       ///< [in] handle of resource
            SysmanResContainer* pResContainer               ///< [in] pointer to owner object
            );

        ~SysmanResource( void ) = default;

        SysmanResource( SysmanResource const& other ) = delete;
        void operator=( SysmanResource const& other ) = delete;

        SysmanResource( SysmanResource&& other ) = delete;
        void operator=( SysmanResource&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getRescontainer( void ) const { return m_pResContainer; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get generic information about a resource
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Sysman::resource_info_t: Generic information about the resource.
        /// 
        /// @throws result_t
        Sysman::resource_info_t __xecall
        GetInfo(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get PSU property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetPsuProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const psu_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set new PSU properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetPsuProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const psu_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get temperature sensor property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetTempProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const temp_properties_t* pIndexes,              ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set temperature sensor properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetTempProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const temp_properties_t* pIndexes,              ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get fan property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetFanProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const fan_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set new fan properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetFanProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const fan_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get LED property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetLedProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const led_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set LED properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetLedProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const led_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get firmware property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetFirmwareProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const firmware_properties_t* pIndexes,          ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set firmware properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetFirmwareProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const firmware_properties_t* pIndexes,          ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power domain property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetPwrProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const pwr_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set power domain properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetPwrProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const pwr_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get frequency domain property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetFreqProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const freq_properties_t* pIndexes,              ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set frequency domain properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetFreqProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const freq_properties_t* pIndexes,              ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power-well domain property data
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetPwrWellProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const pwrwell_properties_t* pIndexes,           ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set power-well domain properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetPwrWellProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const pwrwell_properties_t* pIndexes,           ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get accelerator asset resource properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetAccelProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const accel_properties_t* pIndexes,             ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set accelerator asset resource properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetAccelProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const accel_properties_t* pIndexes,             ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory resource properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetMemProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const mem_properties_t* pIndexes,               ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set memory resource properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetMemProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const mem_properties_t* pIndexes,               ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get link resource properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        GetLinkProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const link_properties_t* pIndexes,              ///< [in] An array of property indexes to be read
            void* pValues,                                  ///< [in] A pointer to storage for the data of the requested properties.
            uint32_t* pSize                                 ///< [in,out] Pointer to the total size of data pointed to by pValues.
                                                            ///< If size is zero, then the driver will update the value with the size
                                                            ///< required to store the requested properties.
                                                            ///< If size is less than that required to store the requested data for the
                                                            ///< properties, the driver will update the value with the required size
                                                            ///< and return an error.
                                                            ///< If size is larger than that required to store the requested data for
                                                            ///< the properties, the driver will update the value with the size of the
                                                            ///< data returned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set link resource properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __xecall
        SetLinkProperties(
            uint32_t count,                                 ///< [in] The number of properties in the array pIndexes
            const link_properties_t* pIndexes,              ///< [in] An array of property indexes to be set
            void* pValues,                                  ///< [in] A pointer to storage for new settings for the specified
                                                            ///< properties.
            uint32_t size                                   ///< [in] Size of property data pointed to by pValues.
            );

    };

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::init_flags_t to std::string
    std::string to_string( const Sysman::init_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::res_container_type_t to std::string
    std::string to_string( const Sysman::res_container_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_type_t to std::string
    std::string to_string( const Sysman::resource_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::res_container_uuid_t to std::string
    std::string to_string( const Sysman::res_container_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::res_container_info_t to std::string
    std::string to_string( const Sysman::res_container_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_uuid_t to std::string
    std::string to_string( const Sysman::resource_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::resource_info_t to std::string
    std::string to_string( const Sysman::resource_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_data_t to std::string
    std::string to_string( const Sysman::event_data_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::accel_asset_t to std::string
    std::string to_string( const SysmanResContainer::accel_asset_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::board_properties_t to std::string
    std::string to_string( const SysmanResContainer::board_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::board_prop_serial_number_t to std::string
    std::string to_string( const SysmanResContainer::board_prop_serial_number_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::board_prop_board_number_t to std::string
    std::string to_string( const SysmanResContainer::board_prop_board_number_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::pci_bar_type_t to std::string
    std::string to_string( const SysmanResContainer::pci_bar_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::pci_bar_info_t to std::string
    std::string to_string( const SysmanResContainer::pci_bar_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::hw_error_type_t to std::string
    std::string to_string( const SysmanResContainer::hw_error_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_properties_t to std::string
    std::string to_string( const SysmanResContainer::device_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_brand_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_brand_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_model_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_model_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_deviceid_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_deviceid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_vendor_name_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_vendor_name_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_accel_asset_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_accel_asset_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_accel_assets_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_accel_assets_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_driver_version_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_driver_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_bars_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_bars_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResContainer::device_prop_error_stats_t to std::string
    std::string to_string( const SysmanResContainer::device_prop_error_stats_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_voltage_status_t to std::string
    std::string to_string( const SysmanResource::psu_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_properties_t to std::string
    std::string to_string( const SysmanResource::psu_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::psu_prop_voltage_status_t to std::string
    std::string to_string( const SysmanResource::psu_prop_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::temp_properties_t to std::string
    std::string to_string( const SysmanResource::temp_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_speed_mode_t to std::string
    std::string to_string( const SysmanResource::fan_speed_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_speed_units_t to std::string
    std::string to_string( const SysmanResource::fan_speed_units_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_temp_speed_t to std::string
    std::string to_string( const SysmanResource::fan_temp_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_properties_t to std::string
    std::string to_string( const SysmanResource::fan_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_mode_t to std::string
    std::string to_string( const SysmanResource::fan_prop_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_fixed_speed_t to std::string
    std::string to_string( const SysmanResource::fan_prop_fixed_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::fan_prop_speed_table_t to std::string
    std::string to_string( const SysmanResource::fan_prop_speed_table_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::led_properties_t to std::string
    std::string to_string( const SysmanResource::led_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::led_prop_state_t to std::string
    std::string to_string( const SysmanResource::led_prop_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_properties_t to std::string
    std::string to_string( const SysmanResource::firmware_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_prop_name_t to std::string
    std::string to_string( const SysmanResource::firmware_prop_name_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_prop_version_t to std::string
    std::string to_string( const SysmanResource::firmware_prop_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_prop_check_t to std::string
    std::string to_string( const SysmanResource::firmware_prop_check_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::firmware_prop_flash_t to std::string
    std::string to_string( const SysmanResource::firmware_prop_flash_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_properties_t to std::string
    std::string to_string( const SysmanResource::pwr_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_sustained_limit_version_t to std::string
    std::string to_string( const SysmanResource::pwr_sustained_limit_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_sustained_limit_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_sustained_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_burst_limit_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_burst_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwr_prop_peak_limit_t to std::string
    std::string to_string( const SysmanResource::pwr_prop_peak_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_domain_type_t to std::string
    std::string to_string( const SysmanResource::freq_domain_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::dvfs_mode_t to std::string
    std::string to_string( const SysmanResource::dvfs_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_throttle_reasons_t to std::string
    std::string to_string( const SysmanResource::freq_throttle_reasons_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_divider_t to std::string
    std::string to_string( const SysmanResource::freq_divider_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_properties_t to std::string
    std::string to_string( const SysmanResource::freq_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_domain_type_t to std::string
    std::string to_string( const SysmanResource::freq_prop_domain_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_avail_clocks_t to std::string
    std::string to_string( const SysmanResource::freq_prop_avail_clocks_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_avail_dividers_t to std::string
    std::string to_string( const SysmanResource::freq_prop_avail_dividers_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_src_freq_t to std::string
    std::string to_string( const SysmanResource::freq_prop_src_freq_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_dvfs_mode_t to std::string
    std::string to_string( const SysmanResource::freq_prop_dvfs_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_freq_range_t to std::string
    std::string to_string( const SysmanResource::freq_prop_freq_range_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::freq_prop_freq_divider_t to std::string
    std::string to_string( const SysmanResource::freq_prop_freq_divider_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_promo_mode_t to std::string
    std::string to_string( const SysmanResource::pwrwell_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_properties_t to std::string
    std::string to_string( const SysmanResource::pwrwell_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::pwrwell_prop_promo_mode_t to std::string
    std::string to_string( const SysmanResource::pwrwell_prop_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::accel_properties_t to std::string
    std::string to_string( const SysmanResource::accel_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_type_t to std::string
    std::string to_string( const SysmanResource::mem_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_retire_reason_t to std::string
    std::string to_string( const SysmanResource::mem_retire_reason_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_retire_info_t to std::string
    std::string to_string( const SysmanResource::mem_retire_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_properties_t to std::string
    std::string to_string( const SysmanResource::mem_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_type_t to std::string
    std::string to_string( const SysmanResource::mem_prop_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_bad_list_t to std::string
    std::string to_string( const SysmanResource::mem_prop_bad_list_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_utilization_t to std::string
    std::string to_string( const SysmanResource::mem_prop_utilization_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_bandwidth_t to std::string
    std::string to_string( const SysmanResource::mem_prop_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::mem_prop_ecc_counters_t to std::string
    std::string to_string( const SysmanResource::mem_prop_ecc_counters_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_type_t to std::string
    std::string to_string( const SysmanResource::link_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_speed_t to std::string
    std::string to_string( const SysmanResource::link_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_properties_t to std::string
    std::string to_string( const SysmanResource::link_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_type_t to std::string
    std::string to_string( const SysmanResource::link_prop_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_bus_address_t to std::string
    std::string to_string( const SysmanResource::link_prop_bus_address_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_avail_speeds_t to std::string
    std::string to_string( const SysmanResource::link_prop_avail_speeds_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_bandwidth_t to std::string
    std::string to_string( const SysmanResource::link_prop_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_speed_t to std::string
    std::string to_string( const SysmanResource::link_prop_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanResource::link_prop_speed_range_t to std::string
    std::string to_string( const SysmanResource::link_prop_speed_range_t val );

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_SYSMAN_HPP
