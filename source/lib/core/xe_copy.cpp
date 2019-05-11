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
* @file xe_copy.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Copies
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/copy.yml
* @endcond
*
******************************************************************************/
#include "xe_api.hpp"
#include "xe_api.h"

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
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendMemoryCopy( handle, dstptr, srcptr, size, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemoryCopy");
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
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendMemorySet( handle, ptr, value, size, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemorySet");
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
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendImageCopy( handle, pDstImage, pSrcImage, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendImageCopy");
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
        image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
        image_region_t* pSrcRegion,                     ///< [in][optional] source region descriptor
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendImageCopyRegion( handle, pDstImage, pSrcImage, pDstRegion, pSrcRegion, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendImageCopyRegion");
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
        image_region_t* pSrcRegion,                     ///< [in][optional] source region descriptor
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendImageCopyToMemory( handle, dstptr, pSrcImage, pSrcRegion, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendImageCopyToMemory");
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
        image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        Event* phWaitEvents                             ///< [in][optional] pointer to the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendImageCopyFromMemory( handle, pDstImage, srcptr, pDstRegion, pSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendImageCopyFromMemory");
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
        size_t count                                    ///< [in] size in bytes of the memory range to prefetch
        )
    {
        // auto result = ::xeCommandListAppendMemoryPrefetch( handle, ptr, count );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemoryPrefetch");
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
        // auto result = ::xeCommandListAppendMemAdvise( handle, pDevice, ptr, size, advice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemAdvise");
    }

} // namespace xe
