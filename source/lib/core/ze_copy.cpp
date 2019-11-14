/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_copy.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Copies
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/copy.yml
 * @endcond
 *
 */
#include "ze_lib.h"

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == srcptr
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendMemoryCopy(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendMemoryCopy = ze_lib::context.ddiTable.CommandList.pfnAppendMemoryCopy;
    if( nullptr == pfnAppendMemoryCopy )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Initializes host, device, or shared memory.
/// 
/// @details
///     - The memory pointed to by dstptr must be accessible by the device on
///       which the command list is created.
///     - The value to initialize memory to is described by the pattern and the
///       pattern size.
///     - The pattern size must be a power of two.
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == ptr
///         + nullptr == pattern
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendMemoryFill(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    const void* pattern,                            ///< [in] pointer to value to initialize memory to
    size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
    size_t size,                                    ///< [in] size in bytes to initialize
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendMemoryFill = ze_lib::context.ddiTable.CommandList.pfnAppendMemoryFill;
    if( nullptr == pfnAppendMemoryFill )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hEvent );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == dstRegion
///         + nullptr == srcptr
///         + nullptr == srcRegion
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendMemoryCopyRegion(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
    uint32_t dstPitch,                              ///< [in] destination pitch in bytes
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
    uint32_t srcPitch,                              ///< [in] source pitch in bytes
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendMemoryCopyRegion = ze_lib::context.ddiTable.CommandList.pfnAppendMemoryCopyRegion;
    if( nullptr == pfnAppendMemoryCopyRegion )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == hSrcImage
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendImageCopy(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendImageCopy = ze_lib::context.ddiTable.CommandList.pfnAppendImageCopy;
    if( nullptr == pfnAppendImageCopy )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == hSrcImage
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendImageCopyRegion(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendImageCopyRegion = ze_lib::context.ddiTable.CommandList.pfnAppendImageCopyRegion;
    if( nullptr == pfnAppendImageCopyRegion )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == hSrcImage
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendImageCopyToMemory(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendImageCopyToMemory = ze_lib::context.ddiTable.CommandList.pfnAppendImageCopyToMemory;
    if( nullptr == pfnAppendImageCopyToMemory )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == srcptr
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendImageCopyFromMemory(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    auto pfnAppendImageCopyFromMemory = ze_lib::context.ddiTable.CommandList.pfnAppendImageCopyFromMemory;
    if( nullptr == pfnAppendImageCopyFromMemory )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == ptr
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendMemoryPrefetch(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t size                                     ///< [in] size in bytes of the memory range to prefetch
    )
{
    auto pfnAppendMemoryPrefetch = ze_lib::context.ddiTable.CommandList.pfnAppendMemoryPrefetch;
    if( nullptr == pfnAppendMemoryPrefetch )
        return ZE_RESULT_ERROR_UNSUPPORTED;

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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hDevice
///         + nullptr == ptr
///         + invalid value for advice
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendMemAdvise(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    auto pfnAppendMemAdvise = ze_lib::context.ddiTable.CommandList.pfnAppendMemAdvise;
    if( nullptr == pfnAppendMemAdvise )
        return ZE_RESULT_ERROR_UNSUPPORTED;

    return pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
}

} // extern "C"

namespace ze
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
    void __zecall
    CommandList::AppendMemoryCopy(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopy(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            srcptr,
            size,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemoryCopy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes host, device, or shared memory.
    /// 
    /// @details
    ///     - The memory pointed to by dstptr must be accessible by the device on
    ///       which the command list is created.
    ///     - The value to initialize memory to is described by the pattern and the
    ///       pattern size.
    ///     - The pattern size must be a power of two.
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
    void __zecall
    CommandList::AppendMemoryFill(
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryFill(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ptr,
            pattern,
            pattern_size,
            size,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemoryFill" );
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
    void __zecall
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
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopyRegion(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<const ze_copy_region_t*>( dstRegion ),
            dstPitch,
            srcptr,
            reinterpret_cast<const ze_copy_region_t*>( srcRegion ),
            srcPitch,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemoryCopyRegion" );
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
    void __zecall
    CommandList::AppendImageCopy(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopy(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendImageCopy" );
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
    void __zecall
    CommandList::AppendImageCopyRegion(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyRegion(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const ze_image_region_t*>( pDstRegion ),
            reinterpret_cast<const ze_image_region_t*>( pSrcRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendImageCopyRegion" );
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
    void __zecall
    CommandList::AppendImageCopyToMemory(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyToMemory(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const ze_image_region_t*>( pSrcRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendImageCopyToMemory" );
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
    void __zecall
    CommandList::AppendImageCopyFromMemory(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyFromMemory(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            srcptr,
            reinterpret_cast<const ze_image_region_t*>( pDstRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendImageCopyFromMemory" );
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
    void __zecall
    CommandList::AppendMemoryPrefetch(
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryPrefetch(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemoryPrefetch" );
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
    void __zecall
    CommandList::AppendMemAdvise(
        Device* pDevice,                                ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        memory_advice_t advice                          ///< [in] Memory advice for the memory range
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemAdvise(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            ptr,
            size,
            static_cast<ze_memory_advice_t>( advice ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemAdvise" );
    }

} // namespace ze

namespace ze
{
} // namespace ze
