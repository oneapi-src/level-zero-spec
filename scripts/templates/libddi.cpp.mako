<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/**************************************************************************//**
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
* @file ${name}.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/libddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "${n}_lib.h"

namespace ${n}_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    ${x}_result_t context_t::Init()
    {
        loader = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "${x}_loader" ) );

        if( NULL == loader )
            return ${X}_RESULT_ERROR_UNINITIALIZED;

        ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for tbl in th.get_pfntables(specs, meta, n, tags):
        if( ${X}_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR(loader, "${tbl['export']['name']}") );
            result = getTable( ${X}_API_VERSION_1_0, &ddiTable.${tbl['name']} );
        }

    %endfor
        return result;
    }
} // namespace ${n}_lib
