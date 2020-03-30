"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file zex.py
 @version v0.91-275

 """
import platform
from ctypes import *
from enum import *

###############################################################################
__version__ = "1.0"

###############################################################################
## @brief Handle of command list object
class zex_command_list_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's command graph object
class zex_command_graph_handle_t(c_void_p):
    pass

###############################################################################
## @brief API version of ::zex_command_graph_desc_t
class zex_command_graph_desc_version_v(IntEnum):
    CURRENT = ZE_MAKE_VERSION( 0, 91 )              ## version 0.91

class zex_command_graph_desc_version_t(c_int):
    def __str__(self):
        return str(zex_command_graph_desc_version_v(value))


###############################################################################
## @brief Supported command graph creation flags
class zex_command_graph_flag_v(IntEnum):
    NONE = 0                                        ## default behavior

class zex_command_graph_flag_t(c_int):
    def __str__(self):
        return str(zex_command_graph_flag_v(value))


###############################################################################
## @brief CommandGraph descriptor
class zex_command_graph_desc_t(Structure):
    _fields_ = [
        ("version", zex_command_graph_desc_version_t),                  ## [in] ::ZEX_COMMAND_GRAPH_DESC_VERSION_CURRENT
        ("flags", zex_command_graph_flag_t)                             ## [in] creation flags
    ]

###############################################################################
"""
class cl_context(c_void_p):
    pass

class cl_program(c_void_p):
    pass

class cl_mem(c_void_p):
    pass

class cl_command_queue(c_void_p):
    pass
"""

###############################################################################
__use_win_types = "Windows" == platform.uname()[0]

###############################################################################
## @brief Function-pointer for zexCommandListReserveSpace
if __use_win_types:
    _zexCommandListReserveSpace_t = WINFUNCTYPE( ze_result_t, zex_command_list_handle_t, c_size_t, POINTER(c_void_p) )
else:
    _zexCommandListReserveSpace_t = CFUNCTYPE( ze_result_t, zex_command_list_handle_t, c_size_t, POINTER(c_void_p) )


###############################################################################
## @brief Table of CommandList functions pointers
class _zex_command_list_dditable_t(Structure):
    _fields_ = [
        ("pfnReserveSpace", c_void_p)                                   ## _zexCommandListReserveSpace_t
    ]

###############################################################################
## @brief Function-pointer for zexCommandGraphCreate
if __use_win_types:
    _zexCommandGraphCreate_t = WINFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(zex_command_graph_desc_t), POINTER(zex_command_graph_handle_t) )
else:
    _zexCommandGraphCreate_t = CFUNCTYPE( ze_result_t, ze_device_handle_t, POINTER(zex_command_graph_desc_t), POINTER(zex_command_graph_handle_t) )

###############################################################################
## @brief Function-pointer for zexCommandGraphDestroy
if __use_win_types:
    _zexCommandGraphDestroy_t = WINFUNCTYPE( ze_result_t, zex_command_graph_handle_t )
else:
    _zexCommandGraphDestroy_t = CFUNCTYPE( ze_result_t, zex_command_graph_handle_t )

###############################################################################
## @brief Function-pointer for zexCommandGraphClose
if __use_win_types:
    _zexCommandGraphClose_t = WINFUNCTYPE( ze_result_t, zex_command_graph_handle_t )
else:
    _zexCommandGraphClose_t = CFUNCTYPE( ze_result_t, zex_command_graph_handle_t )


###############################################################################
## @brief Table of CommandGraph functions pointers
class _zex_command_graph_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _zexCommandGraphCreate_t
        ("pfnDestroy", c_void_p),                                       ## _zexCommandGraphDestroy_t
        ("pfnClose", c_void_p)                                          ## _zexCommandGraphClose_t
    ]

###############################################################################
class _zex_dditable_t(Structure):
    _fields_ = [
        ("CommandList", _zex_command_list_dditable_t),
        ("CommandGraph", _zex_command_graph_dditable_t)
    ]

###############################################################################
## @brief zex device-driver interfaces
class ZEX_DDI:
    def __init__(self, version : ze_api_version_t):
        # load the xe_loader library
        if "Windows" == platform.uname()[0]:
            self.__dll = WinDLL("ze_loader.dll")
        else:
            self.__dll = CDLL("ze_loader.so")

        # fill the ddi tables
        self.__dditable = _zex_dditable_t()

        # call driver to get function pointers
        _CommandList = _zex_command_list_dditable_t()
        r = ze_result_v(self.__dll.zexGetCommandListProcAddrTable(version, byref(_CommandList)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandList = _CommandList

        # attach function interface to function address
        self.zexCommandListReserveSpace = _zexCommandListReserveSpace_t(self.__dditable.CommandList.pfnReserveSpace)

        # call driver to get function pointers
        _CommandGraph = _zex_command_graph_dditable_t()
        r = ze_result_v(self.__dll.zexGetCommandGraphProcAddrTable(version, byref(_CommandGraph)))
        if r != ze_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandGraph = _CommandGraph

        # attach function interface to function address
        self.zexCommandGraphCreate = _zexCommandGraphCreate_t(self.__dditable.CommandGraph.pfnCreate)
        self.zexCommandGraphDestroy = _zexCommandGraphDestroy_t(self.__dditable.CommandGraph.pfnDestroy)
        self.zexCommandGraphClose = _zexCommandGraphClose_t(self.__dditable.CommandGraph.pfnClose)

        # success!
