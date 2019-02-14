<%
import re
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
* @file ${x}_all.hpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/api_all.hpp.mako
* @endcond
*
******************************************************************************/
#ifndef _${X}_ALL_HPP
#define _${X}_ALL_HPP
#if defined(__cplusplus)
#pragma once
#endif

%for f in files:
%if not re.match(r"\w+_common", f):
#include "${f}"
%endif
%endfor

#endif // _${X}_ALL_HPP