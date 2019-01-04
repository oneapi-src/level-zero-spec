/**************************************************************************//**
* 
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
* 
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
* 
* @file xe_driver.h
* 
* @brief Intel Xe Driver APIs
* 
******************************************************************************/
#ifndef _XE_DRIVER_H
#define _XE_DRIVER_H
#if defined( __cplusplus )
#pragma once
#endif
#include "xe_common.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialization flags
XE_DECLARE_ENUM( xe_init_flags_t )
{
    XE_INIT_FLAG_NONE = 0       ///< default behavior
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the Xe Driver API and must be called before any other
///     API function.
/// @remarks _Analogues:_
///     - **cuInit**
xe_result_t __xecall
  xeInit( 
    xe_init_flags_t flags       ///< initialization flags
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines driver versions
/// @details Driver versions contain major and minor attributes,
///     use XE_MAJOR_VERSION and XE_MINOR_VERSION
XE_DECLARE_ENUM( xe_driver_version_t )
{
    XE_DRIVER_VERSION_1_0 = XE_MAKE_VERSION( 1, 0 ) ///< 1.0
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the current versions of the driver
/// @remarks _Analogues:_
///     - **cuDriverGetVersion**
xe_result_t __xecall
 xeDriverGetVersion(
    xe_driver_version_t* version    ///< [out] driver version
    );

#endif // _XE_DRIVER_H