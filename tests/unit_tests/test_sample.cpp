#include "cmdlist.h"
#include "cmdqueue.h"
#include "driver.h"
#include "device.h"
#include "event.h"
#include "memory.h"
#include "mock_module.h"
#include "gtest/gtest.h"

namespace xe {
namespace ult {

TEST(sample, waitOnEvent) {
    auto result = xe::xeDriverInit(XE_INIT_FLAG_NONE);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_device_handle_t device = {};
    result = xe::xeDriverGetDevice(0,
                                   &device);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_queue_handle_t hCommandQueue = {};
    xe_command_queue_desc_t desc = {};
    result = xe::xeDeviceCreateCommandQueue(device,
                                            &desc,
                                            &hCommandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_list_desc_t descCommandList = {};
    xe_command_list_handle_t hCommandList = {};
    result = xe::xeDeviceCreateCommandList(device,
                                           &descCommandList,
                                           &hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_event_desc_t descEvent = {};
    xe_event_handle_t hEvent = {};
    result = xe::xeDeviceCreateEvent(device,
                                     &descEvent,
                                     &hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xe::xeCommandListEncodeSignalEvent(hCommandList,
                                                hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xe::xeCommandListEncodeWaitOnEvent(hCommandList,
                                                hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xe::xeCommandListClose(hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_fence_handle_t hFence = {};
    result = xe::xeCommandQueueEnqueueCommandLists(hCommandQueue,
                                                   1,
                                                   &hCommandList,
                                                   (xe_fence_handle_t)0);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xe::xeEventDestroy(hEvent);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xe::xeCommandListDestroy(hCommandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueDestroy(hCommandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}

extern std::unique_ptr<char[]> readBinaryTestFile(const std::string &name, size_t &outSize);

TEST(sample, helloWorld) {
    UserRealCompilerGuard realCompilerGuard; // just for now

    auto result = xe::xeDriverInit(XE_INIT_FLAG_NONE);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_device_handle_t hDevice = {};
    result = xe::xeDriverGetDevice(0,
                                   &hDevice);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_queue_handle_t commandQueue = {};
    xe_command_queue_desc_t descCommandQueue = {};
    result = xe::xeDeviceCreateCommandQueue(hDevice,
                                            &descCommandQueue,
                                            &commandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_command_list_desc_t descCommandList = {};
    xe_command_list_handle_t commandList = {};
    result = xe::xeDeviceCreateCommandList(hDevice,
                                           &descCommandList,
                                           &commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    size_t moduleSize = 0u;
    auto inputModule = readBinaryTestFile("test_files/spv_modules/cstring_module.spv", moduleSize);
    ASSERT_NE(moduleSize, 0u);

    xe_module_desc_t descModule = {};
    xe_module_handle_t module = {};
    descModule.version = XE_API_HEADER_VERSION;
    descModule.pInputModule = inputModule.get();
    descModule.inputSize = static_cast<uint32_t>(moduleSize);
    descModule.format = XE_MODULE_FORMAT_IL_SPIRV;
    result = xe::xeDeviceCreateModule(hDevice,
                                      &descModule,
                                      &module,
                                      nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_function_desc_t descFunction = {};
    xe_function_handle_t function = {};
    descFunction.version = XE_API_HEADER_VERSION;
    descFunction.flags = XE_FUNCTION_FLAG_NONE;
    descFunction.pFunctionName = "memcpy_bytes";
    result = xe::xeModuleCreateFunction(module,
                                        &descFunction,
                                        &function);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_function_args_handle_t functionArgs = {};
    result = ::xe::xeFunctionCreateFunctionArgs(function,
                                                &functionArgs);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_mem_allocator_handle_t hMemAllocHandle = {};
    xe_device_mem_alloc_flag_t deviceFlags = {};
    xe_host_mem_alloc_flag_t hostFlags = {};
    size_t bufferSize = 4096u;
    void *dest = nullptr;
    result = ::xe::xeSharedMemAlloc(hMemAllocHandle,
                                    hDevice,
                                    deviceFlags,
                                    hostFlags,
                                    bufferSize,
                                    4096u,
                                    &dest);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = ::xe::xeFunctionArgsSetValue(functionArgs, 0, sizeof(dest), &dest);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    void *src = nullptr;
    result = ::xe::xeSharedMemAlloc(hMemAllocHandle,
                                    hDevice,
                                    deviceFlags,
                                    hostFlags,
                                    bufferSize,
                                    4096u,
                                    &src);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
    memset(reinterpret_cast<void *>(src), 0xbf, bufferSize);

    result = ::xe::xeFunctionArgsSetValue(functionArgs, 1, sizeof(src), &src);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    xe_dispatch_function_arguments_t dispatchFunctionArgs = {};
    dispatchFunctionArgs.version = XE_DISPATCH_FUNCTION_ARGS_VERSION;
    dispatchFunctionArgs.groupCountX = 2;
    dispatchFunctionArgs.groupCountY = 1;
    dispatchFunctionArgs.groupCountZ = 1;
    dispatchFunctionArgs.groupSizeX = 32;
    dispatchFunctionArgs.groupSizeX = 1;
    dispatchFunctionArgs.groupSizeX = 1;
    result = xe::xeCommandListEncodeDispatchFunction(commandList,
                                                     function,
                                                     functionArgs,
                                                     &dispatchFunctionArgs,
                                                     nullptr);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xe::xeCommandListClose(commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xe::xeCommandQueueEnqueueCommandLists(commandQueue,
                                                   1,
                                                   &commandList,
                                                   (xe_fence_handle_t)0);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeMemFree(hMemAllocHandle, src);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeMemFree(hMemAllocHandle, dest);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xe::xeCommandListDestroy(commandList);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    result = xeCommandQueueDestroy(commandQueue);
    ASSERT_EQ(XE_RESULT_SUCCESS, result);
}

} // namespace ult
} // namespace xe
