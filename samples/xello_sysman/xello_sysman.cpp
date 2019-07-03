/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "xello_sysman.h"

//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "xet_api.h"

void ShowDeviceInfo(xet_sysman_handle_t hSysman, xet_res_container_handle_t hDeviceContainer); // Forward declaration
void ShowFanInfo(xet_sysman_handle_t hSysman, xet_resource_handle_t hFanResource); // Forward declaration

void ShowFans(xet_sysman_handle_t hSysman, xet_res_container_handle_t hBoardContainer)
{
    uint32_t numFans = 0;
    if (xetSysmanResContainerGetResources(hBoardContainer, XET_RESOURCE_TYPE_FAN, &numFans, NULL) == XE_RESULT_SUCCESS)
    {
        xet_resource_handle_t* phFans = (xet_resource_handle_t*)malloc(numFans * sizeof(xet_resource_handle_t));
        if (xetSysmanResContainerGetResources(hBoardContainer, XET_RESOURCE_TYPE_FAN, &numFans, phFans) == XE_RESULT_SUCCESS)
        {
            for (uint32_t i = 0; i < numFans; i++)
            {
                ShowFanInfo(hSysman, phFans[i]);
            }
        }
        free(phFans);
    }
}

void ShowFanInfo(xet_sysman_handle_t hSysman, xet_resource_handle_t hFanResource)
{
    xet_resource_info_t info;
    if (xetSysmanResourceGetInfo(hFanResource, &info) == XE_RESULT_SUCCESS)
    {
        char uuidStr[XET_RESOURCE_UUID_STRING_SIZE + 1] = { 0 };
        uint32_t size = sizeof(uuidStr);
        xetSysmanConvertUuidToString(hSysman, &info.uuid, &size, uuidStr);

        fprintf(stdout, "Fan\n");
        fprintf(stdout, "    UUID: %s\n", uuidStr);
        fprintf(stdout, "\n");
    }

}

void ShutdownDevice(xet_res_container_handle_t hDeviceContainer)
{
    xet_device_properties_t prop = XET_DEVICE_PROP_COLD_SHUTDOWN;
    xe_bool_t shutdown = 1;
    if (xetSysmanResContainerSetDeviceProperties(
        hDeviceContainer,
        1,
        &prop,
        &shutdown,
        sizeof(shutdown)) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Device shutdown initiated.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem shutting down the device.\n");
    }
}

static const xet_board_properties_t sBoardProperties[] = {
    XET_BOARD_PROP_SERIAL_NUMBER,
    XET_BOARD_PROP_BOARD_NUMBER
};
struct BoardData
{
    xet_board_prop_serial_number_t  SerialNumber;
    xet_board_prop_board_number_t   BoardNumber;
};

void ShowBoardInfo(xet_sysman_handle_t hSysman, xet_res_container_handle_t hDeviceContainer)
{
    xet_res_container_handle_t hParentContainer;
    if (xetSysmanResContainerGetParent(hDeviceContainer, &hParentContainer) != XE_RESULT_SUCCESS)
    {
        // This device has no parent container
        return;
    }

    xet_res_container_info_t info;
    if (xetSysmanResContainerGetInfo(hParentContainer, &info) != XE_RESULT_SUCCESS)
    {
        // Can't get information about the parent
        return;
    }

    if (info.type != XET_RES_CONTAINER_TYPE_BOARD)
    {
        // Parent is not a board
        return;
    }

    BoardData data;
    uint32_t size = sizeof(data);
    if (xetSysmanResContainerGetBoardProperties(
        hParentContainer,
        sizeof(sBoardProperties) / sizeof(sBoardProperties[0]),
        sBoardProperties,
        &data,
        &size) == XE_RESULT_SUCCESS)
    {
        char uuidStr[XET_RESOURCE_UUID_STRING_SIZE + 1] = { 0 };
        uint32_t size = sizeof(uuidStr);
        xetSysmanConvertUuidToString(hSysman, &info.uuid, &size, uuidStr);

        fprintf(stdout, "Board\n");
        fprintf(stdout, "    UUID:    %s\n", uuidStr);
        fprintf(stdout, "    Serial#: %s\n", data.SerialNumber.str);
        fprintf(stdout, "    Board#:  %s\n", data.BoardNumber.str);
    }
}

