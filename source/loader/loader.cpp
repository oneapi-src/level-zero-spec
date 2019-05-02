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
* @file loader.cpp
*
******************************************************************************/
#include <mutex>
#include <stdlib.h>
#include "loader.h"
#include "xe_api.h"
#include "xex_api.h"
#include "xet_api.h"

///////////////////////////////////////////////////////////////////////////////
extern xe_apitable_t xe_apitable;
extern xex_apitable_t xex_apitable;
extern xet_apitable_t xet_apitable;

bool xeLoadExports( void* );
bool xexLoadExports( void* );
bool xetLoadExports( void* );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t( __xecall *xe_pfnInitLayer_t )(
    xe_apitable_t*,
    xex_apitable_t*,
    xet_apitable_t*
    );


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeInit(
    xe_init_flag_t flags )
{
    static std::mutex crit;
    std::lock_guard<std::mutex> lockGuard{crit};

    static bool initialized = false;
    if( initialized )
        return XE_RESULT_SUCCESS;
        
    auto driverLibrary = LOAD_DRIVER_LIBRARY("xe_common"); // todo: fix persistent handle

    initialized =
        xeLoadExports( driverLibrary ) &&
        xexLoadExports( driverLibrary ) &&
        xetLoadExports (driverLibrary );
            
    if( !initialized )
        return XE_RESULT_ERROR_UNINITIALIZED;

    const char* env_var = getenv( "XE_ENABLE_VALIDATION_LAYER" );
    if((nullptr != env_var) && (0 != atoi(env_var))){
        auto validationLayer = LOAD_DRIVER_LIBRARY("xe_validation_layer"); // todo: fix persistent handle
        auto xeInitLayer = (xe_pfnInitLayer_t)LOAD_FUNCTION_PTR(validationLayer, "xeInitLayer");
        xeInitLayer( &xe_apitable, &xex_apitable, &xet_apitable );
    }

    return xe_apitable.pfnInit( flags );
}

#if defined(__cplusplus)
};
#endif
