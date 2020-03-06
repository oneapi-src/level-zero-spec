/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "zello_sysman.h"

//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "zet_api.h"

void PrintRasDetails(zet_ras_details_t* pDetails)
{
    fprintf(stdout, "        Number new resets:                %llu\n", (long long unsigned int)pDetails->numResets);
    fprintf(stdout, "        Number new programming errors:    %llu\n", (long long unsigned int)pDetails->numProgrammingErrors);
    fprintf(stdout, "        Number new driver errors:         %llu\n", (long long unsigned int)pDetails->numDriverErrors);
    fprintf(stdout, "        Number new compute errors:        %llu\n", (long long unsigned int)pDetails->numComputeErrors);
    fprintf(stdout, "        Number new non-compute errors:    %llu\n", (long long unsigned int)pDetails->numNonComputeErrors);
    fprintf(stdout, "        Number new cache errors:          %llu\n", (long long unsigned int)pDetails->numCacheErrors);
    fprintf(stdout, "        Number new display errors:        %llu\n", (long long unsigned int)pDetails->numDisplayErrors);
}

void ShowRasErrors(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numRasErrorSets;
    zet_sysman_ras_handle_t* phRasErrorSets;
    if (zetSysmanRasGet(hSysmanDevice, &numRasErrorSets, NULL) != ZE_RESULT_SUCCESS)
    {
        return;
    }
    if (numRasErrorSets == 0)
    {
        fprintf(stdout, "No RAS error sets available/enabled on this device.\n");
        return;
    }
    phRasErrorSets =
        (zet_sysman_ras_handle_t*)malloc(numRasErrorSets * sizeof(zet_sysman_ras_handle_t));
    if (zetSysmanRasGet(hSysmanDevice, &numRasErrorSets, phRasErrorSets) == ZE_RESULT_SUCCESS)
    {
        for (uint32_t rasIndex = 0; rasIndex < numRasErrorSets; rasIndex++)
        {
            zet_ras_properties_t props;
            if (zetSysmanRasGetProperties(phRasErrorSets[rasIndex], &props) == ZE_RESULT_SUCCESS)
            {
                uint64_t newErrors;
                zet_ras_details_t errorDetails;
                const char* pErrorType;
                switch (props.type)
                {
                case ZET_RAS_ERROR_TYPE_CORRECTABLE:
                    pErrorType = "Correctable";
                    break;
                case ZET_RAS_ERROR_TYPE_UNCORRECTABLE:
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
                if (zetSysmanRasGetState(phRasErrorSets[rasIndex], 1, &newErrors, &errorDetails)
                    == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "    Number new errors: %llu\n", (long long unsigned int)newErrors);
                    if (newErrors)
                    {
                        PrintRasDetails(&errorDetails);
                    }
                }
            }
        }
    }
    free(phRasErrorSets);
}

void ListDiagnosticTests(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numTestSuites;
    if ((zetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, NULL) == ZE_RESULT_SUCCESS) && numTestSuites)
    {
        zet_sysman_diag_handle_t* phTestSuites =
            (zet_sysman_diag_handle_t*)malloc(numTestSuites * sizeof(zet_sysman_diag_handle_t));
        if (zetSysmanDiagnosticsGet(hSysmanDevice, &numTestSuites, phTestSuites) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t suiteIndex = 0; suiteIndex < numTestSuites; suiteIndex++)
            {
                uint32_t numTests = 0;
                zet_diag_test_t* pTests;
                zet_diag_properties_t suiteProps;
                if (zetSysmanDiagnosticsGetProperties(phTestSuites[suiteIndex], &suiteProps) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                fprintf(stdout, "Diagnostic test suite %s:\n", suiteProps.name);
                if (!suiteProps.haveTests)
                {
                    fprintf(stdout, "    There are no individual tests that can be selected.\n");
                    continue;
                }
                if (zetSysmanDiagnosticsGetTests(phTestSuites[suiteIndex], &numTests, NULL) != ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "    Problem getting list of individual tests.\n");
                    continue;
                }
                pTests = (zet_diag_test_t*)malloc(numTests * sizeof(zet_diag_test_t*));
                if (zetSysmanDiagnosticsGetTests(phTestSuites[suiteIndex], &numTests, pTests) != ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "    Problem getting list of individual tests.\n");
                    continue;
                }
                for (uint32_t i = 0; i < numTests; i++)
                {
                    fprintf(stdout, "    Test %u: %s\n", pTests[i].index, pTests[i].name);
                }
                free(pTests);
            }
        }
        free(phTestSuites);
    }
}

