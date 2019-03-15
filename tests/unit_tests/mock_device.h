#pragma once
#include "device.h"
#include "mock.h"
#include "white_box.h"

namespace L0 {
namespace ult {

template <>
struct WhiteBox<::L0::Device> : public ::L0::Device {
};

using Device = WhiteBox<::L0::Device>;

template <>
struct Mock<Device> : public Device {
    Mock();
    virtual ~Mock();

    MOCK_METHOD2(canAccessPeer, xe_result_t(xe_device_handle_t hPeerDevice,
                                            bool *value));
    MOCK_METHOD2(copyCommandList, xe_result_t(xe_command_list_handle_t hCommandList,
                                              xe_command_list_handle_t *phCommandList));

    MOCK_METHOD2(createCommandGraph, xe_result_t(const xe_command_graph_desc_t *desc,
                                                 xe_command_graph_handle_t *phCommandGraph));

    MOCK_METHOD2(createCommandList, xe_result_t(const xe_command_list_desc_t *desc,
                                                xe_command_list_handle_t *commandList));

    MOCK_METHOD2(createCommandQueue, xe_result_t(const xe_command_queue_desc_t *desc,
                                                 xe_command_queue_handle_t *commandQueue));

    MOCK_METHOD2(createEvent, xe_result_t(const xe_event_desc_t *desc,
                                          xe_event_handle_t *event));
    MOCK_METHOD2(createImage, xe_result_t(const xe_image_desc_t *desc,
                                          xe_image_handle_t *phImage));

    MOCK_METHOD3(createModule, xe_result_t(const xe_module_desc_t *desc,
                                           xe_module_handle_t *module,
                                           xe_module_build_log_handle_t *buildLog));
    MOCK_METHOD2(createSampler, xe_result_t(const xe_sampler_desc_t *pDesc,
                                            xe_sampler_handle_t *phSampler));
    MOCK_METHOD2(createSemaphore, xe_result_t(const xe_semaphore_desc_t *desc,
                                              xe_semaphore_handle_t *phSemaphore));
    MOCK_METHOD1(evictImage, xe_result_t(xe_image_handle_t hImage));
    MOCK_METHOD2(evictMemory, xe_result_t(void *ptr,
                                          size_t size));
    MOCK_METHOD1(getApiVersion, xe_result_t(xe_api_version_t *version));
    MOCK_METHOD1(getComputeProperties, xe_result_t(xe_device_compute_properties_t *pComputeProperties));
    MOCK_METHOD1(getMemoryProperties, xe_result_t(xe_device_memory_properties_t *pMemProperties));
    MOCK_METHOD1(getProperties, xe_result_t(xe_device_properties_t *pDeviceProperties));
    MOCK_METHOD2(getSubDevice, xe_result_t(uint32_t ordinal,
                                           xe_device_handle_t *phSubDevice));
    MOCK_METHOD1(makeImageResident, xe_result_t(xe_image_handle_t hImage));
    MOCK_METHOD2(makeMemoryResident, xe_result_t(void *ptr,
                                                 size_t size));
    MOCK_METHOD3(placeEvent, xe_result_t(const xe_event_desc_t *desc,
                                         void *ptr,
                                         xe_event_handle_t *phEvent));
    MOCK_METHOD1(setIntermediateCacheConfig, xe_result_t(xe_cache_config_t CacheConfig));
    MOCK_METHOD1(setLastLevelCacheConfig, xe_result_t(xe_cache_config_t CacheConfig));

    // Runtime internal methods
    MOCK_METHOD0(getMemoryManager, MemoryManager *());

    void *deviceRT;
    void *csrRT;
};

} // namespace ult
} // namespace L0
