<%
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/**************************************************************************//**
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
* @file ${n}_api.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/${section}
* @endcond
*
******************************************************************************/
#ifndef _${N}_API_H
#define _${N}_API_H
#if defined(__cplusplus)
#pragma once
#endif

%for f in files:
%if not re.match(r"\w+_common", f):
#include "${f}"
%endif
%endfor

#if defined(__cplusplus)
extern "C" {
#endif

%for tbl in th.get_pfntables(specs, meta, n, tags):
///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ${tbl['name']} functions pointers
typedef struct _${tbl['type']}
{
    %for obj in tbl['functions']:
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    ${th.append_ws(th.make_pfn_type(n, tags, obj), 59)} ${th.make_pfn_name(n, tags, obj)};
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif
    %endfor
} ${tbl['type']};

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ${tbl['name']} table
///        with current process' addresses
///
/// @returns
///     - ::${X}_RESULT_SUCCESS
///     - ::${X}_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::${X}_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__${x}dllexport ${x}_result_t __${x}call
${tbl['export']}(
    uint32_t version,        ///< [in] ::${X}_API_HEADER_VERSION
    ${tbl['type']}* ptable   ///< [in,out] pointer to table of API function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for ${tbl['export']}
typedef ${x}_result_t (__${x}call *${tbl['pfn']})(
    uint32_t,
    ${tbl['type']}*
    );

%endfor
#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _${N}_API_H