void WaitForExcessTemperatureEvent(zet_driver_handle_t hDriver, double tempLimit)
{
    uint32_t deviceCount = 0;
    uint32_t numEventHandles = 0;
    ze_device_handle_t* phDevices;
    zet_sysman_event_handle_t* phEvents;
    zet_sysman_event_handle_t* phListenEvents;
    uint32_t* pListenDeviceIndex;

    // Get list of all devices under this driver
    zeDeviceGet(hDriver, &deviceCount, nullptr);
    phDevices = (ze_device_handle_t*)malloc(deviceCount * sizeof(ze_device_handle_t));
    phEvents = (zet_sysman_event_handle_t*)malloc(deviceCount * sizeof(zet_sysman_event_handle_t));
    phListenEvents = (zet_sysman_event_handle_t*)malloc(deviceCount * sizeof(zet_sysman_event_handle_t));
    pListenDeviceIndex = (uint32_t*)malloc(deviceCount * sizeof(uint32_t));
    zeDeviceGet(hDriver, &deviceCount, phDevices);
    for(uint32_t d = 0; d < deviceCount; ++d)
    {
        // Get Sysman handle, event handle and list of temperature sensors in the device
        uint32_t numTempSensors = 0;
        uint32_t numConfiguredTempSensors = 0;
        zet_sysman_temp_handle_t* allTempSensors;
        zet_sysman_handle_t hSysmanDevice;
        if (zetSysmanGet(phDevices[d], ZET_SYSMAN_VERSION_CURRENT, &hSysmanDevice) != ZE_RESULT_SUCCESS)
        {
            continue;
        }
        if (zetSysmanEventGet(hSysmanDevice, &phEvents[d]) != ZE_RESULT_SUCCESS)
        {
            continue;
        }
        if (zetSysmanTemperatureGet(hSysmanDevice, &numTempSensors, NULL) != ZE_RESULT_SUCCESS)
        {
            continue;
        }
        allTempSensors = (zet_sysman_temp_handle_t*)malloc(deviceCount * sizeof(zet_sysman_temp_handle_t));
        if (zetSysmanTemperatureGet(hSysmanDevice, &numTempSensors, allTempSensors) == ZE_RESULT_SUCCESS)
        {
            // Configure each temperature sensor to trigger a critical event and a threshold1 event
            zet_temp_config_t config;
            for (uint32_t t = 0; t < numTempSensors; t++)
            {
                if (zetSysmanTemperatureGetConfig(allTempSensors[t], &config) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                config.enableCritical = true;
                config.threshold1.enableHighToLow = false;
                config.threshold1.enableLowToHigh = true;
                config.threshold1.threshold = tempLimit;
                config.threshold2.enableHighToLow = false;
                config.threshold2.enableLowToHigh = false;
                if (zetSysmanTemperatureSetConfig(allTempSensors[t], &config) == ZE_RESULT_SUCCESS)
                {
                    numConfiguredTempSensors++;
                }
            }
        }
        if (numConfiguredTempSensors)
        {
            zet_event_config_t eventConfig;
            eventConfig.registered = ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL | ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1;
            if (zetSysmanEventSetConfig(phEvents[d], &eventConfig) == ZE_RESULT_SUCCESS)
            {
                phListenEvents[numEventHandles] = phEvents[d];
                pListenDeviceIndex[numEventHandles] = d;
                numEventHandles++;
            }
        }
        free(allTempSensors);
    }

    if (numEventHandles)
    {
        uint32_t events;
        // Block until we receive events
        if (zetSysmanEventListen(hDriver, ZET_EVENT_WAIT_INFINITE, deviceCount, phListenEvents, &events) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t e = 0; e < numEventHandles; e++)
            {
                if (zetSysmanEventGetState(phListenEvents[e], true, &events) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                if (events & ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL)
                {
                    fprintf(stdout, "Device %u: Went above the critical temperature.\n", pListenDeviceIndex[e]);
                }
                else if (events & ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1)
                {
                    fprintf(stdout, "Device %u: Went above the temperature threshold %f.\n", pListenDeviceIndex[e], tempLimit);
                }
            }
        }
    }

    free(phDevices);
    free(phEvents);
    free(phListenEvents);
}

void ResetDevice(zet_sysman_handle_t hSysmanDevice)
{
    if (zetSysmanDeviceReset(hSysmanDevice))
    {
        fprintf(stdout, "Device reset initiated.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem resetting the device.\n");
    }
}

void ShowFabricPortInfo(zet_sysman_fabric_port_handle_t hPort)
{
    zet_fabric_port_properties_t props;
    if (zetSysmanFabricPortGetProperties(hPort, &props) == ZE_RESULT_SUCCESS)
    {
        zet_fabric_port_state_t state;
        if (zetSysmanFabricPortGetState(hPort, &state) == ZE_RESULT_SUCCESS)
        {
            zet_fabric_link_type_t link;
            if (zetSysmanFabricPortGetLinkType(hPort, false, &link) == ZE_RESULT_SUCCESS)
            {
                zet_fabric_port_config_t config;
                if (zetSysmanFabricPortGetConfig(hPort, &config) == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout,
                        "        Model:                 %s\n", props.model);
                    if (props.onSubdevice)
                    {
                        fprintf(stdout,
                            "        On sub-device:         %u\n", props.subdeviceId);
                    }
                    if (config.enabled)
                    {
                        const char* status;
                        fprintf(stdout,
                            "        Config:                UP\n");
                        switch (state.status)
                        {
                        case ZET_FABRIC_PORT_STATUS_GREEN:
                            status = "GREEN - The port is up and operating as expected";
                            break;
                        case ZET_FABRIC_PORT_STATUS_YELLOW:
                            status = "YELLOW - The port is up but has quality and/or bandwidth degradation";
                            break;
                        case ZET_FABRIC_PORT_STATUS_RED:
                            status = "RED - Port connection instabilities";
                            break;
                        case ZET_FABRIC_PORT_STATUS_BLACK:
                            status = "BLACK - The port is configured down";
                            break;
                        default:
                            status = "UNKNOWN";
                            break;
                        }
                        fprintf(stdout,
                            "        Status:                %s\n", status);
                        fprintf(stdout,
                            "        Link type:             %s\n", link.desc);
                        fprintf(stdout,
                            "        Max speed (rx/tx):     %llu/%llu bytes/sec\n",
                            (long long unsigned int)props.maxRxSpeed.maxBandwidth,
                            (long long unsigned int)props.maxTxSpeed.maxBandwidth);
                        fprintf(stdout,
                            "        Current speed (rx/tx): %llu/%llu bytes/sec\n",
                            (long long unsigned int)state.rxSpeed.maxBandwidth,
                            (long long unsigned int)state.txSpeed.maxBandwidth);
                    }
                    else
                    {
                        fprintf(stdout,
                            "        Config:                DOWN\n");
                    }
                }
            }
        }
    }
}