void ShowDeviceInfo(xet_sysman_handle_t hSysman, xet_res_container_handle_t hDeviceContainer)
{
    xet_res_container_info_t info;
    if (xetSysmanResContainerGetInfo(hDeviceContainer, &info) == XE_RESULT_SUCCESS)
    {
        char uuidStr[XET_RESOURCE_UUID_STRING_SIZE + 1] = { 0 };
        uint32_t size = sizeof(uuidStr);
        xetSysmanConvertUuidToString(hSysman, &info.uuid, &size, uuidStr);

        fprintf(stdout, "Device\n");
        fprintf(stdout, "    UUID: %s\n", uuidStr);
        fprintf(stdout, "    # sub-devices: %u\n", info.numChildren);
        fprintf(stdout, "    # p2p links: %u\n", info.numPeers);
        fprintf(stdout, "    Assets:\n");
        for (int i = 0; i < XET_ACCEL_ASSET_MAX_TYPES; i++)
        {
            const char* pResName;
            xetSysmanResContainerGetAccelAssetName(hDeviceContainer, (xet_accel_asset_t)i, &pResName);
            if (info.numResourcesByType[i])
            {
                fprintf(stdout, "        %s: %u\n", pResName, info.numResourcesByType[i]);
            }
        }
        fprintf(stdout, "\n");
    }
}

void ListDevices(xet_sysman_handle_t hSysman)
{
    uint32_t numDevices = 0;
    if (xetSysmanGetResourceContainers(hSysman, XET_RES_CONTAINER_TYPE_DEVICE, &numDevices, NULL) == XE_RESULT_SUCCESS)
    {
        xet_res_container_handle_t* phContainers = (xet_res_container_handle_t*)malloc(numDevices * sizeof(xet_res_container_handle_t));
        if (xetSysmanGetResourceContainers(hSysman, XET_RES_CONTAINER_TYPE_DEVICE, &numDevices, phContainers) == XE_RESULT_SUCCESS)
        {
            for (uint32_t i = 0; i < numDevices; i++)
            {
                ShowDeviceInfo(hSysman, phContainers[i]);
            }
        }
        free(phContainers);
    }
}

int main( int argc, char *argv[] )
{
    xet_sysman_handle_t hSysman;
    int ret = -1;
    if ( (xeInit(XE_INIT_FLAG_NONE) != XE_RESULT_SUCCESS) ||
         (xetInit(XE_INIT_FLAG_NONE) != XE_RESULT_SUCCESS) )
    {
        fprintf(stderr, "Can't initialize the API.\n");
        ret = 1;
    }
    else
    {
        uint32_t numDeviceGroups = 1;
        xe_device_group_handle_t hDeviceGroup;
        if (xeDeviceGroupGet(&numDeviceGroups, &hDeviceGroup) == XE_RESULT_SUCCESS)
        {
            xe_result_t res = xetSysmanCreate(hDeviceGroup, XET_SYSMAN_INIT_FLAGS_WRITE, &hSysman);
            if (res == XE_RESULT_SUCCESS)
            {
                fprintf(stdout, "Have access to system resource management.\n\n");

                ListDevices(hSysman);

                xetSysmanDestroy(hSysman);
            }
            else if (res == XE_RESULT_ERROR_ACCESS_DENIED)
            {
                fprintf(stderr, "ERROR: Don't have write access to accelerator resources.\n");
            }
            else
            {
                fprintf(stderr, "ERROR: Can't initialize management of accelerator resources.\n");
            }
        }
    }

    return ret;
}