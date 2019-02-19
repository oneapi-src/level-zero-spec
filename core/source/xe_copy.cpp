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
* @brief Intel Xe Driver APIs for Copies
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/copy.yml
* @endcond
*
******************************************************************************/
#include "../include/xe_copy.h"

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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == srcptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeMemoryCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size                                     ///< [in] size in bytes to copy
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == dstptr, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == srcptr, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {10322d2f80ab2c4d1de8c74ebd5dcd44b30666c7d93497a0525875fe05511385}

    // @todo: insert <code> here

    /// @end   {10322d2f80ab2c4d1de8c74ebd5dcd44b30666c7d93497a0525875fe05511385}
    return XE_RESULT_SUCCESS;
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeImageCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage                     ///< [in] handle of source image to copy from
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hDstImage, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hSrcImage, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {243c2116a4f9a00f96b590eaf48bbc87a5ed95083afa49768bd94c9994d4c5e1}

    // @todo: insert <code> here

    /// @end   {243c2116a4f9a00f96b590eaf48bbc87a5ed95083afa49768bd94c9994d4c5e1}
    return XE_RESULT_SUCCESS;
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeImageCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion                   ///< [in][optional] source region descriptor
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hDstImage, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hSrcImage, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {ec5a7f583e0bfc8d5a755587f411c7bc145e5f9e004527daa436297696035d30}

    // @todo: insert <code> here

    /// @end   {ec5a7f583e0bfc8d5a755587f411c7bc145e5f9e004527daa436297696035d30}
    return XE_RESULT_SUCCESS;
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == dstptr
///         + nullptr == hSrcImage
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeImageCopyToMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion                   ///< [in][optional] source region descriptor
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == dstptr, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hSrcImage, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {69f20a6c73958cc782ea516378e1c353ce2f5620b69c8da457e9fe385274ae41}

    // @todo: insert <code> here

    /// @end   {69f20a6c73958cc782ea516378e1c353ce2f5620b69c8da457e9fe385274ae41}
    return XE_RESULT_SUCCESS;
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
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hDstImage
///         + nullptr == srcptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeImageCopyFromMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    void* srcptr                                    ///< [in] pointer to source memory to copy from
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hDstImage, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == srcptr, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {9c2889454d2b805cd41419469082ddba5fc930632d7ad1d19e5c05c2ee59e464}

    // @todo: insert <code> here

    /// @end   {9c2889454d2b805cd41419469082ddba5fc930632d7ad1d19e5c05c2ee59e464}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Asynchronously prefetches shared memory to the device associated with
///        the specified command list
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == ptr
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeMemoryPrefetch(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory region to prefetch
    size_t count                                    ///< [in] size in bytes of the memory region to prefetch
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == ptr, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {2d3f1674f77d6735fb9987fcab395bce6dc9726c938772ca747fb9494e4a9c23}

    // @todo: insert <code> here

    /// @end   {2d3f1674f77d6735fb9987fcab395bce6dc9726c938772ca747fb9494e4a9c23}
    return XE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a shared memory range
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
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == hCommandList
///         + nullptr == hDevice
///         + nullptr == ptr
///         + invalid value for advice
///     - ::XE_RESULT_ERROR_UNSUPPORTED
/*@todo: __declspec(dllexport)*/
xe_result_t __xecall
  xeCommandListEncodeMemAdvise(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    // @todo: check_return(nullptr == get_driver(), XE_RESULT_ERROR_UNINITIALIZED);

    // Check parameters
    // @todo: check_return(nullptr == hCommandList, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == hDevice, XE_RESULT_ERROR_INVALID_PARAMETER);
    // @todo: check_return(nullptr == ptr, XE_RESULT_ERROR_INVALID_PARAMETER);
    /// @begin {2c1eaf9d7e8276047aecaeba08566fcadb26720fa7c263446f0445cbe91bf1c6}

    // @todo: insert <code> here

    /// @end   {2c1eaf9d7e8276047aecaeba08566fcadb26720fa7c263446f0445cbe91bf1c6}
    return XE_RESULT_SUCCESS;
}