void ShowFabricPorts(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numPorts;
    if ((zetSysmanFabricPortGet(hSysmanDevice, &numPorts, NULL) == ZE_RESULT_SUCCESS) && numPorts)
    {
        zet_sysman_fabric_port_handle_t* phPorts =
            (zet_sysman_fabric_port_handle_t*)malloc(numPorts * sizeof(zet_sysman_fabric_port_handle_t));
        if (zetSysmanFabricPortGet(hSysmanDevice, &numPorts, phPorts) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numPorts; index++)
            {
                fprintf(stdout, "    Port %u:\n", index);
                ShowFabricPortInfo(phPorts[index]);
            }
        }
        free(phPorts);
    }
}

// Try to overclock frequency 5% above the factory default with 10% increase in voltage
bool SetOverclock(zet_sysman_freq_handle_t hFreqDomain)
{
    bool ret = false;
    zet_oc_capabilities_t oc_caps;
    if (zetSysmanFrequencyOcGetCapabilities(hFreqDomain, &oc_caps) == ZE_RESULT_SUCCESS)
    {
        double CurrentMaxFrequencyMhz = oc_caps.maxFactoryDefaultFrequency;
        CurrentMaxFrequencyMhz *= 1.05;
        if (CurrentMaxFrequencyMhz <= oc_caps.maxOcFrequency)
        {
            ze_result_t status;
            zet_oc_config_t config;
            ze_bool_t reset;
            config.mode = zet_oc_mode_t::ZET_OC_MODE_INTERPOLATIVE;
            config.frequency = CurrentMaxFrequencyMhz;
            config.voltageTarget = oc_caps.maxFactoryDefaultVoltage * 1.1;
            config.voltageOffset = 0.0;

            status = zetSysmanFrequencyOcSetConfig(hFreqDomain, &config, &reset);
            if (status == ZE_RESULT_SUCCESS)
            {
                fprintf(stdout, "Successfully overclocked to %.3f Mhz\n", CurrentMaxFrequencyMhz);
                if (reset)
                {
                    fprintf(stderr, "Please reset the device for the new overclock settings to take effect.\n");
                }
                ret = true;
            }
            else if (status == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE)
            {
                fprintf(stderr, "ERROR: Overclocking not supported.\n");
            }
            else if (status == ZE_RESULT_ERROR_NOT_AVAILABLE)
            {
                fprintf(stderr, "ERROR: Overclocking locked by the BIOS.\n");
            }
            else if (status == ZE_RESULT_ERROR_INVALID_ARGUMENT)
            {
                fprintf(stderr, "ERROR: The overclock frequency or voltage is too high.\n");
            }
            else if (status == ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS )
            {
                fprintf(stderr, "ERROR: You don't have permission to overclock.\n");
            }
            else
            {
                fprintf(stderr, "ERROR: Problem requesting overclock.\n");
            }
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Problem getting overclock capabilities.\n");
    }
    return ret;
}

void ShowOcCapabilities(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFreqDomains;
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zet_sysman_freq_handle_t* pFreqHandles = (zet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(zet_sysman_freq_handle_t));
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zet_freq_properties_t props;
                zet_oc_capabilities_t oc_caps;
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                // Only control GPU frequency domains
                if (props.type != ZET_FREQ_DOMAIN_GPU)
                {
                    continue;
                }
                if (zetSysmanFrequencyOcGetCapabilities(pFreqHandles[index], &oc_caps) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                fprintf(stdout, "GPU frequency domaion %u:\n", index);
                if (oc_caps.isOcSupported)
                {
                    fprintf(stdout, "    Overclocking supported with these capabilities:\n");
                    fprintf(stdout, "        Max overclock Frequency: %.3f MHz\n", oc_caps.maxOcFrequency);
                    fprintf(stdout, "        Max overclock Voltage: %.3f Volts\n", oc_caps.maxOcVoltage);
                    fprintf(stdout, "        Max factory default frequency: %.3f\n", oc_caps.maxFactoryDefaultFrequency);
                    fprintf(stdout, "        Max factory default voltage: %.3f\n", oc_caps.maxFactoryDefaultVoltage);
                    fprintf(stdout, "        Is high voltage capable: %s\n", oc_caps.isHighVoltModeCapable ? "yes" : "no");
                    fprintf(stdout, "        Is high voltage enabled: %s\n", oc_caps.isHighVoltModeEnabled ? "yes" : "no");
                    fprintf(stdout, "        Is TjMax Supported: %s\n", oc_caps.isTjMaxSupported ? "yes" : "no");
                    fprintf(stdout, "        Is IccMax Supported: %s\n", oc_caps.isIccMaxSupported ? "yes" : "no");

                    if (oc_caps.isIccMaxSupported)
                    {
                        double iccmax;
                        if (zetSysmanFrequencyOcGetIccMax(pFreqHandles[index], &iccmax) == ZE_RESULT_SUCCESS) 
                        {
                            fprintf(stdout, "    Icc Max: %.3f A\n", iccmax);
                        }
                    }

                    if (oc_caps.isTjMaxSupported)
                    {
                        double tjmax;
                        if (zetSysmanFrequencyOcGetTjMax(pFreqHandles[index], &tjmax) == ZE_RESULT_SUCCESS)
                        {
                            fprintf(stdout, "    TjMax: %.3f\n", tjmax);
                        }
                    }                                                 
                }
                else
                {
                    fprintf(stdout, "    Overclocking not supported\n");
                }
            }
        }
        free(pFreqHandles);
    }    
}

