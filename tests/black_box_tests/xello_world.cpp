#include "icd_loader/icd_loader.h"

#include "xe_all.h"

#if defined(__linux__)
#include <dlfcn.h>
#define LOAD_DRIVER_LIBRARY() dlopen("liblevel_zero.so", RTLD_LAZY | RTLD_LOCAL)
#define CLOSE_LIBRARY(LIB) dlclose(LIB)
#define LOAD_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#elif defined(_WIN32)
#include <Windows.h>
#define LOAD_DRIVER_LIBRARY() LoadLibraryA("level_zero.dll")
#define CLOSE_LIBRARY(LIB) FreeLibrary(LIB)
#define LOAD_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress((HMODULE)LIB, FUNC_NAME)
#else
#error "Unsupported OS"
#endif

#include <iostream>
#include <fstream>
#include <memory>

template <typename SizeT>
inline std::unique_ptr<char[]> readBinaryFile(const std::string &name, SizeT &outSize) {
    std::ifstream file(name, std::ios_base::binary);
    if (false == file.good()) {
        outSize = 0;
        return nullptr;
    }

    size_t length;
    file.seekg(0, file.end);
    length = static_cast<size_t>(file.tellg());
    file.seekg(0, file.beg);

    auto storage = std::make_unique<char[]>(length);
    file.read(storage.get(), length);

    outSize = static_cast<SizeT>(length);
    return storage;
}

template <typename ResulT>
inline void successOrTerminate(ResulT result, const char *message) {
    if (result == 0) { // assumption 0 is success
        return;
    }

    std::cerr << message;
    std::terminate();
}

#define SUCCESS_OR_TERMINATE(CALL) successOrTerminate(CALL, #CALL)
#define SUCCESS_OR_TERMINATE_BOOL(FLAG) successOrTerminate(!(FLAG), #FLAG)

int main() {
    // 0. Load the driver
    auto driverLibrary = LOAD_DRIVER_LIBRARY();
    if (NULL == driverLibrary) {
        std::cerr << "Failed to load driver library\n";
        return 1;
    }
    xe_dispatch_table_t xeApi = {};
    load_xe(
        driverLibrary,
        [](void *library, const char *funcName) -> void * { return LOAD_FUNCTION_PTR(library, funcName); },
        &xeApi);

    // 1. Set-up
    constexpr size_t allocSize = 4096;
    xe_device_handle_t device0;
    xe_module_handle_t module;
    xe_function_handle_t function;
    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;
    xe_mem_allocator_handle_t allocator;
    void *srcBuffer = nullptr;
    void *dstBuffer = nullptr;

    SUCCESS_OR_TERMINATE(xeApi.xeDriverInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeApi.xeDriverGetDevice(0, &device0));
    {
        uint32_t spirvSize = 0;
        auto spirvModule = readBinaryFile("test_files/spv_modules/cstring_module.spv", spirvSize);
        SUCCESS_OR_TERMINATE_BOOL(spirvSize != 0);

        xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION};
        moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
        moduleDesc.pInputModule = spirvModule.get();
        moduleDesc.inputSize = spirvSize;
        SUCCESS_OR_TERMINATE(xeApi.xeDeviceCreateModule(device0, &moduleDesc, &module, nullptr));
    }

    {
        xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION};
        functionDesc.pFunctionName = "memcpy_bytes";
        SUCCESS_OR_TERMINATE(xeApi.xeModuleCreateFunction(module, &functionDesc, &function));
    }

    uint32_t groupSizeX = 32u;
    uint32_t groupSizeY = 1u;
    uint32_t groupSizeZ = 1u;
    SUCCESS_OR_TERMINATE(xeApi.xeFunctionSetGroupSize(function, groupSizeX, groupSizeY, groupSizeZ));

    {
        xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION};
        cmdQueueDesc.ordinal = 0;
        cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
        SUCCESS_OR_TERMINATE(xeApi.xeDeviceCreateCommandQueue(device0, &cmdQueueDesc, &cmdQueue));
    }

    {
        xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION};
        SUCCESS_OR_TERMINATE(xeApi.xeDeviceCreateCommandList(device0, &cmdListDesc, &cmdList));
    }

    SUCCESS_OR_TERMINATE(xeApi.xeCreateMemAllocator(&allocator));
#if UNSUPPORTED
    SUCCESS_OR_TERMINATE(xeApi.xeMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &srcBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBuffer));
#else
    SUCCESS_OR_TERMINATE(xeApi.xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &srcBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBuffer));
#endif

// 2. Encode initialize memory
#if UNSUPPORTED
    uint8_t initData[allocSize];
    memset(initData, 7, sizeof(initData));
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeMemoryCopy(cmdList, srcBuffer, initData, sizeof(initData)));
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeExecutionBarrier(cmdList)); // copying of data must finish before running the user function
#else
    memset(srcBuffer, 7u, allocSize);
    memset(dstBuffer, 2u, allocSize);
#endif

    // 3. Encode run user function
    SUCCESS_OR_TERMINATE(xeApi.xeFunctionSetArgumentValue(function, 0, sizeof(dstBuffer), &dstBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeFunctionSetArgumentValue(function, 1, sizeof(srcBuffer), &srcBuffer));
    {
        xe_dispatch_function_arguments_t dispatchTraits{XE_DISPATCH_FUNCTION_ARGS_VERSION};
        dispatchTraits.groupCountX = allocSize / groupSizeX;
        dispatchTraits.groupCountY = 1;
        dispatchTraits.groupCountZ = 1;
        SUCCESS_OR_TERMINATE_BOOL(dispatchTraits.groupCountX * groupSizeX == allocSize);
        SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeDispatchFunction(cmdList, function, &dispatchTraits, nullptr));
    }

// 4. Encode read back memory
#if UNSUPPORTED
    uint8_t readBackData[allocSize];
    memset(readBackData, 2, sizeof(readBackData));
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeExecutionBarrier(cmdList)); // user function must finish before we start copying data
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListEncodeMemoryCopy(cmdList, readBackData, dstBuffer, sizeof(readBackData)));
#endif

    // 5. Dispatch and wait
    SUCCESS_OR_TERMINATE(xeApi.xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeApi.xeCommandQueueEnqueueCommandLists(cmdQueue, 1, &cmdList, nullptr));
#if UNSUPPORTED
    SUCCESS_OR_TERMINATE(xeApi.xeCommandQueueSynchronize(cmdQueue, XE_SYNCHRONIZATION_MODE_POLL, 0, 0, -1));
#endif

    // 6. Validate
#if UNSUPPORTED
    SUCCESS_OR_TERMINATE(0 == memcmp(srcBuffer, dstBuffer, allocSize));
#endif

    // X. Cleanup
    SUCCESS_OR_TERMINATE(xeApi.xeMemFree(allocator, dstBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeMemFree(allocator, srcBuffer));
    SUCCESS_OR_TERMINATE(xeApi.xeMemAllocatorDestroy(allocator));

    SUCCESS_OR_TERMINATE(xeApi.xeCommandListDestroy(cmdList));

    SUCCESS_OR_TERMINATE(xeApi.xeCommandQueueDestroy(cmdQueue));

    SUCCESS_OR_TERMINATE(xeApi.xeFunctionDestroy(function));
    SUCCESS_OR_TERMINATE(xeApi.xeModuleDestroy(module));

    CLOSE_LIBRARY(driverLibrary);
}
