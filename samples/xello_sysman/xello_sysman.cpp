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

void PrintRasDetails(xet_ras_details_t* pDetails)
{
    fprintf(stdout, "        Number new resets:                %llu\n", pDetails->numResets);
    fprintf(stdout, "        Number new programming errors:    %llu\n", pDetails->numProgrammingErrors);
    fprintf(stdout, "        Number new driver errors:         %llu\n", pDetails->numDriverErrors);
    fprintf(stdout, "        Number new compute errors:        %llu\n", pDetails->numComputeErrors);
    fprintf(stdout, "        Number new non-compute errors:    %llu\n", pDetails->numNonComputeErrors);
    fprintf(stdout, "        Number new cache errors:          %llu\n", pDetails->numCacheErrors);
    fprintf(stdout, "        Number new memory errors:         %llu\n", pDetails->numMemoryErrors);
    fprintf(stdout, "        Number new PCI errors:            %llu\n", pDetails->numPciErrors);
    fprintf(stdout, "        Number new switch errors:         %llu\n", pDetails->numSwitchErrors);
    fprintf(stdout, "        Number new display errors:        %llu\n", pDetails->numDisplayErrors);
}

void ShowRasErrors(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numRasErrorSets;
    if ((xetSysmanRasGet(hSysmanDevice, &numRasErrorSets, NULL) == XE_RESULT_SUCCESS) && numRasErrorSets)
    {
        xet_sysman_ras_handle_t* phRasErrorSets =
            (xet_sysman_ras_handle_t*)malloc(numRasErrorSets * sizeof(xet_sysman_ras_handle_t));
        if (xetSysmanRasGet(hSysmanDevice, &numRasErrorSets, phRasErrorSets) == XE_RESULT_SUCCESS)
        {
            for (uint32_t rasIndex = 0; rasIndex < numRasErrorSets; rasIndex++)
            {
                xet_ras_properties_t props;
                if (xetSysmanRasGetProperties(phRasErrorSets[rasIndex], &props) == XE_RESULT_SUCCESS)
                {
                    const char* pErrorType;
                    switch (props.type)
                    {
                    case XET_RAS_ERROR_TYPE_CORRECTABLE:
                        pErrorType = "Correctable";
                        break;
                    case XET_RAS_ERROR_TYPE_UNCORRECTABLE:
                        pErrorType = "Uncorrectable";
                        break;
                    default:
                        pErrorType = "Unknown";
                        break;
                    }
                    fprintf(stdout, "RAS %s errors\n", pErrorType);
                    if (props.onSubdevice)
                    {
                        fprintf(stdout, "    On sub-device: %u\n", props.subdeviceId);
                    }
                    fprintf(stdout, "    RAS supported: %s\n", props.supported ? "yes" : "no");
                    fprintf(stdout, "    RAS enabled: %s\n", props.enabled ? "yes" : "no");
                    if (props.supported && props.enabled)
                    {
                        uint64_t newErrors;
                        xet_ras_details_t errorDetails;
                        if (xetSysmanRasGetErrors(phRasErrorSets[rasIndex], 1, &newErrors, &errorDetails)
                            == XE_RESULT_SUCCESS)
                        {
                            fprintf(stdout, "    Number new errors: %llu\n", newErrors);
                            if (newErrors)
                            {
                                PrintRasDetails(&errorDetails);
                            }
                        }
                    }
                }
            }
        }
        free(phRasErrorSets);
    }
}

void ListDiagnosticTests(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numTestSuites;
    if ((xetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, NULL) == XE_RESULT_SUCCESS) && numTestSuites)
    {
        xet_sysman_diag_handle_t* phTestSuites =
            (xet_sysman_diag_handle_t*)malloc(numTestSuites * sizeof(xet_sysman_diag_handle_t));
        if (xetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, phTestSuites) == XE_RESULT_SUCCESS)
        {
            for (uint32_t suiteIndex = 0; suiteIndex < numTestSuites; suiteIndex++)
            {
                xet_diag_properties_t suiteProps;
                if (xetSysmanDiagnosticsGetProperties(phTestSuites[suiteIndex], &suiteProps) == XE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "Diagnostic test suite %s:\n", suiteProps.name);
                    if (suiteProps.numTests)
                    {
                        for (uint32_t i = 0; i < suiteProps.numTests; i++)
                        {
                            const xet_diag_test_t* pTest = &suiteProps.pTests[i];
                            fprintf(stdout, "    Test %u: %s\n", pTest->index, pTest->name);
                        }
                    }
                    else
                    {
                        fprintf(stdout, "    Cannot run subset of tests.\n");
                    }
                }
            }
        }
        free(phTestSuites);
    }
}