void FixGpuFrequency(zet_sysman_handle_t hSysmanDevice, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zet_sysman_freq_handle_t* pFreqHandles = (zet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(zet_sysman_freq_handle_t));
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zet_freq_properties_t props;
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZET_FREQ_DOMAIN_GPU)
                    {
                        if (props.canControl)
                        {
                            zet_freq_range_t range;
                            range.min = FreqMHz;
                            range.max = FreqMHz;
                            if (zetSysmanFrequencySetRange(pFreqHandles[index], &range) != ZE_RESULT_SUCCESS)
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

void FixSubdeviceGpuFrequency(zet_sysman_handle_t hSysmanDevice, uint32_t subdeviceId, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zet_sysman_freq_handle_t* pFreqHandles = (zet_sysman_freq_handle_t*)malloc(numFreqDomains * sizeof(zet_sysman_freq_handle_t));
        if (zetSysmanFrequencyGet(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zet_freq_properties_t props;
                if (zetSysmanFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZET_FREQ_DOMAIN_GPU)
                    {
                        // Only control the GPU frequency domain for a specific sub-device
                        if (props.onSubdevice && (props.subdeviceId == subdeviceId))
                        {
                            if (props.canControl)
                            {
                                zet_freq_range_t range;
                                range.min = FreqMHz;
                                range.max = FreqMHz;
                                if (zetSysmanFrequencySetRange(pFreqHandles[index], &range) != ZE_RESULT_SUCCESS)
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

void SetFanSpeed(zet_sysman_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    uint32_t numFans;
    if (zetSysmanFanGet(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_fan_handle_t* phFans =
            (zet_sysman_fan_handle_t*)malloc(numFans * sizeof(zet_sysman_fan_handle_t));
        if (zetSysmanFanGet(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
        {
            zet_fan_config_t config;
            config.mode = ZET_FAN_SPEED_MODE_FIXED;
            config.speed = SpeedRpm;
            config.speedUnits = ZET_FAN_SPEED_UNITS_RPM;
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                zet_fan_properties_t fanprops;
                if (zetSysmanFanGetProperties(phFans[fanIndex], &fanprops) == ZE_RESULT_SUCCESS)
                {
                    if (fanprops.canControl)
                    {
                        zetSysmanFanSetConfig(phFans[fanIndex], &config);
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

void ShowFans(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numFans;
    if (zetSysmanFanGet(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_fan_handle_t* phFans =
            (zet_sysman_fan_handle_t*)malloc(numFans * sizeof(zet_sysman_fan_handle_t));
        if (zetSysmanFanGet(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
        {
            fprintf(stdout, "    Fans\n");
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                uint32_t speed;
                if (zetSysmanFanGetState(phFans[fanIndex], ZET_FAN_SPEED_UNITS_RPM, &speed)
                    == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "        Fan %u: %u RPM\n", fanIndex, speed);
                }
            }
        }
        free(phFans);
    }
}

void ShowAveragePower(zet_sysman_pwr_handle_t hPower, zet_power_energy_counter_t* pPrevEnergyCounter)
{
    zet_power_energy_counter_t newEnergyCounter;
    if (zetSysmanPowerGetEnergyCounter(hPower, &newEnergyCounter) == ZE_RESULT_SUCCESS)
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

// Forward declarations
void ShowPowerLimits(zet_sysman_pwr_handle_t hPower);
void ShowEnergyThreshold(zet_sysman_pwr_handle_t hPower);

void ShowPowerDomains(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numPowerDomains;
    if (zetSysmanPowerGet(hSysmanDevice, &numPowerDomains, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_pwr_handle_t* phPower =
            (zet_sysman_pwr_handle_t*)malloc(numPowerDomains * sizeof(zet_sysman_pwr_handle_t));
        if (zetSysmanPowerGet(hSysmanDevice, &numPowerDomains, phPower) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t pwrIndex = 0; pwrIndex < numPowerDomains; pwrIndex++)
            {
                zet_power_properties_t props;
                if (zetSysmanPowerGetProperties(phPower[pwrIndex], &props) == ZE_RESULT_SUCCESS)
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

                ShowEnergyThreshold(phPower[pwrIndex]);
            }
        }
        free(phPower);
    }
}

void ShowPowerLimits(zet_sysman_pwr_handle_t hPower)
{
    zet_power_sustained_limit_t sustainedLimits;
    zet_power_burst_limit_t burstLimits;
    zet_power_peak_limit_t peakLimits;
    if (zetSysmanPowerGetLimits(hPower, &sustainedLimits, &burstLimits, &peakLimits) == ZE_RESULT_SUCCESS)
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
        fprintf(stdout, "        Peak AC:     %.3f\n", ((double)peakLimits.powerAC) / 1000);
        fprintf(stdout, "        Peak DC:     %.3f\n", ((double)peakLimits.powerDC) / 1000);
    }
}

void ShowEnergyThreshold(zet_sysman_pwr_handle_t hPower)
{
    zet_energy_threshold_t energyThreshold;
    if (zetSysmanPowerGetEnergyThreshold(hPower, &energyThreshold) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Energy Threshold: ");
        if (energyThreshold.enable)
        {
            fprintf(stdout, "Enabled, %0.3f Joules, Process ID %u\n", energyThreshold.threshold, energyThreshold.processId);
        }
        else
        {
            fprintf(stdout, "Disabled");
        }
        fprintf(stdout, "\n");
    }

}

void ShowDeviceInfo(zet_sysman_handle_t hSysmanDevice)
{
    zet_sysman_properties_t devProps;
    zet_sysman_state_t devState;
    if (zetSysmanDeviceGetProperties(hSysmanDevice, &devProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:           %s\n", devProps.core.uuid.id);
        fprintf(stdout, "    #subdevices:    %u\n", devProps.numSubdevices);
        fprintf(stdout, "    brand:          %s\n", devProps.brandName);
        fprintf(stdout, "    model:          %s\n", devProps.modelName);
        fprintf(stdout, "    driver timeout: disabled\n");
    }
    if (zetSysmanDeviceGetState(hSysmanDevice, &devState) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Was repaired:   %s\n", (devState.repaired == ZET_REPAIR_STATUS_PERFORMED) ? "yes" : "no");
        if (devState.reset != ZET_RESET_REASONS_NONE)
        {
            fprintf(stdout, "DEVICE RESET REQUIRED:\n");
            if (devState.reset & ZET_RESET_REASONS_WEDGED)
            {
                fprintf(stdout, "- Hardware is wedged\n");
            }
            if (devState.reset & ZET_RESET_REASONS_REPAIR)
            {
                fprintf(stdout, "- Hardware needs to complete repairs\n");
            }
        }
    }
}

void DisableSchedulerQueueWatchdog(zet_sysman_sched_handle_t hScheduler)
{
    ze_result_t res;
    zet_sched_mode_t currentMode;
    res = zetSysmanSchedulerGetCurrentMode(hScheduler, &currentMode);
    if (res == ZE_RESULT_SUCCESS)
    {
        ze_bool_t requireReboot;
        zet_sched_timeout_properties_t props;
        props.watchdogTimeout = ZET_SCHED_WATCHDOG_DISABLE;
        res = zetSysmanSchedulerSetTimeoutMode(hScheduler, &props, &requireReboot);
        if (res == ZE_RESULT_SUCCESS)
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
        else if(res == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE )
        {
            fprintf(stderr, "ERROR: The timeout scheduler mode is not supported on this device.\n");
        }
        else if(res == ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS )
        {
            fprintf(stderr, "ERROR: Don't have permissions to change the scheduler mode.\n");
        }
        else
        {
            fprintf(stderr, "ERROR: Problem calling the API to change the scheduler mode.\n");
        }
    }
    else if(res == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE )
    {
        fprintf(stderr, "ERROR: Scheduler modes are not supported on this device.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem calling the API.\n");
    }
}

void DisableSchedulerQueueWatchdog(zet_sysman_handle_t hSysmanDevice)
{
    uint32_t numSchedulerQueues;
    if (zetSysmanSchedulerGet(hSysmanDevice, &numSchedulerQueues, NULL) == ZE_RESULT_SUCCESS)
    {
        zet_sysman_sched_handle_t* phScheduler =
            (zet_sysman_sched_handle_t*)malloc(numSchedulerQueues * sizeof(zet_sysman_sched_handle_t));
        if (zetSysmanSchedulerGet(hSysmanDevice, &numSchedulerQueues, phScheduler) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numSchedulerQueues; index++)
            {
                DisableSchedulerQueueWatchdog(phScheduler[index]);
            }
        }
    }
}

void ShowPciInfo(zet_sysman_handle_t hSysmanDevice)
{
    zet_pci_properties_t pciProps;
    if (zetSysmanPciGetProperties(hSysmanDevice, &pciProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    PCI address:        %04u:%02u:%02u.%u\n", pciProps.address.domain, pciProps.address.bus, pciProps.address.device, pciProps.address.function);
    }
}

int gNumDevices = 0;    // Global

int ListDevice(ze_device_handle_t hDevice)
{
    int ret = 0;

    zet_sysman_handle_t hSysmanDevice;
    ze_result_t res = zetSysmanGet(hDevice, ZET_SYSMAN_VERSION_CURRENT, &hSysmanDevice);
    if (res == ZE_RESULT_SUCCESS)
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
    if ( (zeInit(ZE_INIT_FLAG_NONE) != ZE_RESULT_SUCCESS) ||
         (zetInit(ZE_INIT_FLAG_NONE) != ZE_RESULT_SUCCESS) )
    {
        fprintf(stderr, "Can't initialize the API.\n");
        ret = 1;
    }
    else
    {
        // Discover all the device groups and devices
        uint32_t driversCount = 0;
        zeDriverGet(&driversCount, nullptr);
        ze_driver_handle_t* allDrivers = (ze_driver_handle_t*)
            malloc(driversCount * sizeof(ze_driver_handle_t));
        zeDriverGet(&driversCount, allDrivers);

        // Find the first GPU device group
        ze_driver_handle_t hDriver = nullptr;
        for(uint32_t i = 0; i < driversCount; ++i)
        {
            uint32_t deviceCount = 0;
            zeDeviceGet(allDrivers[i], &deviceCount, nullptr);

            ze_device_handle_t* allDevices = (ze_device_handle_t*)
                malloc(deviceCount * sizeof(ze_device_handle_t));
            zeDeviceGet(allDrivers[i], &deviceCount, allDevices);

            for(uint32_t d = 0; d < deviceCount; ++d)
            {
                ze_device_properties_t device_properties;
                zeDeviceGetProperties(allDevices[d], &device_properties);
                if(ZE_DEVICE_TYPE_GPU == device_properties.type)
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
