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

void ShowDeviceInfo(xet_sysman_handle_t hSysman, xet_resource_handle_t hDeviceContainer); // Forward declaration
void ShowFanInfo(xet_sysman_handle_t hSysman, xet_resource_handle_t hFanResource); // Forward declaration

void ShowFans(xet_sysman_handle_t hSysman, xet_resource_handle_t hBoardContainer)
{
    uint32_t numFans = 0;
    if (xetSysmanGetResources(hSysman, hBoardContainer, XET_RESOURCE_TYPE_FAN, &numFans, NULL) == XE_RESULT_SUCCESS)
    {
        xet_resource_handle_t* phFans = (xet_resource_handle_t*)malloc(numFans * sizeof(xet_resource_handle_t));
        if (xetSysmanGetResources(hSysman, hBoardContainer, XET_RESOURCE_TYPE_FAN, &numFans, phFans) == XE_RESULT_SUCCESS)
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

void ShutdownDevice(xet_resource_handle_t hDeviceContainer)
{
    struct
    {
        xet_device_prop_cold_shutdown_t shutdown;
    } data;
    xet_device_property_request_t requests[] = 
    {
        { XET_DEVICE_PROP_COLD_SHUTDOWN,    &data.shutdown, sizeof(data.shutdown) },
    };
    data.shutdown.doShutdown = 1;

    if (xetSysmanResourceSetDeviceProperties(
        hDeviceContainer,
        sizeof(requests) / sizeof(requests[0]),
        requests) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "Device shutdown initiated.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem shutting down the device.\n");
    }
}

struct BoardData
{
    xet_board_prop_serial_number_t  SerialNumber;
    xet_board_prop_board_number_t   BoardNumber;
};

void ShowBoardInfo(xet_sysman_handle_t hSysman, xet_resource_handle_t hDeviceContainer)
{
    xet_resource_handle_t hParentContainer;
    if (xetSysmanResourceGetParent(hDeviceContainer, &hParentContainer) != XE_RESULT_SUCCESS)
    {
        // This device has no parent container
        return;
    }

    xet_resource_info_t info;
    if (xetSysmanResourceGetInfo(hParentContainer, &info) != XE_RESULT_SUCCESS)
    {
        // Can't get information about the parent
        return;
    }

    if (info.type != XET_RESOURCE_TYPE_BOARD_CONTAINER)
    {
        // Parent is not a board
        return;
    }

    BoardData data;
    xet_board_property_request_t requests[] = 
    {
        { XET_BOARD_PROP_SERIAL_NUMBER,     &data.SerialNumber, sizeof(data.SerialNumber) },
        { XET_BOARD_PROP_BOARD_NUMBER,      &data.BoardNumber,  sizeof(data.BoardNumber)  },
    };
    if (xetSysmanResourceGetBoardProperties(
        hParentContainer,
        sizeof(requests) / sizeof(requests[0]),
        requests) == XE_RESULT_SUCCESS)
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

void ShowDeviceInfo(xet_sysman_handle_t hSysman, xet_resource_handle_t hDeviceContainer)
{
    xet_resource_info_t info;
    if (xetSysmanResourceGetInfo(hDeviceContainer, &info) == XE_RESULT_SUCCESS)
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
            xetSysmanGetAccelAssetName(hSysman, (xet_accel_asset_t)i, &pResName);
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
    if (xetSysmanGetResources(hSysman, XET_INVALID_SYSMAN_RESOURCE_HANDLE, XET_RESOURCE_TYPE_DEVICE_CONTAINER, &numDevices, NULL) == XE_RESULT_SUCCESS)
    {
        xet_resource_handle_t* phContainers = (xet_resource_handle_t*)malloc(numDevices * sizeof(xet_resource_handle_t));
        if (xetSysmanGetResources(hSysman, XET_INVALID_SYSMAN_RESOURCE_HANDLE, XET_RESOURCE_TYPE_DEVICE_CONTAINER, &numDevices, phContainers) == XE_RESULT_SUCCESS)
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
            xe_result_t res = xetSysmanCreate(hDeviceGroup, XET_SYSMAN_VERSION_CURRENT, XET_SYSMAN_INIT_FLAGS_WRITE, &hSysman);
            if (res == XE_RESULT_SUCCESS)
            {
                fprintf(stdout, "Have access to system resource management.\n\n");

                ListDevices(hSysman);

                xetSysmanDestroy(hSysman);
            }
            else if (res == XE_RESULT_ACCESS_DENIED)
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