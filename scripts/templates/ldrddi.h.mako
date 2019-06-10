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
* @file ${name}.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/ldrddi.h.mako
* @endcond
*
******************************************************************************/
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    %for obj in th.extract_objs(specs, r"handle"):
    %if 'class' in obj:
    <%
        _handle_t = th.subt(n, tags, obj['name'])
        _object_t = re.sub(r"(\w+)_handle_t", r"\1_object_t", _handle_t)
        _factory_t = re.sub(r"(\w+)_handle_t", r"\1_factory_t", _handle_t)
    %>using ${th.append_ws(_object_t, 35)} = object_t < ${_handle_t} >;
    using ${th.append_ws(_factory_t, 35)} = singleton_factory_t < ${_object_t}, ${_handle_t} >;

    %endif
    %endfor
}
