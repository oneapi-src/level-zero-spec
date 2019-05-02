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
* @file layer.cpp
*
******************************************************************************/
#include "layer.h"
#include "xe_ddi.h"
#include "xex_ddi.h"
#include "xet_ddi.h"

///////////////////////////////////////////////////////////////////////////////
extern xe_apitable_t xe_apitable;
extern xex_apitable_t xex_apitable;
extern xet_apitable_t xet_apitable;

bool xeIntercept( xe_apitable_t* );
bool xexIntercept( xex_apitable_t* );
bool xetIntercept( xet_apitable_t* );


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeInitLayer(
    xe_apitable_t*  xeapi,
    xex_apitable_t* xexapi,
    xet_apitable_t* xetapi )
{
    bool initialized = 
        xeIntercept(xeapi) &&
        xexIntercept(xexapi) &&
        xetIntercept(xetapi);
            
    if( !initialized )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return XE_RESULT_SUCCESS;
}

#if defined(__cplusplus)
};
#endif
