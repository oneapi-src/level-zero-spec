"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT
"""
import os, sys
sys.path.append('../../include')
from ze import *

os.environ['PATH'] = "%s;%s"%(os.environ['PATH'],os.path.abspath("../../build/bin/Debug"))
os.environ['ZE_ENABLE_NULL_DRIVER'] = "1"

dll = ZE_DDI(ze_api_version_v._1_0.value)

def init_ze():
    r = ze_result_v(dll.zeInit(ze_init_flag_v.NONE).value)
    if ze_result_v.SUCCESS != r:
        raise Exception(r)


def findDeviceGroup(type : ze_device_type_t):
    count = c_ulong()
    r = ze_result_v(dll.zeDeviceGroupGet(byref(count), None).value)
    if ze_result_v.SUCCESS != r:
        raise Exception(r)

    device_group_handles = (ze_device_group_handle_t * count.value)()
    r = ze_result_v(dll.zeDeviceGroupGet(byref(count), device_group_handles).value)
    if ze_result_v.SUCCESS != r:
        raise Exception(r)

    for handle in device_group_handles:
        device_properties = ze_device_properties_t()
        r = ze_result_v(dll.zeDeviceGroupGetDeviceProperties(handle, byref(device_properties)).value)
        if ze_result_v.SUCCESS != r:
            raise Exception(r)
        if type.value == device_properties.type.value:
            print("Found %s device group..."%ze_device_type_v(type.value))
            for field in device_properties._fields_:
                print("%s : %s"%(field[0], getattr(device_properties, field[0])))
            return handle
    return None


def main():
    init_ze()
    findDeviceGroup(ze_device_type_v.GPU)
    print("Done!")

if __name__ == '__main__':
    main()
# END OF FILE
