<%!
import re
import extended_helper as th
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
* @file test_forwarding_${name}.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/${name}.yml
* @endcond
*
******************************************************************************/
#include "${name}.h"
#include "mock_${name}.h"

using ::testing::Return;

namespace L0 {
namespace ult {

%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if re.match(r"function", obj['type']):
%if name == th.class_to_actor_name(cls):
TEST(${x}${th.make_driver_frontend_class_name(name)}${th.change_case_camel_to_pascal(th.make_driver_frontend_class_member_func_declaration_name(x, obj, cls))}, redirectsTo${th.change_case_camel_to_pascal(th.make_driver_frontend_class_name(name))}Object) {
    Mock<${th.make_driver_frontend_class_name(name)}> ${th.change_case_pascal_to_camel(th.make_driver_frontend_class_name(name))};
    auto asHandle = ${th.change_case_pascal_to_camel(th.make_driver_frontend_class_name(name))}.toHandle();
    
    %for param in obj['params']:
    ${th.subx(x, param['type'])} ${param['name']} = {};
    %endfor
    
    EXPECT_CALL(${th.change_case_pascal_to_camel(th.make_driver_frontend_class_name(name))}, ${th.make_driver_frontend_class_member_func_declaration_name(x, obj, cls)}(${th.make_params_list_single_line(obj, cls, 1, False)}))
        .Times(1)
        .WillRepeatedly(Return(${X}_RESULT_SUCCESS));
        
    auto result = L0::${th.make_func_name(x, obj, cls)}(asHandle ${th.make_params_list_single_line(obj, cls, 1, True)});
        
    EXPECT_EQ(${X}_RESULT_SUCCESS, result);
}
%endif
%endif
%endfor
%endfor 

} // namespace ult
} // namespace L0

