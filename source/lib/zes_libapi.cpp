/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_libapi.cpp
 *
 * @brief C++ static library for zes
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the handle to access Sysman features for a device
/// 
/// @details
///     - The returned handle is unique.
///     - ::zes_device_handle_t returned by ::zeDeviceGetSubDevices() are not
///       support. Only use handles returned by ::zeDeviceGet(). All resources
///       on sub-devices can be enumerated through the primary device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + version
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phSysman`
ze_result_t __zecall
zesSysmanGet(
    zes_device_handle_t hDevice,                    ///< [in] Handle of the device
    zes_sysman_version_t version,                   ///< [in] Sysman version that application was built with
    zes_sysman_handle_t* phSysman                   ///< [out] Handle for accessing Sysman features
    )
{
    auto pfnGet = ze_lib::context.zesDdiTable.Sysman.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGet( hDevice, version, phSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanDeviceGetProperties(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zes_sysman_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
    )
{
    auto pfnDeviceGetProperties = ze_lib::context.zesDdiTable.Sysman.pfnDeviceGetProperties;
    if( nullptr == pfnDeviceGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceGetProperties( hSysman, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about the state of the device - if a reset is
///        required, reasons for the reset and if the device has been repaired
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zesSysmanDeviceGetState(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zes_sysman_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
    )
{
    auto pfnDeviceGetState = ze_lib::context.zesDdiTable.Sysman.pfnDeviceGetState;
    if( nullptr == pfnDeviceGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceGetState( hSysman, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @details
///     - Performs a PCI bus reset of the device. This will result in all
///       current device state being lost.
///     - All applications using the device should be stopped before calling
///       this function.
///     - If the force argument is specified, all applications using the device
///       will be forcibly killed.
///     - The function will block until the device has restarted or a timeout
///       occurred waiting for the reset to complete.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE - "Reset cannot be performed because applications are using this device."
///     - ::ZE_RESULT_ERROR_UNKNOWN - "There were problems unloading the device driver, performing a bus reset or reloading the device driver."
ze_result_t __zecall
zesSysmanDeviceReset(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                    ///< device will be forcibly killed.
    )
{
    auto pfnDeviceReset = ze_lib::context.zesDdiTable.Sysman.pfnDeviceReset;
    if( nullptr == pfnDeviceReset )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceReset( hSysman, force );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle to a scheduler component
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanSchedulerGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_sched_handle_t* phScheduler          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnSchedulerGet = ze_lib::context.zesDdiTable.Sysman.pfnSchedulerGet;
    if( nullptr == pfnSchedulerGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerGet( hSysman, pCount, phScheduler );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a scheduler component
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanSchedulerGetProperties(
    zes_sysman_sched_handle_t hScheduler,           ///< [in] Handle for the component.
    zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanScheduler.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hScheduler, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current scheduling mode in effect on a scheduler component.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t __zecall
zesSysmanSchedulerGetCurrentMode(
    zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
    )
{
    auto pfnGetCurrentMode = ze_lib::context.zesDdiTable.SysmanScheduler.pfnGetCurrentMode;
    if( nullptr == pfnGetCurrentMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetCurrentMode( hScheduler, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMEOUT
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t __zecall
zesSysmanSchedulerGetTimeoutModeProperties(
    zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
    )
{
    auto pfnGetTimeoutModeProperties = ze_lib::context.zesDdiTable.SysmanScheduler.pfnGetTimeoutModeProperties;
    if( nullptr == pfnGetTimeoutModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMESLICE
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t __zecall
zesSysmanSchedulerGetTimesliceModeProperties(
    zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
    )
{
    auto pfnGetTimesliceModeProperties = ze_lib::context.zesDdiTable.SysmanScheduler.pfnGetTimesliceModeProperties;
    if( nullptr == pfnGetTimesliceModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMEOUT or update scheduler
///        mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized for multiple applications or contexts
///       submitting work to the hardware. When higher priority work arrives,
///       the scheduler attempts to pause the current executing work within some
///       timeout interval, then submits the other work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zesSysmanSchedulerSetTimeoutMode(
    zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetTimeoutMode = ze_lib::context.zesDdiTable.SysmanScheduler.pfnSetTimeoutMode;
    if( nullptr == pfnSetTimeoutMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMESLICE or update
///        scheduler mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized to provide fair sharing of hardware execution
///       time between multiple contexts submitting work to the hardware
///       concurrently.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zesSysmanSchedulerSetTimesliceMode(
    zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetTimesliceMode = ze_lib::context.zesDdiTable.SysmanScheduler.pfnSetTimesliceMode;
    if( nullptr == pfnSetTimesliceMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_EXCLUSIVE
/// 
/// @details
///     - This mode is optimized for single application/context use-cases. It
///       permits a context to run indefinitely on the hardware without being
///       preempted or terminated. All pending work for other contexts must wait
///       until the running context completes with no further submitted work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zesSysmanSchedulerSetExclusiveMode(
    zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetExclusiveMode = ze_lib::context.zesDdiTable.SysmanScheduler.pfnSetExclusiveMode;
    if( nullptr == pfnSetExclusiveMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetExclusiveMode( hScheduler, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_COMPUTE_UNIT_DEBUG
/// 
/// @details
///     - This mode is optimized for application debug. It ensures that only one
///       command queue can execute work on the hardware at a given time. Work
///       is permitted to run as long as needed without enforcing any scheduler
///       fairness policies.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zesSysmanSchedulerSetComputeUnitDebugMode(
    zes_sysman_sched_handle_t hScheduler,           ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    auto pfnSetComputeUnitDebugMode = ze_lib::context.zesDdiTable.SysmanScheduler.pfnSetComputeUnitDebugMode;
    if( nullptr == pfnSetComputeUnitDebugMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handles to accelerator domains whose performance can be optimized
///        via a Performance Factor
/// 
/// @details
///     - A Performance Factor should be tuned for each workload.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanPerformanceFactorGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_perf_handle_t* phPerf                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnPerformanceFactorGet = ze_lib::context.zesDdiTable.Sysman.pfnPerformanceFactorGet;
    if( nullptr == pfnPerformanceFactorGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPerformanceFactorGet( hSysman, pCount, phPerf );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about a Performance Factor domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanPerformanceFactorGetProperties(
    zes_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
    zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                    ///< Factor domain.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanPerformanceFactor.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPerf, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current Performance Factor for a given domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFactor`
