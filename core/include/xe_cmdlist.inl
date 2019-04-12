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
* @file xe_cmdlist.inl
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/cmdlist.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_CMDLIST_INL
#define _XE_CMDLIST_INL
#if defined(__cplusplus)
#pragma once
#include "xe_cmdlist.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendBarrier
    /// 
    /// @details
    ///     - If numWaitEvents is zero, then all previous commands are completed
    ///       prior to the execution of the barrier.
    ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
    ///       signalled prior to the execution of the barrier.
    ///     - This command blocks all following commands from beginning until the
    ///       execution of the barrier completes.
    ///     - Memory and cache hierarchies are flushed and invalidated sufficient
    ///       for device and host access.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkCmdPipelineBarrier**
    ///     - clEnqueueBarrierWithWaitList
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendBarrier(
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before executing
                                                        ///< barrier
        )
    {
        // auto result = ::xeCommandListAppendBarrier( handle, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendBarrier");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendMemoryRangesBarrier
    /// 
    /// @details
    ///     - If numWaitEvents is zero, then all previous commands are completed
    ///       prior to the execution of the barrier.
    ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
    ///       signalled prior to the execution of the barrier.
    ///     - This command blocks all following commands from beginning until the
    ///       execution of the barrier completes.
    ///     - Memory and cache hierarchies are flushed and invalidated sufficient
    ///       for device and host access.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendMemoryRangesBarrier(
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in] array of sizes of memory range
        const void** pRanges,                           ///< [in] array of memory ranges
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before executing
                                                        ///< barrier
        )
    {
        // auto result = ::xeCommandListAppendMemoryRangesBarrier( handle, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemoryRangesBarrier");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListCreate
    /// 
    /// @details
    ///     - The command list is created in the 'open' state.
    ///     - This function may be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ::command_list_handle_t: pointer to handle of command list object created
    /// 
    /// @throws result_t
    inline command_list_handle_t 
    CommandList::Create(
        device_handle_t hDevice,                        ///< [in] handle of the device object
        const command_list_desc_t* desc                 ///< [in] pointer to command list descriptor
        )
    {
        // auto result = ::xeCommandListCreate( handle, hDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Create");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListCreateImmediate
    /// 
    /// @details
    ///     - The command list is created in the 'open' state and never needs to be
    ///       closed.
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ::command_list_handle_t: pointer to handle of command list object created
    /// 
    /// @throws result_t
    inline command_list_handle_t 
    CommandList::CreateImmediate(
        device_handle_t hDevice,                        ///< [in] handle of the device object
        const CommandQueue::command_queue_desc_t* desc  ///< [in] pointer to command queue descriptor
        )
    {
        // auto result = ::xeCommandListCreateImmediate( handle, hDevice, desc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::CreateImmediate");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListDestroy
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the command list before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this command list.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::Destroy(
        command_list_handle_t hCommandList              ///< [in] handle of command list object to destroy
        )
    {
        // auto result = ::xeCommandListDestroy( handle, hCommandList );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListClose
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::Close(
        void
        )
    {
        // auto result = ::xeCommandListClose( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Close");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListReset
    /// 
    /// @details
    ///     - The application is responsible for making sure the GPU is not
    ///       currently referencing the command list before it is reset
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::Reset(
        void
        )
    {
        // auto result = ::xeCommandListReset( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::Reset");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListSetParameter
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - cuCtxSetCacheConfig
    ///     - cuCtxSetLimit
    ///     - cuCtxSetSharedMemConfig
    /// 
    /// @throws result_t
    inline void 
    CommandList::SetParameter(
        command_list_parameter_t parameter,             ///< [in] parameter to change
        uint32_t value                                  ///< [in] value of attribute
        )
    {
        // auto result = ::xeCommandListSetParameter( handle, parameter, value );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::SetParameter");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListGetParameter
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - cuCtxGetCacheConfig
    ///     - cuCtxGetLimit
    ///     - cuCtxGetSharedMemConfig
    ///     - cuCtxGetStreamPriorityRange
    /// 
    /// @returns
    ///     - uint32_t: value of attribute
    /// 
    /// @throws result_t
    inline uint32_t 
    CommandList::GetParameter(
        command_list_parameter_t parameter              ///< [in] parameter to retrieve
        )
    {
        // auto result = ::xeCommandListGetParameter( handle, parameter );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::GetParameter");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListResetParameters
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::ResetParameters(
        void
        )
    {
        // auto result = ::xeCommandListResetParameters( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::ResetParameters");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListReserveSpace
    /// 
    /// @details
    ///     - The pointer returned is valid for both Host and device access.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to command buffer space reserved
    /// 
    /// @throws result_t
    inline void* 
    CommandList::ReserveSpace(
        size_t size                                     ///< [in] size (in bytes) to reserve
        )
    {
        // auto result = ::xeCommandListReserveSpace( handle, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::ReserveSpace");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendMemoryCopy
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
    inline void 
    CommandList::AppendMemoryCopy(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendMemoryCopy( handle, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemoryCopy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendMemorySet
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
    inline void 
    CommandList::AppendMemorySet(
        void* ptr,                                      ///< [in] pointer to memory to initialize
        int value,                                      ///< [in] value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initailize
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendMemorySet( handle, ptr, value, size, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemorySet");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendImageCopy
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
    inline void 
    CommandList::AppendImageCopy(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendImageCopy( handle, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendImageCopy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendImageCopyRegion
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendImageCopyRegion(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
        image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
        image_region_t* pSrcRegion,                     ///< [in][optional] source region descriptor
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendImageCopyRegion( handle, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendImageCopyRegion");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendImageCopyToMemory
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
    inline void 
    CommandList::AppendImageCopyToMemory(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
        image_region_t* pSrcRegion,                     ///< [in][optional] source region descriptor
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendImageCopyToMemory( handle, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendImageCopyToMemory");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendImageCopyFromMemory
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
    inline void 
    CommandList::AppendImageCopyFromMemory(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before copy
        )
    {
        // auto result = ::xeCommandListAppendImageCopyFromMemory( handle, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendImageCopyFromMemory");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendMemoryPrefetch
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
    inline void 
    CommandList::AppendMemoryPrefetch(
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t count                                    ///< [in] size in bytes of the memory range to prefetch
        )
    {
        // auto result = ::xeCommandListAppendMemoryPrefetch( handle, ptr, count );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemoryPrefetch");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendMemAdvise
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
    inline void 
    CommandList::AppendMemAdvise(
        device_handle_t hDevice,                        ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        memory_advice_t advice                          ///< [in] Memory advice for the memory range
        )
    {
        // auto result = ::xeCommandListAppendMemAdvise( handle, hDevice, ptr, size, advice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendMemAdvise");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendSignalEvent
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetUserEventStatus**
    ///     - cuEventRecord
    ///     - vkCmdSetEvent
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendSignalEvent(
        event_handle_t hEvent                           ///< [in] handle of the event
        )
    {
        // auto result = ::xeCommandListAppendSignalEvent( handle, hEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendSignalEvent");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendWaitOnEvents
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendWaitOnEvents(
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        event_handle_t* phEvents                        ///< [in] handle of the events to wait on before continuing
        )
    {
        // auto result = ::xeCommandListAppendWaitOnEvents( handle, numEvents, phEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendWaitOnEvents");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendEventReset
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkResetEvent
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendEventReset(
        event_handle_t hEvent                           ///< [in] handle of the event
        )
    {
        // auto result = ::xeCommandListAppendEventReset( handle, hEvent );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendEventReset");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendLaunchFunction
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendLaunchFunction(
        function_handle_t hFunction,                    ///< [in] handle of the function object
        const thread_group_dimensions_t* pLaunchFuncArgs,   ///< [in] launch function arguments.
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before launching
        )
    {
        // auto result = ::xeCommandListAppendLaunchFunction( handle, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendLaunchFunction");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendLaunchFunctionIndirect
    /// 
    /// @details
    ///     - The launch arguments need to be device visible.
    ///     - The launch arguments buffer may not be reusued until the function has
    ///       completed on the device.
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendLaunchFunctionIndirect(
        function_handle_t hFunction,                    ///< [in] handle of the function object
        const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain launch arguments
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before launching
        )
    {
        // auto result = ::xeCommandListAppendLaunchFunctionIndirect( handle, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendLaunchFunctionIndirect");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendLaunchMultipleFunctionsIndirect
    /// 
    /// @details
    ///     - The array of launch arguments need to be device visible.
    ///     - The array of launch arguments buffer may not be reusued until the
    ///       function has completed on the device.
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendLaunchMultipleFunctionsIndirect(
        uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
        const function_handle_t* phFunctions,           ///< [in] handles of the function objects
        const size_t* pNumLaunchArguments,              ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of launch arguments; must be less-than or equal-to numFunctions
        const thread_group_dimensions_t* pLaunchArgumentsBuffer,///< [in] pointer to device buffer that will contain a contiguous array of
                                                        ///< launch arguments
        event_handle_t hSignalEvent,                    ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        event_handle_t* phWaitEvents                    ///< [in][optional] handle of the events to wait on before launching
        )
    {
        // auto result = ::xeCommandListAppendLaunchMultipleFunctionsIndirect( handle, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendLaunchMultipleFunctionsIndirect");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListAppendLaunchHostFunction
    /// 
    /// @details
    ///     - This may **not** be called for a command list created with
    ///       ::COMMAND_LIST_FLAG_COPY_ONLY.
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchHostFunc**
    /// 
    /// @throws result_t
    inline void 
    CommandList::AppendLaunchHostFunction(
        host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
        )
    {
        // auto result = ::xeCommandListAppendLaunchHostFunction( handle, pfnHostFunc, pUserData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::AppendLaunchHostFunction");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDLIST_INL