void ResetDevice(xet_sysman_handle_t hSysmanDevice)
{
    if (xetSysmanDeviceReset(hSysmanDevice))
    {
        fprintf(stdout, "Device reset initiated.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem resetting the device.\n");
    }
}

void ShowSwitchInfo(xet_sysman_link_switch_handle_t hSwitch)
{
    xet_link_switch_properties_t swprops;
    if (xetSysmanLinkSwitchGetProperties(hSwitch, &swprops) == XE_RESULT_SUCCESS)
    {
        xet_link_switch_state_t swstate;
        if (xetSysmanLinkSwitchGetState(hSwitch, &swstate) == XE_RESULT_SUCCESS)
        {
            if (swprops.onSubdevice)
            {
                fprintf(stdout, "        On sub-device: %u\n", swprops.subdeviceId);
            }
            fprintf(stdout, "        State:         %s\n", swstate.enabled ? "Enabled" : "Disabled");
            if (swstate.enabled)
            {
                uint32_t numPorts;
                if (xetSysmanLinkSwitchGetPorts(hSwitch, &numPorts, NULL) == XE_RESULT_SUCCESS)
                {
                    xet_sysman_link_port_handle_t* phPorts =
                        (xet_sysman_link_port_handle_t*)malloc(numPorts * sizeof(xet_sysman_link_port_handle_t));
                    if (xetSysmanLinkSwitchGetPorts(hSwitch, &numPorts, phPorts) == XE_RESULT_SUCCESS)
                    {
                        fprintf(stdout, "        Ports:\n");
                        for (uint32_t portIndex = 0; portIndex < numPorts; portIndex++)
                        {
                            xet_link_port_state_t portstate;
                            if (xetSysmanLinkPortGetState(phPorts[portIndex], &portstate)
                                == XE_RESULT_SUCCESS)
                            {
                                fprintf(stdout, "            %u: ", portIndex);
                                if (portstate.isConnected)
                                {
                                    fprintf(stdout,
                                        "connected, max rx/tx bandwidth: %u/%u bytes/sec\n",
                                        portstate.rxSpeed.maxBandwidth, portstate.txSpeed.maxBandwidth);
                                }
                                else
                                {
                                    fprintf(stdout, "not connected\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void ShowSwitches(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numSwitches;
    if ((xetSysmanLinkSwitchGet(hSysmanDevice, &numSwitches, NULL) == XE_RESULT_SUCCESS) && numSwitches)
    {
        xet_sysman_link_switch_handle_t* phSwitches =
            (xet_sysman_link_switch_handle_t*)malloc(numSwitches * sizeof(xet_sysman_link_switch_handle_t));
        if (xetSysmanLinkSwitchGet(hSysmanDevice, &numSwitches, phSwitches) == XE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numSwitches; index++)
            {
                fprintf(stdout, "    Switch %u:\n", index);
                ShowSwitchInfo(phSwitches[index]);
            }
        }
    }
}

void FixGpuFrequency(xet_sysman_handle_t hSysmanDevice, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((xetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == XE_RESULT_SUCCESS) && numFreqDomains)
    {
        xet_sysman_freq_handle_t* pFreqHandles = (xet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(xet_sysman_freq_handle_t));
        if (xetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == XE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                xet_freq_properties_t props;
                if (xetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == XE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == XET_FREQ_DOMAIN_GPU)
                    {
                        if (props.canControl)
                        {
                            xet_freq_range_t range;
                            range.min = FreqMHz;
                            range.max = FreqMHz;
                            if (xetSysmanFrequencySetRange(pFreqHandles[index], &range) != XE_RESULT_SUCCESS)
                            {
                                fprintf(stderr, "ERROR: Problem setting the frequency range for domain with index %u.\n", index);
                            }
                        }
                        else
                        {
                            fprintf(stderr, "ERROR: Can't control GPU frequency domain with index %u.\n", index);
                        }
                    }
                }
            }
        }
        free(pFreqHandles);
    }
}

void FixSubdeviceGpuFrequency(xet_sysman_handle_t hSysmanDevice, uint32_t subdeviceId, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((xetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == XE_RESULT_SUCCESS) && numFreqDomains)
    {
        xet_sysman_freq_handle_t* pFreqHandles = (xet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(xet_sysman_freq_handle_t));
        if (xetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == XE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                xet_freq_properties_t props;
                if (xetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == XE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == XET_FREQ_DOMAIN_GPU)
                    {
                        // Only control the GPU frequency domain for a specific sub-device
                        if (props.onSubdevice && (props.subdeviceId == subdeviceId))
                        {
                            if (props.canControl)
                            {
                                xet_freq_range_t range;
                                range.min = FreqMHz;
                                range.max = FreqMHz;
                                if (xetSysmanFrequencySetRange(pFreqHandles[index], &range) != XE_RESULT_SUCCESS)
                                {
                                    fprintf(stderr, "ERROR: Problem setting the frequency range for domain with index %u.\n", index);
                                }
                            }
                            else
                            {
                                fprintf(stderr, "ERROR: Can't control GPU frequency domain with index %u.\n", index);
                            }
                        }
                    }
                }
            }
        }
        free(pFreqHandles);
    }
}

void SetFanSpeed(xet_sysman_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    uint32_t numFans;
    if (xetSysmanFanGet(hSysmanDevice, &numFans, NULL) == XE_RESULT_SUCCESS)
    {
        xet_sysman_fan_handle_t* phFans =
            (xet_sysman_fan_handle_t*)malloc(numFans * sizeof(xet_sysman_fan_handle_t));
        if (xetSysmanFanGet(hSysmanDevice, &numFans, phFans) == XE_RESULT_SUCCESS)
        {
            xet_fan_config_t config;
            config.mode = XET_FAN_SPEED_MODE_FIXED;
            config.speed = SpeedRpm;
            config.speedUnits = XET_FAN_SPEED_UNITS_RPM;
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                xet_fan_properties_t fanprops;
                if (xetSysmanFanGetProperties(phFans[fanIndex], &fanprops) == XE_RESULT_SUCCESS)
                {
                    if (fanprops.canControl)
                    {
                        xetSysmanFanSetConfig(phFans[fanIndex], &config);
                    }
                    else
                    {
                        fprintf(stderr, "ERROR: Can't control fan %u.\n", fanIndex);
                    }
                }
            }
        }
        free(phFans);
    }
}

void ShowFans(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFans;
    if (xetSysmanFanGet(hSysmanDevice, &numFans, NULL) == XE_RESULT_SUCCESS)
    {
        xet_sysman_fan_handle_t* phFans =
            (xet_sysman_fan_handle_t*)malloc(numFans * sizeof(xet_sysman_fan_handle_t));
        if (xetSysmanFanGet(hSysmanDevice, &numFans, phFans) == XE_RESULT_SUCCESS)
        {
            fprintf(stdout, "    Fans\n");
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                xet_fan_state_t state;
                if (xetSysmanFanGetState(phFans[fanIndex], XET_FAN_SPEED_UNITS_RPM, &state)
                    == XE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "        Fan %u: %u RPM\n", fanIndex, state.speed);
                }
            }
        }
        free(phFans);
    }
}

void ShowAveragePower(xet_sysman_pwr_handle_t hPower, xet_power_energy_counter_t* pPrevEnergyCounter)
{
    xet_power_energy_counter_t newEnergyCounter;
    if (xetSysmanPowerGetEnergyCounter(hPower, &newEnergyCounter) == XE_RESULT_SUCCESS)
    {
        uint64_t deltaTime = newEnergyCounter.timestamp - pPrevEnergyCounter->timestamp;
        if (deltaTime)
        {
            fprintf(stdout, "    Average power: %.3f W\n",
                ((double)(newEnergyCounter.energy - pPrevEnergyCounter->energy)) / ((double)deltaTime));
            *pPrevEnergyCounter = newEnergyCounter;
        }
    }
}

// Forward declaration
void ShowPowerLimits(xet_sysman_pwr_handle_t hPower);

void ShowPowerDomains(xet_sysman_handle_t hSysmanDevice)
{
    uint32_t numPowerDomains;
    if (xetSysmanPowerGet(hSysmanDevice, &numPowerDomains, NULL) == XE_RESULT_SUCCESS)
    {
        xet_sysman_pwr_handle_t* phPower =
            (xet_sysman_pwr_handle_t*)malloc(numPowerDomains * sizeof(xet_sysman_pwr_handle_t));
        if (xetSysmanPowerGet(hSysmanDevice, &numPowerDomains, phPower) == XE_RESULT_SUCCESS)
        {
            for (uint32_t pwrIndex = 0; pwrIndex < numPowerDomains; pwrIndex++)
            {
                xet_power_properties_t props;
                if (xetSysmanPowerGetProperties(phPower[pwrIndex], &props) == XE_RESULT_SUCCESS)
                {
                    if (props.onSubdevice)
                    {
                        fprintf(stdout, "Sub-device %u power:\n", props.subdeviceId);
                        fprintf(stdout, "    Can control: %s\n", props.canControl ? "yes" : "no");
                        ShowPowerLimits(phPower[pwrIndex]);
                    }
                    else
                    {
                        fprintf(stdout, "Total package power:\n");
                        fprintf(stdout, "    Can control: %s\n", props.canControl ? "yes" : "no");
                        ShowPowerLimits(phPower[pwrIndex]);
                    }
                }
            }
        }
        free(phPower);
    }
}

void ShowPowerLimits(xet_sysman_pwr_handle_t hPower)
{
    xet_power_sustained_limit_t sustainedLimits;
    xet_power_burst_limit_t burstLimits;
    xet_power_peak_limit_t peakLimits;
    if (xetSysmanPowerGetLimits(hPower, &sustainedLimits, &burstLimits, &peakLimits) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Power limits\n");
        if (sustainedLimits.enabled)
        {
            fprintf(stdout, "        Sustained: %.3f W %.3f sec\n",
                ((double)sustainedLimits.power) / 1000, ((double)sustainedLimits.interval) / 1000);
        }
        else
        {
            fprintf(stdout, "        Sustained: Disabled\n");
        }
        if (burstLimits.enabled)
        {
            fprintf(stdout, "        Burst:     %.3f\n", ((double)burstLimits.power) / 1000);
        }
        else
        {
            fprintf(stdout, "        Burst:     Disabled\n");
        }
        fprintf(stdout, "        Burst:     %.3f\n", ((double)peakLimits.power) / 1000);
    }
}

void ShowDeviceInfo(xet_sysman_handle_t hSysmanDevice)
{
    xet_sysman_properties_t devProps;
    xe_bool_t repaired;
    if (xetSysmanDeviceGetProperties(hSysmanDevice, &devProps) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:           %s\n", devProps.core.uuid.id);
        fprintf(stdout, "    #subdevices:    %u\n", devProps.numSubdevices);
        fprintf(stdout, "    brand:          %s\n", devProps.brandName);
        fprintf(stdout, "    model:          %s\n", devProps.modelName);
        fprintf(stdout, "    driver timeout: disabled\n");
    }
    if (xetSysmanDeviceWasRepaired(hSysmanDevice, &repaired) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Was repaired:   %s\n", repaired ? "yes" : "no");
    }
}

void DisableSchedulerWatchdog(xet_sysman_handle_t hSysmanDevice)
{
    xe_result_t res;
    xet_sched_mode_t currentMode;
    res = xetSysmanDeviceSchedulerGetCurrentMode(hSysmanDevice, &currentMode);
    if (res == XE_RESULT_SUCCESS)
    {
        xe_bool_t requireReboot;
        xet_sched_concurrent_properties_t props;
        props.watchdogTimeout = XET_SCHED_WATCHDOG_DISABLE;
        res = xetSysmanDeviceSchedulerSetConcurrentMode(hSysmanDevice, &props, &requireReboot);
        if (res == XE_RESULT_SUCCESS)
        {
            if (requireReboot)
            {
                fprintf(stderr, "WARNING: Reboot required to complete desired configuration.\n");
            }
            else
            {
                fprintf(stdout, "Schedule mode changed successfully.\n");
            }
        }
        else if(res == XE_RESULT_ERROR_UNSUPPORTED)
        {
            fprintf(stderr, "ERROR: The concurrent scheduler mode is not supported on this device.\n");
        }
        else if(res == XE_RESULT_ERROR_INSUFFICENT_PERMISSIONS)
        {
            fprintf(stderr, "ERROR: Don't have permissions to change the scheduler mode.\n");
        }
        else
        {
            fprintf(stderr, "ERROR: Problem calling the API to change the scheduler mode.\n");
        }
    }
    else if(res == XE_RESULT_ERROR_UNSUPPORTED)
    {
        fprintf(stderr, "ERROR: Scheduler modes are not supported on this device.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem calling the API.\n");
    }
}

void ShowPciInfo(xet_sysman_handle_t hSysmanDevice)
{
    xet_pci_properties_t pciProps;
    if (xetSysmanPciGetProperties(hSysmanDevice, &pciProps) == XE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    PCI address:        %04u:%02u:%02u.%u\n", pciProps.address.domain, pciProps.address.bus, pciProps.address.device, pciProps.address.function);
    }
}

int gNumDevices = 0;    // Global

int ListDevice(xe_device_handle_t hDevice)
{
    int ret = 0;

    xet_sysman_handle_t hSysmanDevice;
    xe_result_t res = xetSysmanGet(hDevice, XET_SYSMAN_VERSION_CURRENT, &hSysmanDevice);
    if (res == XE_RESULT_SUCCESS)
    {
        gNumDevices++;

        fprintf(stdout, "Device %d\n", gNumDevices);

        ShowDeviceInfo(hSysmanDevice);
    }
    else
    {
        fprintf(stderr, "ERROR: Can't initialize system resource management for this device.\n");
        ret++;
    }

    return ret;
}

int main( int argc, char *argv[] )
{
    int ret = -1;
    if ( (xeInit(XE_INIT_FLAG_NONE) != XE_RESULT_SUCCESS) ||
         (xetInit(XE_INIT_FLAG_NONE) != XE_RESULT_SUCCESS) )
    {
        fprintf(stderr, "Can't initialize the API.\n");
        ret = 1;
    }
    else
    {
        // Discover all the device groups and devices
        uint32_t driversCount = 0;
        xeDriverGet(&driversCount, nullptr);
        xe_driver_handle_t* allDrivers = (xe_driver_handle_t*)
            malloc(driversCount * sizeof(xe_driver_handle_t));
        xeDriverGet(&driversCount, allDrivers);

        // Find the first GPU device group
        xe_driver_handle_t hDriver = nullptr;
        for(uint32_t i = 0; i < driversCount; ++i)
        {
            uint32_t deviceCount = 0;
            xeDeviceGet(allDrivers[i], &deviceCount, nullptr);

            xe_device_handle_t* allDevices = (xe_device_handle_t*)
                malloc(deviceCount * sizeof(xe_device_handle_t));
            xeDeviceGet(allDrivers[i], &deviceCount, allDevices);

            for(uint32_t d = 0; d < deviceCount; ++i)
            {
                xe_device_properties_t device_properties;
                xeDeviceGetProperties(allDevices[d], &device_properties);
                if(XE_DEVICE_TYPE_GPU == device_properties.type)
                {
                    if ((ret = ListDevice(allDevices[d])) != 0)
                    {
                        break;
                    }
                }
            }

            free(allDevices);
        }

        free(allDrivers);
    }

    if (gNumDevices == 0)
    {
        fprintf(stdout, "No managed devices found.\n");
    }

    return ret;
}
