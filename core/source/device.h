#pragma once
#include "xe_cmdgraph.h"
#include "xe_cmdlist.h"
#include "xe_cmdqueue.h"
#include "xe_device.h"
#include "xe_event.h"
#include "xe_image.h"
#include "xe_module.h"
#include "xe_semaphore.h"
#include "driver.h"

struct _xe_device_handle_t {
};

namespace xe {
struct MemoryManager;

struct Device : _xe_device_handle_t {
    virtual xe_result_t canAccessPeer(xe_device_handle_t hPeerDevice,
                                      bool *value) = 0;
    virtual xe_result_t copyCommandList(xe_command_list_handle_t hCommandList,
                                        xe_command_list_handle_t *phCommandList) = 0;

    virtual xe_result_t createCommandGraph(const xe_command_graph_desc_t *desc,
                                           xe_command_graph_handle_t *phCommandGraph) = 0;

    virtual xe_result_t createCommandList(const xe_command_list_desc_t *desc,
                                          xe_command_list_handle_t *commandList) = 0;

    virtual xe_result_t createCommandQueue(const xe_command_queue_desc_t *desc,
                                           xe_command_queue_handle_t *commandQueue) = 0;

    virtual xe_result_t createEvent(const xe_event_desc_t *desc,
                                    xe_event_handle_t *event) = 0;
    virtual xe_result_t createImage(const xe_image_desc_t *desc,
                                    xe_image_handle_t *phImage) = 0;

    virtual xe_result_t createModule(const xe_module_desc_t *desc,
                                     xe_module_handle_t *module,
                                     xe_module_build_log_handle_t *buildLog) = 0;
    virtual xe_result_t createSemaphore(const xe_semaphore_desc_t *desc,
                                        xe_semaphore_handle_t *phSemaphore) = 0;
    virtual xe_result_t evictImage(xe_image_handle_t hImage) = 0;
    virtual xe_result_t evictMemory(void *ptr,
                                    size_t size) = 0;
    virtual xe_result_t getApiVersion(xe_api_version_t *version) = 0;
    virtual xe_result_t getComputeProperties(xe_device_compute_properties_t *pComputeProperties) = 0;
    virtual xe_result_t getMemoryProperties(xe_device_memory_properties_t *pMemProperties) = 0;
    virtual xe_result_t getProperties(xe_device_properties_t *pDeviceProperties) = 0;
    virtual xe_result_t getSubDevice(uint32_t ordinal,
                                     xe_device_handle_t *phSubDevice) = 0;
    virtual xe_result_t makeImageResident(xe_image_handle_t hImage) = 0;
    virtual xe_result_t makeMemoryResident(void *ptr,
                                           size_t size
                                           ) = 0;
    virtual xe_result_t placeEvent(const xe_event_desc_t *desc,
                                   void *ptr,
                                   xe_event_handle_t *phEvent) = 0;
    virtual xe_result_t setIntermediateCacheConfig(xe_cache_config_t CacheConfig) = 0;
    virtual xe_result_t setLastLevelCacheConfig(xe_cache_config_t CacheConfig) = 0;

    virtual MemoryManager *getMemoryManager() = 0;

    static Device *fromHandle(xe_device_handle_t handle) {
        return static_cast<Device *>(handle);
    }

    inline xe_device_handle_t toHandle() {
        return this;
    }

    static Device *create(void *device);
};

} // namespace xe
