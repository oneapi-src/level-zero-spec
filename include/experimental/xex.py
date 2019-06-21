"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

 @file xex.py

 @cond DEV
 DO NOT EDIT: generated from /scripts/templates/libddi.py.mako
 @endcond

"""
import platform
from ctypes import *
from enum import *

###############################################################################
__version__ = "1.0"

###############################################################################
## @brief Handle of command list object
class xex_command_list_handle_t(c_void_p):
    pass

###############################################################################
## @brief Handle of driver's command graph object
class xex_command_graph_handle_t(c_void_p):
    pass

###############################################################################
## @brief API version of ::xex_command_graph_desc_t
class xex_command_graph_desc_version_v(IntEnum):
    CURRENT = XE_MAKE_VERSION( 1, 0 )               ## version 1.0

class xex_command_graph_desc_version_t(c_int):
    def __str__(self):
        return str(xex_command_graph_desc_version_v(value))


###############################################################################
## @brief Supported command graph creation flags
class xex_command_graph_flag_v(IntEnum):
    NONE = 0                                        ## default behavior

class xex_command_graph_flag_t(c_int):
    def __str__(self):
        return str(xex_command_graph_flag_v(value))


###############################################################################
## @brief CommandGraph descriptor
class xex_command_graph_desc_t(Structure):
    _fields_ = [
        ("version", xex_command_graph_desc_version_t),                  ## [in] ::XEX_COMMAND_GRAPH_DESC_VERSION_CURRENT
        ("flags", xex_command_graph_flag_t)                             ## [in] creation flags
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
## @brief Function-pointer for xexInit
if __use_win_types:
    _xexInit_t = WINFUNCTYPE( xe_result_t, xe_init_flag_t )
else:
    _xexInit_t = CFUNCTYPE( xe_result_t, xe_init_flag_t )


###############################################################################
## @brief Table of Global functions pointers
class _xex_global_dditable_t(Structure):
    _fields_ = [
        ("pfnInit", c_void_p)                                           ## _xexInit_t
    ]

###############################################################################
## @brief Function-pointer for xexCommandListReserveSpace
if __use_win_types:
    _xexCommandListReserveSpace_t = WINFUNCTYPE( xe_result_t, xex_command_list_handle_t, c_size_t, POINTER(c_void_p) )
else:
    _xexCommandListReserveSpace_t = CFUNCTYPE( xe_result_t, xex_command_list_handle_t, c_size_t, POINTER(c_void_p) )


###############################################################################
## @brief Table of CommandList functions pointers
class _xex_command_list_dditable_t(Structure):
    _fields_ = [
        ("pfnReserveSpace", c_void_p)                                   ## _xexCommandListReserveSpace_t
    ]

###############################################################################
## @brief Function-pointer for xexCommandGraphCreate
if __use_win_types:
    _xexCommandGraphCreate_t = WINFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xex_command_graph_desc_t), POINTER(xex_command_graph_handle_t) )
else:
    _xexCommandGraphCreate_t = CFUNCTYPE( xe_result_t, xe_device_handle_t, POINTER(xex_command_graph_desc_t), POINTER(xex_command_graph_handle_t) )

###############################################################################
## @brief Function-pointer for xexCommandGraphDestroy
if __use_win_types:
    _xexCommandGraphDestroy_t = WINFUNCTYPE( xe_result_t, xex_command_graph_handle_t )
else:
    _xexCommandGraphDestroy_t = CFUNCTYPE( xe_result_t, xex_command_graph_handle_t )

###############################################################################
## @brief Function-pointer for xexCommandGraphClose
if __use_win_types:
    _xexCommandGraphClose_t = WINFUNCTYPE( xe_result_t, xex_command_graph_handle_t )
else:
    _xexCommandGraphClose_t = CFUNCTYPE( xe_result_t, xex_command_graph_handle_t )


###############################################################################
## @brief Table of CommandGraph functions pointers
class _xex_command_graph_dditable_t(Structure):
    _fields_ = [
        ("pfnCreate", c_void_p),                                        ## _xexCommandGraphCreate_t
        ("pfnDestroy", c_void_p),                                       ## _xexCommandGraphDestroy_t
        ("pfnClose", c_void_p)                                          ## _xexCommandGraphClose_t
    ]

###############################################################################
class _xex_dditable_t(Structure):
    _fields_ = [
        ("Global", _xex_global_dditable_t),
        ("CommandList", _xex_command_list_dditable_t),
        ("CommandGraph", _xex_command_graph_dditable_t)
    ]

###############################################################################
## @brief xex device-driver interfaces
class XEX_DDI:
    def __init__(self, version : xe_api_version_t):
        # load the xe_loader library
        if "Windows" == platform.uname()[0]:
            self.__dll = WinDLL("xe_loader.dll")
        else:
            self.__dll = CDLL("xe_loader.so")

        # fill the ddi tables
        self.__dditable = _xex_dditable_t()

        # call driver to get function pointers
        _Global = _xex_global_dditable_t()
        r = xe_result_v(self.__dll.xexGetGlobalProcAddrTable(version, byref(_Global)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.Global = _Global

        # attach function interface to function address
        self.xexInit = _xexInit_t(self.__dditable.Global.pfnInit)

        # call driver to get function pointers
        _CommandList = _xex_command_list_dditable_t()
        r = xe_result_v(self.__dll.xexGetCommandListProcAddrTable(version, byref(_CommandList)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandList = _CommandList

        # attach function interface to function address
        self.xexCommandListReserveSpace = _xexCommandListReserveSpace_t(self.__dditable.CommandList.pfnReserveSpace)

        # call driver to get function pointers
        _CommandGraph = _xex_command_graph_dditable_t()
        r = xe_result_v(self.__dll.xexGetCommandGraphProcAddrTable(version, byref(_CommandGraph)))
        if r != xe_result_v.SUCCESS:
            raise Exception(r)
        self.__dditable.CommandGraph = _CommandGraph

        # attach function interface to function address
        self.xexCommandGraphCreate = _xexCommandGraphCreate_t(self.__dditable.CommandGraph.pfnCreate)
        self.xexCommandGraphDestroy = _xexCommandGraphDestroy_t(self.__dditable.CommandGraph.pfnDestroy)
        self.xexCommandGraphClose = _xexCommandGraphClose_t(self.__dditable.CommandGraph.pfnClose)

        # success!