ze_result_t __zecall
zesSysmanPerformanceFactorGetConfig(
    zes_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
    double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                    ///< hardware (may not be the same as the requested Performance Factor).
    )
{
    auto pfnGetConfig = ze_lib::context.zesDdiTable.SysmanPerformanceFactor.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hPerf, pFactor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the performance factor for a domain
/// 
/// @details
///     - The Performance Factor is a number between 0 and 100.
///     - A Performance Factor is a hint to the hardware. Depending on the
///       hardware, the request may not be granted. Follow up this function with
///       a call to ::zesSysmanPerformanceFactorGetConfig() to determine the
///       actual factor being used by the hardware.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
ze_result_t __zecall
zesSysmanPerformanceFactorSetConfig(
    zes_sysman_perf_handle_t hPerf,                 ///< [in] Handle for the Performance Factor domain.
    double factor                                   ///< [in] The new Performance Factor.
    )
{
    auto pfnSetConfig = ze_lib::context.zesDdiTable.SysmanPerformanceFactor.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hPerf, factor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about host processes using the device
/// 
/// @details
///     - The number of processes connected to the device is dynamic. This means
///       that between a call to determine the correct value of pCount and the
///       subsequent call, the number of processes may have increased. It is
///       recommended that a large array be passed in so as to avoid receiving
///       the error ::ZE_RESULT_ERROR_INVALID_SIZE.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + The provided value of pCount is not big enough to store information about all the processes currently attached to the device.
ze_result_t __zecall
zesSysmanProcessesGetState(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of processes currently using the device.
                                                    ///< if count is non-zero but less than the number of processes, the driver
                                                    ///< will set to the number of processes currently using the device and
                                                    ///< return the error ::ZE_RESULT_ERROR_INVALID_SIZE.
                                                    ///< if count is larger than the number of processes, then the driver will
                                                    ///< update the value with the correct number of processes that are returned.
    zes_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                    ///< one for each process currently using the device
    )
{
    auto pfnProcessesGetState = ze_lib::context.zesDdiTable.Sysman.pfnProcessesGetState;
    if( nullptr == pfnProcessesGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnProcessesGetState( hSysman, pCount, pProcesses );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI properties - address, max speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanPciGetProperties(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
    )
{
    auto pfnPciGetProperties = ze_lib::context.zesDdiTable.Sysman.pfnPciGetProperties;
    if( nullptr == pfnPciGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetProperties( hSysman, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current PCI state - current speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zesSysmanPciGetState(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
    )
{
    auto pfnPciGetState = ze_lib::context.zesDdiTable.Sysman.pfnPciGetState;
    if( nullptr == pfnPciGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetState( hSysman, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about each configured bar
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanPciGetBars(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of bars.
                                                    ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                    ///< if count is larger than the number of bar, then the driver will update
                                                    ///< the value with the correct number of bars that are returned.
    zes_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of bar properties
    )
{
    auto pfnPciGetBars = ze_lib::context.zesDdiTable.Sysman.pfnPciGetBars;
    if( nullptr == pfnPciGetBars )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetBars( hSysman, pCount, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI stats - bandwidth, number of packets, number of replays
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zesSysmanPciGetStats(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
    )
{
    auto pfnPciGetStats = ze_lib::context.zesDdiTable.Sysman.pfnPciGetStats;
    if( nullptr == pfnPciGetStats )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetStats( hSysman, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanPowerGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_pwr_handle_t* phPower                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnPowerGet = ze_lib::context.zesDdiTable.Sysman.pfnPowerGet;
    if( nullptr == pfnPowerGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPowerGet( hSysman, pCount, phPower );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a power domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanPowerGetProperties(
    zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanPower.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPower, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEnergy`
ze_result_t __zecall
zesSysmanPowerGetEnergyCounter(
    zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
    )
{
    auto pfnGetEnergyCounter = ze_lib::context.zesDdiTable.SysmanPower.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetEnergyCounter( hPower, pEnergy );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
ze_result_t __zecall
zesSysmanPowerGetLimits(
    zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit.
    zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit.
    zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit.
    )
{
    auto pfnGetLimits = ze_lib::context.zesDdiTable.SysmanPower.pfnGetLimits;
    if( nullptr == pfnGetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t __zecall
zesSysmanPowerSetLimits(
    zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
    const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
    const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
    )
{
    auto pfnSetLimits = ze_lib::context.zesDdiTable.SysmanPower.pfnSetLimits;
    if( nullptr == pfnSetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy threshold
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThreshold`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check ::zes_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t __zecall
zesSysmanPowerGetEnergyThreshold(
    zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                    ///< enabled/energy threshold/process ID.
    )
{
    auto pfnGetEnergyThreshold = ze_lib::context.zesDdiTable.SysmanPower.pfnGetEnergyThreshold;
    if( nullptr == pfnGetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetEnergyThreshold( hPower, pThreshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
/// 
/// @details
///     - An event ::ZES_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED will be
///       generated when the delta energy consumed starting from this call
///       exceeds the specified threshold. Use the function
///       ::zesSysmanEventSetConfig() to start receiving the event.
///     - Only one running process can control the energy threshold at a given
///       time. If another process attempts to change the energy threshold, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesSysmanPowerGetEnergyThreshold() to determine the process ID
///       currently controlling this setting.
///     - Calling this function will remove any pending energy thresholds and
///       start counting from the time of this call.
///     - Once the energy threshold has been reached and the event generated,
///       the threshold is automatically removed. It is up to the application to
///       request a new threshold.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check ::zes_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process has set the energy threshold.
ze_result_t __zecall
zesSysmanPowerSetEnergyThreshold(
    zes_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    double threshold                                ///< [in] The energy threshold to be set in joules.
    )
{
    auto pfnSetEnergyThreshold = ze_lib::context.zesDdiTable.SysmanPower.pfnSetEnergyThreshold;
    if( nullptr == pfnSetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetEnergyThreshold( hPower, threshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of frequency domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanFrequencyGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_freq_handle_t* phFrequency           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnFrequencyGet = ze_lib::context.zesDdiTable.Sysman.pfnFrequencyGet;
    if( nullptr == pfnFrequencyGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFrequencyGet( hSysman, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency properties - available frequencies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanFrequencyGetProperties(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanFrequency.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFrequency, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get available non-overclocked hardware clock frequencies for the
///        frequency domain
/// 
/// @details
///     - The list of available frequencies is returned in order of slowest to
///       fastest.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanFrequencyGetAvailableClocks(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of frequencies available.
                                                    ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                    ///< If count is larger than the number of frequencies available, then the
                                                    ///< driver will update the value with the correct number of frequencies available.
    double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                    ///< MHz and sorted from slowest to fastest
    )
{
    auto pfnGetAvailableClocks = ze_lib::context.zesDdiTable.SysmanFrequency.pfnGetAvailableClocks;
    if( nullptr == pfnGetAvailableClocks )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
ze_result_t __zecall
zesSysmanFrequencyGetRange(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    auto pfnGetRange = ze_lib::context.zesDdiTable.SysmanFrequency.pfnGetRange;
    if( nullptr == pfnGetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency range between which the hardware can operate.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zesSysmanFrequencySetRange(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    auto pfnSetRange = ze_lib::context.zesDdiTable.SysmanFrequency.pfnSetRange;
    if( nullptr == pfnSetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency state - frequency request, actual frequency, TDP
///        limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zesSysmanFrequencyGetState(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanFrequency.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hFrequency, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency throttle time
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThrottleTime`
ze_result_t __zecall
zesSysmanFrequencyGetThrottleTime(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    )
{
    auto pfnGetThrottleTime = ze_lib::context.zesDdiTable.SysmanFrequency.pfnGetThrottleTime;
    if( nullptr == pfnGetThrottleTime )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetThrottleTime( hFrequency, pThrottleTime );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the overclocking capabilities.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcCapabilities`
ze_result_t __zecall
zesSysmanFrequencyOcGetCapabilities(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                    ///< ::zes_oc_capabilities_t.
    )
{
    auto pfnOcGetCapabilities = ze_lib::context.zesDdiTable.SysmanFrequency.pfnOcGetCapabilities;
    if( nullptr == pfnOcGetCapabilities )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking configuration.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcConfiguration`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
ze_result_t __zecall
zesSysmanFrequencyOcGetConfig(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zes_oc_config_t* pOcConfiguration               ///< [in,out] Pointer to the configuration structure ::zes_oc_config_t.
    )
{
    auto pfnOcGetConfig = ze_lib::context.zesDdiTable.SysmanFrequency.pfnOcGetConfig;
    if( nullptr == pfnOcGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetConfig( hFrequency, pOcConfiguration );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the overclocking configuration.
/// 
/// @details
///     - If ::zes_oc_config_t.mode is set to ::ZES_OC_MODE_OFF, overclocking
///       will be turned off and the hardware returned to run with factory
///       voltages/frequencies. Call ::zesSysmanFrequencyOcSetIccMax() and
///       ::zesSysmanFrequencyOcSetTjMax() separately with 0.0 to return those
///       settings to factory defaults.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcConfiguration`
///         + `nullptr == pDeviceRestart`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zes_oc_capabilities_t.maxOcFrequency, ::zes_oc_capabilities_t.maxOcVoltage, ::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zes_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zesSysmanFrequencyOcSetConfig(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zes_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zes_oc_config_t.
    ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                    ///< in order to enable the new overclock settings.
    )
{
    auto pfnOcSetConfig = ze_lib::context.zesDdiTable.SysmanFrequency.pfnOcSetConfig;
    if( nullptr == pfnOcSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum current limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcIccMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
ze_result_t __zecall
zesSysmanFrequencyOcGetIccMax(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                    ///< successful return.
    )
{
    auto pfnOcGetIccMax = ze_lib::context.zesDdiTable.SysmanFrequency.pfnOcGetIccMax;
    if( nullptr == pfnOcGetIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetIccMax( hFrequency, pOcIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum current limit setting.
/// 
/// @details
///     - Setting ocIccMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified current limit is too low or too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zesSysmanFrequencyOcSetIccMax(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
    )
{
    auto pfnOcSetIccMax = ze_lib::context.zesDdiTable.SysmanFrequency.pfnOcSetIccMax;
    if( nullptr == pfnOcSetIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetIccMax( hFrequency, ocIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum temperature limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcTjMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
ze_result_t __zecall
zesSysmanFrequencyOcGetTjMax(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                    ///< on successful return.
    )
{
    auto pfnOcGetTjMax = ze_lib::context.zesDdiTable.SysmanFrequency.pfnOcGetTjMax;
    if( nullptr == pfnOcGetTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetTjMax( hFrequency, pOcTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum temperature limit setting.
/// 
/// @details
///     - Setting ocTjMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zes_oc_capabilities_t.isOcSupported)
///         + Capability ::zes_oc_capabilities_t.isTjMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified temperature limit is too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zesSysmanFrequencyOcSetTjMax(
    zes_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
    )
{
    auto pfnOcSetTjMax = ze_lib::context.zesDdiTable.SysmanFrequency.pfnOcSetTjMax;
    if( nullptr == pfnOcSetTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetTjMax( hFrequency, ocTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of engine groups
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanEngineGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_engine_handle_t* phEngine            ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnEngineGet = ze_lib::context.zesDdiTable.Sysman.pfnEngineGet;
    if( nullptr == pfnEngineGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEngineGet( hSysman, pCount, phEngine );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine group properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanEngineGetProperties(
    zes_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanEngine.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hEngine, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the activity stats for an engine group
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
ze_result_t __zecall
zesSysmanEngineGetActivity(
    zes_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                    ///< counters.
    )
{
    auto pfnGetActivity = ze_lib::context.zesDdiTable.SysmanEngine.pfnGetActivity;
    if( nullptr == pfnGetActivity )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetActivity( hEngine, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of standby controls
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanStandbyGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_standby_handle_t* phStandby          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnStandbyGet = ze_lib::context.zesDdiTable.Sysman.pfnStandbyGet;
    if( nullptr == pfnStandbyGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnStandbyGet( hSysman, pCount, phStandby );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get standby hardware component properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanStandbyGetProperties(
    zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanStandby.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hStandby, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
ze_result_t __zecall
zesSysmanStandbyGetMode(
    zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
    )
{
    auto pfnGetMode = ze_lib::context.zesDdiTable.SysmanStandby.pfnGetMode;
    if( nullptr == pfnGetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetMode( hStandby, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + mode
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zesSysmanStandbySetMode(
    zes_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
    )
{
    auto pfnSetMode = ze_lib::context.zesDdiTable.SysmanStandby.pfnSetMode;
    if( nullptr == pfnSetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetMode( hStandby, mode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of firmwares
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanFirmwareGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_firmware_handle_t* phFirmware        ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnFirmwareGet = ze_lib::context.zesDdiTable.Sysman.pfnFirmwareGet;
    if( nullptr == pfnFirmwareGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFirmwareGet( hSysman, pCount, phFirmware );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanFirmwareGetProperties(
    zes_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                    ///< firmware
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanFirmware.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFirmware, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware checksum
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pChecksum`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t __zecall
zesSysmanFirmwareGetChecksum(
    zes_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
    )
{
    auto pfnGetChecksum = ze_lib::context.zesDdiTable.SysmanFirmware.pfnGetChecksum;
    if( nullptr == pfnGetChecksum )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetChecksum( hFirmware, pChecksum );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Flash a new firmware image
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImage`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t __zecall
zesSysmanFirmwareFlash(
    zes_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    )
{
    auto pfnFlash = ze_lib::context.zesDdiTable.SysmanFirmware.pfnFlash;
    if( nullptr == pfnFlash )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFlash( hFirmware, pImage, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of memory modules
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanMemoryGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_mem_handle_t* phMemory               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnMemoryGet = ze_lib::context.zesDdiTable.Sysman.pfnMemoryGet;
    if( nullptr == pfnMemoryGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnMemoryGet( hSysman, pCount, phMemory );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanMemoryGetProperties(
    zes_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanMemory.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hMemory, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory state - health, allocated
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zesSysmanMemoryGetState(
    zes_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanMemory.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hMemory, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory bandwidth
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBandwidth`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zesSysmanMemoryGetBandwidth(
    zes_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the current health, free memory, total memory
                                                    ///< size.
    )
{
    auto pfnGetBandwidth = ze_lib::context.zesDdiTable.SysmanMemory.pfnGetBandwidth;
    if( nullptr == pfnGetBandwidth )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetBandwidth( hMemory, pBandwidth );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of Fabric ports in a device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanFabricPortGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_fabric_port_handle_t* phPort         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnFabricPortGet = ze_lib::context.zesDdiTable.Sysman.pfnFabricPortGet;
    if( nullptr == pfnFabricPortGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFabricPortGet( hSysman, pCount, phPort );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanFabricPortGetProperties(
    zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanFabricPort.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPort, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port link type
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLinkType`
ze_result_t __zecall
zesSysmanFabricPortGetLinkType(
    zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
    zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                    ///< port.
    )
{
    auto pfnGetLinkType = ze_lib::context.zesDdiTable.SysmanFabricPort.pfnGetLinkType;
    if( nullptr == pfnGetLinkType )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetLinkType( hPort, verbose, pLinkType );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zesSysmanFabricPortGetConfig(
    zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
    )
{
    auto pfnGetConfig = ze_lib::context.zesDdiTable.SysmanFabricPort.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zesSysmanFabricPortSetConfig(
    zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
    )
{
    auto pfnSetConfig = ze_lib::context.zesDdiTable.SysmanFabricPort.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port state - status (green/yellow/red/black), reasons for
///        link degradation or instability, current rx/tx speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zesSysmanFabricPortGetState(
    zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanFabricPort.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hPort, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port throughput
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThroughput`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zesSysmanFabricPortGetThroughput(
    zes_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
    )
{
    auto pfnGetThroughput = ze_lib::context.zesDdiTable.SysmanFabricPort.pfnGetThroughput;
    if( nullptr == pfnGetThroughput )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetThroughput( hPort, pThroughput );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of temperature sensors
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanTemperatureGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_temp_handle_t* phTemperature         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnTemperatureGet = ze_lib::context.zesDdiTable.Sysman.pfnTemperatureGet;
    if( nullptr == pfnTemperatureGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnTemperatureGet( hSysman, pCount, phTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature sensor properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanTemperatureGetProperties(
    zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanTemperature.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hTemperature, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature configuration for this sensor - which events are
///        triggered and the trigger conditions
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally this is only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL
///         + One or both of the thresholds is not supported - check ::zes_temp_properties_t.isThreshold1Supported and ::zes_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t __zecall
zesSysmanTemperatureGetConfig(
    zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
    )
{
    auto pfnGetConfig = ze_lib::context.zesDdiTable.SysmanTemperature.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature configuration for this sensor - indicates which events
///        are triggered and the trigger conditions
/// 
/// @details
///     - Events ::ZES_SYSMAN_EVENT_TYPE_TEMP_CRITICAL will be triggered when
///       temperature reaches the critical range. Use the function
///       ::zesSysmanEventSetConfig() to start receiving this event.
///     - Events ::ZES_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 and
///       ::ZES_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 will be generated when
///       temperature cross the thresholds set using this function. Use the
///       function ::zesSysmanEventSetConfig() to start receiving these events.
///     - Only one running process can set the temperature configuration at a
///       time. If another process attempts to change the configuration, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesSysmanTemperatureGetConfig() will return the process ID currently
///       controlling these settings.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally they are only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL
///         + Enabling the critical temperature event is not supported - check ::zes_temp_properties_t.isCriticalTempSupported
///         + One or both of the thresholds is not supported - check ::zes_temp_properties_t.isThreshold1Supported and ::zes_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or both the thresholds is above TjMax (see ::zesSysmanFrequencyOcGetTjMax()). Temperature thresholds must be below this value.
ze_result_t __zecall
zesSysmanTemperatureSetConfig(
    zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    const zes_temp_config_t* pConfig                ///< [in] New configuration.
    )
{
    auto pfnSetConfig = ze_lib::context.zesDdiTable.SysmanTemperature.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the temperature from a specified sensor
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTemperature`
ze_result_t __zecall
zesSysmanTemperatureGetState(
    zes_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                    ///< in degrees Celsius.
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanTemperature.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hTemperature, pTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power supplies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanPsuGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_psu_handle_t* phPsu                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnPsuGet = ze_lib::context.zesDdiTable.Sysman.pfnPsuGet;
    if( nullptr == pfnPsuGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPsuGet( hSysman, pCount, phPsu );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power supply properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanPsuGetProperties(
    zes_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanPsu.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPsu, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current power supply state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zesSysmanPsuGetState(
    zes_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanPsu.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hPsu, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of fans
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanFanGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_fan_handle_t* phFan                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnFanGet = ze_lib::context.zesDdiTable.Sysman.pfnFanGet;
    if( nullptr == pfnFanGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFanGet( hSysman, pCount, phFan );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanFanGetProperties(
    zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanFan.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFan, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current fan configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zesSysmanFanGetConfig(
    zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
    )
{
    auto pfnGetConfig = ze_lib::context.zesDdiTable.SysmanFan.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hFan, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zesSysmanFanSetConfig(
    zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    const zes_fan_config_t* pConfig                 ///< [in] New fan configuration.
    )
{
    auto pfnSetConfig = ze_lib::context.zesDdiTable.SysmanFan.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hFan, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a fan - current mode and speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + units
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSpeed`
ze_result_t __zecall
zesSysmanFanGetState(
    zes_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                    ///< requested.
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanFan.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hFan, units, pSpeed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of LEDs
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanLedGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_led_handle_t* phLed                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnLedGet = ze_lib::context.zesDdiTable.Sysman.pfnLedGet;
    if( nullptr == pfnLedGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnLedGet( hSysman, pCount, phLed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get LED properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanLedGetProperties(
    zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanLed.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hLed, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a LED - on/off, color
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zesSysmanLedGetState(
    zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanLed.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hLed, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set state of a LED - on/off, color
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zesSysmanLedSetState(
    zes_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    const zes_led_state_t* pState                   ///< [in] New state of the LED.
    )
{
    auto pfnSetState = ze_lib::context.zesDdiTable.SysmanLed.pfnSetState;
    if( nullptr == pfnSetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetState( hLed, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of all RAS error sets on a device
/// 
/// @details
///     - A RAS error set is a collection of RAS error counters of a given type
///       (correctable/uncorrectable) from hardware blocks contained within a
///       sub-device or within the device.
///     - A device without sub-devices will typically return two handles, one
///       for correctable errors sets and one for uncorrectable error sets.
///     - A device with sub-devices will return RAS error sets for each
///       sub-device and possibly RAS error sets for hardware blocks outside the
///       sub-devices.
///     - If the function completes successfully but pCount is set to 0, RAS
///       features are not available/enabled on this device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanRasGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_ras_handle_t* phRas                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnRasGet = ze_lib::context.zesDdiTable.Sysman.pfnRasGet;
    if( nullptr == pfnRasGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnRasGet( hSysman, pCount, phRas );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS properties of a given RAS error set - this enables discovery
///        of the type of RAS error set (correctable/uncorrectable) and if
///        located on a sub-device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanRasGetProperties(
    zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanRas.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hRas, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the configured
///       threshold, the event ::ZES_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS
///       will be triggered.
///     - When a particular RAS uncorrectable error counter exceeds the
///       configured threshold, the event
///       ::ZES_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be triggered.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zesSysmanRasGetConfig(
    zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                    ///< thresholds used to trigger events
    )
{
    auto pfnGetConfig = ze_lib::context.zesDdiTable.SysmanRas.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the specified
///       threshold, the event ::ZES_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS
///       will be generated.
///     - When a particular RAS uncorrectable error counter exceeds the
///       specified threshold, the event
///       ::ZES_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be generated.
///     - Call ::zesSysmanRasGetState() and set the clear flag to true to
///       restart event generation once counters have exceeded thresholds.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to set thresholds.
ze_result_t __zecall
zesSysmanRasSetConfig(
    zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
    )
{
    auto pfnSetConfig = ze_lib::context.zesDdiTable.SysmanRas.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current value of RAS error counters for a particular error set
/// 
/// @details
///     - Clearing errors will affect other threads/applications - the counter
///       values will start from zero.
///     - Clearing errors requires write permissions.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTotalErrors`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t __zecall
zesSysmanRasGetState(
    zes_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    uint64_t* pTotalErrors,                         ///< [in,out] The number total number of errors that have occurred
    zes_ras_details_t* pDetails                     ///< [in,out][optional] Breakdown of where errors have occurred
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanRas.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hRas, clear, pTotalErrors, pDetails );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the event handle for the specified device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvent`
ze_result_t __zecall
zesSysmanEventGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    zes_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
    )
{
    auto pfnEventGet = ze_lib::context.zesDdiTable.Sysman.pfnEventGet;
    if( nullptr == pfnEventGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEventGet( hSysman, phEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which events are currently registered on the specified device
///        event handler
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zesSysmanEventGetConfig(
    zes_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
    zes_event_config_t* pConfig                     ///< [in,out] Will contain the current event configuration (list of
                                                    ///< registered events).
    )
{
    auto pfnGetConfig = ze_lib::context.zesDdiTable.SysmanEvent.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hEvent, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set a new event configuration (list of registered events) on the
///        specified device event handler
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zesSysmanEventSetConfig(
    zes_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
    const zes_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
    )
{
    auto pfnSetConfig = ze_lib::context.zesDdiTable.SysmanEvent.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hEvent, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get events that have been triggered for a specific device
/// 
/// @details
///     - If events have occurred on the specified device event handle, they are
///       returned and the corresponding event status is cleared if the argument
///       clear = true.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEvents`
ze_result_t __zecall
zesSysmanEventGetState(
    zes_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device.
    ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
    uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_sysman_event_type_t that have been
                                                    ///< triggered by this device.
    )
{
    auto pfnGetState = ze_lib::context.zesDdiTable.SysmanEvent.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hEvent, clear, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for the specified list of event handles to receive any registered
///        events
/// 
/// @details
///     - If previous events arrived and were not cleared using
///       ::zesSysmanEventGetState(), this call will return immediately.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied event handles are for devices that belong to a different driver handle.
ze_result_t __zecall
zesSysmanEventListen(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                    ///< ::ZES_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                    ///< ::ZES_EVENT_WAIT_INFINITE to block until events arrive.
    uint32_t count,                                 ///< [in] Number of handles in phEvents
    zes_sysman_event_handle_t* phEvents,            ///< [in][range(0, count)] Handle of events that should be listened to
    uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zes_sysman_event_type_t that have been
                                                    ///< triggered by any of the supplied event handles. If timeout is not
                                                    ///< ::ZES_EVENT_WAIT_INFINITE and this value is
                                                    ///< ::ZES_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
    )
{
    auto pfnListen = ze_lib::context.zesDdiTable.SysmanEvent.pfnListen;
    if( nullptr == pfnListen )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnListen( hDriver, timeout, count, phEvents, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of diagnostics test suites
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanDiagnosticsGet(
    zes_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zes_sysman_diag_handle_t* phDiagnostics         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnDiagnosticsGet = ze_lib::context.zesDdiTable.Sysman.pfnDiagnosticsGet;
    if( nullptr == pfnDiagnosticsGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties of a diagnostics test suite
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zesSysmanDiagnosticsGetProperties(
    zes_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                    ///< suite
    )
{
    auto pfnGetProperties = ze_lib::context.zesDdiTable.SysmanDiagnostics.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hDiagnostics, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get individual tests that can be run separately. Not all test suites
///        permit running individual tests - check
///        ::zes_diag_properties_t.haveTests
/// 
/// @details
///     - The list of available tests is returned in order of increasing test
///       index ::zes_diag_test_t.index.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zesSysmanDiagnosticsGetTests(
    zes_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of tests available.
                                                    ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                    ///< If count is larger than the number of tests available, then the driver
                                                    ///< will update the value with the correct number of tests available.
    zes_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
                                                    ///< increasing value of ::zes_diag_test_t.index
    )
{
    auto pfnGetTests = ze_lib::context.zesDdiTable.SysmanDiagnostics.pfnGetTests;
    if( nullptr == pfnGetTests )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTests( hDiagnostics, pCount, pTests );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - WARNING: Performancing diagnostics may destroy current device state
///       information. Gracefully close any running workloads before initiating.
///     - To run all tests in a test suite, set start =
///       ::ZES_DIAG_FIRST_TEST_INDEX and end = ::ZES_DIAG_LAST_TEST_INDEX.
///     - If the test suite permits running individual tests,
///       ::zes_diag_properties_t.haveTests will be true. In this case, the
///       function ::zesSysmanDiagnosticsGetTests() can be called to get the
///       list of tests and corresponding indices that can be supplied to the
///       arguments start and end in this function.
///     - This function will block until the diagnostics have completed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pResult`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform diagnostics.
ze_result_t __zecall
zesSysmanDiagnosticsRunTests(
    zes_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
    )
{
    auto pfnRunTests = ze_lib::context.zesDdiTable.SysmanDiagnostics.pfnRunTests;
    if( nullptr == pfnRunTests )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnRunTests( hDiagnostics, start, end, pResult );
}

} // extern "C"
