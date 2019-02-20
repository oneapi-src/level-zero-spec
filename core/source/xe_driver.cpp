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
* @file xe_driver.cpp
*
* @brief Intel Xe Driver APIs
*
* DO NOT EDIT: generated from /scripts/<type>/driver.yml
*
******************************************************************************/
#include "../include/xe_driver.h"

#include <exception>    // @todo: move to common and/or precompiled header

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the Xe Driver API and must be called before any other API
///        function.
/// 
/// @details
///     - Only one instance of a driver per process can be loaded.
///     - There is no reference tracking if multiple drivers are initialized.
///     - If this function is not called then all other functions will return
///       ::XE_RESULT_ERROR_UNINITIALIZED.
///     - This function is thread-safe for scenarios where multiple libraries
///       may initialize the driver simultaneously.
/// 
/// @remarks
///   _Analogues_
///     - **cuInit**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for flags
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///     - ::XE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///
/// @hash {0ae71bd1cc936ad12438c9cc7d3471f98557ec8f6b1fb62d2649cc618eb16351}
///
__xedllexport xe_result_t __xecall
  xeDriverInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;

            // Check parameters
        }
        /// @begin

        // @todo: insert <code> here

        /// @end
        return XE_RESULT_SUCCESS;
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the current version of the installed driver.
/// 
/// @details
///     - The driver version is a non-zero, monotonically increasing value where
///       higher values always indicate a more recent version.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuDriverGetVersion**
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + nullptr == version
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///
/// @hash {6ae964da2310ff18a63fe79a8fabcfaa071a342064d2f092042eb2b830d7c54f}
///
__xedllexport xe_result_t __xecall
  xeDriverGetVersion(
    uint32_t* version                               ///< [out] driver version
    )
{
    try
    {
        //if( XE_DRIVER_PARAMETER_VALIDATION_LEVEL >= 0 )
        {
            // if( nullptr == driver ) return XE_RESULT_ERROR_UNINITIALIZED;

            // Check parameters
            if( nullptr == version ) return XE_RESULT_ERROR_INVALID_PARAMETER;
        }
        /// @begin

        // @todo: insert <code> here

        /// @end
        return XE_RESULT_SUCCESS;
    }
    catch(xe_result_t& result)
    {
        return result;
    }
    catch(std::bad_alloc&)
    {
        return XE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }
    catch(std::exception&)
    {
        // @todo: pfnOnException(e.what());
        return XE_RESULT_ERROR_UNKNOWN;
    }
}

