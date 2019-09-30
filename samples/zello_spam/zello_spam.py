"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT
"""
import sys
sys.path.append('../../include/core')
from xe import *

dll = XE_DDI(xe_api_version_v._1_0.value)

def init_xe():
    r = xe_result_v(dll.xeInit(xe_init_flag_v.NONE).value)
    if xe_result_v.SUCCESS != r:
        raise Exception(r)


def findDeviceGroup(type : xe_device_type_t):
    count = c_ulong()
    r = xe_result_v(dll.xeDeviceGroupGet(byref(count), None).value)
    if xe_result_v.SUCCESS != r:
        raise Exception(r)

    device_group_handles = (xe_device_group_handle_t * count.value)()
    r = xe_result_v(dll.xeDeviceGroupGet(byref(count), device_group_handles).value)
    if xe_result_v.SUCCESS != r:
        raise Exception(r)

    for handle in device_group_handles:
        device_properties = xe_device_properties_t()
        r = xe_result_v(dll.xeDeviceGroupGetDeviceProperties(handle, byref(device_properties)).value)
        if xe_result_v.SUCCESS != r:
            raise Exception(r)
        if type.value == device_properties.type.value:
            print("Found %s device group..."%xe_device_type_v(type.value))
            for field in device_properties._fields_:
                print("%s : %s"%(field[0], getattr(device_properties, field[0])))
            return handle
    return None


def main():
    init_xe()
    findDeviceGroup(xe_device_type_v.GPU)
    print("Done!")

if __name__ == '__main__':
    main()
# END OF FILE
