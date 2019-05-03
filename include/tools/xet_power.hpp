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
* @file xet_power.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for Power
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/power.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_POWER_HPP
#define _XET_POWER_HPP
#if defined(__cplusplus)
#pragma once
#include "xet_common.hpp"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of a frequency domain on a device
    class Power;
    using freq_domain_handle_t = Power*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Fan capabilities
    enum class fan_capabilities_t
    {
        GET_SPEED_PERCENTAGE = XE_BIT( 0 ),             ///< can query fan speed as a percentage
        SET_SPEED_PERCENTAGE = XE_BIT( 1 ),             ///< can set fan speed as a percentage
        GET_SPEED_RPM = XE_BIT( 2 ),                    ///< can query fan speed as rpm
        SET_SPEED_RPM = XE_BIT( 3 ),                    ///< can set fan speed as rpm
        HAVE_TEMPERATURE_SPEED_TABLE = XE_BIT( 4 ),     ///< can set temperature/fan speed table

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Fan speed modes
    enum class fan_speed_mode_t
    {
        AUTO = 0,                                       ///< fan speed is dynamically controlled based on temperature
        FIXED,                                          ///< fan speed is fixed

    };

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_POWER_HPP
