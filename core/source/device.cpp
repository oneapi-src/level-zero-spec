#include "cmdlist.h"
#include "cmdqueue.h"
#include "device.h"
#include "event.h"
#include "memory_manager.h"
#include "module.h"
#include "image.h"
#include "runtime/device/device.h"
#include "runtime/helpers/hw_helper.h"
#include "runtime/helpers/string.h"
#include "runtime/os_interface/debug_settings_manager.h"

namespace L0 {

struct DeviceImp : public Device {
    xe_result_t canAccessPeer(xe_device_handle_t hPeerDevice,
                              bool *value) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t copyCommandList(xe_command_list_handle_t hCommandList,
                                xe_command_list_handle_t *phCommandList) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t createCommandGraph(const xe_command_graph_desc_t *desc,
                                   xe_command_graph_handle_t *phCommandGraph) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                  xe_command_list_handle_t *commandList) override {
        auto productFamily = deviceRT->getHardwareInfo().pPlatform->eProductFamily;
        *commandList = CommandList::create(productFamily, this);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                   xe_command_queue_handle_t *commandQueue) override {
        auto productFamily = deviceRT->getHardwareInfo().pPlatform->eProductFamily;

        auto executionEnvironment = deviceRT->getExecutionEnvironment();
        auto csrRT = executionEnvironment->commandStreamReceivers[0][0].get();

        *commandQueue = CommandQueue::create(productFamily, this, csrRT);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createEvent(const xe_event_desc_t *desc,
                            xe_event_handle_t *event) override {
        *event = Event::create(this);
        return XE_RESULT_SUCCESS;
    }

    xe_result_t createImage(const xe_image_desc_t *desc,
                            xe_image_handle_t *phImage) override {
        auto productFamily = deviceRT->getHardwareInfo().pPlatform->eProductFamily;
        *phImage = Image::create(productFamily, this, desc);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createModule(const xe_module_desc_t *desc,
                             xe_module_handle_t *module,
                             xe_module_build_log_handle_t *buildLog) override {
        ModuleBuildLog *moduleBuildLog = nullptr;

        if (buildLog) {
            moduleBuildLog = ModuleBuildLog::create();
            *buildLog = moduleBuildLog->toHandle();
        }
        *module = Module::create(this, desc, deviceRT, moduleBuildLog);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t createSemaphore(const xe_semaphore_desc_t *desc,
                                xe_semaphore_handle_t *phSemaphore) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t evictImage(xe_image_handle_t hImage) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t evictMemory(void *ptr,
                            size_t size) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getApiVersion(xe_api_version_t *version) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getComputeProperties(xe_device_compute_properties_t *pComputeProperties) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getMemoryProperties(xe_device_memory_properties_t *pMemProperties) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getProperties(xe_device_properties_t *pDeviceProperties) override {
        assert(pDeviceProperties != nullptr);
        assert(pDeviceProperties->version == XE_DEVICE_PROPERTIES_VERSION);
        const auto &deviceInfo = this->deviceRT->getDeviceInfo();
        const auto &hardwareInfo = this->deviceRT->getHardwareInfo();
        auto &hwHelper = OCLRT::HwHelper::get(hardwareInfo.pPlatform->eRenderCoreFamily);
        auto enableLocalMemory = hwHelper.getEnableLocalMemory(hardwareInfo);

        memcpy_s(pDeviceProperties->device_name, sizeof(pDeviceProperties->device_name),
                 deviceInfo.name, strlen(deviceInfo.name) + 1);
        pDeviceProperties->coreClockRate = deviceInfo.maxClockFrequency;
        pDeviceProperties->vendorId = deviceInfo.vendorId;
        //pDeviceProperties->deviceId;                              ///< [out] device id from PCI configuration
        pDeviceProperties->subdeviceId = isSubdevice ? this->deviceRT->getDeviceIndex() : 0;
        pDeviceProperties->isSubdevice = isSubdevice;
        pDeviceProperties->numSubDevices = isSubdevice ? 0 : deviceInfo.partitionMaxSubDevices;
        pDeviceProperties->coreClockRate = deviceInfo.maxClockFrequency;
        //pDeviceProperties->memClockRate;                          ///< [out] Clock rate for device global memory
        //pDeviceProperties->memGlobalBusWidth;                     ///< [out] Bus width between core and memory.
        pDeviceProperties->totalLocalMemSize = enableLocalMemory ? OCLRT::DebugManager.flags.HBMSizePerTileInGigabytes.get() * MemoryConstants::gigaByte : 0;
        pDeviceProperties->numAsyncComputeEngines = static_cast<uint32_t>(hwHelper.getGpgpuEngineInstances().size());
        pDeviceProperties->numAsyncCopyEngines = 1; //  hwHelper.getCopyEngineInstances().size(); // NEO refactor
        pDeviceProperties->numComputeCores = deviceInfo.maxComputUnits;
        pDeviceProperties->maxCommandQueuePriority = 0; // map to cl_khr_priority_hints ?
        return XE_RESULT_SUCCESS;
    }

    xe_result_t getSubDevice(uint32_t ordinal,
                             xe_device_handle_t *phSubDevice) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t makeImageResident(xe_image_handle_t hImage) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t makeMemoryResident(void *ptr,
                                   size_t size) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t placeEvent(const xe_event_desc_t *desc,
                           void *ptr,
                           xe_event_handle_t *phEvent) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t setIntermediateCacheConfig(xe_cache_config_t CacheConfig) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t setLastLevelCacheConfig(xe_cache_config_t CacheConfig) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    MemoryManager *getMemoryManager() override {
        return memoryManager;
    }

    OCLRT::Device *deviceRT = nullptr;
    MemoryManager *memoryManager = nullptr;
    bool isSubdevice = false;
};

Device *Device::create(void *ptr) {
    auto device = new DeviceImp;

    auto deviceRT = static_cast<OCLRT::Device *>(ptr);
    device->deviceRT = deviceRT;
    device->memoryManager = MemoryManager::create(deviceRT->getMemoryManager());

    return device;
}

xe_result_t deviceGetLinkProperties(uint32_t srcOrdinal,
                                    uint32_t dstOrdinal,
                                    xe_device_link_properties_t *pLinkProperties) {
    return XE_RESULT_ERROR_UNSUPPORTED;
}

} // namespace L0
