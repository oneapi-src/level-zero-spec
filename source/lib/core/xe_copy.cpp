/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_copy.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Copies
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/copy.yml
 * @endcond
 *
 */
#include "xe_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies host, device, or shared memory.
/// 
/// @details
///     - The memory pointed to by both srcptr and dstptr must be accessible by
///       the device on which the command list is created.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyBuffer**
///     - **clEnqueueReadBuffer**
///     - **clEnqueueWriteBuffer**
///     - **clEnqueueSVMMemcpy**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == srcptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendMemoryCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendMemoryCopy = xe_lib::context.ddiTable.CommandList.pfnAppendMemoryCopy;
    if( nullptr == pfnAppendMemoryCopy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Initializes host, device, or shared memory.
/// 
/// @details
///     - The memory pointed to by dstptr must be accessible by the device on
///       which the command list is created.
///     - The value to initialize memory to is interpreted as an 8-bit unsigned
///       char; the upper 24-bits are ignored.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueFillBuffer**
///     - **clEnqueueSVMMemFill**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendMemorySet(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    int value,                                      ///< [in] value to initialize memory to
    size_t size,                                    ///< [in] size in bytes to initailize
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendMemorySet = xe_lib::context.ddiTable.CommandList.pfnAppendMemorySet;
    if( nullptr == pfnAppendMemorySet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMemorySet( hCommandList, ptr, value, size, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region from a 2D array of host, device, or shared memory.
/// 
/// @details
///     - The memory pointed to by both srcptr and dstptr must be accessible by
///       the device on which the command list is created.
///     - The region width and height for both src and dst must be same. The
///       origins can be different.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == dstRegion
///         + nullptr == srcptr
///         + nullptr == srcRegion
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendMemoryCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const xe_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
    uint32_t dstPitch,                              ///< [in] destination pitch in bytes
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const xe_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
    uint32_t srcPitch,                              ///< [in] source pitch in bytes
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendMemoryCopyRegion = xe_lib::context.ddiTable.CommandList.pfnAppendMemoryCopyRegion;
    if( nullptr == pfnAppendMemoryCopyRegion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a image.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyImage**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendImageCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendImageCopy = xe_lib::context.ddiTable.CommandList.pfnAppendImageCopy;
    if( nullptr == pfnAppendImageCopy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region of a image to another image.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendImageCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const xe_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    const xe_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendImageCopyRegion = xe_lib::context.ddiTable.CommandList.pfnAppendImageCopyRegion;
    if( nullptr == pfnAppendImageCopyRegion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies from a image to device or shared memory.
/// 
/// @details
///     - The memory pointed to by dstptr must be accessible by the device on
///       which the command list is created.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueReadImage
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendImageCopyToMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const xe_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendImageCopyToMemory = xe_lib::context.ddiTable.CommandList.pfnAppendImageCopyToMemory;
    if( nullptr == pfnAppendImageCopyToMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies to a image from device or shared memory.
/// 
/// @details
///     - The memory pointed to by srcptr must be accessible by the device on
///       which the command list is created.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueWriteImage
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == srcptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendImageCopyFromMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const xe_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendImageCopyFromMemory = xe_lib::context.ddiTable.CommandList.pfnAppendImageCopyFromMemory;
    if( nullptr == pfnAppendImageCopyFromMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Asynchronously prefetches shared memory to the device associated with
///        the specified command list
/// 
/// @details
///     - This is a hint to improve performance only and is not required for
///       correctness.
///     - Only prefetching to the device associated with the specified command
///       list is supported.
///       Prefetching to the host or to a peer device is not supported.
///     - Prefetching may not be supported for all allocation types for all devices.
///       If memory prefetching is not supported for the specified memory range
///       the prefetch hint may be ignored.
///     - Prefetching may only be supported at a device-specific granularity,
///       such as at a page boundary.
///       In this case, the memory range may be expanded such that the start and
///       end of the range satisfy granularity requirements.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - cudaMemPrefetchAsync
///     - clEnqueueSVMMigrateMem
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendMemoryPrefetch(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t size                                     ///< [in] size in bytes of the memory range to prefetch
    )
{
    auto pfnAppendMemoryPrefetch = xe_lib::context.ddiTable.CommandList.pfnAppendMemoryPrefetch;
    if( nullptr == pfnAppendMemoryPrefetch )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMemoryPrefetch( hCommandList, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a shared memory range
/// 
/// @details
///     - Memory advice is a performance hint only and is not required for
///       functional correctness.
///     - Memory advice can be used to override driver heuristics to explicitly
///       control shared memory behavior.
///     - Not all memory advice hints may be supported for all allocation types
///       for all devices.
///       If a memory advice hint is not supported by the device it will be ignored.
///     - Memory advice may only be supported at a device-specific granularity,
///       such as at a page boundary.
///       In this case, the memory range may be expanded such that the start and
///       end of the range satisfy granularity requirements.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cudaMemAdvise**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hDevice
///         + nullptr == ptr
///         + invalid value for advice
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xeCommandListAppendMemAdvise(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    auto pfnAppendMemAdvise = xe_lib::context.ddiTable.CommandList.pfnAppendMemAdvise;
    if( nullptr == pfnAppendMemAdvise )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
}

} // extern "C"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies host, device, or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by both srcptr and dstptr must be accessible by
    ///       the device on which the command list is created.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueCopyBuffer**
    ///     - **clEnqueueReadBuffer**
    ///     - **clEnqueueWriteBuffer**
    ///     - **clEnqueueSVMMemcpy**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMemoryCopy(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendMemoryCopy(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            dstptr,
            srcptr,
            size,
            ( pEvent ) ? reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendMemoryCopy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes host, device, or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by dstptr must be accessible by the device on
    ///       which the command list is created.
    ///     - The value to initialize memory to is interpreted as an 8-bit unsigned
    ///       char; the upper 24-bits are ignored.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueFillBuffer**
    ///     - **clEnqueueSVMMemFill**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMemorySet(
        void* ptr,                                      ///< [in] pointer to memory to initialize
        int value,                                      ///< [in] value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initailize
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendMemorySet(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            ptr,
            value,
            size,
            ( pEvent ) ? reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendMemorySet" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a region from a 2D array of host, device, or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by both srcptr and dstptr must be accessible by
    ///       the device on which the command list is created.
    ///     - The region width and height for both src and dst must be same. The
    ///       origins can be different.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMemoryCopyRegion(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const copy_region_t* dstRegion,                 ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const copy_region_t* srcRegion,                 ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendMemoryCopyRegion(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<const xe_copy_region_t*>( dstRegion ),
            dstPitch,
            srcptr,
            reinterpret_cast<const xe_copy_region_t*>( srcRegion ),
            srcPitch,
            ( pEvent ) ? reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendMemoryCopyRegion" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a image.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueCopyImage**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendImageCopy(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendImageCopy(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<xe_image_handle_t>( pSrcImage->getHandle() ),
            ( pEvent ) ? reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendImageCopy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a region of a image to another image.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendImageCopyRegion(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendImageCopyRegion(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<xe_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const xe_image_region_t*>( pDstRegion ),
            reinterpret_cast<const xe_image_region_t*>( pSrcRegion ),
            ( pEvent ) ? reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendImageCopyRegion" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies from a image to device or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by dstptr must be accessible by the device on
    ///       which the command list is created.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clEnqueueReadImage
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendImageCopyToMemory(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendImageCopyToMemory(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<xe_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const xe_image_region_t*>( pSrcRegion ),
            ( pEvent ) ? reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendImageCopyToMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies to a image from device or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by srcptr must be accessible by the device on
    ///       which the command list is created.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clEnqueueWriteImage
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendImageCopyFromMemory(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendImageCopyFromMemory(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_image_handle_t>( pDstImage->getHandle() ),
            srcptr,
            reinterpret_cast<const xe_image_region_t*>( pDstRegion ),
            ( pEvent ) ? reinterpret_cast<xe_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendImageCopyFromMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Asynchronously prefetches shared memory to the device associated with
    ///        the specified command list
    /// 
    /// @details
    ///     - This is a hint to improve performance only and is not required for
    ///       correctness.
    ///     - Only prefetching to the device associated with the specified command
    ///       list is supported.
    ///       Prefetching to the host or to a peer device is not supported.
    ///     - Prefetching may not be supported for all allocation types for all devices.
    ///       If memory prefetching is not supported for the specified memory range
    ///       the prefetch hint may be ignored.
    ///     - Prefetching may only be supported at a device-specific granularity,
    ///       such as at a page boundary.
    ///       In this case, the memory range may be expanded such that the start and
    ///       end of the range satisfy granularity requirements.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - cudaMemPrefetchAsync
    ///     - clEnqueueSVMMigrateMem
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMemoryPrefetch(
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendMemoryPrefetch(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendMemoryPrefetch" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Provides advice about the use of a shared memory range
    /// 
    /// @details
    ///     - Memory advice is a performance hint only and is not required for
    ///       functional correctness.
    ///     - Memory advice can be used to override driver heuristics to explicitly
    ///       control shared memory behavior.
    ///     - Not all memory advice hints may be supported for all allocation types
    ///       for all devices.
    ///       If a memory advice hint is not supported by the device it will be ignored.
    ///     - Memory advice may only be supported at a device-specific granularity,
    ///       such as at a page boundary.
    ///       In this case, the memory range may be expanded such that the start and
    ///       end of the range satisfy granularity requirements.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cudaMemAdvise**
    /// 
    /// @throws result_t
    void __xecall
    CommandList::AppendMemAdvise(
        Device* pDevice,                                ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        memory_advice_t advice                          ///< [in] Memory advice for the memory range
        )
    {
        auto result = static_cast<result_t>( ::xeCommandListAppendMemAdvise(
            reinterpret_cast<xe_command_list_handle_t>( getHandle() ),
            reinterpret_cast<xe_device_handle_t>( pDevice->getHandle() ),
            ptr,
            size,
            static_cast<xe_memory_advice_t>( advice ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xe::CommandList::AppendMemAdvise" );
    }

} // namespace xe

namespace xe
{
} // namespace xe
