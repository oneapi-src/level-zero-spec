/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_residency.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Memory Residency
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/residency.yml
 * @endcond
 *
 */
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Makes memory resident for the device.
/// 
/// @details
///     - If the application does not properly manage residency then the device
///       may experience unrecoverable page-faults.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceMakeMemoryResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    )
{
    auto pfnMakeMemoryResident = xe_lib::context.ddiTable.Device.pfnMakeMemoryResident;
    if( nullptr == pfnMakeMemoryResident )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnMakeMemoryResident( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allows memory to be evicted from the device.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the memory before it is evicted
///     - Memory is always implicitly evicted if it is resident when freed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceEvictMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    )
{
    auto pfnEvictMemory = xe_lib::context.ddiTable.Device.pfnEvictMemory;
    if( nullptr == pfnEvictMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnEvictMemory( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Makes image resident for the device.
/// 
/// @details
///     - If the application does not properly manage residency then the device
///       may experience unrecoverable page-faults.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceMakeImageResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    )
{
    auto pfnMakeImageResident = xe_lib::context.ddiTable.Device.pfnMakeImageResident;
    if( nullptr == pfnMakeImageResident )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnMakeImageResident( hDevice, hImage );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allows image to be evicted from the device.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the memory before it is evicted
///     - An image is always implicitly evicted if it is resident when
///       destroyed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == hImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeDeviceEvictImage(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    )
{
    auto pfnEvictImage = xe_lib::context.ddiTable.Device.pfnEvictImage;
    if( nullptr == pfnEvictImage )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnEvictImage( hDevice, hImage );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Makes memory resident for the device.
    /// 
    /// @details
    ///     - If the application does not properly manage residency then the device
    ///       may experience unrecoverable page-faults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Device::MakeMemoryResident(
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceMakeMemoryResident(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::MakeMemoryResident" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allows memory to be evicted from the device.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the memory before it is evicted
    ///     - Memory is always implicitly evicted if it is resident when freed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Device::EvictMemory(
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceEvictMemory(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::EvictMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Makes image resident for the device.
    /// 
    /// @details
    ///     - If the application does not properly manage residency then the device
    ///       may experience unrecoverable page-faults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Device::MakeImageResident(
        Image* pImage                                   ///< [in] pointer to image to make resident
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceMakeImageResident(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            reinterpret_cast<xe_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::MakeImageResident" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allows image to be evicted from the device.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the memory before it is evicted
    ///     - An image is always implicitly evicted if it is resident when
    ///       destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    Device::EvictImage(
        Image* pImage                                   ///< [in] pointer to image to make evict
        )
    {
        auto result = static_cast<result_t>( ::xeDeviceEvictImage(
            reinterpret_cast<xe_device_handle_t>( getHandle() ),
            reinterpret_cast<xe_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::Device::EvictImage" );
    }

} // namespace xe

namespace xe
{
} // namespace xe
