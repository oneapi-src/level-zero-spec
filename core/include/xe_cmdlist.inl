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
* @brief C++ wrapper of Intel Xe Driver APIs for Command List
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
    /// @brief C++ wrapper for ::xeCommandListEncodeExecutionBarrier
    /// 
    /// @details
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
    CommandList::EncodeExecutionBarrier(
        void
        )
    {
        // auto result = ::xeCommandListEncodeExecutionBarrier( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeExecutionBarrier");
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
        void
        )
    {
        // auto result = ::xeCommandListDestroy( handle );
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
    /// @brief C++ wrapper for ::xeCommandListEncodeCommandLists
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::EncodeCommandLists(
        uint32_t numCommandLists,                       ///< [in] number of command lists to encode
        command_list_handle_t* phCommandLists           ///< [in] list of handles of the command lists to encode for execution
        )
    {
        // auto result = ::xeCommandListEncodeCommandLists( handle, numCommandLists, phCommandLists->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeCommandLists");
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
    /// @brief C++ wrapper for ::xeCommandListEncodeMemoryCopy
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
    CommandList::EncodeMemoryCopy(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size                                     ///< [in] size in bytes to copy
        )
    {
        // auto result = ::xeCommandListEncodeMemoryCopy( handle, dstptr, srcptr, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeMemoryCopy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeMemorySet
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
    CommandList::EncodeMemorySet(
        void* ptr,                                      ///< [in] pointer to memory to initialize
        int value,                                      ///< [in] value to initialize memory to
        size_t size                                     ///< [in] size in bytes to initailize
        )
    {
        // auto result = ::xeCommandListEncodeMemorySet( handle, ptr, value, size );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeMemorySet");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeImageCopy
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
    CommandList::EncodeImageCopy(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        image_handle_t hSrcImage                        ///< [in] handle of source image to copy from
        )
    {
        // auto result = ::xeCommandListEncodeImageCopy( handle, hDstImage->getHandle(), hSrcImage->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeImageCopy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyRegion
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::EncodeImageCopyRegion(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
        image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
        image_region_t* pSrcRegion                      ///< [in][optional] source region descriptor
        )
    {
        // auto result = ::xeCommandListEncodeImageCopyRegion( handle, hDstImage->getHandle(), pDstRegion, hSrcImage->getHandle(), pSrcRegion );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeImageCopyRegion");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyToMemory
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
    CommandList::EncodeImageCopyToMemory(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        image_handle_t hSrcImage,                       ///< [in] handle of source image to copy from
        image_region_t* pSrcRegion                      ///< [in][optional] source region descriptor
        )
    {
        // auto result = ::xeCommandListEncodeImageCopyToMemory( handle, dstptr, hSrcImage->getHandle(), pSrcRegion );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeImageCopyToMemory");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeImageCopyFromMemory
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
    CommandList::EncodeImageCopyFromMemory(
        image_handle_t hDstImage,                       ///< [in] handle of destination image to copy to
        image_region_t* pDstRegion,                     ///< [in][optional] destination region descriptor
        const void* srcptr                              ///< [in] pointer to source memory to copy from
        )
    {
        // auto result = ::xeCommandListEncodeImageCopyFromMemory( handle, hDstImage->getHandle(), pDstRegion, srcptr );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeImageCopyFromMemory");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeMemoryPrefetch
    /// 
    /// @details
    ///     - This is a hint to improve performance only and is not required for
    ///       correctness.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    ///     - Prefetch to Host and Peer Device are not supported.
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
    CommandList::EncodeMemoryPrefetch(
        const void* ptr,                                ///< [in] pointer to start of the memory region to prefetch
        size_t count                                    ///< [in] size in bytes of the memory region to prefetch
        )
    {
        // auto result = ::xeCommandListEncodeMemoryPrefetch( handle, ptr, count );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeMemoryPrefetch");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeMemAdvise
    /// 
    /// @details
    ///     - Memory advice is a performance hint only; applications are not
    ///       required to use this for functionality.
    ///     - Memory advice can be used to override driver heuristics to explicitly
    ///       control shared memory behavior.
    ///     - Not all memory advice may be supported by all devices.
    ///     - Memory advice may only be supported at a device-specific granularity,
    ///       such as at a page boundary. In this case, the memory range may be
    ///       expanded such that the start and end of the range satisfy granularity
    ///       requirements.
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
    CommandList::EncodeMemAdvise(
        device_handle_t hDevice,                        ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        memory_advice_t advice                          ///< [in] Memory advice for the memory range
        )
    {
        // auto result = ::xeCommandListEncodeMemAdvise( handle, hDevice->getHandle(), ptr, size, advice );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeMemAdvise");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeSignalEvent
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
    CommandList::EncodeSignalEvent(
        event_handle_t hEvent                           ///< [in] handle of the event
        )
    {
        // auto result = ::xeCommandListEncodeSignalEvent( handle, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeSignalEvent");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeWaitOnEvent
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    inline void 
    CommandList::EncodeWaitOnEvent(
        event_handle_t hEvent                           ///< [in] handle of the event
        )
    {
        // auto result = ::xeCommandListEncodeWaitOnEvent( handle, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeWaitOnEvent");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeEventReset
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
    CommandList::EncodeEventReset(
        event_handle_t hEvent                           ///< [in] handle of the event
        )
    {
        // auto result = ::xeCommandListEncodeEventReset( handle, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeEventReset");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeDispatchFunction
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    inline void 
    CommandList::EncodeDispatchFunction(
        function_handle_t hFunction,                    ///< [in] handle of the function object
        const dispatch_function_arguments_t* pDispatchFuncArgs, ///< [in] dispatch function arguments.
        event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
        )
    {
        // auto result = ::xeCommandListEncodeDispatchFunction( handle, hFunction->getHandle(), pDispatchFuncArgs, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeDispatchFunction");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeDispatchFunctionIndirect
    /// 
    /// @details
    ///     - The dispatch arguments need to be device visible.
    ///     - The dispatch arguments buffer may not be reusued until dispatch has
    ///       completed on the device.
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    inline void 
    CommandList::EncodeDispatchFunctionIndirect(
        function_handle_t hFunction,                    ///< [in] handle of the function object
        const dispatch_function_arguments_t* pDispatchArgumentsBuffer,  ///< [in] pointer to device buffer that will contain dispatch arguments
        event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
        )
    {
        // auto result = ::xeCommandListEncodeDispatchFunctionIndirect( handle, hFunction->getHandle(), pDispatchArgumentsBuffer, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeDispatchFunctionIndirect");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeDispatchMultipleFunctionsIndirect
    /// 
    /// @details
    ///     - The array of dispatch arguments need to be device visible.
    ///     - The array of dispatch arguments buffer may not be reusued until
    ///       dispatch has completed on the device.
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchKernel**
    /// 
    /// @throws result_t
    inline void 
    CommandList::EncodeDispatchMultipleFunctionsIndirect(
        uint32_t numFunctions,                          ///< [in] maximum number of functions to dispatch
        const function_handle_t* phFunctions,           ///< [in] handles of the function objects
        const size_t* pNumDispatchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of dispatch arguments; must be less-than or equal-to
                                                        ///< numFunctions
        const dispatch_function_arguments_t* pDispatchArgumentsBuffer,  ///< [in] pointer to device buffer that will contain a contiguous array of
                                                        ///< dispatch arguments
        event_handle_t hEvent                           ///< [in][optional] handle of the event to signal on completion
        )
    {
        // auto result = ::xeCommandListEncodeDispatchMultipleFunctionsIndirect( handle, numFunctions, phFunctions, pNumDispatchArguments, pDispatchArgumentsBuffer, hEvent->getHandle() );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeDispatchMultipleFunctionsIndirect");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeCommandListEncodeDispatchHostFunction
    /// 
    /// @details
    ///     - This function may **not** be called from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuLaunchHostFunc**
    /// 
    /// @throws result_t
    inline void 
    CommandList::EncodeDispatchHostFunction(
        host_pfn_t pfnHostFunc,                         ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
        )
    {
        // auto result = ::xeCommandListEncodeDispatchHostFunction( handle, pfnHostFunc, pUserData );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::CommandList::EncodeDispatchHostFunction");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_CMDLIST_INL
