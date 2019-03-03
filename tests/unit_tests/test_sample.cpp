#include "xe_driver.h"
#include "xe_device.h"
#include "xe_cmdlist.h"
#include "xe_cmdqueue.h"
#include "xe_event.h"
#include "xe_memory.h"
#include "xe_module.h"
#include "mock_compiler.h"
#include "mock_module.h"
#include "gtest/gtest.h"

namespace L0 {
namespace ult {

TEST(sample, waitOnEvent) {
    auto result = xeDriverInit(XE_INIT_FLAG_NONE);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_device_handle_t device = {};
    result = xeDriverGetDevice(0,
                               &device);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_queue_handle_t hCommandQueue = {};
    xe_command_queue_desc_t desc = {};
    result = xeDeviceCreateCommandQueue(device,
                                        &desc,
                                        &hCommandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_list_desc_t descCommandList = {};
    xe_command_list_handle_t hCommandList = {};
    result = xeDeviceCreateCommandList(device,
                                       &descCommandList,
                                       &hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_event_desc_t descEvent = {};
    xe_event_handle_t hEvent = {};
    result = xeDeviceCreateEvent(device,
                                 &descEvent,
                                 &hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListEncodeSignalEvent(hCommandList,
                                            hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListEncodeWaitOnEvent(hCommandList,
                                            hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListClose(hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_fence_handle_t hFence = {};
    result = xeCommandQueueEnqueueCommandLists(hCommandQueue,
                                               1,
                                               &hCommandList,
                                               (xe_fence_handle_t)0);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeEventDestroy(hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListDestroy(hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueDestroy(hCommandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}

extern std::unique_ptr<char[]> readBinaryTestFile(const std::string &name, size_t &outSize);

TEST(sample, helloWorld) {
    UserRealCompilerGuard realCompilerGuard; // just for now

    auto result = xeDriverInit(XE_INIT_FLAG_NONE);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_device_handle_t hDevice = {};
    result = xeDriverGetDevice(0,
                               &hDevice);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t descCommandQueue = {};
    result = xeDeviceCreateCommandQueue(hDevice,
                                        &descCommandQueue,
                                        &commandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_list_desc_t descCommandList = {};
    xe_command_list_handle_t commandList = {};
    result = xeDeviceCreateCommandList(hDevice,
                                       &descCommandList,
                                       &commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    size_t moduleSize = 0u;
    auto inputModule = readBinaryTestFile("test_files/spv_modules/cstring_module.spv", moduleSize);
    ASSERT_NE(moduleSize, 0u);

    xe_module_desc_t descModule = {};
    xe_module_handle_t module = {};
    descModule.version = XE_MODULE_DESC_VERSION;
    descModule.pInputModule = inputModule.get();
    descModule.inputSize = static_cast<uint32_t>(moduleSize);
    descModule.format = XE_MODULE_FORMAT_IL_SPIRV;
    result = xeDeviceCreateModule(hDevice,
                                  &descModule,
                                  &module,
                                  nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_function_desc_t descFunction = {};
    xe_function_handle_t function = {};
    descFunction.version = XE_API_HEADER_VERSION;
    descFunction.flags = XE_FUNCTION_FLAG_NONE;
    descFunction.pFunctionName = "memcpy_bytes";
    result = xeModuleCreateFunction(module,
                                    &descFunction,
                                    &function);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    uint32_t groupSizeX = 32u;
    uint32_t groupSizeY = 1u;
    uint32_t groupSizeZ = 1u;
    result = xeFunctionSetGroupSize(function,
                                    groupSizeX,
                                    groupSizeY,
                                    groupSizeZ);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_mem_allocator_handle_t hMemAllocHandle = {};
    result = xeCreateMemAllocator(&hMemAllocHandle);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_device_mem_alloc_flag_t deviceFlags = {};
    xe_host_mem_alloc_flag_t hostFlags = {};
    size_t bufferSize = 4096u;
    void *dest = nullptr;
    result = xeSharedMemAlloc(hMemAllocHandle,
                              hDevice,
                              deviceFlags,
                              hostFlags,
                              bufferSize,
                              4096u,
                              &dest);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeFunctionSetArgumentValue(function, 0, sizeof(dest), &dest);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    void *src = nullptr;
    result = xeSharedMemAlloc(hMemAllocHandle,
                              hDevice,
                              deviceFlags,
                              hostFlags,
                              bufferSize,
                              4096u,
                              &src);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
    memset(reinterpret_cast<void *>(src), 0xbf, bufferSize);

    result = xeFunctionSetArgumentValue(function, 1, sizeof(src), &src);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_dispatch_function_arguments_t dispatchFunctionArgs = {};
    dispatchFunctionArgs.version = XE_DISPATCH_FUNCTION_ARGS_VERSION;
    dispatchFunctionArgs.groupCountX = 2;
    dispatchFunctionArgs.groupCountY = 1;
    dispatchFunctionArgs.groupCountZ = 1;
    result = xeCommandListEncodeDispatchFunction(commandList,
                                                 function,
                                                 &dispatchFunctionArgs,
                                                 nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListClose(commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueEnqueueCommandLists(commandQueue,
                                               1,
                                               &commandList,
                                               (xe_fence_handle_t)0);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeMemFree(hMemAllocHandle, src);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeMemFree(hMemAllocHandle, dest);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeMemAllocatorDestroy(hMemAllocHandle);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandListDestroy(commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueDestroy(commandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}

} // namespace ult
} // namespace L0
